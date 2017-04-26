#pragma once

#include <cstdint>

namespace FieaGameEngine
{
	template <typename T>
	class Vector
	{

	private:

		std::uint32_t mSize;
		std::uint32_t mCapacity;
		T *mBuffer;

	public:

		class Iterator
		{
			friend class Vector;
		public:

			/**
			*Default Constructor.
			@result mIndex Is 0 And mOwner Is nullptr.
			*/
			Iterator() : mIndex(0), mOwner(nullptr) {}

			/**
			*Parameterized Constructor.
			@param	rhsIndex	A Const std::unit32_t That is The Location In List To Point To.
			@param rhsOwner		A Const Vector<T> Reference That Is The Owner of This Iterator.
			@result mIndex Is 0 And mOwner Is nullptr.
			*/
			Iterator(const std::uint32_t rhsIndex, const Vector<T>& rhsOwner) : mIndex(rhsIndex), mOwner(&rhsOwner) {}

			/**
			*Copy Constructor.
			@param rhs A Const Iterator Reference To Copy Data From
			@result mIndex = rhs.mIndex And mOwner = rhs.mOwner.
			*/
			Iterator(const Iterator& rhs)
			{
				operator=(rhs);
			}

			/**
			*Overloaded Equal Operator.
			@result Same As Copy Constructor, But With Self Check
			@returns *This
			*/
			Iterator& operator=(const Iterator& rhs)
			{
				if (this != &rhs)
				{
					mIndex = rhs.mIndex;
					mOwner = rhs.mOwner;
				}

				return *this;
			}

			/**
			*Overloaded Prefix Increment
			@exception If Going Out Of Range
			@result Prefix Increment Of mIndex
			@returns *this
			*/
			Iterator& operator++()
			{
				if (mOwner == nullptr || mIndex >= mOwner->mSize)
					throw std::exception("Out Of Range");

				++mIndex;
				return *this;
			}

			/**
			*Overloaded Postfix Increment
			@exception If Going Out Of Range
			@result Prefix Increment Of mIndex
			@returns Copy Of Self Before The Increment
			*/
			Iterator operator++(int)
			{
				Iterator temp(*this);
				operator++();
				return temp;
			}

			
			Iterator& operator--()
			{
				if (mOwner == nullptr)
					throw std::exception("Out Of Range");

				if(mIndex > 0)
					--mIndex;
				return *this;
			}

			Iterator operator--(int)
			{
				Iterator temp(*this);
				operator--();
				return temp;
			}

			/**
			*Overloaded == Operator
			@param rhs A Const Iterator Reference To Compare Self To.
			@returns True If Indices And Owners Are Same For Both, False Otherwise
			*/
			bool operator==(const Iterator& rhs) const
			{
				return ((mIndex == rhs.mIndex) && (mOwner == rhs.mOwner));
			}

			/**
			*Overloaded != Operator
			@param Same As == Operator
			@returns Opposite Of == Operator
			*/
			bool operator!=(const Iterator& rhs) const
			{
				return !(operator==(rhs));
			}

			/**
			*Overloaded Dereference Operator
			@exception If Iterator Points To Something Out Of The List
			@returns A T Reference To Element That Iterator Is Pointing To
			*/
			T& operator*()
			{
				if (mOwner == nullptr || mOwner->isEmpty())
					throw std::exception("Empty List");

				if (mIndex >= mOwner->Size() || mIndex < 0)
					throw std::exception("Out Of Range");

				return mOwner->mBuffer[mIndex];
			}

			const T& operator*() const
			{
				if (mOwner == nullptr || mOwner->Size() == 0)
					throw std::exception("Empty List");

				if (mIndex >= mOwner->Size() || mIndex < 0)
					throw std::exception("Out Of Range");

				return mOwner->mBuffer[mIndex];
			}

		private:
			std::uint32_t mIndex;
			const Vector<T>* mOwner;
		};

		/**
		* Parameterized Constructor.
		@param Capacity A Const Int That Determines How Much Memory To Allocate
		@result Same As Default Constructor, Except mCapacity Is Defined By User
		*/
		explicit Vector(const int Capacity = 10);
		
