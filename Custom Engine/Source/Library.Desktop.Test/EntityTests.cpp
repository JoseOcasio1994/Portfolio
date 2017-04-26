#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopTest
{

	TEST_CLASS(EntityTests)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
#ifdef _DEBUG
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
#endif
		}

		TEST_METHOD(EntityName)
		{
			std::string emptyStr = "", Jose = "Jose", Bob = "Bob";
			Entity thing1, thing2(Jose);
			
			Assert::AreEqual(thing1.Name(), emptyStr);
			Assert::AreEqual(thing2.Name(), Jose);
			Assert::AreEqual(thing2["Name"].Get<std::string>(), Jose);
			Assert::AreEqual(true, thing2.IsPrescribedAttribute("Name"));

			auto expression = [&thing2, &emptyStr] { thing2.SetName(emptyStr); };
			Assert::ExpectException<std::exception>(expression);

			thing2.SetName(Bob);
			Assert::AreEqual(thing2.Name(), Bob);
			Assert::AreEqual(thing2["Name"].Get<std::string>(), Bob);

		}

		TEST_METHOD(SectorName)
		{
			std::string emptyStr = "", Besaid = "Besaid", Midgar = "Midgar";
			Sector thing1, thing2(Besaid);

			Assert::AreEqual(thing1.Name(), emptyStr);
			Assert::AreEqual(thing2.Name(), Besaid);
			Assert::AreEqual(thing2["Name"].Get<std::string>(), Besaid);
			Assert::AreEqual(true, thing2.IsPrescribedAttribute("Name"));

			auto expression = [&thing2, &emptyStr] { thing2.SetName(emptyStr); };
			Assert::ExpectException<std::exception>(expression);

			thing2.SetName(Midgar);
			Assert::AreEqual(thing2.Name(), Midgar);
			Assert::AreEqual(thing2["Name"].Get<std::string>(), Midgar);
		}

		TEST_METHOD(EntitySector)
		{
			std::string Jose = "Jose", Besaid = "Besaid", Midgar = "Midgar";
			Sector location1(Besaid), location2(Midgar);
			Entity Person(Jose, &location1);

 			Assert::IsTrue(Person.GetSector() == &location1);
 			Person.SetSector(location2);
 			Assert::IsTrue(Person.GetSector() == &location2);
		}

		TEST_METHOD(SectorCreateEntities)
		{
			std::string Jose = "Jose", Besaid = "Besaid";
			Sector location1(Besaid);
			FooEntityFactory fooFactory; fooFactory;
			Entity* entity;

 			Assert::IsNotNull(location1.Entities());
 			Assert::AreEqual(true, location1.IsPrescribedAttribute("Entities"));
 			Assert::AreEqual(0U, location1.Entities()->Size());
			Datum* datum = location1.Entities(); datum;

			entity = &location1.CreateEntity("FooEntity", "Foo1");
 			Assert::IsNotNull(location1.Entities());
 			Assert::AreEqual(1U, location1.Entities()->Size());
 			Assert::AreEqual(std::string("Foo1"), entity->Name());

			entity = &location1.CreateEntity("FooEntity", "Foo2");
 			Assert::AreEqual(2U, location1.Entities()->Size());
 			Assert::AreEqual(std::string("Foo2"), entity->Name());
		}

		TEST_METHOD(WorldName)
		{
			WorldState state;
			std::string emptyStr = "", Earth = "Earth", Mars = "Mars";
			World planet1, planet2(Earth);

  			Assert::AreEqual(planet1.Name(), emptyStr);
 			Assert::AreEqual(planet2.Name(), Earth);
			Assert::AreEqual(planet2["Name"].Get<std::string>(), Earth);
			Assert::AreEqual(true, planet2.IsPrescribedAttribute("Name"));
 
 			auto expression = [&planet2, &emptyStr] { planet2.SetName(emptyStr); };
 			Assert::ExpectException<std::exception>(expression);
 
 			planet2.SetName(Mars);
 			Assert::AreEqual(planet2.Name(), Mars);
			Assert::AreEqual(planet2["Name"].Get<std::string>(), Mars);
		}

		TEST_METHOD(SectorWorld)
		{
			WorldState state;
			std::string Midgar = "Midgar", Earth = "Earth", Mars = "Mars";
			World planet(Earth), planet2(Mars);
			Sector sector(Midgar, &planet);

			Assert::IsTrue(sector.GetWorld() == &planet);
			sector.SetWorld(planet2);
			Assert::IsTrue(sector.GetWorld() == &planet2);
		}

		TEST_METHOD(WorldCreateSector)
		{
			std::string Earth = "Earth", Lestallum = "Lestallum", Altissia = "Altissia";
			World planetEarth(Earth);
			Sector* curSector; curSector;

			Assert::IsNotNull(planetEarth.Sectors());
			Assert::AreEqual(0U, planetEarth.Sectors()->Size());

			curSector = &planetEarth.CreateSector(Lestallum);
 			Assert::AreEqual(1U, planetEarth.Sectors()->Size());
 			Assert::AreEqual(Lestallum, curSector->Name());
 
			curSector = &planetEarth.CreateSector(Altissia);
			Assert::AreEqual(2U, planetEarth.Sectors()->Size());
			Assert::AreEqual(Altissia, curSector->Name());
		}

		TEST_METHOD(UpdateTest)
		{
			GameTime gametime, *gtPointer;
			WorldState worldState(&gametime);
			gtPointer = worldState.GetGameTime();
			FooEntityFactory fooFactory;

			World Orience("Orience");
			Sector* Rubrum = &Orience.CreateSector("Rubrum");
			&Rubrum->CreateEntity("FooEntity", "Ace");

			Orience.Update();

 			auto expression1 = [&Orience] {Orience.Sectors()->Pushback(new Scope()); Orience.Update(); };
 			Assert::ExpectException<std::exception>(expression1);

 			Sector* Berith = &Orience.CreateSector("Berith");
 			auto expression2 = [&Berith, &worldState] { Berith->Entities()->Pushback(new Scope()); Berith->Update(worldState); };
  			Assert::ExpectException<std::exception>(expression2);

		}

		TEST_METHOD(Parsing)
		{
			FooEntityFactory fooFactory; fooFactory;
			FooActionFactory fooActionFactory; fooActionFactory;
			ScopeSharedData foo;
			Scope* scope = &foo.scope; scope;
			XMLParseMaster masterParser(foo);
			XMLTableParser scopeHelper;
			masterParser.AddHelper(scopeHelper);

			Assert::AreEqual(0U, foo.Depth());
			masterParser.ParseFromFile("..\\..\\..\\..\\..\\WorldTest.xml");

			Assert::AreEqual(true, scope->Find("Worlds")->Get<Scope*>()->Is(World::TypeIdClass()));
			World* curWorld = scope->Find("Worlds")->Get<Scope*>()->As<World>(); curWorld;

			Datum* sectors = curWorld->Sectors();
			Assert::IsNotNull(sectors);
			Assert::AreEqual(1U, sectors->Size());

			Assert::AreEqual(true, sectors->Get<Scope*>()->Is(Sector::TypeIdClass()));
			Sector* curSector = sectors->Get<Scope*>()->As<Sector>(); curSector;

			// Sector Midgar Is In World(Earth)
			Assert::IsTrue(curSector->GetParent() == curWorld);

			sectors = curWorld->Find("Entities");
 			Assert::IsNotNull(sectors);
 			Entity* curEntity = sectors->Get<Scope*>()->As<Entity>();
			Assert::IsNotNull(curEntity);
			Assert::AreEqual(std::string("Jose"), curEntity->Name());
 
 			// Entity Jose Is In World(Earth)
 			Assert::IsTrue(curEntity->GetParent() == curWorld); 
 
 			curEntity = curSector->Entities()->Get<Scope*>()->As<Entity>();
 			Assert::IsNotNull(curEntity);
			Assert::AreEqual(std::string("Bob"), curEntity->Name());
 
 			// Entity Bob Is In Sector(Midgar) In World(Earth)
 			Assert::IsTrue(curEntity->GetParent() == curSector);
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

	_CrtMemState EntityTests::sStartMemState;
}