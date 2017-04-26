#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopTest
{
	TEST_CLASS(HashMapTest)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
#ifdef _DEBUG
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
#endif
		}

		TEST_METHOD(HashMapConstructorAndInsert)
		{
			HashMap<int, double> list;
			HashMap<int*, double> listIntStar;
			HashMap<char*, int> listChar;
			HashMap<std::string, int> listString;

			int a = 1;
			double b = 2;
			char* aStar = "Hello";
			bool inserted = false;

			std::pair<int, double> pair(a, b);
			std::pair<int*, double> pairIntStar(&a, b);
			std::pair<char*, int> pairChar(aStar, a);
			std::pair<std::string, int> pairString(aStar, a);

			// Insert Data, Check Size == 1
			list.Insert(pair, &inserted);
			Assert::AreEqual(1U, list.Size());
			Assert::AreEqual(true, inserted);

			listIntStar.Insert(pairIntStar, &inserted);
			Assert::AreEqual(1U, list.Size());
			Assert::AreEqual(true, inserted);

			listChar.Insert(pairChar, &inserted);
			Assert::AreEqual(1U, listChar.Size());
			Assert::AreEqual(true, inserted);

			listString.Insert(pairString, &inserted);
			Assert::AreEqual(1U, listString.Size());
			Assert::AreEqual(true, inserted);

			// Insert Same Data, Position Should Be The Same Therefore List Is Unmodified
			
			list.Insert(pair, &inserted);
			Assert::AreEqual(1U, list.Size());
			Assert::AreEqual(false, inserted);

			listIntStar.Insert(pairIntStar, &inserted);
			Assert::AreEqual(1U, list.Size());
			Assert::AreEqual(false, inserted);

			listChar.Insert(pairChar, &inserted);
			Assert::AreEqual(1U, list.Size());
			Assert::AreEqual(false, inserted);

			listString.Insert(pairString, &inserted);
			Assert::AreEqual(1U, listString.Size());
			Assert::AreEqual(false, inserted);
		}

		TEST_METHOD(HashMapCopyConstructor)
		{
			HashMap<int, double> list;
			HashMap<int*, double> listIntStar;
			HashMap<char*, int> listChar;
			HashMap<std::string, int> listString;

			int a = 1;
			int c = 3;
			double b = 2;
			char* aStar = "Hello";
			char* bStar = "Bye";

			std::pair<int, double> pair(a, b);
			std::pair<int, double> pair2((int)b, a);
			std::pair<int*, double> pairIntStar(&a, b);
			std::pair<int*, double> pairIntStar2(&c, b);
			std::pair<char*, int> pairChar(aStar, a);
			std::pair<char*, int> pairChar2(bStar, a);
			std::pair<std::string, int> pairString(aStar, a);
			std::pair<std::string, int> pairString2(bStar, a);

			list.Insert(pair);
			listIntStar.Insert(pairIntStar);
			listChar.Insert(pairChar);
			listString.Insert(pairString);
			
			HashMap<int, double> copy(list);
			HashMap<int*, double> intStarCopy(listIntStar);
			HashMap<char*, int> charCopy(listChar);
			HashMap<std::string, int> stringCopy(listString);
			copy.Insert(pair2);
			intStarCopy.Insert(pairIntStar2);
			charCopy.Insert(pairChar2);
			stringCopy.Insert(pairString2);

			// Size Of Each Are Different
			Assert::AreEqual(1U, list.Size());
			Assert::AreEqual(2U, copy.Size());

			Assert::AreEqual(1U, listIntStar.Size());
			Assert::AreEqual(2U, intStarCopy.Size());

			Assert::AreEqual(1U, listChar.Size());
			Assert::AreEqual(2U, charCopy.Size());

			Assert::AreEqual(1U, listString.Size());
			Assert::AreEqual(2U, stringCopy.Size());
		}

		TEST_METHOD(HashMapBracketAndContain)
		{
			HashMap<int, double> list;
			HashMap<int*, double> listIntStar;
			HashMap<char*, int> listChar;
			HashMap<std::string, int> listString;

			int a = 1;
			double b = 18;
			char* aStar = "Hello";

			std::pair<int, double> pair(a, b);
			std::pair<int*, double> pairIntStar(&a, b);
			std::pair<char*, int> pairChar(aStar, a);
			std::pair<std::string, int> pairString(aStar, a);

			list.Insert(pair);
			listIntStar.Insert(pairIntStar);
			listChar.Insert(pairChar);
			listString.Insert(pairString);

			Assert::AreEqual(pair.second, list[a]);
			Assert::AreEqual(true, list.ContainsKey(a));
			Assert::AreEqual(pair.second, list.At(a));

			Assert::AreEqual(pairIntStar.second, listIntStar[&a]);
			Assert::AreEqual(true, listIntStar.ContainsKey(&a));
			Assert::AreEqual(pairIntStar.second, listIntStar.At(&a));

			Assert::AreEqual(pairChar.second, listChar[aStar]);
			Assert::AreEqual(true, listChar.ContainsKey(aStar));
			Assert::AreEqual(pair.second, list.At(a));

			Assert::AreEqual(pairString.second, listString[aStar]);
			Assert::AreEqual(true, listString.ContainsKey(aStar));
			Assert::AreEqual(pairString.second, listString.At(aStar));
		}

		TEST_METHOD(HashMapFind)
		{
			HashMap<int, double> list;
			HashMap<int*, double> listIntStar;
			HashMap<char*, int> listChar;
			HashMap<std::string, int> listString;

			int a = 1;
			int c = 3;
			double b = 18;
			char* aStar = "Hello";
			char* bStar = "Bye";

			std::pair<int, double> pair(a, b);
			std::pair<int, double> pair2((int)b, a);
			std::pair<int*, double> pairIntStar(&a, b);
			std::pair<int*, double> pairIntStar2(&c, a);
			std::pair<char*, int> pairChar(aStar, a);
			std::pair<char*, int> pairChar2(bStar, a);
			std::pair<std::string, int> pairString(aStar, a);
			std::pair<std::string, int> pairString2(bStar, a);

			list.Insert(pair);
			list.Insert(pair2);
			listIntStar.Insert(pairIntStar);
			listIntStar.Insert(pairIntStar2);
			listChar.Insert(pairChar);
			listChar.Insert(pairChar2);
			listString.Insert(pairString);
			listString.Insert(pairString2);

			// <Int, Double>
			HashMap<int, double>::Iterator it = list.Find(a);
			Assert::AreEqual(pair.second, (*it).second);

			it = list.Find((int)b);
			Assert::AreEqual(pair2.second, (*it).second);

			// <Int*, Double>
			HashMap<int*, double>::Iterator itIntStar = listIntStar.Find(&a);
			Assert::AreEqual(pairIntStar.second, (*itIntStar).second);

			itIntStar = listIntStar.Find(&c);
			Assert::AreEqual(pairIntStar2.second, (*itIntStar).second);

			// <Char*, Double>
			HashMap<char*, int>::Iterator itChar = listChar.Find(aStar);
			Assert::AreEqual(pairChar.second, (*itChar).second);

			itChar = listChar.Find(bStar);
			Assert::AreEqual(pairChar2.second, (*itChar).second);

			// <String, Double>
			HashMap<std::string, int>::Iterator itString = listString.Find(aStar);
			Assert::AreEqual(pairString.second, (*itString).second);

			itString = listString.Find(bStar);
			Assert::AreEqual(pairString2.second, (*itString).second);
		}

		TEST_METHOD(HashMapRemove)
		{
			HashMap<int, double> list;
			HashMap<int*, double> listIntStar;
			HashMap<char*, int> listChar;
			HashMap<std::string, int> listString;

			int a = 1;
			int c = 3;
			double b = 18;
			char* aStar = "Hello";
			char* bStar = "Bye";

			std::pair<int, double> pair(a, b);
			std::pair<int, double> pair2((int)b, a);
			std::pair<int*, double> pairIntStar(&a, b);
			std::pair<int*, double> pairIntStar2(&c, a);
			std::pair<char*, int> pairChar(aStar, a);
			std::pair<char*, int> pairChar2(bStar, a);
			std::pair<std::string, int> pairString(aStar, a);
			std::pair<std::string, int> pairString2(bStar, a);

			list.Insert(pair);
			list.Insert(pair2);
			listIntStar.Insert(pairIntStar);
			listIntStar.Insert(pairIntStar2);
			listChar.Insert(pairChar);
			listChar.Insert(pairChar2);
			listString.Insert(pairString);
			listString.Insert(pairString2);

			list.Remove(a);
			list.Remove(a); // Returns Unmodified List
			Assert::AreEqual(1U, list.Size());
			Assert::AreEqual(false, list.ContainsKey(a));
			Assert::AreEqual(true, list.ContainsKey((int)b));

			listIntStar.Remove(&a);
			listIntStar.Remove(&a);
			Assert::AreEqual(1U, listIntStar.Size());
			Assert::AreEqual(false, listIntStar.ContainsKey(&a));
			Assert::AreEqual(true, listIntStar.ContainsKey(&c));

			listChar.Remove(aStar);
			listChar.Remove(aStar);
			Assert::AreEqual(1U, listChar.Size());
			Assert::AreEqual(false, listChar.ContainsKey(aStar));
			Assert::AreEqual(true, listChar.ContainsKey(bStar));

			listString.Remove(aStar);
			listString.Remove(aStar);
			Assert::AreEqual(1U, listString.Size());
			Assert::AreEqual(false, listString.ContainsKey(aStar));
			Assert::AreEqual(true, listString.ContainsKey(bStar));
		}

		TEST_METHOD(HashMapExceptions)
		{
			HashMap<int, int> list;
			const HashMap<int, int>* list2 = &list;

			int a = 1;
			int b = 18;
			std::pair<int, int> pair(a, b);

			auto exceptionAt = [&list, &a] {list.At(a); };
			Assert::ExpectException<std::exception>(exceptionAt);

			auto exceptionAtConst = [&list2, &a] {(*list2).At(a); };
			Assert::ExpectException<std::exception>(exceptionAtConst);
		}

		TEST_METHOD(HashMapFoo)
		{
			HashMap<Foo<int>, int, Foo<int>> list; 

			int a = 4;
			int b = 3;
			Foo<int> foo(a);
			Foo<int> foo2(b);
			std::pair<Foo<int>, int> pair(foo, b);
			std::pair<Foo<int>, int> pair2(foo2, a);

			list.Insert(pair);
			Assert::AreEqual(1U, list.Size());

			// Copy
			HashMap<Foo<int>, int, Foo<int>> copy(list);
			copy.Insert(pair2);

			// Size Are Different After Insert In Copy
			Assert::AreEqual(1U, list.Size());
			Assert::AreEqual(2U, copy.Size());

			// Bracket, Contains Key, At()
			Assert::AreEqual(pair.second, copy[foo]);
			Assert::AreEqual(true, copy.ContainsKey(foo));
			Assert::AreEqual(pair.second, copy.At(foo));

			// Find
			HashMap<Foo<int>, int, Foo<int>>::Iterator it = list.Find(foo);
			Assert::AreEqual(pair.second, (*it).second);

			// Remove
			copy.Remove(foo);
			Assert::AreEqual(1U, copy.Size());
			Assert::AreEqual(false, copy.ContainsKey(foo));
			Assert::AreEqual(true, copy.ContainsKey(foo2));

		}

		TEST_METHOD(HashMapUnchecked)
		{
			HashMap<int, int> list;
			const HashMap<int, int>* list2 = &list;

			int a = 2;
			int b = 3;
			int c = 4;

			std::pair<int, int> pair(a, b);
			std::pair<int, int> pair2(b, a);
			std::pair<int, int> pair3(c, a*b);

			list.Insert(pair);
			list.Insert(pair2);

			Assert::AreEqual(pair.second, (*list2)[a]);
			Assert::AreEqual(false, (*list2).ContainsKey(c));
			Assert::AreEqual(false, list.ContainsKey(c));

			list.Remove(c);
			Assert::AreEqual(2U, (*list2).Size());

			HashMap<int, int>::Iterator It = list.begin();
			Assert::AreEqual(pair.second, (It++)->second);

			const HashMap<int, int>::Iterator constIt = list.begin();
			Assert::AreEqual(pair.second, constIt->second);
			Assert::AreEqual(pair.second, (*constIt).second);

			It.~Iterator();
		}

		TEST_METHOD(HashMapMove)
		{
			HashMap<int, int> list;
			int a = 1, b = 2, c = 3;
			std::pair<int, int> pair(a, b), pair2(b, c), pair3(c, a);

			list.Insert(pair);
			list.Insert(pair2);
			list.Insert(pair3);

			HashMap<int, int> list2 = std::move(list);
			Assert::IsTrue(0 == list.Size());
			Assert::IsTrue(3 == list2.Size());
			Assert::IsTrue(c == list2[b]);

			HashMap<int, int> list3;
			list3 = std::move(list2);
			Assert::IsTrue(0 == list.Size());
			Assert::IsTrue(0 == list2.Size());
			Assert::IsTrue(3 == list3.Size());
			Assert::IsTrue(a == list3[c]);
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

	_CrtMemState HashMapTest::sStartMemState;
}