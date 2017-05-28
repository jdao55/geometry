
template<template<typename ComponentT> class PointT, template class ComponentT>
Triangle<PointT<ComponentT>, ComponentT>::Triangle() {}

template<template<typename ComponentT> class PointT, template class ComponentT>
Triangle<PointT, ComponentT>::Triangle(PointT _p1, PointT _p2, PointT _p3)
{
	setPoints(_p1, _p2, _p3);
}

template<template<typename ComponentT> class PointT, template class ComponentT>
void
Triangle<PointT, ComponentT>::setPoints
(PointT<ComponentT> _p1, PointT<ComponentT> _p2, PointT<ComponentT> _p3)
{
	p1 = _p1;
	p2 = _p2;
	p3 = _p3;
}