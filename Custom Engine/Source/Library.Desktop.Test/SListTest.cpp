
#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopTest
{
	TEST_CLASS(SListTest)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
#ifdef _DEBUG
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
#endif
		}

		TEST_METHOD(SListExceptions)
		{
			SList<int> list;
			SList<int*> ptrList;
			SList<Foo<int>> fooList;

			Assert::AreEqual(true, list.isEmpty());
			Assert::AreEqual(true, ptrList.isEmpty());
			Assert::AreEqual(true, fooList.isEmpty());
			
			// Pop Exceptions
			auto popException = [&list] {list.PopFrontWithReturn(); };
			Assert::ExpectException<std::exception>(popException);

			auto popExceptionPtr = [&ptrList] {ptrList.PopFrontWithReturn(); };
			Assert::ExpectException<std::exception>(popExceptionPtr);

			auto popExceptionFoo = [&fooList] {fooList.PopFrontWithReturn(); };
			Assert::ExpectException<std::exception>(popExceptionFoo);

			// Front Exceptions
			auto frontException = [&list] {list.Front(); };
			Assert::ExpectException<std::exception>(frontException);

			auto frontExceptionPtr = [&ptrList] {ptrList.Front(); };
			Assert::ExpectException<std::exception>(frontExceptionPtr);

			auto frontExceptionFoo = [&fooList] {fooList.Front(); };
			Assert::ExpectException<std::exception>(frontExceptionFoo);

			// Back Exceptions
			auto backException = [&list] {list.Back(); };
			Assert::ExpectException<std::exception>(backException);

			auto backExceptionPtr = [&ptrList] {ptrList.Back(); };
			Assert::ExpectException<std::exception>(backExceptionPtr);

			auto backExceptionFoo = [&fooList] {fooList.Back(); };
			Assert::ExpectException<std::exception>(backExceptionFoo);
		}

		TEST_METHOD(SListPushPop)
		{
			SList<int> list;
			SList<int*> ptrList;
			SList<Foo<int>> fooList;
			std::uint32_t size = 1;

			int a = 10;
			int b = 20;
			int c = 5;
			Foo<int> foo(a);
			Foo<int> foo2(b);
			Foo<int> foo3(c);

			// PushBack() works on empty list
			list.PushBack(a);
			Assert::AreEqual(a, list.Front());
			Assert::AreEqual(a, list.Back());
			Assert::AreEqual(size, list.Size());
			list.Clear();

			ptrList.PushBack(&a);
			Assert::AreEqual(&a, ptrList.Front());
			Assert::AreEqual(&a, ptrList.Back());
			Assert::AreEqual(size, ptrList.Size());
			ptrList.Clear();

			fooList.PushBack(foo);
			Assert::AreEqual(a, *fooList.Front());
			Assert::AreEqual(a, *fooList.Back());
			Assert::AreEqual(size, fooList.Size());
			fooList.Clear();

			// PushFront() works on empty list
			list.PushFront(a);
			Assert::AreEqual(a, list.Front());
			Assert::AreEqual(a, list.Back());
			Assert::AreEqual(size, list.Size());

			ptrList.PushFront(&a);
			Assert::AreEqual(&a, ptrList.Front());
			Assert::AreEqual(&a, ptrList.Back());
			Assert::AreEqual(size, list.Size());

			fooList.PushFront(foo2);
			Assert::AreEqual(b, *fooList.Front());
			Assert::AreEqual(a, list.Back());
			Assert::AreEqual(size, list.Size());

			// Push works on existing list
			list.PushFront(c);
			list.PushBack(b);
			Assert::AreEqual(c, list.Front());
			Assert::AreEqual(b, list.Back());
			Assert::AreEqual(size += 2, list.Size());

			ptrList.PushFront(&c);
			ptrList.PushBack(&b);
			Assert::AreEqual(&c, ptrList.Front());
			Assert::AreEqual(&b, ptrList.Back());
			Assert::AreEqual(size, ptrList.Size());

			fooList.PushFront(foo3);
			fooList.PushBack(foo2);
			Assert::AreEqual(c, *fooList.Front());
			Assert::AreEqual(b, *fooList.Back());
			Assert::AreEqual(size, fooList.Size());

		}

		TEST_METHOD(SListCopyConstructor)
		{
			SList<int> list;
			SList<int*> ptrList;
			SList<Foo<int>> fooList;
			
			int a = 10;
			int b = 20;
			Foo<int> foo(a);
			Foo<int> foo2(b);

			list.PushBack(a);
			ptrList.PushBack(&a);
			fooList.PushBack(foo);

			// Copy Lists
			SList<int> listCopy(list);
			SList<int*> ptrCopy(ptrList);

			// Check Lists Are Equal
			Assert::AreEqual(list.Front(), listCopy.Front());
			Assert::AreEqual(list.Back(), listCopy.Back());
			Assert::AreEqual(list.Size(), listCopy.Size());

			Assert::AreEqual(ptrList.Front(), ptrCopy.Front());
			Assert::AreEqual(ptrList.Back(), ptrCopy.Back());
			Assert::AreEqual(ptrList.Size(), ptrCopy.Size());


			// Check Changes In 1 Don't Affect Others
			listCopy.PushBack(b);
			Assert::AreNotEqual(list.Back(), listCopy.Back());

			ptrCopy.PushBack(&b);
			Assert::AreNotEqual(ptrList.Back(), ptrCopy.Back());

		}

		TEST_METHOD(SListIteratorFind)
		{
			SList<int> list;

			int a = 1;
			int b = 2;
			int c = 3;
			int d = 4;

			list.PushBack(a);
			list.PushBack(b);
			list.PushBack(c);
			list.PushBack(d);

			// Check That Increment Works And List Is The Same
			int i = 1;
			for (SList<int>::Iterator it = list.begin(); it != list.end(); ++it)
			{
				Assert::AreEqual(i, *it);
				++i;
			}
			
			SList<int>::Iterator findIt = list.Find(1);
			Assert::AreEqual(1, *findIt);
		}

		TEST_METHOD(SListIteratorRemove)
		{
			SList<int> list;
			std::uint32_t size = 4;

			int a = 1;
			int b = 2;
			int c = 3;
			int d = 4;
			int e = 5;

			list.PushBack(a);
			list.PushBack(b);
			list.PushBack(c);
			list.PushBack(d);
			list.PushBack(e);

			// Remove Front [1,2,3,4,5] --> [2,3,4,5]
			Assert::AreEqual(a, list.Front());
			bool wasRemoved = list.Remove(a);
			Assert::AreEqual(true, wasRemoved);
			Assert::AreEqual(b, list.Front());
			Assert::AreEqual(size, list.Size());

			// Remove Mid [2,3,4,5] --> [2,4,5]
			wasRemoved = list.Remove(c);
			Assert::AreEqual(true, wasRemoved);
			list.PopFront();
			Assert::AreEqual(d, list.Front());
			list.PushFront(b);
			Assert::AreEqual(--size, list.Size());

			// Remove End  [2,4,5] --> [2,4]
			wasRemoved = list.Remove(e);
			Assert::AreEqual(true, wasRemoved);

			// Failed Removed
			wasRemoved = list.Remove(10);
			Assert::AreEqual(false, wasRemoved);
		}

		TEST_METHOD(SListIteratorInsert)
		{
			SList<int> list;
			std::uint32_t size = 4;

			int a = 1;
			int b = 2;
			int c = 3;
			int d = 4;
			int e = 5;

			list.PushBack(a);
			list.PushBack(b);
			list.PushBack(c);

			SList<int>::Iterator It = list.begin();

			// Insert To Back
			++It;
			++It;
			It = list.InsertAfter(d, It);
			Assert::AreEqual(size, list.Size());
			Assert::AreEqual(d, list.Back());
			Assert::AreEqual(d, *It);

			// Insert Beginning
			It = list.begin();
			It = list.InsertAfter(e, It);
			Assert::AreEqual(++size, list.Size());
			list.PopFront();
			Assert::AreEqual(e, list.Front());
		}

		TEST_METHOD(SListMove)
		{
			SList<int> list;
			int a = 1, b = 2, c = 3;

			list.PushBack(a);
			list.PushBack(b);
			list.PushBack(c);

			SList<int> list2 = std::move(list);
			Assert::IsTrue(0 == list.Size());
			Assert::IsTrue(3 == list2.Size());
			Assert::IsTrue(a == list2.Front());
			Assert::IsTrue(c == list2.Back());

			SList<int> list3;
			list3 = std::move(list2);
			Assert::IsTrue(0 == list.Size());
			Assert::IsTrue(0 == list2.Size());
			Assert::IsTrue(3 == list3.Size());
			Assert::IsTrue(a == list3.Front());
			Assert::IsTrue(c == list3.Back());
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

	_CrtMemState SListTest::sStartMemState;
}
