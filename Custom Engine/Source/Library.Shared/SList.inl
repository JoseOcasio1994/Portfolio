		
		template <typename T>
		SList<T>::SList() : mFront(nullptr), mBack(nullptr), mSize(0) {}

		template <typename T>
		SList<T>::SList(const SList<T>& Original) :
		mFront(nullptr), mBack(nullptr), mSize(0)
		{	
			operator=(Original);
		}
		
		template <typename T>
		SList<T>::SList(SList<T>&& Original) :
			mFront(Original.mFront), mBack(Original.mBack), mSize(Original.mSize)
		{
			Original.mFront = nullptr;
			Original.mBack = nullptr;
			Original.mSize = 0;
		}

 		template <typename T>
 		SList<T>& SList<T>::operator=(const SList<T>& Original)
 		{
 			if (this != &Original)
			{
				if (Size() > 0)
					Clear();

				Node<T> *currentOriginal = Original.mFront;
		 
				while (currentOriginal != nullptr)
				{
					PushBack(currentOriginal->mData);
					currentOriginal = currentOriginal->mNext;
				}
			}

			return *this;
 		}

		template <typename T>
		SList<T>& SList<T>::operator=(SList<T>&& Original)
		{
			if (this != &Original)
			{
				Clear();
				mFront = Original.mFront; 
				mBack = Original.mBack;
				mSize = Original.mSize;

				Original.mFront = nullptr;
				Original.mBack = nullptr;
				Original.mSize = 0;
			}

			return *this;
		}

		template <typename T>
		SList<T>::~SList()
		{
			Clear();
		}

		template <typename T>
		typename SList<T>::Iterator SList<T>::PushFront(const T &Data)
		{
			mFront = new Node<T>(Data, mFront);

			if (mBack == nullptr)
			{
				mBack = mFront;
			}

			++mSize;
			return Iterator(*mFront, *this);
		}

		template <typename T>
		void SList<T>::PopFront()
		{
			if (!isEmpty())
			{
				if (mSize == 1)
				{
					mBack = nullptr;
				}

				Node<T>* delNode = mFront;
				mFront = mFront->mNext;
				delete delNode;
				--mSize;
			}
		}

		template <typename T>
		T SList<T>::PopFrontWithReturn()
		{
			if (isEmpty())
				throw std::exception("Can't pop from empty list");

			T Data = mFront->mData;

			PopFront();

			return Data;
		}

		template <typename T>
		typename SList<T>::Iterator SList<T>::PushBack(const T &Data)
		{
			Node<T> *temp = new Node<T>(Data, nullptr);

			if (mFront == nullptr)
			{
				mFront = temp;
			}
			else
			{
				mBack->mNext = temp;
			}
			mBack = temp;

			++mSize;
			return Iterator(*mBack, *this);
		}

		template<typename T>
		bool SList<T>::isEmpty() const
		{
			return Size() == 0;
		}

		template <typename T>
		T& SList<T>::Front()
		{
			if (isEmpty())
				throw std::exception("Empty List");

			return mFront->mData;
		}

		template <typename T>
		T& SList<T>::Front() const
		{
			if (isEmpty())
				throw std::exception("Empty List");

			return mFront->mData;
		}

		template <typename T>
		T& SList<T>::Back() 
		{
			if (isEmpty())
				throw std::exception("Empty List");

			return mBack->mData;
		}

		template <typename T>
		T& SList<T>::Back() const
		{
			if (isEmpty())
				throw std::exception("Empty List");

			return mBack->mData;
		}

		template<typename T>
		std::uint32_t SList<T>::Size() const
		{
			return mSize;
		}

		template <typename T>
		void SList<T>::Clear()
		{
			while (Size() > 0)
			{
				PopFront();
			}
		}

		template <typename T>
		typename SList<T>::Iterator SList<T>::begin() const
		{
			return Iterator(*mFront, *this);
		}

		template <typename T>
		typename SList<T>::Iterator SList<T>::end() const
		{
			return Iterator(*this);
		}

		template <typename T>
		typename  SList<T>::Iterator SList<T>::InsertAfter(const T &Data, Iterator &It)
		{
			if ((It.mNode == mBack) || (It == end() ))
			{
				PushBack(Data);
				return Iterator(*mBack, *this);
			}
			else
			{
				It.mNode->mNext = new Node<T>(Data, It.mNode->mNext);
				++mSize;
				return Iterator(*It.mNode, *this);
			}
		}

		template <typename T>
		typename SList<T>::Iterator SList<T>::Find(const T& Value) const
		{
			SList<T>::Iterator temp = begin();
			
			for (; temp != end(); ++temp)
			{
				if (temp.mNode->mData == Value)
					break;
			}

			return temp;
		}

		template <typename T>
		typename bool SList<T>::Remove(const T& Value)
		{
			SList<T>::Iterator Current = begin();

			// Remove From Front
			if (Current.mNode->mData == Value && Current.mNode == mFront)
			{
				PopFront();
				return true;
			}

			// Remove From Rest
			for (; Current.mNode != mBack; ++Current)
			{
				if (Current.mNode->mNext->mData == Value)
				{
					Node<T> *delNode = Current.mNode->mNext;
					
					if (Current.mNode->mNext == mBack)
					{
						mBack = Current.mNode;
						Current.mNode->mNext = nullptr;
					}
					else
					{
						Current.mNode->mNext = Current.mNode->mNext->mNext;
					}

					delete delNode;
					--mSize;
					return true;
				}
			}

			return false;
		}
