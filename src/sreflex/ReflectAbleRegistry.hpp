#pragma once

#include <algorithm>
#include <functional>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include "ReflectAble.hpp"

namespace sreflex
{
	/**
	 * The function that use to construct object.
	 */
	using CreateFunctionPtr = std::function<std::unique_ptr<ReflectAble>()>;

	/**
	 * @brief the registry that store the informations of all RelectAble instances.
	 *
	 * The BasicReflectAbleRegistry is the basic templated class that ReflectAbleRegistry and
	 * OrderedReflectAbleRegistry use. Each implementation of the BasicReflectAbleRegistry are different and does not
	 * relate to each other. The BasicReflectAbleRegistry is a singleton class to avoid duplication of registry with
	 * same type.
	 * @tparam MapType type of map to implement registry.
	 */
	template<typename MapType>
	class BasicReflectAbleRegistry
	{
	public:
		/**
		 * Get the instance of the registry.
		 */
		static BasicReflectAbleRegistry& getInstance()
		{
			static BasicReflectAbleRegistry instance;
			return instance;
		}

		/**
		 * Register a ReflectAble instance to the registry.
		 * @param name[in] Name of the object, prefix with namespace where the object declare is recommended.
		 * @param ptr[in] CreationFunction of the instance.
		 * @throw std::logic_error if @p name is redefined in the registry.
		 */
		void registerObject(const std::string& name, CreateFunctionPtr ptr)
		{
			auto result = reg.insert(
			{ name, std::move(ptr) });
			if (result.second != true)
			{
				throw std::logic_error{
					"The object \"" + name + "\" aready exist in the registry, prefix with namespace to avoid it"
				};
			}
		}

		/**
		 * Determine if given object is registered.
		 * @param name[in] Name of the object.
		 * @return true if @p name is registered, false otherwise.
		 */
		bool hasObject(const std::string& name)
		{
			return reg.find(name) == reg.end() ? false : true;
		}

		/**
		 * Get the CreationFunction of the given object.
		 * @param name[in] Name of the object.
		 * @throw std::out_of_range if @p name does not found in the registry.
		 */
		CreateFunctionPtr getObjCreator(const std::string& name)
		{
			auto result = reg.find(name);
			if (result == reg.end())
				throw std::out_of_range{ "The object \"" + name + "\" is not exist in the registry." };
			return result->second;
		}
	private:
		BasicReflectAbleRegistry() {}
		~BasicReflectAbleRegistry() {}
		MapType reg;
	};

	using ReflectAbleRegistry = BasicReflectAbleRegistry<std::unordered_map<std::string, CreateFunctionPtr>>;
	using OrderedReflectAbleRegistry = BasicReflectAbleRegistry<std::map<std::string, CreateFunctionPtr>>;
}
