#pragma once

#include <cstdint>
#include "SList.h"
#include "Vector.h"
#include "HashFunction.h"

namespace FieaGameEngine
{
	template <typename TKey, typename TData, typename HashFunctor = HashFunction<TKey>>
	class HashMap
	{

	private:
		typedef std::pair<TKey, TData>	PairType;
		typedef SList<PairType>			ChainType;
		typedef Vector<ChainType>		BucketType;

		BucketType mBucket;
		std::uint32_t mSize;

	public:
#pragma region ITERATOR

		class Iterator
		{
			friend class HashMap;

		public:
			std::uint32_t mIndex;

			/**
			* Default Constructor.
			@result mIndex = 0, mOwner = nullptr
			*/
			Iterator();

			/**
			* Deconstructor.
			@result mOwner = nullptr
			*/
			~Iterator();

			/**
			* Copy Constructor.
			@param rhs A const Iterator Reference
			@result copy mIndex, mOwner, and mChainit from rhs
			*/
			Iterator(const Iterator& rhs);

			/**
			* Overloaded = Operator.
			@param rhs A const Iterator Reference
			@result Self-check before copy mIndex, mOwner, and mChainit from rhs
			*/
			Iterator& operator=(const Iterator& rhs);

			/**
			* Overloaded Prefix Increment Operator.
			@exception "Invalid Iterator" If mOwner == nullptr
			@result Increment mChainIt. If nullptr, increment mIndex until Bucket[mIndex] is not empty, then set mChainIt to Bucket[mIndex].begin()
			@returns An Iterator pointing to an element in Bucket[mIndex]
			*/
			Iterator& operator++();

			/**
			* Overloaded Postfix Increment Operator
			* Return a copy of self before incrementing
			*/
			Iterator operator++(int);

			/**
			* Overloaded == Operator.
			@param rhs A const Iterator Reference
			@returns A bool comparing mOwner and mIndex, excludes mCHainIt
			*/
			const bool operator==(const Iterator& rhs) const;

			/**
			* Overloaded != Operator. Returns !(Operator==())
			*/
			const bool operator!=(const Iterator& rhs) const;

			/**
			* Overloaded Dereference Operator.
			@returns A PairType, Which Is Dereferenced From mChainIt
			*/
			PairType& operator*();

			PairType& operator*() const;

			/**
			* Overloaded Arrow Dereference Operator.
			@returns A PairType, Which Is Dereferenced From mChainIt
			*/
			PairType* operator->();

			PairType* operator->() const;

		private:

			
			typename ChainType::Iterator mChainIt;
			const HashMap<TKey, TData, HashFunctor>* mOwner;

			Iterator(const HashMap& Owner, const std::uint32_t Index, typename ChainType::Iterator chainIt);
		};
#pragma endregion
		
#pragma region HASHMAP	

		static const std::int32_t defaultCapacity = 25;

		/**
		* Default Constructor. Sets mBucket (A Vector) Capacity To 25 By Default, Or As Desired By User
		@param Capacity A const std::uint32_t.
		@result A PairType, Which Is Dereferenced From mChainIt
		*/
		explicit HashMap(const std::uint32_t Capacity = defaultCapacity);

		/**
		* Copy Constructor. Copies Bucket and mSize From Another Hashmap.
		@param Original A Const Hashmap Reference
		@result A PairType, Which Is Dereferenced From mChainIt
		*/
		HashMap(const HashMap& Original);
		HashMap(HashMap&& Original);

		/**
		* Overloaded Equal Operator. Same As Copy Constructor, But clears Buckets
		@param Capacity A const std::uint32_t.
		@result A PairType, Which Is Dereferenced From mChainIt
		*/
		HashMap& operator=(const HashMap& Original);
		HashMap& operator=(HashMap&& Original);


		~HashMap() = default;

		/**
		* Overloaded Bracket Operator. Calls Insert On Key and returns TData of either an existing location of Key was
		* already in the list, or a new TData if Key was not in the list
		@param Index A Const TKey Reference
		@returns A reference to a TData that was stored at TKey.
		*/
		TData& operator[](const TKey& Index);

		/**
		* Overloaded COnst Bracket Operator. Returns an existing TData if it was found with Key
		@exception "No Item Found" if there is no existing pair containing key
		@param Index A Const TKey Reference
		@returns A reference to a TData that was stored at TKey.
		*/
		const TData& operator[](const TKey& Index) const;

		/**
		*  Returns an existing TData if it was found with Key
		@exception "No Item Found" if there is no existing pair containing key
		@param Index A Const TKey Reference
		@returns A reference to a TData that was stored at TKey.
		*/
		TData& At(const TKey& Key);
		const TData& At(const TKey& Key) const;

		/**
		*Returns an iterator pointing to pair containing Key
		@param Key A Const TKey Reference
		@returns An iterator pointing to pair containing Key
		*/
		Iterator Find(const TKey& Key);
		const Iterator Find(const TKey& Key) const;

		/**
		* Insert Data By Hashing TKey To Find An Index Into A Bucket, And Calls Pushback On THe SList Of That Location
		@param Key A Const PairType Reference
		@returns An iterator pointing to where Data was stored
		*/
		Iterator Insert(const PairType& Data, bool* isInserted = false);

		/**
		* Call Find() On Key And Remove It From List if Found
		@param Key A Const TKey Reference
		@result If found, pair containing key is removed from list.
		*/
		void Remove(const TKey& Key);

		/**
		* Loop through buckets and call Clear()
		@result An empty vector (mBucket) that maintains capacity
		*/
		void Clear();

		/**
		* Amount of elements stored across all buckets
		@returns Amount of elements stored across all buckets
		*/
		std::uint32_t Size();
		const std::uint32_t Size() const;

		/**
		* returns True or false if Key was found
		@param Key A COnst TKey Reference
		@returns True or false if Key was found
		*/
		bool ContainsKey(const TKey& Key);
		const bool ContainsKey(const TKey& Key) const;

		/**
		* returns Iterator pointing to "front" of list. Front Is the top of the first non-empty bucket
		@returns Iterator pointing to "front" of list
		*/
		Iterator begin() const;

		/**
		* returns Iterator pointing to "back" of list. Back is size of vector, since it is 1 past the end of the list
		@returns Iterator pointing to "back" of list
		*/
		Iterator end() const;
#pragma endregion

	};

#include "HashMap.inl"	
}
