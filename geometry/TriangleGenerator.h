#pragma once
#include <vector>
#include "Triangle.h"
#include "Point3.h"


using namespace std;

template<	template<	template <class ComponentT> class PointT> class Triangle,
			template<class ComponentT> class PointT, 
			class ComponentT>
class TriangleGenerator
{
public:
	typedef Triangle<

	TriangleGenerator(){}

	vector<Triangle<PointT<ComponentT>, ComponentT>> 
	getTrianglesFrom2dGrid(int xSpacing, int ySpacing, int pointCountX, int pointCountY)
	{
		vector<Triangle<PointT, ComponentT>> tris;

		for (int iX = 0; iX < pointCountX, iY++)
			for (int iY = 0; iY < pointCountX, iY++)
			{
				PointT pTL();		//point top left

			}
	}
};