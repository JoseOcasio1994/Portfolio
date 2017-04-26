#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopTest
{

	TEST_CLASS(ScopeParserTest)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
#ifdef _DEBUG
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
#endif
		}

		TEST_METHOD(ScopeParsing)
		{
			ScopeSharedData foo;
			Scope* scope = &foo.scope;
			XMLParseMaster masterParser(foo);
			XMLTableParser scopeHelper;
			masterParser.AddHelper(scopeHelper);

			Assert::AreEqual(0U, scope->Size());
			masterParser.ParseFromFile("..\\..\\..\\..\\..\\TableXML.xml");
			Assert::AreEqual(6U, scope->Size());

			Assert::IsNotNull(scope->Find("Health"));
			Assert::IsNotNull(scope->Find("Mana"));
			Assert::IsNotNull(scope->Find("Position"));
			Assert::IsNotNull(scope->Find("The Matrix"));
			Assert::IsNotNull(scope->Find("Name"));
			Assert::IsNotNull(scope->Find("Powers"));

			Assert::AreEqual(100, scope->Find("Health")->Get<std::int32_t>());
			Assert::AreEqual(200.0f, scope->Find("Mana")->Get<std::float_t>());
			Assert::IsTrue(glm::vec4(1,2,3,4) == scope->Find("Position")->Get<glm::vec4>());
			Assert::IsTrue(glm::mat4x4(1,2,3,4,2,4,6,8,1,3,5,7,8,0,0,8) == scope->Find("The Matrix")->Get<glm::mat4x4>());
			Assert::AreEqual(std::string("Jose"), scope->Find("Name")->Get<std::string>());
			Assert::IsTrue(0U == scope->Find("Powers")->Get<Scope*>()->Size());
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

	_CrtMemState ScopeParserTest::sStartMemState;
}