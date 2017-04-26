
template <typename T>
std::uint32_t HashFunction<T>::operator()(T& key)
{
	std::uint8_t * data = reinterpret_cast<std::uint8_t*>(&key);
	std::uint32_t hash = 0;

	for (int i = 0; i < sizeof(T); ++i)
		hash += Constant * data[i];

	return hash;
}


template <typename T>
std::uint32_t HashFunction<T*>::operator()(const T* key)
{
	std::uint32_t hash = 0;
	T copy = *key;
	std::uint8_t * data = reinterpret_cast<std::uint8_t*>(&copy);

	for (int i = 0; i < sizeof(copy); ++i)
		hash += Constant * data[i];

	return hash;
}