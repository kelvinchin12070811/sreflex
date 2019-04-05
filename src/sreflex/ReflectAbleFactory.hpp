#include <type_traits>
#include "ReflectAbleRegistry.hpp"

namespace sreflex
{
	template <typename RegistryType>
	class BasicReflectAbleFactory
	{
	public:
		/**
		 * Create and return a new instance of an ReflectAble object and cast it to targeted type.
		 * @tparam TargetType TargetType to cast with dynamic cast.
		 * @param name[in] Name of the object.
		 * @throw std::out_of_range if @p name does not registered.
		 * @throw std::runtime_error if creation of instance failed.
		 */
		template <typename TargetType, typename std::enable_if<
				!std::is_same<TargetType, ReflectAble>::value
			>::type* = nullptr>
		std::unique_ptr<TargetType> createInstance(const std::string& name)
		{
			auto result = createInstance<ReflectAble>(name);
			auto rwPtr = std::unique_ptr<TargetType>{ dynamic_cast<TargetType*>(result.get()) };
			if (rwPtr == nullptr)
				throw std::runtime_error{ "" };

			result.release();
			return rwPtr;
		}

		template <typename TargetType, typename std::enable_if<
				std::is_same<TargetType, ReflectAble>::value
			>::type* = nullptr>
		std::unique_ptr<TargetType> createInstance(const std::string& name)
		{
			auto result = RegistryType::getInstance().getObjCreator(name)();
			if (result == nullptr)
				throw std::runtime_error{ "Unable to create the object \"" + name + "\", it was nullptr internally" };
			return result;
		}
	};

	using ReflectAbleFactory = BasicReflectAbleFactory<sreflex::ReflectAbleRegistry>;
	using OrderedReflectAbleFactory = BasicReflectAbleFactory<sreflex::OrderedReflectAbleRegistry>;
}
