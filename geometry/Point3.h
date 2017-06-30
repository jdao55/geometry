#ifndef GEOMENTRY_POINT3_H
#define GEOMENTRY_POINT3_H
#include <cstddef>
#include <functional>
#include <cmath>

template <typename ComponentT>
class Point3
{
	protected:
		

	public:

		ComponentT components[3];

		Point3() {
			setComponents(HUGE_VALF , HUGE_VALF , HUGE_VALF );
		}
		Point3(ComponentT _c1, ComponentT _c2, ComponentT _c3)
		{
			setComponents(_c1, _c2, _c3);
		}
		void setComponents(ComponentT _c1, ComponentT _c2, ComponentT _c3)
		{
			components[0] = _c1;
			components[1] = _c2;
			components[2] = _c3;
		}
};

template <class ComponentT>
inline bool operator==(const Point3<ComponentT>& lhs, const Point3<ComponentT>& rhs)
{
	return	lhs.components[0] == rhs.components[0] &&
		lhs.components[1] == rhs.components[1] &&
		lhs.components[2] == rhs.components[2];
}


//define the hash function for Point3
namespace std
{
	template <class ComponentT>
	struct hash<Point3<ComponentT>>
	{
		uint32_t operator()(Point3<ComponentT> const & p) const noexcept
		{
			std::hash<ComponentT> hasher;
			size_t seed=0;
			for(int i=0;i<3;i++)
			{
				seed ^= hasher(p.components[i])+0x9e3779b9+(seed<<6)+(seed>>2);
			}
			return seed;
		}
	};
}


#endif
