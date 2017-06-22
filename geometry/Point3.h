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
		bool less_than_distance(const Point3<float>& rhs, const Point3<float>& point)
		{
			float lhs_d=0, rhs_d=0;
			for(int i=0; i<3;i++)
			{
				rhs_d+=(point.components[i]-rhs.components[i])*(point.components[i]-rhs.components[i]);
				lhs_d+=(point.components[i]-components[i])*(point.components[i]-components[i]);
			}
			return lhs_d<rhs_d;
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
			return (
				
				(743 + std::hash<ComponentT>()(p.components[0])) * 9967
				+ std::hash<ComponentT>()(p.components[1])
				);
		}
	};
}


#endif
