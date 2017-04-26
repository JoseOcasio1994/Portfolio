#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopTest
{

	TEST_CLASS(ReactionTest)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
#ifdef _DEBUG
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
#endif
		}

		TEST_METHOD(EventMessageTest)
		{
			std::string Earthstr = "Earth";
			WorldState state;
			World Earth(Earthstr);
			EventMessage em;

			em.SetSubtype("Collision");
			em.SetWorld(Earth);

			Assert::IsTrue(em.GetWorld() == Earth);
			Assert::IsTrue(em.Subtype() == std::string("Collision"));

			EventMessage emCopy(em), emCopy2;
			Assert::IsTrue(emCopy.GetWorld() == Earth);
			Assert::IsTrue(emCopy.Subtype() == std::string("Collision"));

			emCopy2 = em;
			Assert::IsTrue(emCopy2.GetWorld() == Earth);
			Assert::IsTrue(emCopy2.Subtype() == std::string("Collision"));
		}

		TEST_METHOD(ActionEventTest)
		{
			std::string collision = "Collision";
			World Earth("Earth");
			ActionEventFactory factory;
			ActionEvent *event = Factory<Action>::Create("ActionEvent")->As<ActionEvent>();

			Assert::AreEqual(true, event->IsPrescribedAttribute("Subtype"));
			Assert::AreEqual(true, event->IsPrescribedAttribute("Delay"));
			Assert::AreEqual(std::string("Unknown"), event->Find("Subtype")->Get<std::string>());
			Assert::AreEqual(0, event->Find("Delay")->Get<std::int32_t>());

			event->SetDelay(10);
			event->SetSubType(collision);

			Assert::AreEqual(collision, event->GetSubType());
			Assert::AreEqual(10, event->GetDelay());

			ActionEvent event2(collision, 10);
			Assert::AreEqual(collision, event2.GetSubType());
			Assert::AreEqual(10, event2.GetDelay());

			Earth.Update();
			event->Append("Health") = 100;
			event->Update(Earth.GetWorldState());
			Earth.GetEventQueue()->Clear();

			delete event;
		}

		TEST_METHOD(ReactionAttributedTest)
		{
			std::string Healthstr = "Health";
			World Earth("Earth");
			ReactionAttributedFactory factory;
			ReactionAttributed *reaction = Factory<Action>::Create("ReactionAttributed")->As<ReactionAttributed>();
			
			Assert::IsTrue(reaction->IsPrescribedAttribute("Subtype"));
			
			reaction->AddSubtype(Healthstr);
			reaction->AddSubtype("Mana");
			Assert::AreEqual(reaction->GetSubtypes()->Size(), 2U);

			Assert::AreEqual(reaction->GetSubtypes()->Get<std::string>(), Healthstr);
			Assert::AreEqual(reaction->GetSubtypes()->Get<std::string>(1), std::string("Mana"));

			EventMessage* message = new EventMessage(Healthstr, &Earth);
			message->Append("RandomInt") = 100;

			Event<EventMessage> event(*message);
			reaction->Notify(event);

			delete reaction;
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

	_CrtMemState ReactionTest::sStartMemState;
}