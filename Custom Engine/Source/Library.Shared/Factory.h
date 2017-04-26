#pragma once
#include "pch.h"
#include <cstdint>

namespace FieaGameEngine
{
	template <class Product>
	class Factory
	{

	private:
		typedef typename HashMap<std::string, Factory&>::Iterator Iterator;
		static HashMap<std::string, Factory& > mFactories;

	public:

		virtual ~Factory() = default;

		bool operator==(const Factory& rhs)
		{
			return this == &rhs;
		}

		static Factory* Find(const std::string& name)
		{
			Iterator found = mFactories.Find(name);

			if (found != end())
				return &found->second;

			return nullptr;
		}

		static Product* Create(const std::string& name)
		{
			Factory* Found = Find(name);

			if (Found != nullptr)
				return mFactories.At(name).Create();
			else
				throw std::exception("No Compatible Factory Found");
		}

		static Iterator begin()
		{
			return mFactories.begin();
		}

		static Iterator end()
		{
			return mFactories.end();
		}

		static void Add(Factory& factory)
		{
			std::pair<std::string, Factory&> newFactory( factory.ClassName(), factory );
			mFactories.Insert(newFactory);
		}

		static void Remove(Factory& factory)
		{
			mFactories.Remove(factory.ClassName());
		}

		virtual Product* Create(void) = 0;

		virtual const std::string ClassName(void) = 0;
		
	};

#define ConcreteFactory( AbstractProduct, ConcreteProduct )			\
	class ConcreteProduct ## Factory : public Factory<AbstractProduct>		\
	{															\
		public:													\
		ConcreteProduct ## Factory()  { Add   ( *this ) ; }		\
	   ~ConcreteProduct ## Factory()  { Remove( *this ) ; }		\
		virtual const std::string ClassName( void )			    \
	        { return # ConcreteProduct; }						\
		virtual  AbstractProduct*  Create(void)					\
	    {														\
		   AbstractProduct* product = new  ConcreteProduct();	\
		   return product;										\
	    }														\
	};															\

}