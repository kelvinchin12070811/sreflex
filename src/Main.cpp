#include <iostream>
#include "sreflex/AutoRegistar.hpp"
#include "sreflex/ReflectAbleFactory.hpp"

using namespace std;

class Test : public sreflex::ReflectAble
{
	SREFLEX_MARKOBJ
public:
	~Test() = default;
	void test()
	{
		cout << "hello from test" << endl;
	}
};
SREFLEX_REGOBJ(Test)

namespace scene
{
	class Test : public sreflex::ReflectAble
	{
		SREFLEX_MARKOBJ
	public:
		~Test() = default;
		void print()
		{
			cout << "from test in scene::test" << endl;
		}
	};
	SREFLEX_REGOBJ(scene::Test)
}

int main()
{
	sreflex::ReflectAbleFactory factory;
	auto ins = factory.createInstance<scene::Test>("scene::Test");
	(ins.get())->print();
	return 0;
}
