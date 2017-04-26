#pragma once

#include <cstdint>

namespace FieaGameEngine
{
	template <typename T>
	class SList
	{

	private:

		/**
		* Node Struct: contains pointer to another node and Data of type T
		* Also, contains constructor to set Data and *Next to some input value and nullptr respectively
		*/
		template <typename T>
		struct Node
		{
			Node* mNext;
			T mData;

			Node(const T &Data, Node *Next) : mData(Data), mNext(Next) {}
		};

		Node<T>* mFront;
		Node<T>* mBack;
		std::uint32_t mSize;

	public:

		class Iterator
		{

		public:
			/**
			* Default ConStructer: sets node and container pointers to nullptr
			*/
			Iterator() : mNode(nullptr), mOwner(nullptr) {}

			/**
			* Default ConStructer
			@param	rhsNode		a Node reference
			@param	rhsOwner	a const SList<T> reference
			*/
			Iterator(Node<T>& rhsNode, const SList<T>& rhsOwner) : mNode(&rhsNode), mOwner(&rhsOwner) {}

			/**
			* Default ConStructer
			@param	rhsOwner	a const SList<T> reference
			*/
			Iterator(const SList<T>& rhsOwner) : mNode(nullptr), mOwner(&rhsOwner) {}

			/**
			* Copy Constructor
			@param	rhs		a const Iterator reference
			*/
			Iterator(const Iterator& rhs)
			{
				mNode = rhs.mNode;
				mOwner = rhs.mOwner;
			}

			/**
			* Overloaded Equal Operator
			@param	rhs		a const Iterator reference
			@returns this pointer after deep copy of rhs
			*/
			Iterator& operator=(const Iterator& rhs)
			{
				if (this != &rhs)
				{
					mNode = rhs.mNode;
					mOwner = rhs.mOwner;
				}

				return *this;
			}

			/**
			* Prefix Increment Operator: point to next node and return *this
			@exception	std::exception out of range
			@returns pointer to an iterator that points to next node
			*/
			Iterator& operator++()
			{
				if (mNode == nullptr)
					throw std::exception("Out Of Range");

				mNode = mNode->mNext;
				return *this;
			}

			/**
			* Postfix Increment: Make a copy of iterator, point to next node, and return copy
			@exception	std::exception out of range
			@returns pointer to an iterator copy that points to next node
			*/
			Iterator operator++(int)
			{
				Iterator temp(*this);
				operator++();
				return temp;
			}

			/**
			* Overloaded == Operator
			@param	rhs		a const Iterator reference
			@returns bool if this iterator == rhs
			*/
			bool operator==(const Iterator& rhs) const
			{
				return ((mNode == rhs.mNode) && (mOwner == rhs.mOwner));
			}

			/**
			* Overloaded != Operator
			@param	rhs		a const Iterator reference
			@returns bool if this iterator != rhs
			*/
			bool operator!=(const Iterator& rhs) const
			{
				return !(operator==(rhs));
			}

			/**
			* Overloaded Dereference Operator
			@exception std::exception empty list
			@returns data stored in node
			*/
			T& operator*() const
			{
				if (mNode == nullptr)
					throw std::exception("Empty List");

				return mNode->mData;
			}

			Node<T>* mNode;
			const SList<T>* mOwner;
		};


		/**
		* Constructor that sets mFront and mBack pointers to nullptr and mSize to 0.
		*/
		SList();

		/**
		* Copy Constructor. Copies another Slist variable by using the Pushback function.
		@param	Original	a constant SList<T> reference
		*/
		SList(const SList<T>& Original);
		SList(SList<T>&& Original);

		/**
		* Overloaded Equal Operator. Operates the same way as Copy Constructor.
		@param	Original	a consant SList<T> reference
		@return This pointer with a deep copy of Original
		*/
		SList<T>& operator=(const SList<T>& Original);
		SList<T>& operator=(SList<T>&& Original);

		/**
		* Destructor. Deallocates memory in mFront and mBack.
		*/
		virtual ~SList();

		/** Push Data To Front Of List
		@param	Data	a constant T reference
		@result Data put in front of list
		*/
		Iterator	PushFront(const T &Data);

		/** Remove item from front of list
		@result Remove item from front of list
		*/
		void	PopFront();

		/** Remove item from front of list and return its value
		@exception std::exception list is empty
		@result Remove item from front of the list
		@return Item from front of the list
		*/
		T PopFrontWithReturn();

		/** Push Data to back of the list
		@param	Data	a constant T reference
		@result Data put in back of list
		*/
		Iterator	PushBack(const T &Data);

		/** return a bool if list is empty
		@return If list is empty
		*/
		bool	isEmpty() const;

		/** return value in front of the list
		@exception  std::exception list is empty
		@returns First value in list if not empty
		*/
		T&		Front();
		T&	Front() const;

		/** return value in back of the list
		@exception std::exception list is empty
		@returns last value in list if not empty
		*/
		T&		Back();
		T&	Back() const;

		/**return size of the list
		@returns size of list
		*/
		std::uint32_t Size() const;

		/** clear the list
		@result clear the list
		*/
		void	Clear();

		/** return iterator point to front of list
		@return Iterator pointing to front of list
		*/
		Iterator begin() const;

		/** return Iterator pointing to end of list (mNode == nullptr)
		@return Iterator pointing to end of list (mNode == nullptr)
		*/
		Iterator end() const;

		/** Insert data at next location
		@param	Data	a const T reference
		@param	It		an Iterator<T> reference
		@returns an Iterator pointing at inserted element
		*/
		Iterator InsertAfter(const T &Data, Iterator &It);

		/** Find the desired value in list
		@param	Value	a const T reference
		@return Iterator pointing to desired element if found, or end() if not found
		*/
		Iterator Find(const T& Value) const;

		/** Remove the value from list
		@param	Value	a const T reference
		@returns bool if element was removed or not
		@result desired element was removed if it existed
		*/
		bool Remove(const T& Value);

	};

#include "SList.inl"	
}

