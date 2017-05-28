#include "TriangleGenerator.h"


template<class PointT, class ComponentT>
TriangleGenerator<PointT, ComponentT>::TriangleGenerator() {}

template<class PointT, class ComponentT>
vector<Triangle<PointT, ComponentT>> 
TriangleGenerator< PointT, ComponentT>::getTrianglesFrom2dGrid
(int xSpacing, int ySpacing, int pointCountX, int pointCountY)

