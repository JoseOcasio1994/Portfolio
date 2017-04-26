#pragma once

#include <cstdint>

namespace FieaGameEngine
{
	template <typename T>
	class HashFunction
	{
	public:
		std::uint32_t operator()( T& key);

	private:
		std::uint32_t Constant = 101;
	};

	template<>
	class HashFunction<char*>
	{
	public:
		std::uint32_t operator()(const char* key)
		{
			std::uint32_t hash = 0;

			for (int i = 0; i < (int)strlen(key); ++i)
			{
				hash += Constant * key[i];
			}

			return hash;
		}

	private:
		std::uint32_t Constant = 101;
	};

	template<>
	class HashFunction<std::string>
	{
	public:
		std::uint32_t operator()(const std::string key)
		{
			std::uint32_t hash = 0;

			for (int i = 0; key[i] != '\0'; ++i)
			{
				hash += Constant * key[i];
			}

			return hash;
		}

	private:
		std::uint32_t Constant = 101;
	};

	template<typename T>
	class HashFunction<T*>
	{
	public:
		std::uint32_t operator()(const T* key);

	private:
		std::uint32_t Constant = 101;
	};

#include "HashFunction.inl"
	
}