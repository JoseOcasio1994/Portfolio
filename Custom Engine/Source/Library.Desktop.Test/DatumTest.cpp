#include "pch.h"
#include "CppUnitTest.h"
#include "Scope.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopTest
{
	TEST_CLASS(DatumTest)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
#ifdef _DEBUG
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
#endif
		}

		TEST_METHOD(DatumType)
		{
			Datum unknownList;
			Datum intList(Datum::Integer);
			Datum floatList(Datum::Float);
			Datum vectorList(Datum::Vector);
			Datum matrixList(Datum::Matrix);
			Datum pointerList(Datum::Pointer);

			// Check Types
			Assert::IsTrue(Datum::Unknown == unknownList.Type());
			Assert::IsTrue(Datum::Integer == intList.Type());
			Assert::IsTrue(Datum::Float == floatList.Type());
			Assert::IsTrue(Datum::Vector == vectorList.Type());
			Assert::IsTrue(Datum::Matrix == matrixList.Type());
			Assert::IsTrue(Datum::Pointer == pointerList.Type());

			// Change Unknown To A Type
			unknownList.SetType(Datum::Integer);
			Assert::IsTrue(Datum::Integer == unknownList.Type());

			// Can't Change After Being Assigned
			auto expression = [&unknownList] { unknownList.SetType(Datum::Float); };
			Assert::ExpectException<std::exception>(expression);
		}

		TEST_METHOD(DatumSize)
		{
			Datum unknownList;
			Datum intList(Datum::Integer);
			Datum floatList(Datum::Float);
			Datum vectorList(Datum::Vector);
			Datum matrixList(Datum::Matrix);
			Datum stringList(Datum::String);

			// Check Sizes Are 0 (Default Is 0)
			Assert::IsTrue(0U == unknownList.Size());
			Assert::IsTrue(0U == intList.Size());
			Assert::IsTrue(0U == floatList.Size());
			Assert::IsTrue(0U == vectorList.Size());
			Assert::IsTrue(0U == matrixList.Size());
			Assert::IsTrue(0U == stringList.Size());

			// Change Sizes
			unknownList.Reserve(1U);
			Assert::IsTrue(0U == unknownList.Size());

			intList.Reserve(2U);
			Assert::IsTrue(0U == intList.Size());

			floatList.Reserve(3U);
			Assert::IsTrue(0U == floatList.Size());

			vectorList.Reserve(4U);
			Assert::IsTrue(0U == vectorList.Size());

			matrixList.Reserve(5U);
			Assert::IsTrue(0U == matrixList.Size());

			stringList.Reserve(6U);
			Assert::IsTrue(0U == stringList.Size());
		}
		
		TEST_METHOD(DatumSetGet)
		{
			Datum unknownList;
			Datum intList(Datum::Integer);
			Datum floatList(Datum::Float);
			Datum vectorList(Datum::Vector);
			Datum matrixList(Datum::Matrix);
			Datum stringList(Datum::String);
			Datum pointerList(Datum::Pointer);

			std::int32_t a = 1, b = 2, c = 3, d = 4;
			std::float_t floatA = 1.0, floatB = 2.0;
			glm::vec4 vectorA = { a, b, floatA, floatB }, vectorB = {b, a, floatB, floatA};
			glm::mat4x4 matrixA = {a, a, a, a, b, b, b, b, c, c, c, c, d, d, d, d};
			std::string strA = "Hello", strB = "Bye";
			Foo<int> fooA(a), fooB(b);
			RTTI* ptr = &fooA, *ptr2 = &fooB;
			
			// Set Unknown To Type Passed In
			unknownList.Pushback(a);
			unknownList.Set(2*a);
			Assert::IsTrue(Datum::Integer == unknownList.Type());
			Assert::IsTrue(2*a == unknownList.Get<std::int32_t>(0));

			intList.Pushback(a);
			intList.Set(2*a);
			Assert::IsTrue(2*a == intList.Get<std::int32_t>());

			floatList.Pushback(floatA);
			floatList.Set(2*floatA);
			Assert::IsTrue(2*floatA == floatList.Get<std::float_t>());

			vectorList.Pushback(vectorA);
			vectorList.Set(2*vectorA);
			Assert::IsTrue(2*vectorA == vectorList.Get<glm::vec4>());

			matrixList.Pushback(matrixA);
			matrixList.Set(2*matrixA);
			Assert::IsTrue(2*matrixA == matrixList.Get<glm::mat4x4>());

			stringList.Pushback(strA);
			stringList.Set("");
			Assert::IsTrue("" == stringList.Get<std::string>());

			pointerList.Pushback(ptr);
			pointerList.Set(ptr2);
			Assert::IsTrue(ptr2 == pointerList.Get<RTTI*>());

		}

		TEST_METHOD(DatumPushback)
		{
			Datum unknownList;
			Datum floatList(Datum::Float);
			Datum vectorList(Datum::Vector);
			Datum matrixList(Datum::Matrix);
			Datum stringList(Datum::String);
			Datum pointerList(Datum::Pointer);

			unknownList.Reserve(5);
			floatList.Reserve(5);
			vectorList.Reserve(5);
			matrixList.Reserve(5);
			stringList.Reserve(5);
			pointerList.Reserve(5);

			std::int32_t a = 1;
			std::float_t floatA = 1.0;
			glm::vec4 vecA = {1, 2, 3, 4};
			glm::mat4x4 matA = {vecA, vecA, vecA, vecA};
			std::string strA = "Jose Ocasio";
			Foo<int> fooA(a);
			RTTI* ptrA = &fooA;
			
			unknownList.Pushback(a);
			Assert::IsTrue(1U == unknownList.Size());
			Assert::IsTrue(a == unknownList.Get<std::int32_t>());

			floatList.Pushback(floatA);
			Assert::IsTrue(1U == floatList.Size());
			Assert::IsTrue(floatA == floatList.Get<std::float_t>());

			vectorList.Pushback(vecA);
			Assert::IsTrue(1U == vectorList.Size());
			Assert::IsTrue(vecA == vectorList.Get<glm::vec4>());

			matrixList.Pushback(matA);
			Assert::IsTrue(1U == matrixList.Size());
			Assert::IsTrue(matA == matrixList.Get<glm::mat4x4>());

			stringList.Pushback(strA);
			Assert::IsTrue(1U == stringList.Size());
			Assert::IsTrue(strA == stringList.Get<std::string>());

			pointerList.Pushback(ptrA);
			Assert::IsTrue(1U == pointerList.Size());
			Assert::IsTrue(ptrA == pointerList.Get<RTTI*>());
		}

		TEST_METHOD(DatumSetFromString1)
		{
			Datum intList(Datum::Integer);
			Datum floatList(Datum::Float);
			Datum stringList(Datum::String);
			std::string myString = "Hello";

			intList.Pushback(0);
			floatList.Pushback(0.0f);
			stringList.Pushback(myString);
		
			// Int--------------------------------------------------------
			myString = "1234";

			intList.SetFromString(myString, 0);
			Assert::AreEqual(1234, intList.Get<std::int32_t>());

			myString = "-1234";

			intList.SetFromString(myString, 0);
			Assert::AreEqual(-1234, intList.Get<std::int32_t>());

			myString = "1234.567";

			intList.SetFromString(myString, 0);
			Assert::AreEqual(1234, intList.Get<std::int32_t>());

			// Float--------------------------------------------------------
			myString = "1234";

			floatList.SetFromString(myString, 0);
			Assert::AreEqual(1234.0f, floatList.Get<std::float_t>());

			myString = "-1234";

			floatList.SetFromString(myString, 0);
			Assert::AreEqual(-1234.0f, floatList.Get<std::float_t>());

			myString = "1234.567";

			floatList.SetFromString(myString, 0);
			Assert::AreEqual(1234.567f, floatList.Get<std::float_t>());

			myString = "--1234";
			auto exception1 = [&floatList, &myString] { floatList.SetFromString(myString, 0); };
			Assert::ExpectException<std::exception>(exception1);

			myString = "1234..55";
			floatList.SetFromString(myString, 0);
			Assert::AreEqual(1234.0f, floatList.Get<std::float_t>());

			// String
			stringList.SetFromString(myString, 0);
			Assert::AreEqual(myString, stringList.Get<std::string>());

		}

		TEST_METHOD(DatumSetFromString2)
		{
			Datum vectorList(Datum::Vector);
			Datum matrixList(Datum::Matrix);

			vectorList.Pushback(glm::vec4());
			glm::vec4 vecA = { 1.00000000, 2.00000000, 3.00000000 , 4.00000000 };
			glm::vec4 vecB = { -1.00000000, 2.50000000, -3.75000000 , 4.00000000 };

			matrixList.Pushback(glm::mat4x4());
			glm::mat4x4 matA = { vecA, vecA, vecA, vecA };
			glm::mat4x4 matB = { vecB, vecB, vecB, vecB };

			// Vector--------------------------------------------------------

			std::string myString = "1 2 3 4";
			vectorList.SetFromString(myString, 0);
			Assert::IsTrue(vecA == vectorList.Get<glm::vec4>());

			myString = "-1 2.5 -3.75 4";
			vectorList.SetFromString(myString, 0);
			Assert::IsTrue(vecB == vectorList.Get<glm::vec4>());

			// Matrix--------------------------------------------------------

			myString = "1 2 3 4 1 2 3 4 1 2 3 4 1 2 3 4";
			matrixList.SetFromString(myString, 0);
			Assert::IsTrue(matA == matrixList.Get<glm::mat4x4>());

			myString = "-1 2.5 -3.75 4 -1 2.5 -3.75 4 -1 2.5 -3.75 4 -1 2.5 -3.75 4";
			matrixList.SetFromString(myString, 0);
			Assert::IsTrue(matB == matrixList.Get<glm::mat4x4>());

		}

		TEST_METHOD(DatumToString)
		{
			Datum intList(Datum::Integer);
			Datum floatList(Datum::Float);
			Datum vectorList(Datum::Vector);
			Datum matrixList(Datum::Matrix);
			Datum stringList(Datum::String);
			Datum pointerList(Datum::Pointer);

			std::int32_t a = 5;
			std::float_t floatA = 5.0;
			glm::vec4 vectA = { 1, 2, 3, 4 };
			glm::mat4x4 matA = {1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8};
			std::string strA = "Jose Ocasio";
			Foo<int> fooA(a);
			RTTI* ptr = &fooA;

			intList.Pushback(a);
			floatList.Pushback(floatA);
			vectorList.Pushback(vectA);
			matrixList.Pushback(matA);
			stringList.Pushback(strA);
			pointerList.Pushback(ptr);

			std::string cmpString = "5";
			Assert::AreEqual(cmpString, intList.ToString());

			cmpString = "5.000000";
			Assert::AreEqual(cmpString, floatList.ToString());

			cmpString = "vec4(1.000000, 2.000000, 3.000000, 4.000000)";
			Assert::AreEqual(cmpString, vectorList.ToString());

			cmpString = "Jose Ocasio";
			Assert::AreEqual(cmpString, stringList.ToString());

			cmpString = "RTTI";
			Assert::AreEqual(cmpString, pointerList.ToString());

			cmpString = "mat4x4((1.000000, 2.000000, 3.000000, 4.000000), (5.000000, 6.000000, 7.000000, 8.000000), (1.000000, 2.000000, 3.000000, 4.000000), (5.000000, 6.000000, 7.000000, 8.000000))";
			Assert::AreEqual(cmpString, matrixList.ToString());
		}

		TEST_METHOD(DatumSetStorage)
		{
			Datum unknownList;

			std::int32_t a = 1, b = 2, c = 3, d[] = { a, b, c };

			// Int
			unknownList.SetStorage(d, 3);
			Assert::IsTrue(3 == unknownList.Size());
			Assert::IsTrue(a == unknownList.Get<std::int32_t>());
			unknownList.Set(c);
			Assert::IsTrue(c == unknownList.Get<std::int32_t>());
		}

		TEST_METHOD(DatumGetExceptions)
		{
			Datum unknownList;
			Datum intList(Datum::Integer);
			Datum floatList(Datum::Float);
			Datum vectorList(Datum::Vector);
			Datum matrixList(Datum::Matrix);
			Datum stringList(Datum::String);
			Datum pointerList(Datum::Pointer);

			unknownList.Reserve(10);

			auto intGetWrong = [&unknownList] {unknownList.Get<std::int32_t>(); };
			Assert::ExpectException<std::exception>(intGetWrong);

			auto intGetOOR = [&intList] {intList.Get<std::int32_t>(5U); };
			Assert::ExpectException<std::exception>(intGetOOR);

			auto floatGetWrong = [&unknownList] {unknownList.Get<std::float_t>(); };
			Assert::ExpectException<std::exception>(floatGetWrong);

			auto floatGetOOR = [&floatList] {floatList.Get<std::float_t>(5U); };
			Assert::ExpectException<std::exception>(floatGetOOR);

			auto vectorGetWrong = [&unknownList] {unknownList.Get<glm::vec4>(); };
			Assert::ExpectException<std::exception>(vectorGetWrong);

			auto vectorGetOOR = [&vectorList] {vectorList.Get<glm::vec4>(5U); };
			Assert::ExpectException<std::exception>(vectorGetOOR);

			auto matGetWrong = [&unknownList] {unknownList.Get<glm::mat4x4>(); };
			Assert::ExpectException<std::exception>(matGetWrong);

			auto matGetOOR = [&matrixList] {matrixList.Get<glm::mat4x4>(5U); };
			Assert::ExpectException<std::exception>(matGetOOR);

			auto strGetWrong = [&unknownList] {unknownList.Get<std::string>(); };
			Assert::ExpectException<std::exception>(strGetWrong);

			auto strGetOOR = [&stringList] {stringList.Get<std::string>(5U); };
			Assert::ExpectException<std::exception>(strGetOOR);

			auto ptrGetWrong = [&unknownList] {unknownList.Get<std::string>(); };
			Assert::ExpectException<std::exception>(ptrGetWrong);

			auto ptrGetOOR = [&pointerList] {pointerList.Get<RTTI*>(5U); };
			Assert::ExpectException<std::exception>(ptrGetOOR);
		}

		TEST_METHOD(DatumSetExceptions)
		{
			Datum unknownList;

			std::int32_t a = 1;
			std::float_t floatA;
			glm::vec4 vecA = { 1, 2, 3, 4 };
			glm::mat4x4 matA = { vecA, 2*vecA, 3*vecA, 4*vecA };
			std::string strA = "Hello";
			Foo<int> fooA(a);
			RTTI* ptr = &fooA;

			auto exception6 = [&unknownList, &a, &floatA] {unknownList.Set(a); unknownList.Set(floatA); };
			Assert::ExpectException<std::exception>(exception6);

			auto exception7 = [&unknownList, &a, &vecA] {unknownList.Set(a); unknownList.Set(vecA); };
			Assert::ExpectException<std::exception>(exception7);

			auto exception8 = [&unknownList, &a, &matA] {unknownList.Set(a); unknownList.Set(matA); };
			Assert::ExpectException<std::exception>(exception8);

			auto exception9 = [&unknownList, &a, &strA] {unknownList.Set(a); unknownList.Set(strA); };
			Assert::ExpectException<std::exception>(exception9);

			auto exception10 = [&unknownList, &a, &ptr] {unknownList.Set(a); unknownList.Set(ptr); };
			Assert::ExpectException<std::exception>(exception10);

			auto exception11 = [&unknownList, &a, &floatA] {unknownList.Set(floatA); unknownList.Set(a); };
			Assert::ExpectException<std::exception>(exception11);
		}

		TEST_METHOD(DatumStorageExceptions)
		{
			Datum unknownList;

			std::int32_t a = 1, b = 2, c = 3, d[] = { a, b, c };
			std::float_t floatA = 1.0, floatB = 2.0, floatC = 3.0, floatD[] = { floatA, floatB, floatC };
			glm::vec4 vecA = { 1, 2, 3, 4 }, vecB = { 5, 6, 7, 8 }, vecC[] = { vecA, vecB };
			glm::mat4x4 matA = { vecA, vecB, vecA, vecB }, matB = 2 * matA, matC[2] = { matA, matB };
			std::string strA = "Hello", strB = "I Am", strC = "Jose", strD[] = { strA, strB, strC };
			Foo<int> fooA(a), fooB(b), fooC(c);
			RTTI* ptr[3] = { &fooA, &fooB, &fooC };

			// Pushbacks
			auto exception = [&unknownList, &d, &a] {unknownList.SetStorage(d, 3); unknownList.Pushback(a); };
			Assert::ExpectException<std::exception>(exception);

			auto exception1 = [&unknownList, &floatD, &floatA] {unknownList.SetStorage(floatD, 3); unknownList.Pushback(floatA); };
			Assert::ExpectException<std::exception>(exception1);

			auto exception2 = [&unknownList, &vecC, &vecA] {unknownList.SetStorage(vecC, 3); unknownList.Pushback(vecA); };
			Assert::ExpectException<std::exception>(exception2);

			auto exception3 = [&unknownList, &matC, &matA] {unknownList.SetStorage(matC, 3); unknownList.Pushback(matA); };
			Assert::ExpectException<std::exception>(exception3);

			auto exception4 = [&unknownList, &strD, &strA] {unknownList.SetStorage(strD, 3); unknownList.Pushback(strA); };
			Assert::ExpectException<std::exception>(exception4);

			auto exception5 = [&unknownList, &ptr] {unknownList.SetStorage(ptr, 3); unknownList.Pushback(ptr[0]); };
			Assert::ExpectException<std::exception>(exception5);

			// Invalid Types
			auto exception6 = [&unknownList, &d, &floatD] {unknownList.SetStorage(d, 3); unknownList.SetStorage(floatD, 3); };
			Assert::ExpectException<std::exception>(exception6);

			auto exception7 = [&unknownList, &d, &vecC] {unknownList.SetStorage(d, 3); unknownList.SetStorage(vecC, 3); };
			Assert::ExpectException<std::exception>(exception7);

			auto exception8 = [&unknownList, &d, &matC] {unknownList.SetStorage(d, 3); unknownList.SetStorage(matC, 3); };
			Assert::ExpectException<std::exception>(exception8);

			auto exception9 = [&unknownList, &d, &strD] {unknownList.SetStorage(d, 3); unknownList.SetStorage(strD, 3); };
			Assert::ExpectException<std::exception>(exception9);

			auto exception10 = [&unknownList, &d, &ptr] {unknownList.SetStorage(d, 3); unknownList.SetStorage(ptr, 3); };
			Assert::ExpectException<std::exception>(exception10);

			auto exception11 = [&unknownList, &d, &floatD] {unknownList.SetStorage(floatD, 3); unknownList.SetStorage(d, 3); };
			Assert::ExpectException<std::exception>(exception11);
		}

		TEST_METHOD(DatumCopyInternal)
		{
			Datum intList(Datum::Integer);

			int A = 1;
			intList.Reserve(3);
			intList.Pushback(A);

			// FLoat To Int
			Datum floatList(intList);
			Assert::IsTrue(1 == floatList.Size());
			Assert::IsTrue(Datum::Integer == floatList.Type());
			Assert::IsTrue(A == floatList.Get<std::int32_t>());

			// Previous To Vector
			glm::vec4 vecA = {1, 2, 3, 4};
			Datum vectorList(Datum::Vector);
			vectorList.Reserve(4);
			vectorList.Pushback(vecA);

			floatList = vectorList;
			Assert::IsTrue(1 == floatList.Size());
			Assert::IsTrue(Datum::Vector == floatList.Type());
			Assert::IsTrue(vecA == floatList.Get<glm::vec4>());

			// Previous To Matrix
			glm::mat4x4 matA = { vecA, 2*vecA, 3*vecA, 4*vecA };
			Datum matrixList(Datum::Matrix);
			matrixList.Reserve(5);
			matrixList.Pushback(matA);

			floatList = matrixList;
			Assert::IsTrue(1 == floatList.Size());
			Assert::IsTrue(Datum::Matrix == floatList.Type());
			Assert::IsTrue(matA == floatList.Get<glm::mat4x4>());

			// Previous To String
			std::string strA = "Hello";
			Datum strList(Datum::String);
			strList.Reserve(3);
			strList.Pushback(strA);

			floatList = strList;
			Assert::IsTrue(1 == floatList.Size());
			Assert::IsTrue(Datum::String == floatList.Type());
			Assert::IsTrue(strA == floatList.Get<std::string>());

			// Previous To Pointer
			Foo<int> foo(A);
			RTTI* ptrA = &foo;
			Datum ptrList(Datum::Pointer);
			ptrList.Reserve(1);
			ptrList.Pushback(ptrA);

			floatList = ptrList;
			Assert::IsTrue(1 == floatList.Size());
			Assert::IsTrue(Datum::Pointer == floatList.Type());
			Assert::IsTrue(ptrA == floatList.Get<RTTI*>());
			Assert::IsTrue(&foo == floatList.Get<RTTI*>());
			
		}

		TEST_METHOD(DatumCopyExternal)
		{
			Datum intList(Datum::Integer);

			int A = 1, B = 2, C = 3, D[3] = { A, B, C };
			intList.SetStorage(D, 3);

			// FLoat To Int
			Datum floatList(intList);
			Assert::AreEqual(3U, floatList.Size());
			Assert::IsTrue(Datum::Integer == floatList.Type());
			Assert::IsTrue(A == floatList.Get<std::int32_t>());
			Assert::IsTrue(floatList == intList);

			// Previous To Vector
			glm::vec4 vecA = { 1, 2, 3, 4 }, vecB = 2 * vecA, vecC[2] = {vecA, vecB};
			Datum vectorList(Datum::Vector);
			vectorList.SetStorage(vecC, 2);

			floatList = vectorList;
			Assert::IsTrue(2 == floatList.Size());
			Assert::IsTrue(Datum::Vector == floatList.Type());
			Assert::IsTrue(vecA == floatList.Get<glm::vec4>());
			Assert::IsTrue(floatList == vectorList);

			// Previous To Matrix
			glm::mat4x4 matA = { vecA, 2 * vecA, 3 * vecA, 4 * vecA }, matB = 2 * matA, matC[2] = {matA, matB};
			Datum matrixList(Datum::Matrix);
			matrixList.SetStorage(matC, 2);

			floatList = matrixList;
			Assert::IsTrue(2 == floatList.Size());
			Assert::IsTrue(Datum::Matrix == floatList.Type());
			Assert::IsTrue(matA == floatList.Get<glm::mat4x4>());
			Assert::IsTrue(floatList == matrixList);

			// Previous To String
			std::string strA = "Hello", strB = "Bye", strC[2] = {strA, strB};
			Datum strList(Datum::String);
			strList.SetStorage(strC, 2);

			floatList = strList;
			Assert::IsTrue(2 == floatList.Size());
			Assert::IsTrue(Datum::String == floatList.Type());
			Assert::IsTrue(strA == floatList.Get<std::string>());
			Assert::IsTrue(floatList == strList);

			// Previous To Pointer
			Foo<int> fooA(A), fooB(B);
			RTTI* ptrA[2] = { &fooA, &fooB};
			Datum ptrList(Datum::Pointer);
			ptrList.SetStorage(ptrA, 2);

 			floatList = ptrList;
 			Assert::AreEqual(2U, floatList.Size());
 			Assert::IsTrue(Datum::Pointer == floatList.Type());
 			Assert::IsTrue(ptrA[0] == floatList.Get<RTTI*>());
 			Assert::IsTrue(floatList == ptrList);

		}

		TEST_METHOD(DatumEqualOp)
		{
			Datum unknownList;
			Datum floatList;
			Datum vectorList;
			Datum matrixList;
			Datum stringList;
			Datum ptrList;

			std::int32_t A = 1;
			std::float_t floatA = 1.0;
			glm::vec4 vecA = { 1, 2, 3 ,4 };
			glm::mat4x4 matA = { vecA, vecA, vecA, vecA };
			std::string strA = "Hello";
			Foo<int> fooA(A);
			RTTI* ptrA = &fooA;

			unknownList = A;
			Assert::IsTrue(A == unknownList.Get<std::int32_t>());
			Assert::IsTrue(1 == unknownList.Size());

			floatList = floatA;
			Assert::IsTrue(floatA == floatList.Get<std::float_t>());
			Assert::IsTrue(1 == floatList.Size());

			vectorList = vecA;
			Assert::IsTrue(vecA == vectorList.Get<glm::vec4>());
			Assert::IsTrue(1 == vectorList.Size());

			matrixList = matA;
			Assert::IsTrue(matA == matrixList.Get<glm::mat4x4>());
			Assert::IsTrue(1 == matrixList.Size());

			stringList = strA;
			Assert::IsTrue(strA == stringList.Get<std::string>());
			Assert::IsTrue(1 == stringList.Size());

			ptrList = ptrA;
			Assert::IsTrue(ptrA == ptrList.Get<RTTI*>());
			Assert::IsTrue(1 == ptrList.Size());
		}

		TEST_METHOD(DatumMove)
		{
			Datum intList;
			Datum floatList;
			Datum vectorList;
			Datum matrixList;
			Datum stringList;
			Datum ptrList;
			Datum scopeList;

			std::int32_t A = 1;
			std::float_t floatA = 1.0;
			glm::vec4 vecA = { 1, 2, 3 ,4 };
			glm::mat4x4 matA = { vecA, vecA, vecA, vecA };
			std::string strA = "Hello";
			Foo<int> fooA(A);
			RTTI* ptrA = &fooA;

			intList.Pushback(A);
			floatList.Pushback(floatA);
			vectorList.Pushback(vecA);
			matrixList.Pushback(matA);
			stringList.Pushback(strA); ptrA;

			// MOVE CONSTRUCTOR

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

	_CrtMemState DatumTest::sStartMemState;
}