		/**
		* Copy Constructor.
		@param Original A Const Vector<T> Reference. A Vector With Same Type That Is Being Copied From.
		@result mSize = Original.Size()
		@result mCapacity = Original.Capacity();
		@result mBuffer Is A Memcpy Of Original
		@result mElem Is nullptr
		*/
		Vector(const Vector<T>& Original);
		Vector(Vector<T>&& Original);

		/**
		* Overloaded Equal Operator.
		* Same As Copy Constructor, But Does Self Check And Clears List Before Copying
		*/
		Vector<T>& operator=(const Vector<T>& Original);
		Vector<T>& operator=(Vector<T>&& Original);

		bool operator==(const Vector<T>& Original);
		bool operator==(const Vector<T>& Original) const;

		bool operator!=(const Vector<T>& Original);
		bool operator!=(const Vector<T>& Original) const;

		/**
		*  Overloaded [] Operator.
		@param Index A Const std::uint32_t That Points To An Element In mBuffer
		@exception Out Of Range If Index > mSize Or Index < 0
		@returns An Element From mBuffer At Position Index.
		*/
		T& operator[](const std::uint32_t Index);
		T& operator[](const std::uint32_t Index) const;

		/**
		*  Destructor
		@result Clears List, Deallocates Memory, Zero Out mSize/mCapacity, And Set mBuffer/mElems To nullptr
		*/
		virtual ~Vector();

		/** Push Data to end of the list
		@param	Data	A Const T Reference. The Element To Store In List.
		@result Insert	Data At Size And Increment Size By 1.
		@result Reserve More Space If mSize == mCapacity
		*/
		Iterator	PushBack(const T &Data);

		/** remove the last item from the list
		@result Call The Destructor of Last Element And Decrement mSize By 1
		*/
		void	PopBack();

		/** check if list is empty
		@returns If True If mSize Is 0, False Otherwise
		*/
		bool	isEmpty() const;

		/** return the item in front of the list
		@exception If List Is Empty
		@returns A T Reference To Element Stored In Front Of The List
		*/
		T&		Front();
		const T&	Front() const;

		/** return the item at the end of the list
		@exception If List Is Empty
		@returns A T Reference To Element Stored In Back Of The List
		*/
		T&		Back();
		const T&	Back() const;

		/** return element at position of index
		@result Same As Overloaded [] Operator.
		*/
		T&		At(const std::uint32_t Index);

		/** return the size of list
		@returns The Size Of The List As Type std::uint32_t
		*/
		std::uint32_t Size() const;

		/** return the Capacity of the list
		@returns The Capacity Of The List As Type std::uint32_t
		*/
		std::uint32_t Capacity() const;

		/** clear the list
		@result Same As Destructor
		*/
		void	Clear();

		/** remove an element form the list
		@param Value A Const T Reference. The Value To Be Removed From The List
		@result The Value Was Removed If Found
		*/
		void Remove(const T& Value);

		/** remove a range of elements from the list
		@param Start A Const Iterator<T> Reference. The Starting Point Of Removal.
		@param Last A Const Iterator<T> Reference. The End Point Of Removal.
		@exception Invalid Iterators If Either Start/Last Owners Belong To Different List
		@exception Out Of Range If Either Start/Last Point Outside he List
		@result Values From Start To Last Are Removed From List Inclusively. Elements Past End Are Pushed Down.
		*/
		void Remove(const Iterator& start, const Iterator& last);

		/** reserve a block of memory
		@param Amount A std::uint32_t Value That Is The Amount Of Memory To Reserve (The Capacity)
		@result mBuffer Is Allocated Memory Of Size Amount And mCapacity = Amount
		@result A Memcpy May Be Done If mBuffer Was Not Empty
		*/
		void Reserve(std::uint32_t Amount);

		/** An Iterator<T> Pointing To The Front of List (mIndex = 0)
		@returns An Iterator<T> Pointing To The Front of List (mIndex = 0)
		*/
		Iterator begin() const;

		/** An Iterator<T> Pointing To The End of List (mIndex = Size)
		@returns An Iterator<T> Pointing To The End of List (mIndex = Size)
		*/
		Iterator end() const;

		/** FInd an element in the list
		@param Value A Const T Reference. The Element To Try And Look For.
		@returns An Iterator<T> Pointing To Value If It Exists, Or End() Otherwise.
		*/
		Iterator Find(const T& Value) const;

	};

#include "Vector.inl"	
}

