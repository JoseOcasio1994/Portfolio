#include "pch.h"
#include "CppUnitTest.h"
#include "Attributed.h"
#include "AttributedFoo.h"
#include "Foo.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopTest
{

	TEST_CLASS(AttributeTest)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
#ifdef _DEBUG
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
#endif
		}

		TEST_METHOD(AttributedPrescribed)
		{
			AttributedFoo a;

			// Prescribed Check
			Assert::AreEqual(12U, a.Size());
			Assert::AreEqual(true, a.IsPrescribedAttribute("this"));

			Assert::AreEqual(true, a.IsPrescribedAttribute("InternalIntArray"));
			Assert::AreEqual(true, a.IsPrescribedAttribute("InternalFloatArray"));
			Assert::AreEqual(true, a.IsPrescribedAttribute("InternalStringArray"));
			Assert::AreEqual(true, a.IsPrescribedAttribute("InternalVectorArray"));
			Assert::AreEqual(true, a.IsPrescribedAttribute("InternalMatrixArray"));

			Assert::AreEqual(true, a.IsPrescribedAttribute("InternalScope"));

			Assert::AreEqual(true, a.IsPrescribedAttribute("ExternalIntArray"));
			Assert::AreEqual(true, a.IsPrescribedAttribute("ExternalFloatArray"));
			Assert::AreEqual(true, a.IsPrescribedAttribute("ExternalStringArray"));
			Assert::AreEqual(true, a.IsPrescribedAttribute("ExternalVectorArray"));
			Assert::AreEqual(true, a.IsPrescribedAttribute("ExternalMatrixArray"));

			// Value Check
			Assert::IsTrue(&a == a["this"].Get<RTTI*>());

			glm::vec4 vecA(1, 2, 3, 4), vecB(2, 4, 6, 8);
			glm::mat4x4 matA(vecA, vecA, vecA, vecA), matB(2 * matA);

			Assert::AreEqual(1, a["InternalIntArray"].Get<std::int32_t>());
			Assert::AreEqual(1.0f, a["InternalFloatArray"].Get<std::float_t>());
			Assert::AreEqual(std::string("Jose"), a["InternalStringArray"].Get<std::string>());
			Assert::IsTrue(vecA == a["InternalVectorArray"].Get<glm::vec4>());
			Assert::IsTrue(matA == a["InternalMatrixArray"].Get<glm::mat4x4>());

			Assert::AreEqual(100, a["InternalScope"][0][0].Get<std::int32_t>());

			Assert::AreEqual(6, a["ExternalIntArray"].Get<std::int32_t>());
			Assert::AreEqual(6.0f, a["ExternalFloatArray"].Get<std::float_t>());
			Assert::AreEqual(std::string("f"), a["ExternalStringArray"].Get<std::string>());
			Assert::IsTrue(vecB == a["ExternalVectorArray"].Get<glm::vec4>());
			Assert::IsTrue(matB == a["ExternalMatrixArray"].Get<glm::mat4x4>());
		}

		TEST_METHOD(AttributedAuxiliary)
		{
			AttributedFoo a;

			auto exception = [&a] {a.AppendAuxiliaryAttribute("InternalIntArray"); };
			Assert::ExpectException<std::exception>(exception);

			a.AppendAuxiliaryAttribute("Mana") = 200;
			a.AppendScope("Scope2");

			Assert::AreEqual(14U, a.Size());
			Assert::AreEqual(true, a.IsAuxiliaryAttribute("Mana"));
			Assert::AreEqual(true, a.IsAuxiliaryAttribute("Scope2"));

			Assert::AreEqual(12U, a.AuxiliaryBegin());
			Assert::IsTrue(a[a.AuxiliaryBegin()] == a["Mana"]);
		}

		TEST_METHOD(AttributedCopy)
		{
			AttributedFoo a;
			a.AppendAuxiliaryAttribute("Mana") = 200;
			a.AppendScope("Scope2");

			AttributedFoo b(a);
			Assert::IsTrue(&b == b["this"].Get<RTTI*>());
			Assert::AreEqual(true, b.IsAttribute("Mana"));
			Assert::AreEqual(200, b["Mana"].Get<std::int32_t>());
			Assert::AreEqual(true, b.IsAttribute("Scope2"));
			Assert::IsTrue(a["Scope2"][0] == b["Scope2"][0]);
		}

		TEST_METHOD(AttributedMove)
		{
			AttributedFoo a;

 			AttributedFoo b = std::move(a);
// 			Assert::AreEqual(0U, a.Size());
// 			Assert::AreEqual(14U, b.Size());
// 			Assert::AreEqual(true, b.IsPrescribedAttribute("this"));
// 
// 			Assert::AreEqual(true, b.IsPrescribedAttribute("InternalIntArray"));
// 			Assert::AreEqual(true, b.IsPrescribedAttribute("InternalFloatArray"));
// 			Assert::AreEqual(true, b.IsPrescribedAttribute("InternalStringArray"));
// 			Assert::AreEqual(true, b.IsPrescribedAttribute("InternalVectorArray"));
// 			Assert::AreEqual(true, b.IsPrescribedAttribute("InternalMatrixArray"));
// 
// 			Assert::AreEqual(true, b.IsPrescribedAttribute("InternalScope"));
// 
// 			Assert::AreEqual(true, b.IsPrescribedAttribute("ExternalIntArray"));
// 			Assert::AreEqual(true, b.IsPrescribedAttribute("ExternalFloatArray"));
// 			Assert::AreEqual(true, b.IsPrescribedAttribute("ExternalStringArray"));
// 			Assert::AreEqual(true, b.IsPrescribedAttribute("ExternalVectorArray"));
// 			Assert::AreEqual(true, b.IsPrescribedAttribute("ExternalMatrixArray"));
// 
// 			// Value Check
// 			glm::vec4 vecA(1, 2, 3, 4), vecB(2, 4, 6, 8);
// 			glm::mat4x4 matA(vecA, vecA, vecA, vecA), matB(2 * matA);
// 
// 			Assert::AreEqual(1, b["InternalIntArray"].Get<std::int32_t>());
// 			Assert::AreEqual(1.0f, b["InternalFloatArray"].Get<std::float_t>());
// 			Assert::AreEqual(std::string("Jose"), b["InternalStringArray"].Get<std::string>());
// 			Assert::IsTrue(vecA == b["InternalVectorArray"].Get<glm::vec4>());
// 			Assert::IsTrue(matA == b["InternalMatrixArray"].Get<glm::mat4x4>());
// 
// 			Assert::AreEqual(100, b["InternalScope"][0][0].Get<std::int32_t>());
// 
// 			Assert::AreEqual(6, b["ExternalIntArray"].Get<std::int32_t>());
// 			Assert::AreEqual(6.0f, b["ExternalFloatArray"].Get<std::float_t>());
// 			Assert::AreEqual(std::string("f"), b["ExternalStringArray"].Get<std::string>());
// 			Assert::IsTrue(vecB == b["ExternalVectorArray"].Get<glm::vec4>());
// 			Assert::IsTrue(matB == b["ExternalMatrixArray"].Get<glm::mat4x4>());
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

	_CrtMemState AttributeTest::sStartMemState;
}