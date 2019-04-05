#pragma once
#include "ReflectAbleRegistry.hpp"

namespace sreflex
{
	template <typename ReflectAbleObject, typename RegistryType>
	class BasicAutoRegistra
	{
	public:
		static bool registerObj(const std::string& objName, CreateFunctionPtr ptr)
		{
			RegistryType::getInstance().registerObject(objName, std::move(ptr));
			return true;
		}

		static bool registerObj(const std::string& objName)
		{
			return registerObj(objName, [](){ return std::make_unique<ReflectAbleObject>(); });
		}
	};

	template <typename Object>
	using AutoRegistra = BasicAutoRegistra<Object, ReflectAbleRegistry>;
	template <typename Object>
	using OrderedAutoRegistra = BasicAutoRegistra<Object, OrderedReflectAbleRegistry>;
}

#define SREFLEX_MARKOBJ private: static const bool __sreflex_register_result__;
#define SREFLEX_REGOBJ(object)\
		const bool object::__sreflex_register_result__ = sreflex::AutoRegistra<object>::registerObj(#object);
#define SREFLEX_REGOBJ_PTR(object, ptr)\
		const bool object::__sreflex_register_result__ = sreflex::AutoRegistra<object>::registerObj(#object, ptr);
#define SREFLEX_REGOBJ_TYPE(object, registry)\
		const bool object::__sreflex_register_result__ = sreflex::registry<object>::registerObj(#object);
#define SREFLEX_REGOBJ_NAME_TYPE(object, ptr, registry)\
		const bool object::__sreflex_register_result__ = sreflex::registry<object>::registerObj(#object, ptr);
