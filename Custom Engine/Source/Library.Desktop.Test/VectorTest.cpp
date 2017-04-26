
#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopTest
{
	TEST_CLASS(VectorTest)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
#ifdef _DEBUG
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
#endif
		}

		TEST_METHOD(VectorConstructor)
		{
			std::uint32_t size = 0;
			std::uint32_t capacity = 10;

			Vector<int> intV;
			Vector<int*> ptrV;
			Vector<SList<int>> fooV;

			// Default Constructor
			Assert::AreEqual(size, intV.Size());
			Assert::AreEqual(capacity, intV.Capacity());

			Assert::AreEqual(size, ptrV.Size());
			Assert::AreEqual(capacity, ptrV.Capacity());

			Assert::AreEqual(size, fooV.Size());
			Assert::AreEqual(capacity, fooV.Capacity());

			// Destructor
			intV.~Vector();
			ptrV.~Vector();
			fooV.~Vector();

			Assert::AreEqual(size, intV.Size());
			Assert::AreEqual(0U, intV.Capacity());

			Assert::AreEqual(size, ptrV.Size());
			Assert::AreEqual(0U, ptrV.Capacity());

			Assert::AreEqual(size, fooV.Size());
			Assert::AreEqual(0U, fooV.Capacity());
		}

		TEST_METHOD(VectorCopyConstructor)
		{
			std::uint32_t size = 1;
			std::uint32_t capacity = 10;

			Vector<int> intV(capacity);
			Vector<int*> ptrV(capacity);
			Vector<Foo<int>> fooV(capacity);

			int a = 1;
			Foo<int> foo(a);

			intV.PushBack(a);
			ptrV.PushBack(&a);
			fooV.PushBack(foo);

			//Create Copy
			Vector<int> intCopy(intV);
			Vector<int*> ptrCopy(ptrV);

			Assert::AreEqual(intV[0], intCopy[0]);
			Assert::AreEqual(ptrV[0], ptrCopy[0]);

			// Check Size/Capacity Did Not Change
			Assert::AreEqual(size, intCopy.Size());
			Assert::AreEqual(capacity, intCopy.Capacity());

			Assert::AreEqual(size, ptrCopy.Size());
			Assert::AreEqual(capacity, ptrCopy.Capacity());

		}

		TEST_METHOD(VectorExceptions)
		{
			Vector<int> v;
			Vector<int*> ptrV;
			Vector<Foo<int>> fooV;

			Assert::AreEqual(true, v.isEmpty());
			Assert::AreEqual(true, ptrV.isEmpty());
			Assert::AreEqual(true, fooV.isEmpty());

			//Bracket Exceptions
			auto bracketException = [&v] {v[0]; };
			Assert::ExpectException<std::exception>(bracketException);

			auto bracketExceptionPtr = [&ptrV] {ptrV[0]; };
			Assert::ExpectException<std::exception>(bracketExceptionPtr);

			auto bracketExceptionFoo = [&fooV] {fooV[0]; };
			Assert::ExpectException<std::exception>(bracketExceptionFoo);

			// At() Exceptions
			auto atException = [&v] {v.At(1); };
			Assert::ExpectException<std::exception>(atException);

			auto atExceptionPtr = [&ptrV] {ptrV.At(1); };
			Assert::ExpectException<std::exception>(atExceptionPtr);

			auto atExceptionFoo = [&fooV] {fooV.At(1); };
			Assert::ExpectException<std::exception>(atExceptionFoo);

			// Front/Back Exceptions
			auto frontException = [&v] {v.Front(); };
			Assert::ExpectException<std::exception>(frontException);

			auto frontExceptionPtr = [&ptrV] {ptrV.Front(); };
			Assert::ExpectException<std::exception>(frontExceptionPtr);

			auto frontExceptionFoo = [&fooV] {fooV.Front(); };
			Assert::ExpectException<std::exception>(frontExceptionFoo);

			auto backException = [&v] {v.Back(); };
			Assert::ExpectException<std::exception>(backException);

			auto backExceptionPtr = [&ptrV] {ptrV.Back(); };
			Assert::ExpectException<std::exception>(backExceptionPtr);

			auto backExceptionFoo = [&fooV] {fooV.Back(); };
			Assert::ExpectException<std::exception>(backExceptionFoo);

			// Iterator Increment Exceptions
			int a = 0;

			auto incrementException = [&v, &a] {Vector<int>::Iterator It(a, v); ++It; };
			Assert::ExpectException<std::exception>(incrementException);

			auto incrementExceptionPtr = [&ptrV, &a] {Vector<int*>::Iterator It(a, ptrV); ++It; };
			Assert::ExpectException<std::exception>(frontExceptionPtr);

			auto incrementExceptionFoo = [&fooV, &a] {Vector<Foo<int>>::Iterator It(a, fooV); ++It; };
			Assert::ExpectException<std::exception>(incrementExceptionFoo);

			// Iterator Dereference Empty List Exceptions
			auto dereferenceException = [&v, &a] {Vector<int>::Iterator It(a, v); int fail = *It; v.PushBack(fail); };
			Assert::ExpectException<std::exception>(dereferenceException);

			auto dereferenceExceptionPtr = [&ptrV, &a] {Vector<int*>::Iterator It(a, ptrV); int* fail = *It; ptrV.PushBack(fail); };
			Assert::ExpectException<std::exception>(dereferenceExceptionPtr);

			auto dereferenceExceptionFoo = [&fooV, &a] {Vector<Foo<int>>::Iterator It(a, fooV); Foo<int> fail = *It; fooV.PushBack(fail); };
			Assert::ExpectException<std::exception>(dereferenceExceptionFoo);

			// Iterator Dereference Out Of Range Exceptions
			auto dereferenceException2 = [&v, &a] {Vector<int>::Iterator It(5, v); v.PushBack(a); int fail = *It;  v.PushBack(fail); };
			Assert::ExpectException<std::exception>(dereferenceException2);

			auto dereferenceExceptionPtr2 = [&ptrV, &a] {Vector<int*>::Iterator It(5, ptrV); ptrV.PushBack(&a); int* fail = *It;  ptrV.PushBack(fail); };
			Assert::ExpectException<std::exception>(dereferenceExceptionPtr2);

			Foo<int> foo(a);
			auto dereferenceExceptionFoo2 = [&fooV, &a, &foo] {Vector<Foo<int>>::Iterator It(5, fooV); fooV.PushBack(foo); Foo<int> fail = *It; fooV.PushBack(fail); };
			Assert::ExpectException<std::exception>(dereferenceExceptionFoo2);
		}

		TEST_METHOD(VectorPushPop)
		{
			std::uint32_t size = 5;
			std::uint32_t capacity = 5;
			Vector<int> intV(capacity);
			Vector<int*> ptrV(capacity);
			Vector<Foo<int>> fooV(capacity);

			int a = 0;
			int b = 1;
			int c = 2;
			int d = 3;
			int e = 4;
			Foo<int> fooA(a);
			Foo<int> fooB(b);
			Foo<int> fooC(c);
			Foo<int> fooD(d);
			Foo<int> fooE(e);

			// Initialize Vectors
			for (int i = 0; i < (int)size; ++i)
			{
				intV.PushBack(i);
			}
			ptrV.PushBack(&a);
			ptrV.PushBack(&b);
			ptrV.PushBack(&c);
			ptrV.PushBack(&d);
			ptrV.PushBack(&e);

			fooV.PushBack(fooA);
			fooV.PushBack(fooB);
			fooV.PushBack(fooC);
			fooV.PushBack(fooD);
			fooV.PushBack(fooE);

			// Test Front/Back
			Assert::AreEqual(a, intV.Front());
			Assert::AreEqual(e, intV.Back());

			Assert::AreEqual(&a, ptrV.Front());
			Assert::AreEqual(&e, ptrV.Back());

			Assert::AreEqual(*fooA, *fooV.Front());
			Assert::AreEqual(*fooE, *fooV.Back());

			// Test [] And At()
			for (int i = 0; i < (int)size; ++i)
			{
				Assert::AreEqual(i, intV[i]);
				Assert::AreEqual(i, intV.At(i));
			}
			Assert::AreEqual(&a, ptrV[a]);
			Assert::AreEqual(&a, ptrV.At(a));
				
			Assert::AreEqual(*fooB, *fooV[1]);
			Assert::AreEqual(*fooB, *fooV.At(1));

			// Pushback To Cause A Resize
			intV.PushBack(a);
			ptrV.PushBack(&a);
			fooV.PushBack(fooA);

			Assert::AreEqual(capacity+5, intV.Capacity());
			Assert::AreEqual(size+1, intV.Size());
			Assert::AreEqual(a, intV.Front());
			Assert::AreEqual(a, intV.Back());

			Assert::AreEqual(capacity + 5, ptrV.Capacity());
			Assert::AreEqual(size + 1, ptrV.Size());
			Assert::AreEqual(&a, ptrV.Front());
			Assert::AreEqual(&a, ptrV.Back());

			Assert::AreEqual(capacity + 5, fooV.Capacity());
			Assert::AreEqual(size + 1, fooV.Size());
			Assert::AreEqual(*fooA, *fooV.Front());
			Assert::AreEqual(*fooA, *fooV.Back());

			// Test Popback
			intV.PopBack();
			ptrV.PopBack();
			fooV.PopBack();

			Assert::AreEqual(capacity + 5, intV.Capacity());
			Assert::AreEqual(size, intV.Size());
			Assert::AreEqual(a, intV.Front());
			Assert::AreEqual(e, intV.Back());

			Assert::AreEqual(capacity + 5, ptrV.Capacity());
			Assert::AreEqual(size, ptrV.Size());
			Assert::AreEqual(&a, ptrV.Front());
			Assert::AreEqual(&e, ptrV.Back());

			Assert::AreEqual(capacity + 5, fooV.Capacity());
			Assert::AreEqual(size, fooV.Size());
			Assert::AreEqual(*fooA, *fooV.Front());
			Assert::AreEqual(*fooE, *fooV.Back());
		}

		TEST_METHOD(VectorIteratorBeginEnd)
		{
			std::uint32_t size = 5;
			std::uint32_t capacity = 10;
			Vector<int> intV(capacity);
			Vector<int*> ptrV(capacity);
			Vector<Foo<int>> fooV(capacity);

			int a = 0;
			int b = 1;
			int c = 2;
			int d = 3;
			int e = 4;

			for (int i = 0; i < (int)size; ++i)
			{
				intV.PushBack(i);
			}
			ptrV.PushBack(&a);
			ptrV.PushBack(&b);
			ptrV.PushBack(&c);
			ptrV.PushBack(&d);
			ptrV.PushBack(&e);

			fooV.PushBack(Foo<int>(a));
			fooV.PushBack(Foo<int>(b));
			fooV.PushBack(Foo<int>(c));
			fooV.PushBack(Foo<int>(d));
			fooV.PushBack(Foo<int>(e));

			// Test Begin
			Vector<int>::Iterator It = intV.begin();
			Vector<int*>::Iterator ptrIt = ptrV.begin();
			Vector<Foo<int>>::Iterator fooIt = fooV.begin();

			Assert::AreEqual(a, *It);
			Assert::AreEqual(&a, *ptrIt);
			Assert::AreEqual(*Foo<int>(a), **fooIt);

			//Test End
			auto Exception = [&intV, &It] {It = intV.end(); int fail = *It; intV.PushBack(fail); };
			Assert::ExpectException<std::exception>(Exception);

			auto ExceptionPtr = [&ptrV, &ptrIt] {ptrIt = ptrV.end(); int* fail = *ptrIt; ptrV.PushBack(fail); };
			Assert::ExpectException<std::exception>(ExceptionPtr);

			auto ExceptionFoo = [&fooV, &fooIt] {fooIt = fooV.end(); Foo<int> fail = *fooIt; fooV.PushBack(fail); };
			Assert::ExpectException<std::exception>(ExceptionFoo);
		}

		TEST_METHOD(VectorIteratorFind)
		{
			std::uint32_t size = 5;
			std::uint32_t capacity = 10;
			Vector<int> intV(capacity);
			Vector<int*> ptrV(capacity);
			Vector<Foo<int>> fooV(capacity);
			
			int a = 0;
			int b = 1;
			int c = 2;
			int d = 3;
			int e = 4;
			int f = 10;
			Foo<int> fooA(a);
			Foo<int> fooB(b);
			Foo<int> fooC(c);
			Foo<int> fooD(d);
			Foo<int> fooE(e);
			Foo<int> fooF(f);

			// Initialize List
			for (int i = 0; i < (int)size; ++i)
			{
				intV.PushBack(i);
			}
			ptrV.PushBack(&a);
			ptrV.PushBack(&b);
			ptrV.PushBack(&c);
			ptrV.PushBack(&d);
			ptrV.PushBack(&e);

			fooV.PushBack(fooA);
			fooV.PushBack(fooB);
			fooV.PushBack(fooC);
			fooV.PushBack(fooD);
			fooV.PushBack(fooE);

			// Find Valid Element
			Vector<int>::Iterator It = intV.Find(c);
			Vector<int*>::Iterator ptrIt = ptrV.Find(&c);
			Vector<Foo<int>>::Iterator fooIt = fooV.Find(fooC);

			Assert::AreEqual(c, *It);
			Assert::AreEqual(&c, *ptrIt);
			Assert::AreEqual(*fooC, **fooIt);

			// Find Invalid Element
			It = intV.Find(f);
			ptrIt = ptrV.Find(&f);
			fooIt = fooV.Find(fooF);
		}

		TEST_METHOD(VectorIteratorRemove)
		{
			std::uint32_t size = 5;
			std::uint32_t capacity = 10;
			Vector<int> intV(capacity);
			Vector<int*> ptrV(capacity);

			int a = 0;
			int b = 1;
			int c = 2;
			int d = 3;
			int e = 4;

			// Initialize List
			for (int i = 0; i < (int)size; ++i)
			{
				intV.PushBack(i);
			}
			ptrV.PushBack(&a);
			ptrV.PushBack(&b);
			ptrV.PushBack(&c);
			ptrV.PushBack(&d);
			ptrV.PushBack(&e);

			// Remove Front
			intV.Remove(a);
			ptrV.Remove(&a);

			Assert::AreEqual(b, intV.Front());
			Assert::AreEqual(e, intV.Back());
			Assert::AreEqual(--size, intV.Size()); // Size = 4, intV = {b, c, d, e}
			for (int i = 1; i < (int)size; ++i)
			{
				Assert::AreEqual(i, intV[i-1]);
			}

			Assert::AreEqual(&b, ptrV.Front());
			Assert::AreEqual(&e, ptrV.Back());
			Assert::AreEqual(size, ptrV.Size());
			Assert::AreEqual(&c, ptrV[1]);

			// Remove Mid
			intV.Remove(c);
			ptrV.Remove(&c);
			Assert::AreEqual(b, intV.Front());
			Assert::AreEqual(e, intV.Back());
			Assert::AreEqual(--size, intV.Size()); // Size = 3, intV = {b, d}

			Assert::AreEqual(&b, ptrV.Front());
			Assert::AreEqual(&e, ptrV.Back());
			Assert::AreEqual(size, ptrV.Size());

			// Remove Invalid
			auto removeException = [&intV] {int notValid = 200; intV.Remove(notValid); };
			auto removeExceptionPtr = [&ptrV] {int notValid = 200; ptrV.Remove(&notValid); };

			Assert::AreEqual(size, intV.Size());
			Assert::AreEqual(size, ptrV.Size());
		}

		TEST_METHOD(VectorIteratorRemoveRange)
		{
			std::uint32_t size = 7;
			std::uint32_t capacity = 10;
			std::uint32_t start = 0;
			std::uint32_t end = 2;

			Vector<int> intV(capacity);
			Vector<int> intV2(capacity);

			
			for (int i = 0; i < (int)size; ++i)
			{
				intV.PushBack(i);
			}

			Vector<int>::Iterator It1(start, intV);
			Vector<int>::Iterator It2(2*size, intV);
			Vector<int>::Iterator It3(end, intV2);
			
			// Check Unequal Owners Exception
			auto removeException = [&intV, &It1, &It3] {intV.Remove(It1, It3); };
			Assert::ExpectException<std::exception>(removeException);

			// Check Out Of Range Exception
			auto removeException2 = [&intV, &It1, &It2] {intV.Remove(It1, It2); };
			Assert::ExpectException<std::exception>(removeException2);

			// Check Remove Was Correct
			It2 = It1; ++It2; ++It2;
			intV.Remove(It1, It2);
			Assert::AreEqual(size - (end - start + 1), intV.Size()); // Size Is Now 4
			for (int i = 0; i < (int)size - 3; ++i)
			{
				Assert::AreEqual(i+3, intV[i]);
			}

		}

		TEST_METHOD(VectorMove)
		{
			Vector<int> intV(10);
			int a = 1, b = 2, c = 3;

			intV.PushBack(a);
			intV.PushBack(b);
			intV.PushBack(c);

			Vector<int> intV2 = std::move(intV);
			Assert::IsTrue(0 == intV.Size());
			Assert::IsTrue(3 == intV2.Size());
			Assert::IsTrue(b == intV2[1]);

			Vector<int> intV3;
			intV3 = std::move(intV2);
			Assert::IsTrue(0 == intV.Size());
			Assert::IsTrue(0 == intV2.Size());
			Assert::IsTrue(3 == intV3.Size());
			Assert::IsTrue(c == intV3[2]);
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

	_CrtMemState VectorTest::sStartMemState;
}