#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace std::chrono;

namespace LibraryDesktopTest
{

	TEST_CLASS(EventTests)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
#ifdef _DEBUG
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
#endif
		}

		TEST_METHOD(EventSubscriberTest)
		{
			FooMessage foo;
			FooSubscriber sub1, sub2;
			Event<FooMessage> e(foo);

			e.Subscribe(sub1);
			e.Subscribe(sub2);

			Assert::AreEqual(0, sub1.fooInt);
			Assert::AreEqual(0, sub2.fooInt);

			e.Deliver();

			Assert::AreEqual(1, sub1.fooInt);
			Assert::AreEqual(1, sub2.fooInt);

			e.unSubscribe(sub1);

			e.Deliver();

			Assert::AreEqual(1, sub1.fooInt);
			Assert::AreEqual(2, sub2.fooInt);
		}

		TEST_METHOD(EventPublisherTest)
		{
			std::chrono::steady_clock clock; clock;
			std::chrono::milliseconds delay = std::chrono::duration<int>(1);
			std::chrono::high_resolution_clock::time_point timePoint = clock.now();

			GameTime timer;
			
			FooMessage foo;
			FooSubscriber sub1, sub2;
			Event<FooMessage> e(foo);

			e.Subscribe(sub1);
			e.Subscribe(sub2);

			timer.SetCurrentTime(timePoint);

			e.SetTime(timer.CurrentTime());

			Assert::IsTrue(e.TimeEnqueued() == timer.CurrentTime());
			Assert::IsTrue(e.Delay() == std::chrono::duration<int>(0));

			e.SetTime(timer.CurrentTime(), &delay);
			Assert::IsTrue(e.TimeEnqueued() == timer.CurrentTime());
			Assert::IsTrue(e.Delay() == delay);

			Assert::IsTrue(e.isExpired(timer.CurrentTime()) == false);

			timer.SetCurrentTime(timePoint += delay);
			Assert::IsTrue(e.isExpired(timer.CurrentTime()) == true);

		}

		TEST_METHOD(EventTest)
		{
			FooMessage foo, foo2; foo2;
			FooSubscriber sub1, sub2;
			Event<FooMessage> e(foo);

			// Methods Tests
			Assert::AreEqual(0U, Event<FooMessage>::mSubscribers.Size());
			e.Subscribe(sub1);
			Assert::AreEqual(1U, Event<FooMessage>::mSubscribers.Size());
			e.Subscribe(sub2);
			Assert::AreEqual(2U, Event<FooMessage>::mSubscribers.Size());

			e.unSubscribe(sub1);
			Assert::AreEqual(1U, Event<FooMessage>::mSubscribers.Size());

			e.Subscribe(sub1);
			e.UnSubscribeAll();
			Assert::AreEqual(0U, Event<FooMessage>::mSubscribers.Size());

			e.Subscribe(sub1);
			e.Subscribe(sub2);

			Assert::IsTrue(e.Message() == &foo);

			// Copy, Move, Equality Tests
			Event<FooMessage> eCopy(e), eCopy2(foo2);
			
			Assert::IsTrue(e == eCopy);
			Assert::IsTrue(e != eCopy2);
			eCopy2 = e;
			Assert::IsTrue(e == eCopy2);

			Assert::IsTrue(eCopy.Message() == &foo);
			Assert::IsTrue(eCopy2.Message() == &foo);

			Event<FooMessage> eMove(std::move(eCopy)), eMove2(foo2);
			eMove2 = std::move(eCopy2);

			Assert::IsTrue(eCopy.Message() == nullptr);
			Assert::IsTrue(eCopy2.Message() == nullptr);

			Assert::IsTrue(eMove.Message() == &foo);
			Assert::IsTrue(eMove2.Message() == &foo);

			Assert::AreEqual(2U, Event<FooMessage>::mSubscribers.Size());
		}

		TEST_METHOD(EventQueueTest)
		{
			std::chrono::steady_clock clock; clock;
			std::chrono::milliseconds delay = std::chrono::duration<int>(5),
									  delay2 = std::chrono::duration<int>(1),
									  delay3 = std::chrono::duration<int>(20);
			std::chrono::high_resolution_clock::time_point timePoint = clock.now();

			GameTime timer;
			FooMessage foo;
			FooSubscriber sub1, sub2;
			Event<FooMessage>* event1 = new Event<FooMessage>(foo);
			Event<FooMessage>* event2 = new Event<FooMessage>(foo);
			Event<FooMessage>* event3 = new Event<FooMessage>(foo);

			timer.SetCurrentTime(timePoint);

			Event<FooMessage>::Subscribe(sub1);
			Event<FooMessage>::Subscribe(sub2);

			EventQueue q;

			Assert::AreEqual(true, q.isEmpty());
			q.Enqueue(*event1, timer, &delay);
			q.Enqueue(*event2, timer);
			q.Enqueue(*event3, timer, &delay3);
			Assert::AreEqual(true, !q.isEmpty());
			Assert::AreEqual(3U, q.Size());

			timer.SetCurrentTime(timePoint += delay2);
			q.Update(timer);
			Assert::AreEqual(2U, q.Size());

			Assert::AreEqual(1, sub1.fooInt);
			Assert::AreEqual(1, sub2.fooInt);

			timer.SetCurrentTime(timePoint += delay3);
			q.Clear();
			Assert::AreEqual(0U, q.Size());

		}

		TEST_METHOD(AsynchTest)
		{
			std::chrono::steady_clock clock; clock;
			std::chrono::milliseconds delay = std::chrono::duration<int>(5),
				delay2 = std::chrono::duration<int>(1),
				delay3 = std::chrono::duration<int>(20);
			std::chrono::high_resolution_clock::time_point timePoint = clock.now();

			EventQueue q;

			GameTime timer;
			FooMessage foo;
			FooSubscriber sub1, sub2;
			FooSubscriberEnqueue subEnqueue(q);
			FooSubscriberClearQ subClear(q);
			Event<FooMessage>* event1 = new Event<FooMessage>(foo);
			Event<FooMessage>* event2 = new Event<FooMessage>(foo);
			Event<FooMessage>* event3 = new Event<FooMessage>(foo);
			Event<FooMessage>* event4 = new Event<FooMessage>(foo);

			// Initialize
			{
				timer.SetCurrentTime(timePoint);

				Event<FooMessage>::Subscribe(sub1);
				Event<FooMessage>::Subscribe(sub2);

				q.Enqueue(*event1, timer, &delay3);
				q.Enqueue(*event2, timer);
				q.Enqueue(*event3, timer, &delay3);
				q.Enqueue(*event4, timer, &delay3);
			}

			// Subscriber That Enqueues Event
			{
				Event<FooMessage>::Subscribe(subEnqueue);
				timer.SetCurrentTime(timePoint += delay2);
				q.Update(timer);
				Assert::AreEqual(4U, q.Size());

				Assert::AreEqual(1, sub1.fooInt);
				Assert::AreEqual(1, sub2.fooInt);
			}

			// Subscriber That Clears EventQueue
			{
				Event<FooMessage>::Subscribe(subClear);
				timer.SetCurrentTime(timePoint += delay3);
				q.Update(timer);
				Assert::AreEqual(0U, q.Size());
			}

			// Subscriber That Throws Exception
			{
				FooSubscriberException subException;
				Event<FooMessage>* exceptionEvent = new Event<FooMessage>(foo);

				Event<FooMessage>::Subscribe(subException);
				q.Enqueue(*exceptionEvent, timer);

				timer.SetCurrentTime(timePoint += delay3);

				auto expression = [&q, &timer] { q.Update(timer); };
				Assert::ExpectException<std::exception>(expression);
			}

			// Subscriber That Clears Subscribers
			{
				FooSubscriberUnsub subUnsub;
				Event<FooMessage>* UnsubEvent = new Event<FooMessage>(foo);

				Event<FooMessage>::Subscribe(subUnsub);
				q.Enqueue(*UnsubEvent, timer);

				timer.SetCurrentTime(timePoint += delay3);
				q.Update(timer);
			}

			// Subscriber That Adds Subscribers
			{
				FooSubscriberSub subSub;
				Event<FooMessage>* subEvent = new Event<FooMessage>(foo);

				Event<FooMessage>::Subscribe(subSub);
				q.Enqueue(*subEvent, timer);

				timer.SetCurrentTime(timePoint += delay3);
				q.Update(timer);
			}

		}

		TEST_METHOD(AsynchMultiEventsTest)
		{
			std::chrono::steady_clock clock; clock;
			std::chrono::milliseconds delay = std::chrono::duration<int>(1), 
								timeIncrement = std::chrono::duration<int>(1);
			std::chrono::high_resolution_clock::time_point timePoint = clock.now();
			int numEvents = 10000;
			delay /= 10;
			timeIncrement /= 100;

			EventQueue q;

			GameTime timer;
			FooMessage foo;
			FooSubscriber sub1, sub2;
			FooSubscriberEnqueue subEnqueue(q);
			FooSubscriberClearQ subClear(q);

			timer.SetCurrentTime(timePoint);
			Event<FooMessage>::Subscribe(sub1);
			Event<FooMessage>::Subscribe(sub2);

			for (int i = 0; i < numEvents; ++i)
			{
				q.Enqueue(*new Event<FooMessage>(foo), timer, &delay);
				delay += timeIncrement;
			}

			int count = 0;
			timeIncrement *= 100;

			while (!q.isEmpty())
			{
				timer.SetCurrentTime(timePoint += timeIncrement);
				q.Update(timer);
				++count;
			}

			Assert::AreEqual(10000, sub1.fooInt);
			Assert::AreEqual(101, count);
		}

		TEST_METHOD_CLEANUP(Cleanup)
		{
#ifdef _DEBUG
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);

			if (_CrtMemDifference(&diffMemState, &sStartMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
#endif
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState EventTests::sStartMemState;
}