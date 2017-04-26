#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopTest
{

	TEST_CLASS(ActionTest)
	{

	public:

		TEST_METHOD_INITIALIZE(Initialize)
		{
#ifdef _DEBUG
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
#endif
		}

		TEST_METHOD(ActionName)
		{
			std::string jumpStr = "jump";
			FooAction jump;
			
 			auto expression = [&jump] { std::string Empty = ""; jump.SetName(Empty); };
 			Assert::ExpectException<std::exception>(expression);

			jump.SetName(jumpStr);
			Assert::AreEqual(jumpStr, jump.Name());

			Assert::AreEqual(true, jump.IsPrescribedAttribute("Name"));
			Assert::AreEqual(jump.Name(), jump.operator[]("Name").Get<std::string>());
		}

		TEST_METHOD(ActionListTest)
		{
			std::string jumpStr = "jump", dodgeStr = "Dodge", shootStr = "Shoot", reloadStr = "Reload", fooActionStr = "FooAction";
			ActionList Fight("Fight");
			FooActionFactory fooActionFactory;

			Assert::AreEqual(true, Fight.IsAttribute("Name"));
			Assert::AreEqual(std::string("Fight"), Fight.Name());

			Fight.CreateAction(fooActionStr, jumpStr);
			Fight.CreateAction(fooActionStr, dodgeStr);
			Fight.CreateAction(fooActionStr, shootStr);
			Fight.CreateAction(fooActionStr, reloadStr);

			Assert::AreEqual(true, Fight.IsPrescribedAttribute("Actions"));
			Assert::AreEqual(4U, Fight.Actions()->Size());
		}

		TEST_METHOD(EntityCreateActionTest)
		{
			std::string jumpStr = "jump", dodgeStr = "Dodge", shootStr = "Shoot", reloadStr = "Reload";
			FooActionFactory fooFactory;
			Action* curAction;
			Entity Jose("Jose");

			Assert::IsNotNull(Jose.Actions());
			Assert::AreEqual(true, Jose.IsPrescribedAttribute("Actions"));

			curAction = &Jose.CreateAction("FooAction", jumpStr);
			Assert::AreEqual(jumpStr, curAction->Name());

			curAction = &Jose.CreateAction("FooAction", dodgeStr);
			Assert::AreEqual(dodgeStr, curAction->Name());

			curAction = &Jose.CreateAction("FooAction", shootStr);
			Assert::AreEqual(shootStr, curAction->Name());

			curAction = &Jose.CreateAction("FooAction", reloadStr);
			Assert::AreEqual(reloadStr, curAction->Name());
		}

		TEST_METHOD(UpdateTest)
		{
			std::string jumpStr = "Jump";
			GameTime gametime, *gtPointer;
			WorldState worldState(&gametime);
			gtPointer = worldState.GetGameTime();
			FooEntityFactory fooEntityFactory;
			FooActionFactory fooActionFactory;
			ActionList AList;
			AList.CreateAction("FooAction", jumpStr);

			World Orience("Orience");
			Sector* Rubrum = &Orience.CreateSector("Rubrum");
			Entity* Ace = &Rubrum->CreateEntity("FooEntity", "Ace");
			Action* curAction = &Ace->CreateAction("FooAction", "Fight"); curAction;

			Orience.Update();
			AList.Update(worldState);

 			auto expression1 = [&Ace, &worldState] {Ace->Actions()->Pushback(new Scope()); Ace->Update(worldState); };
 			Assert::ExpectException<std::exception>(expression1);
		}

		TEST_METHOD(ParsingTest)
		{
			FooEntityFactory fooEntityFactory; fooEntityFactory;
			FooActionFactory fooActionFactory; fooActionFactory;
			ScopeSharedData foo;
			Scope* scope = &foo.scope;
			XMLParseMaster masterParser(foo);
			XMLTableParser scopeHelper;
			masterParser.AddHelper(scopeHelper);

			Assert::AreEqual(0U, foo.Depth());
			masterParser.ParseFromFile("..\\..\\..\\..\\..\\WorldTest.xml");

			Assert::AreEqual(true, scope->Find("Worlds")->Get<Scope*>()->Is(World::TypeIdClass()));
			World* curWorld = scope->Find("Worlds")->Get<Scope*>()->As<World>();

			Sector* curSector;
			Datum* datum = curWorld->Sectors();
			curSector = datum->Get<Scope*>(0)->As<Sector>();
			Assert::AreEqual(std::string("Midgar"), curSector->Name());

 			datum = curWorld->Find("Entities");
 			Entity* curEntity = datum->Get<Scope*>()->As<Entity>();
			Assert::AreEqual(std::string("Jose"), curEntity->Name());

			// Found Run Action
			datum = curEntity->Actions();
 			Action* curAction = datum->Get<Scope*>()->As<Action>();
 			Assert::IsNotNull(curAction);
 			Assert::AreEqual(std::string("Run"), curAction->Name());
 
 			// Run Is An Action Belonging To Jose
 			Assert::IsTrue(curAction->GetParent() == curEntity);
 
 			datum = curWorld->Actions();
 			curAction = datum->Get<Scope*>()->As<Action>();
 			Assert::IsNotNull(curAction);
			Assert::AreEqual(std::string("Jump"), curAction->Name());
 
 			// Jump Is An Action In The World
 			Assert::IsTrue(curAction->GetParent() == curWorld);
		}

		TEST_METHOD(ActionCreateDestroy)
		{
			GameTime gametime;
			WorldState worldState(&gametime);
			World Earth("Earth");
			ActionCreateAction* action = new ActionCreateAction();
			ActionDestroyAction* action2 = new ActionDestroyAction();
			FooActionFactory fooActionFactory;

			//Create Action
			Earth.Adopt(*action, "Actions");
			Assert::AreEqual(1U, Earth.Actions()->Size());
			action->PendCreateAction("FooAction", "Jump");
 			Earth.Update();
			Assert::AreEqual(2U, Earth.Actions()->Size());

			Action* jump = Earth.Actions()->Get<Scope*>(1)->As<Action>();
			Assert::AreEqual(std::string("Jump"), jump->Name());

			// Delete Action
			Earth.Adopt(*action2, "Actions");
 			Assert::AreEqual(3U, Earth.Actions()->Size());
 			action2->PendDestroyAction("Jump");
 
 			Earth.Update();
 			Earth.Update();
 
 			Assert::AreEqual(2U, Earth.Actions()->Size());
		}

		TEST_METHOD(ActionListIfTest)
		{
			GameTime gametime;
			WorldState worldState(&gametime);
			World Earth("Earth");
			ActionListIf* action = new ActionListIf();
			FooAction* foo = new FooAction(), *foo2 = new FooAction();

			Earth.Adopt(*action, "Actions");

			action->InitializeCondition(10);

			action->GetIfActions()->Adopt(*foo, "Actions");
			action->GetElseActions()->Adopt(*foo2, "Actions");
			Earth.Update();

			Assert::AreEqual(1, foo->fooInt);
			Assert::AreEqual(0, foo2->fooInt);

			action->SetCondition(5);
			Earth.Update();

			Assert::AreEqual(1, foo->fooInt);
			Assert::AreEqual(1, foo2->fooInt);
		}

		TEST_METHOD(ActionParseTest)
		{
			GameTime gametime;
			WorldState worldState(&gametime);
			FooEntityFactory fooEntityFactory; fooEntityFactory;
			FooActionFactory fooActionFactory; fooActionFactory;
			ScopeSharedData foo;
			Scope* scope = &foo.scope;
			XMLParseMaster masterParser(foo);
			XMLTableParser scopeHelper;
			masterParser.AddHelper(scopeHelper);

			masterParser.ParseFromFile("..\\..\\..\\..\\..\\WorldTest.xml");

			World* curWorld = scope->Find("Worlds")->Get<Scope*>()->As<World>();
			Assert::AreEqual(std::string("ActionCreateAction"), curWorld->Actions()->Get<Scope*>(1)->As<Action>()->Name());
			Assert::AreEqual(4U, curWorld->Actions()->Size());

			// ActionCreateAction Found In World
			Datum* ACADatum = curWorld->Actions();
			Assert::IsNotNull(ACADatum);
			ActionCreateAction* ACA = ACADatum->Get<Scope*>(1)->As<ActionCreateAction>();
			Assert::IsNotNull(ACA);

			// Create An Action
			ACA->Update(worldState);
			Assert::AreEqual(5U, curWorld->Actions()->Size());
			Assert::IsNotNull(curWorld->Actions()->Get<Scope*>(4)->As<Action>());
			Assert::AreEqual(std::string("Shoot"), curWorld->Actions()->Get<Scope*>(4)->As<Action>()->Name());

			// ActionDestroyAction Found In World
			Assert::AreEqual(5U, curWorld->Actions()->Size());
			Assert::AreEqual(std::string("ActionDestroyAction"), curWorld->Actions()->Get<Scope*>(2)->As<Action>()->Name());
			
			// Destroy An Action
			curWorld->Update();
			Assert::AreEqual(4U, curWorld->Actions()->Size());

			Assert::AreEqual(std::string("IfAction"), curWorld->Actions()->Get<Scope*>(3)->As<Action>()->Name());

			ActionListIf* actionIfScope = curWorld->Actions()->Get<Scope*>(3)->As<ActionListIf>();
			Assert::IsNotNull(actionIfScope);

			// ActionList If
			ActionListIf* actionIf = actionIfScope->As<ActionListIf>();
			Assert::IsNotNull(actionIf);

			Assert::AreEqual(1U, actionIf->GetIfActions()->Actions()->Size());
			Assert::AreEqual(1U, actionIf->GetElseActions()->Actions()->Size());

			Assert::AreEqual(std::string("IfActions"), actionIf->GetIfActions()->Name());
			Assert::AreEqual(std::string("ElseActions"), actionIf->GetElseActions()->Name());

			// Then Actions
			ActionList* aList = actionIf->GetIfActions()->As<ActionList>();
			Assert::IsNotNull(aList);

			// This, Name, And Actions
			Assert::AreEqual(3U, aList->Size());

			// Else Actions
 			aList = actionIf->GetElseActions()->As<ActionList>();
 			Assert::IsNotNull(aList);
 
 			Assert::AreEqual(3U, aList->Size());

			actionIf->Update(worldState);
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

	_CrtMemState ActionTest::sStartMemState;
}