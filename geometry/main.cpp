#include <iostream>
#include "Point3.h"
#include "Triangle.h"
#include "TriangleGenerator.h"
#include "Mesh.h"

using namespace std;
int main()
{
	TriangleGenerator<Point3, int> t(0);
	Point3<int> p = t.test();

	vector<Triangle<Point3, int>> triangles
		= t.getTrianglesFrom2dGrid(1, 1, 3, 3);

	Mesh<Point3, int> m(triangles);

	return 0;
}