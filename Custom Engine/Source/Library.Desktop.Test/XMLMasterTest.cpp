#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopTest
{

	TEST_CLASS(XMLMasterTest)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
#ifdef _DEBUG
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
#endif
		}

		TEST_METHOD(XMLMasterConstruct)
		{
			FooSharedData data, data2;
			XMLParseMaster parseMaster(data);

			Assert::IsTrue(&data == parseMaster.GetSharedData());
			Assert::IsTrue(&data2 != parseMaster.GetSharedData());
			Assert::AreEqual(0U, data.Depth());
			Assert::AreEqual(0U, data2.Depth());
			Assert::IsTrue(data.GetXMLParseMaster() == &parseMaster);
			Assert::IsNull(data2.GetXMLParseMaster());

			parseMaster.SetSharedData(data2);
			Assert::IsTrue(&data != parseMaster.GetSharedData());
			Assert::IsTrue(&data2 == parseMaster.GetSharedData());
			Assert::IsTrue(data2.GetXMLParseMaster() == &parseMaster);
			Assert::IsNull(data.GetXMLParseMaster());
		}

		TEST_METHOD(XMLMasterHelpers)
		{
			FooSharedData data;
			XMLParseMaster parseMaster(data);
			FooXMLHelper helper1, helper2, helper3;
			parseMaster.AddHelper(helper1);
			parseMaster.AddHelper(helper2);

			bool removed = parseMaster.RemoveHelper(helper1);
			Assert::AreEqual(true, removed);

			removed = parseMaster.RemoveHelper(helper3);
			Assert::AreEqual(false, parseMaster.RemoveHelper(helper3));
		}

		TEST_METHOD(XMLMasterClone)
		{
			FooSharedData data, data2;
			XMLParseMaster parseMaster(data);
			FooXMLHelper helper1, helper2;
			parseMaster.AddHelper(helper1);

			XMLParseMaster* clone = &parseMaster.Clone();
 			clone->GetSharedData()->SetXMLParseMaster(clone);
			Assert::IsTrue(&data != clone->GetSharedData());
   			Assert::IsTrue(clone->GetSharedData()->GetXMLParseMaster() == clone);

			auto expression = [&clone, &helper2] {clone->AddHelper(helper2); };
			Assert::ExpectException<std::exception>(expression);

			auto expression2 = [&clone, &data2] {clone->SetSharedData(data2); };
			Assert::ExpectException<std::exception>(expression2);
			delete clone;
		}

		TEST_METHOD(XMLMasterParse)
		{
			std::string fileName = "..\\..\\..\\..\\..\\test.xml";
			FooSharedData data;
			XMLParseMaster parseMaster(data);
			FooXMLHelper helper1, helper2;

			parseMaster.AddHelper(helper1);
			
			auto expression = [&parseMaster] {parseMaster.ParseFromFile("file.xml"); };
			Assert::ExpectException<std::exception>(expression);
			parseMaster.ParseFromFile(fileName);

			Assert::AreEqual(100, data.Health);
			Assert::AreEqual(200, data.Mana);


			// Get File Name Check
			Assert::AreEqual(fileName,  parseMaster.GetFileName());
			fileName = parseMaster.GetFileName();
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

	_CrtMemState XMLMasterTest::sStartMemState;
}