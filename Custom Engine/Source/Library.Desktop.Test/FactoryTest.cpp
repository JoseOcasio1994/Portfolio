#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopTest
{

	TEST_CLASS(FactoryTest)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
#ifdef _DEBUG
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
#endif
		}

		TEST_METHOD(FactoryNotMacro)
		{
			Foo<int>* fooA;
			FooFactory fooFactory;
			Factory<Foo<int>> *ptr;
			std::string name = "Foo<int>", fakeName = "Foo";
			ptr = FooFactory::Find(name);

			Assert::AreEqual(name, fooFactory.ClassName());

			Assert::IsNotNull(ptr);
			Assert::IsTrue(*ptr == fooFactory);

			auto expression = [&fooA, &fakeName] {fooA = Factory<Foo <int> >::Create(fakeName); };
			Assert::ExpectException<std::exception>(expression);

			fooA = Factory<Foo <int> >::Create(name);
			Assert::IsNotNull(fooA);
			delete fooA;
		}

		TEST_METHOD(FactoryMacro)
		{
			Foo<int>* fooA;
			FooMacroFactory factory;
			Factory<Foo<int>> *ptr;
			std::string name = "FooMacro", fakeName = "Foo";
			ptr = FooFactory::Find(name);

			Assert::AreEqual(name, factory.ClassName());

			Assert::IsNotNull(ptr);
			Assert::IsTrue(*ptr == factory);

			auto expression = [&fooA, &fakeName] {fooA = Factory<Foo <int> >::Create(fakeName); };
			Assert::ExpectException<std::exception>(expression);

			fooA = Factory<Foo <int> >::Create(name);
			Assert::IsNotNull(fooA);
			delete fooA;
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

	_CrtMemState FactoryTest::sStartMemState;
}