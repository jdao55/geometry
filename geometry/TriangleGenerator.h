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

	//returns a vector of triangles that cover the defined grid, which is assumed to lie in the z-plane
	vector<Triangle<PointT, ComponentT>>
	getTrianglesFrom2dGrid(ComponentT xSpacing, ComponentT ySpacing, int pointCountX, int pointCountY)
	{
		vector<Triangle<PointT, ComponentT>> tris;

		//tris.resize(pointCountX*pointCountY*2);

		int xLim = pointCountX - 1;
		int yLim = pointCountY - 1;

		for (int iX = 0; iX < xLim; iX++)
			for (int iY = 0; iY < yLim; iY++)
			{
				PointT<ComponentT> pTL(iX*ySpacing, (iY+1)*ySpacing, 0);
				PointT<ComponentT> pTR((iX+1)*ySpacing, (iY+1)*ySpacing, 0);
				PointT<ComponentT> pBL(iX*ySpacing, iY*ySpacing, 0);
				PointT<ComponentT> pBR((iX+1)*ySpacing, iY*ySpacing, 0);

				Triangle<PointT, ComponentT> tri1(pTL, pTR, pBL);
				Triangle<PointT, ComponentT> tri2(pBR, pTR, pBL);

				tris.push_back(tri1);
				tris.push_back(tri2);

			}

		return tris;
	}
};