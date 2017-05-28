#include <iostream>
#include "Point3.h"
#include "Triangle.h"
#include "TriangleGenerator.h"

int main()
{
	TriangleGenerator<Point3, int> t(0);
	Point3<int> p = t.test();

	return 0;
}