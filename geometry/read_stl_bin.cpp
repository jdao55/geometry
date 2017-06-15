#include "read_stl_bin.h"

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