#pragma once

namespace sreflex
{
	/**
	 * @berif Parent of all instances that need reflection.
	 */
	class ReflectAble
	{
	public:
		/**
		 * Virtual destructor
		 */
		virtual ~ReflectAble() = 0;
	private:
		//ReflectAble() {}
	};

	ReflectAble::~ReflectAble() = default;
}
