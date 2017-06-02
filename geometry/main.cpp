#include <iostream>
#include "Point3.h"
#include "Triangle.h"
#include "TriangleGenerator.h"
#include "Mesh.h"

#include <chrono>

typedef std::chrono::high_resolution_clock clk;

double getConnectivityFormationTime(int);
void testTimeComplexity();

int main()
{
	try
	{
		testTimeComplexity();
		return 0;

	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception Occurred. Message: " << e.what() << std::endl;
		return 1;
	}
}

void testTimeComplexity()
{
	std::vector<int> Ns = { 500,1500,2500};
	std::vector<double> times;

	for (uint32_t i = 0; i < Ns.size(); i++)
	{
		double time = getConnectivityFormationTime(Ns[i]);
		times.push_back(time);
		int numTris = (Ns[i] - 1)*(Ns[i] - 1) * 2;
		std::cout << "Time to form connectivity is " << time << " ms for " << numTris << " triangles.";
		std::cout << " ( " << (double)numTris / time << " triangles per ms ) " << std::endl;
	}
}

double getConnectivityFormationTime(int N)
{
	TriangleGenerator<Point3, int> t(0);

	std::vector<Triangle<Point3, int>> triangles
		= t.getTrianglesFrom2dGrid(1, 1, N, N);

	//first 
	clk::time_point t1 = clk::now();
	Mesh<Point3, int> m(triangles);
	clk::time_point t2 = clk::now();

	double dif = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

	return dif;
}