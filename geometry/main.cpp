#include "Point3.h"
#include "Triangle.h"
#include "TriangleGenerator.h"
#include "Mesh.h"
#include "read_stl_bin.h"

#define pi 3.1415926


void output_nearest_n(Mesh<Point3, float>& point_map,std::string& file);


void printFile(std::ofstream & outfile, const Point3<float>& point, std::vector<Point3<float>>&neighborList_vec);


int main()
{
	std::string in_file_name, out_file_name;
	std::vector<Triangle<Point3,float>> triangle_list;

	std::cout<<"Enter stl file name"<<std::endl;
	std::cin>> in_file_name;
	std::cout<<"Enter output file name"<<std::endl;
	std::cin>> out_file_name;

	try	
	{
		read_stl_bin(triangle_list, in_file_name);

		Mesh<Point3, float> m(triangle_list);
	
		output_nearest_n(m, out_file_name);
		
	}
	catch (const char* msg) 
	{
 		std::cerr << msg << std::endl;
 	}

}

void output_nearest_n(Mesh<Point3, float>& point_map,std::string& file)
{
	std::ofstream outfile;
	outfile.exceptions( std::ofstream::failbit | std::ofstream::badbit );
	outfile.open(file);
	for(auto point=point_map.connectivity.begin();
		point!=point_map.connectivity.end(); point++)
	{
		printFile(outfile,point->first,point->second);
	}
	
}

void printFile(std::ofstream & outfile, const Point3<float>& point, std::vector<Point3<float>>& neighborList_vec)
{
	outfile<<point.components[0]<<" "
		<<point.components[1]<<" "
		<<point.components[2]<<" "
		<<"has nn: \n";
	for(auto it=neighborList_vec.begin();
		it!=neighborList_vec.begin()+4 && it!=neighborList_vec.end();
		it++)
	{
		outfile<<it->components[0]<<" "
		<<it->components[1]<<" "
		<<it->components[2]<<"\n";
	}
	outfile<<std::endl;
}
