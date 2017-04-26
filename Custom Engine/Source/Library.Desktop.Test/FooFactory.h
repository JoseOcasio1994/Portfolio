#pragma once
#include <cstdint>
#include "pch.h"

namespace FieaGameEngine
{
	class FooFactory : public Factory<Foo<int>>
	{

	public:
								
		FooFactory()  { Add   ( *this ) ; }		
	   ~FooFactory()  { Remove( *this ) ; }		

		virtual const std::string ClassName( void )			
	        { return "Foo<int>"; }		

		virtual  Foo<int>*  Create(void)
	    {														
			Foo<int>* product = new Foo<int>();
			return product;										
	    }			

	};
}