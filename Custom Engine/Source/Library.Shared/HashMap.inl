
#pragma region Iterator

template <typename TKey, typename TData, typename HashFunctor>
HashMap<TKey, TData, HashFunctor>::Iterator::Iterator() :
	mIndex(0), mOwner(nullptr), mChainIt(ChainType)
{

}

template <typename TKey, typename TData, typename HashFunctor>
HashMap<TKey, TData, HashFunctor>::Iterator::Iterator(const HashMap& Owner, const std::uint32_t Index, typename ChainType::Iterator chainIt) :
	mIndex(Index), mOwner(&Owner), mChainIt(chainIt)
{
}

template <typename TKey, typename TData, typename HashFunctor>
HashMap<TKey, TData, HashFunctor>::Iterator::~Iterator()
{
	mIndex = 0;
	mOwner = nullptr;
}

template <typename TKey, typename TData, typename HashFunctor>
HashMap<TKey, TData, HashFunctor>::Iterator::Iterator(const Iterator& rhs) :
	mIndex(0), mOwner(nullptr)
{
	operator=(rhs);
}

template <typename TKey, typename TData, typename HashFunctor>
typename HashMap<TKey, TData, HashFunctor>::Iterator& HashMap<TKey, TData, HashFunctor>::Iterator::operator=(const Iterator& rhs)
{
	if (this != &rhs)
	{
		mIndex = rhs.mIndex;
		mChainIt = rhs.mChainIt;
		mOwner = rhs.mOwner;
	}

	return *this;
}

template <typename TKey, typename TData, typename HashFunctor>
typename HashMap<TKey, TData, HashFunctor>::Iterator& HashMap<TKey, TData, HashFunctor>::Iterator::operator++()
{
	if (mOwner == nullptr)
		throw std::exception("Invalid Iterator");

	if (mIndex == mOwner->mBucket.Size())
		return *this;

	++mChainIt;

	if (mChainIt == mOwner->mBucket[mIndex].end())
	{
		for (++mIndex; mIndex < mOwner->mBucket.Size(); ++mIndex)
		{
			if (mOwner->mBucket[mIndex].Size() > 0)
			{
				mChainIt = mOwner->mBucket[mIndex].begin();
				break;
			}
		}
	}

	return *this;
}

template <typename TKey, typename TData, typename HashFunctor>
typename HashMap<TKey, TData, HashFunctor>::Iterator HashMap<TKey, TData, HashFunctor>::Iterator::operator++(int)
{
	Iterator temp(*this);
	Iterator::operator++();
	return temp;
}

template <typename TKey, typename TData, typename HashFunctor>
const bool HashMap<TKey, TData, HashFunctor>::Iterator::operator==(const Iterator& rhs) const
{
	return ((mIndex == rhs.mIndex) && (mOwner == rhs.mOwner));
}

template <typename TKey, typename TData, typename HashFunctor>
const bool HashMap<TKey, TData, HashFunctor>::Iterator::operator!=(const Iterator& rhs) const
{
	return !(Iterator::operator==(rhs));
}

template <typename TKey, typename TData, typename HashFunctor>
typename HashMap<TKey, TData, HashFunctor>::PairType& HashMap<TKey, TData, HashFunctor>::Iterator::operator*()
{
	return *mChainIt;
}

template <typename TKey, typename TData, typename HashFunctor>
typename HashMap<TKey, TData, HashFunctor>::PairType& HashMap<TKey, TData, HashFunctor>::Iterator::operator*() const
{
	return *mChainIt;
}

template <typename TKey, typename TData, typename HashFunctor>
typename HashMap<TKey, TData, HashFunctor>::PairType* HashMap<TKey, TData, HashFunctor>::Iterator::operator->()
{
	return &(*mChainIt);
}

template <typename TKey, typename TData, typename HashFunctor>
typename HashMap<TKey, TData, HashFunctor>::PairType* HashMap<TKey, TData, HashFunctor>::Iterator::operator->() const
{
	return &(*mChainIt);
}

#pragma endregion

#pragma region HashMap

template <typename TKey, typename TData, typename HashFunctor>
HashMap<TKey, TData, HashFunctor>::HashMap(const std::uint32_t Capacity) :
	mSize(0), mBucket(Capacity)
{
	if (Capacity == 0)
		throw std::exception("Size Must Be Greater Than 0.");

	for (std::uint32_t i = 0; i < mBucket.Capacity(); ++i)
	{
		mBucket.PushBack(ChainType());
	}
	mSize = 0;
}

template <typename TKey, typename TData, typename HashFunctor>
HashMap<TKey, TData, HashFunctor>::HashMap(const HashMap& Original) :
	mSize(0), mBucket(defaultCapacity)
{
	operator=(Original);
}

template <typename TKey, typename TData, typename HashFunctor>
HashMap<TKey, TData, HashFunctor>::HashMap(HashMap&& Original) :
	mSize(Original.mSize), mBucket(std::move(Original.mBucket))
{
	Original.mSize = 0;
	//Original.mBucket.Clear();
}

template <typename TKey, typename TData, typename HashFunctor>
HashMap<TKey, TData, HashFunctor>& HashMap<TKey, TData, HashFunctor>::operator=(const HashMap& Original)
{
	if (this != &Original)
	{
		Clear();
		mBucket = Original.mBucket;
		mSize = Original.Size();
	}

	return *this;
}

