#pragma once


template <class ComponentT>
class Point3
{
protected:
	

public:
	Point3();
	Point3(ComponentT _c1, ComponentT _c2, ComponentT _c3);
	void setComponents(ComponentT _c1, ComponentT _c2, ComponentT _c3);

	ComponentT c1, c2, c3;
};