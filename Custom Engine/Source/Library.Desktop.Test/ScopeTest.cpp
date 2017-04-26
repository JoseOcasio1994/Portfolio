#include "pch.h"
#include "CppUnitTest.h"
#include "Scope.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopTest
{

	TEST_CLASS(ScopeTest)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
#ifdef _DEBUG
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
#endif
		}

		TEST_METHOD(ScopeAppendAndBracket)
		{
			std::int32_t Health = 150, Mana = 100;
			Scope Jose(2);

			// Append Various Data
 			Jose.Append("Name") = "Jose";
			Jose.Append("Health") = Health;
			Jose["Mana"] = Mana;
			Assert::IsTrue(3 == Jose.Size());

			// Check Entries Are THere
			Assert::IsTrue("Jose" == Jose[0].Get<std::string>());
			Assert::IsTrue(150 == Jose[1].Get<std::int32_t>());
			Assert::IsTrue(100 == Jose["Mana"].Get<std::int32_t>());
			Assert::IsTrue(100 == Jose[2].Get<std::int32_t>());
			Assert::IsTrue(3 == Jose.Size());

			// Append New Scope
			Jose.AppendScope("Power");
			Assert::IsTrue(4 == Jose.Size());
			Assert::IsTrue(&Jose == Jose[3][0].GetParent());
			Jose.AppendScope("Power");
			Assert::IsTrue(4 == Jose.Size());
			Assert::IsTrue(1 == Jose["Power"][0].Size());
			Assert::IsTrue(&Jose["Power"][0] == Jose["Power"][0]["Power"][0].GetParent());

			// AppendScope Replaces And Appends Non-Table Entry
			auto exception = [&Jose] {Jose.AppendScope("Health"); };
			Assert::ExpectException<std::exception>(exception);

			auto exception2 = [&Jose] {Jose[100]; };
			Assert::ExpectException<std::exception>(exception2);

		}

		TEST_METHOD(ScopeFind)
		{
			std::int32_t Health = 150, Mana = 100;
			Scope Jose(2), Powers(3);
			Datum strDatum(Datum::String);

			Jose.Append("Name") = "Jose";
			Jose.Append("Health") = Health;
			Jose["Mana"] = Mana;

			Datum datum = *Jose.Find("Health");
			Assert::IsTrue(Health == datum.Get<std::int32_t>());
			Assert::IsTrue(1 == datum.Size());

			Jose.AppendScope("Power");
		}

		TEST_METHOD(ScopeSearch)
		{
			std::int32_t Health = 150, Mana = 100;
			Scope Jose(2);

			// Append Various Data
			Jose.Append("Name") = "Jose";
			Jose.Append("Health") = Health;
			Jose["Mana"] = Mana;
			Jose.AppendScope("Power");

			// Double Pointers For Search
			Scope& child = Jose["Power"][0];
			Scope** ptr = new Scope*();
			Datum* foundDatum = child.Search("Health", ptr);

			// Found Health
			Assert::IsNotNull(foundDatum);
			Assert::IsTrue(foundDatum->Type() == Datum::Integer);
			Assert::IsTrue(foundDatum->Get<std::int32_t>() == Health);
			Assert::IsNotNull(ptr);
			Assert::IsTrue(*ptr == &Jose);

			// Found Name
			foundDatum = child.Search("Name");
			Assert::IsNotNull(foundDatum);
			Assert::IsTrue(foundDatum->Type() == Datum::String);
			Assert::IsTrue(foundDatum->Get<std::string>() == "Jose");

			delete ptr;
		}

		TEST_METHOD(ScopeCopy)
		{
			std::int32_t Health = 150, Mana = 100;
			Scope Jose(2);

			// Append Various Data
			Jose.Append("Name") = "Jose";
			Jose.Append("Health") = Health;
			Jose["Mana"] = Mana;
			Jose.AppendScope("Powers");

			Scope Power(Jose);
// 			Assert::IsTrue(Power[0].Get<std::string>() == "Jose");
// 			Assert::IsTrue(Power[1].Get<std::int32_t>() == Health);
// 			Assert::IsTrue(Power[2].Get<std::int32_t>() == Mana);
// 			Assert::IsTrue(Power[3][0] == Jose[3][0]);
		}

		TEST_METHOD(ScopeAdopt)
		{
			std::int32_t Health = 150, Mana = 100;
			Scope Jose(2);
			Scope* Powers = new Scope(), *Temp = new Scope();

			// Init Scope 1
			Jose.Append("Name") = "Jose";
			Jose.Append("Health") = Health;
			Jose["Mana"] = Mana;
			Assert::IsTrue(Jose.Size() == 3);

			// Init Scope 2
			Powers->Append("Power1") = "Fire";
			Powers->Append("Power2") = "Lightning";
			Powers->Append("Power3") = "Ice";

			// Init Scope 3 By Adopting Scope 2
			Temp->Append("Name") = "Bob";
			Temp->Adopt(*Powers, "Power");

			Assert::AreEqual(2U, Temp->Size());

			Assert::IsTrue(Temp->operator[](1)[0][0].Get<std::string>() == "Fire");
			Assert::IsTrue(Temp->operator[](1)[0][1].Get<std::string>() == "Lightning");
			Assert::IsTrue(Temp->operator[](1)[0][2].Get<std::string>() == "Ice");

			// Scope 1 Adopt Scope 2 From Scope 3
			Jose.Adopt(Temp->operator[]("Power")[0], "Power");
			Jose.Adopt(*Temp, "Temp");

			Assert::AreEqual(2U, Temp->Size());
			Assert::AreEqual(0U, Temp->operator[](1).Size());

			Assert::AreEqual(Jose.Size(), 5U);
			Assert::AreEqual(Jose[3][0].Size(), 3U);
			Assert::IsTrue(Jose[3][0][0].Get<std::string>() == "Fire");
			Assert::IsTrue(Jose[3][0][1].Get<std::string>() == "Lightning");
			Assert::IsTrue(Jose[3][0][2].Get<std::string>() == "Ice");

			//Jose.Adopt(*new Scope(), "Power");
		}

		TEST_METHOD(ScopeRTTI)
		{
			Scope scope;

			RTTI* rtti = &scope;
			Assert::IsFalse(rtti->Is("Unknown"));
			Assert::IsTrue(rtti->Is("Scope"));
			Assert::IsTrue(rtti->Is( scope.TypeIdInstance() ));

			Scope* rttiAsScope = rtti->As<Scope>();
			Assert::IsNotNull(rttiAsScope);
			Assert::IsTrue(*rttiAsScope == scope);
			Assert::IsNull(scope.QueryInterface(5));
		}

		TEST_METHOD(ScopeMove)
		{
			std::int32_t Health = 150, Mana = 100;
			Scope Jose(2);

			// Append Various Data
			Jose.Append("Name") = "Jose";
			Jose.Append("Health") = Health;
			Jose.Append("Mana") = Mana;
			Jose.AppendScope("Powers");

			// Copy Constructor
			Scope moveConst = std::move(Jose["Powers"][0]);
			Assert::IsTrue(4 == Jose.Size());
			Assert::IsTrue(0 == Jose["Powers"][0].Size());
			Assert::IsTrue(moveConst == Jose["Powers"][0]);
 			Assert::IsTrue(moveConst.GetParent() == &Jose);

			// Copy Operator
			Scope moveOp;
			moveOp = std::move(Jose);
			Assert::IsTrue(0 == Jose.Size());
			Assert::IsTrue(0 == moveConst.Size());
			Assert::IsTrue(4 == moveOp.Size());
			Assert::IsTrue("Jose" == moveOp["Name"].Get<std::string>());
			Assert::IsTrue(moveConst == moveOp["Powers"][0]);
			//Assert::IsTrue(moveConst.GetParent() == &moveOp);
			Assert::IsTrue(moveOp["Powers"][0].GetParent() == &moveOp);
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

	_CrtMemState ScopeTest::sStartMemState;
}