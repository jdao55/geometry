#pragma once
#include <vector>
#include "Triangle.h"


using namespace std;

template<	template<class ComponentT> class PointT, 
			class ComponentT>
class TriangleGenerator
{
public:
	int x;
	TriangleGenerator(int _x) { x = _x; }

	/*TriangleGenerator() {}*/

	PointT<ComponentT> test()
	{
		return PointT<ComponentT>(0, 0, 0);
	}

	vector<Triangle<PointT, ComponentT>>
	getTrianglesFrom2dGrid(int xSpacing, int ySpacing, int pointCountX, int pointCountY)
	{
		vector<Triangle<PointT, ComponentT>> tris;

		for (int iX = 0; iX < pointCountX, iY++)
			for (int iY = 0; iY < pointCountX, iY++)
			{
				PointT p1(0, 1, 2);

			}
	}
};