#include <iostream>
#include <chrono>
#include <fstream>

#include "Point3.h"
#include "Triangle.h"
#include "TriangleGenerator.h"
#include "Mesh.h"



void read_stl_bin(std::vector<Triangle<Point3,float>>& triangle_list, const char * file);

int main()
{
	char file_name[128];
	std::vector<Triangle<Point3,float>> triangle_list;

	std::cout<<"Enter stl file name"<<std::endl;
	std::cin>> file_name;

	try	
	{
		read_stl_bin(triangle_list, file_name);
		std::cout<<"num of tri : "<<triangle_list.size()<<"\n";
	}

	catch (const char* msg) {
 		std::cerr << msg << std::endl;
 	}

}

void read_stl_bin(std::vector<Triangle<Point3,float>>& triangle_list, const char * file)
{
	uint32_t num_tri;
	std::ifstream stlFile;
	stlFile.exceptions( std::ifstream::failbit | std::ifstream::badbit );
	try
	{
		stlFile.open(file, std::ios::in | std::ios::binary);
		
		//skips header of stl file
		stlFile.seekg(80);
		
		//read number of triangles in stl file, and converts it to usigned int
		stlFile.read((char*)(&num_tri), sizeof(uint32_t));
	
		float point[3];
		for(size_t j=0; j<num_tri; j++)
		{
			Point3<float> pointlist[3];
			stlFile.seekg(12,std::ios_base::cur);
			
			//read 36 bytes (3 points in the triangle)
			for(int i=0;i<3;i++)
			{
				stlFile.read(reinterpret_cast<char*>(point), sizeof(point));
				pointlist[i]=Point3<float>(point[0],point[1],point[2]);
				
			}
			triangle_list.push_back(Triangle<Point3,float>(pointlist[0],pointlist[1],pointlist[2]));
			
			//discards last 2 bytes(hold no inforamtion)
			stlFile.seekg(2,std::ios_base::cur);
		}
		stlFile.close();
	}
	catch (std::ifstream::failure& e) 
	{
		std::cerr <<e.what()<<"\n";
    	throw "Exception opening/reading/closing file";
	}

}	
/*

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
*/