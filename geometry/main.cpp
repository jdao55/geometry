#include <chrono>
#include <fstream>
#include <unordered_set>
#include <algorithm>
#include <functional>
#include <cmath>

#include "Point3.h"
#include "Triangle.h"
#include "TriangleGenerator.h"
#include "Mesh.h"
#include "read_stl_bin.h"

#define pi 3.1415926


void output_nearest_n(Mesh<Point3, float>& point_map, std::vector<Triangle<Point3,float>>& triangle_list,char * file);

double get_angle(const Point3<float>& origin, const Point3<float>& rhs);
double angle_trunc(double angle);
// returns true if lhs closer to point then rhs
bool less_than_distance(const Point3<float>& lhs, const Point3<float>& rhs, const Point3<float>& point);

void printFile(std::ofstream & outfile, const Point3<float>& point, std::vector<Point3<float>>&neighborList_vec);

void get_nn(const Point3<float>& point,std::unordered_set<Point3<float>>& point_set, std::vector<Point3<float>>&neighborList_vec);
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
			std::vector<Point3<float>> neighborList_vec(4);

			get_nn(point->first,neighborList, neighborList_vec);
			printFile(outfile, (point->first), neighborList_vec);
		}
	}
	catch (std::ofstream::failure& e) 
	{
		std::cerr <<e.what()<<"\n";
    	throw "Exception opening/reading/closing file";
	}

}

bool less_than_distance(const Point3<float>& lhs, const Point3<float>& rhs, const Point3<float>& point)
{
	float lhs_d=0, rhs_d=0;
	for(int i=0; i<3;i++)
	{
		rhs_d+=(point.components[i]-rhs.components[i])*(point.components[i]-rhs.components[i]);
		lhs_d+=(point.components[i]-lhs.components[i])*(point.components[i]-lhs.components[i]);
	}
	return lhs_d<rhs_d;
}

double get_angle(const Point3<float>& origin, const Point3<float>& other)
{
	double deltaY = other.components[1]-origin.components[1];
    double deltaX = other.components[0]-origin.components[0];
    return angle_trunc(atan2(deltaY, deltaX));
}

double angle_trunc(double angle)
{
	while (angle < 0.0)
        angle += pi * 2;
    return angle;
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

void get_nn(const Point3<float>& point,std::unordered_set<Point3<float>>& point_set, std::vector<Point3<float>>&neighborList_vec)
{
	for(auto iter=point_set.begin();
			iter!=point_set.end(); iter++)
	{
		double angle =get_angle(point, *iter);
		if ((angle<pi/4 && angle >= 0) || (angle>7*pi/4))
		{
			if(less_than_distance(*iter, neighborList_vec[0],point))
				neighborList_vec[0]=(*iter);
		}
		else if ((angle>=pi/4)&&(angle<pi*3/4))
		{
			if(less_than_distance(*iter, neighborList_vec[1],point))
				neighborList_vec[1]=(*iter);
		}
		else if ((angle>=pi*3/4)&&(angle<pi*5/4))
		{
			if(less_than_distance(*iter, neighborList_vec[2],point))
				neighborList_vec[2]=(*iter);
		}
		else if ((angle>=pi*3/4)&&(angle<=7*pi/4))
		{
			if(less_than_distance(*iter, neighborList_vec[3],point))
				neighborList_vec[3]=(*iter);
		}	
	}
}
