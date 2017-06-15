#include <chrono>
#include <fstream>
#include <unordered_set>
#include <algorithm>
#include <functional>

#include "Point3.h"
#include "Triangle.h"
#include "TriangleGenerator.h"
#include "Mesh.h"
#include "read_stl_bin.h"




void output_nearest_n(Mesh<Point3, float>& point_map, std::vector<Triangle<Point3,float>>& triangle_list,char * file);

// returns true if lhs closer to point then rhs
bool bydistance(const Point3<float>& lhs, Point3<float>& rhs, Point3<float>& point);

int main()
{

	char in_file_name[128], out_file_name[128];
	std::vector<Triangle<Point3,float>> triangle_list;

	std::cout<<"Enter stl file name"<<std::endl;
	std::cin>> in_file_name;
	std::cout<<"Enter output file name"<<std::endl;
	std::cin>> out_file_name;

	try	
	{
		read_stl_bin(triangle_list, in_file_name);

		Mesh<Point3, float> m(triangle_list);
		
		output_nearest_n(m,triangle_list,out_file_name);
	}
	catch (const char* msg) 
	{
 		std::cerr << msg << std::endl;
 	}

}

void output_nearest_n(Mesh<Point3, float>& point_map, std::vector<Triangle<Point3,float>>& triangle_list,char * file)
{
	std::ofstream outfile;
	outfile.exceptions( std::ofstream::failbit | std::ofstream::badbit );
	try
	{
		outfile.open(file, std::ios::out);

		for(auto point=point_map.connectivity.begin();
			point!=point_map.connectivity.end(); point++)
		{
			std::unordered_set<Point3<float>> neighborList;
			

			for(auto index: point->second)
			{
				for(int i=0;i<3;i++){
					if(!(triangle_list[index].points[i]==point->first))
						neighborList.insert(triangle_list[index].points[i]);
				}
			}
			//store in vector so points can be sorted
			std::vector<Point3<float>> neighborList_vec(neighborList.begin(),neighborList.end());

			std::sort(neighborList_vec.begin(),neighborList_vec.end(),
				std::bind(&bydistance, std::placeholders::_1, std::placeholders::_2, (point->first)));

			outfile<<(point->first).components[0]<<" "
				<<(point->first).components[1]<<" "
				<<(point->first).components[2]<<" "
				<<"has nn: \n";
			for(auto it=neighborList_vec.begin();
				it!=neighborList_vec.begin()+4&&it!=neighborList_vec.end();
				it++)
			{
				outfile<<it->components[0]<<" "
				<<it->components[1]<<" "
				<<it->components[2]<<"\n";
			}
			outfile<<std::endl;
		}
	}
	catch (std::ifstream::failure& e) 
	{
		std::cerr <<e.what()<<"\n";
    	throw "Exception opening/reading/closing file";
	}

}

bool bydistance(const Point3<float>& lhs, Point3<float>& rhs, Point3<float>& point)
{
	float lhs_d=0, rhs_d=0;
	for(int i=0; i<3;i++)
	{
		rhs_d+=(point.components[i]-rhs.components[i])*(point.components[i]-rhs.components[i]);
		lhs_d+=(point.components[i]-lhs.components[i])*(point.components[i]-lhs.components[i]);
	}
	return lhs_d<rhs_d?true:false;
}