#include "Point3.h"

template <class ComponentT>
Point3<ComponentT>::Point3(){}

template <class ComponentT>
Point3<ComponentT>::Point3(ComponentT _c1, ComponentT _c2, ComponentT _c3)
{
	setComponents(_c1, _c2, _c3);
}

template <class ComponentT>
void Point3<ComponentT>::setComponents(ComponentT _c1, ComponentT _c2, ComponentT _c3)
{
	c1 = _c1;
	c2 = _c2;
	c3 = _c3;
}