template <typename TKey, typename TData, typename HashFunctor>
HashMap<TKey, TData, HashFunctor>& HashMap<TKey, TData, HashFunctor>::operator=(HashMap&& Original)
{
	if (this != &Original)
	{
		Clear();
		mSize = Original.mSize;
		mBucket = std::move(Original.mBucket);

 		Original.mSize = 0;
// 		Original.mBucket.Clear();
	}

	return *this;
}

template <typename TKey, typename TData, typename HashFunctor>
TData& HashMap<TKey, TData, HashFunctor>::operator[](const TKey& key)
{
	return Insert(PairType(key, TData()))->second;
}

template <typename TKey, typename TData, typename HashFunctor>
const TData& HashMap<TKey, TData, HashFunctor>::operator[](const TKey& Index) const
{
	return  At(Index);
}

template <typename TKey, typename TData, typename HashFunctor>
TData& HashMap<TKey, TData, HashFunctor>::At(const TKey& Key)
{
	Iterator iter = Find(Key);

	if (iter == end())
		throw std::exception("Item Not Found");

	return (*iter).second;
}

template <typename TKey, typename TData, typename HashFunctor>
const TData& HashMap<TKey, TData, HashFunctor>::At(const TKey& Key) const
{
	Iterator iter = Find(Key);

	if (iter == end())
		throw std::exception("Item Not Found");

	return (*iter).second;
}

template <typename TKey, typename TData, typename HashFunctor>
typename HashMap<TKey, TData, HashFunctor>::Iterator HashMap<TKey, TData, HashFunctor>::Find(const TKey& Key)
{

	Iterator It = begin(), itEnd = end();

	for (; It != itEnd; ++It)
	{
		if ((*It).first == Key)
			break;
	}

	return It;
}

template <typename TKey, typename TData, typename HashFunctor>
typename const HashMap<TKey, TData, HashFunctor>::Iterator HashMap<TKey, TData, HashFunctor>::Find(const TKey& Key) const
{
	HashMap<TKey, TData, HashFunctor>::Iterator It = begin();

	Iterator itEnd = end();

	for (; It != itEnd; ++It)
	{
		if ((*It).first == Key)
			break;
	}

	return It;
}

template <typename TKey, typename TData, typename HashFunctor>
typename HashMap<TKey, TData, HashFunctor>::Iterator HashMap<TKey, TData, HashFunctor>::Insert(const PairType& Data, bool* isInserted)
{
	static HashFunctor hashfunct;

	std::uint32_t index = hashfunct(const_cast<TKey&>(Data.first)) % mBucket.Capacity();
	ChainType& chain = mBucket[index];
	typename ChainType::Iterator Iter = chain.begin();

	for (; Iter != chain.end(); ++Iter)
	{
		if ((*Iter).first == Data.first)
		{
			if( isInserted != nullptr ) *isInserted = false;
			return Iterator(*this, index, Iter);
		}
	}

	if (isInserted != nullptr) *isInserted = true;
	chain.PushBack(Data);
	++mSize;

	Iter = chain.Find(Data);
	return Iterator(*this, index, Iter);
}

template <typename TKey, typename TData, typename HashFunctor>
void HashMap<TKey, TData, HashFunctor>::Remove(const TKey& Key)
{
	Iterator find = Find(Key);

	if (find == end())
		return;

	mBucket[find.mIndex].Remove(*find);
	--mSize;
}

template <typename TKey, typename TData, typename HashFunctor>
void HashMap<TKey, TData, HashFunctor>::Clear()
{
	for (std::uint32_t i = 0; i < mBucket.Size(); ++i)
	{
		mBucket[i].Clear();
	}
	mSize = 0;
}

template <typename TKey, typename TData, typename HashFunctor>
std::uint32_t HashMap<TKey, TData, HashFunctor>::Size()
{
	return mSize;
}

template <typename TKey, typename TData, typename HashFunctor>
const std::uint32_t HashMap<TKey, TData, HashFunctor>::Size() const
{
	return mSize;
}

template <typename TKey, typename TData, typename HashFunctor>
bool HashMap<TKey, TData, HashFunctor>::ContainsKey(const TKey& Key)
{

	if (Find(Key) == end())
		return false;

	return true;
}

template <typename TKey, typename TData, typename HashFunctor>
const bool HashMap<TKey, TData, HashFunctor>::ContainsKey(const TKey& Key) const
{

	if (Find(Key) == end())
		return false;

	return true;
}

template <typename TKey, typename TData, typename HashFunctor>
typename  HashMap<TKey, TData, HashFunctor>::Iterator HashMap<TKey, TData, HashFunctor>::begin() const
{
	if (mSize == 0)
		return end();

	for (std::uint32_t i = 0; i < mBucket.Size(); ++i)
	{
		if (mBucket[i].Size() > 0)
		{
			return Iterator(*this, i, mBucket[i].begin());
		}
	}

	return end();
}

template <typename TKey, typename TData, typename HashFunctor>
typename  HashMap<TKey, TData, HashFunctor>::Iterator HashMap<TKey, TData, HashFunctor>::end() const
{
	typename ChainType::Iterator Iter;
	return Iterator(*this, mBucket.Size(), Iter);
}

#pragma endregion
