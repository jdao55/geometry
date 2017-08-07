#include "read_stl.hpp"

void read_triangle(std::vector<Triangle<Point3,float>>& triangle_list, std::string str_list[])
{
    Point3<float> p_list[3];
    for(int i=0; i<3; i++)
    {
        std::istringstream ss(str_list[i]);
        std::string temp;
        std::vector<std::string> num_str{std::istream_iterator<std::string>(ss),
                std::istream_iterator<std::string>()};
        std::vector<float> coordlist;
        std::transform(num_str.begin()+1, num_str.end(), std::back_inserter(coordlist),
                       [](std::string& a)-> float{return std::stof(a);});
        p_list[i]=Point3<float>(coordlist[0], coordlist[1], coordlist[2]);
    }
    triangle_list.push_back(Triangle<Point3, float>(p_list[0], p_list[1], p_list[2])); 
}
void read_stl(std::vector<Triangle<Point3,float>>& triangle_list, const std::string& file)
{
    std::string buffer;
	std::ifstream stlFile;
	stlFile.exceptions( std::ifstream::failbit | std::ifstream::badbit );
	stlFile.open(file, std::ios::in);
    getline(stlFile, buffer);
    if(buffer.find("solid")!=std::string::npos)
    {
        getline(stlFile,buffer);
        while(buffer.find("endsolid")==std::string::npos)
        {
            std::string point_string[3];
            getline(stlFile,buffer);
            for(int i=0; i<3; i++)
            {
                getline(stlFile, point_string[i]);
            }
            read_triangle(triangle_list, point_string);
            getline(stlFile,buffer);
            getline(stlFile,buffer);
            getline(stlFile,buffer);
        }
        stlFile.close();
    }
    else
    {
        stlFile.close();
        read_stl_bin(triangle_list, file);
    }
    
}


void read_stl_bin(std::vector<Triangle<Point3,float>>& triangle_list, const std::string& file)
{
	uint32_t num_tri;
	std::ifstream stlFile;
	stlFile.exceptions( std::ifstream::failbit | std::ifstream::badbit );
	stlFile.open(file, std::ios::in | std::ios::binary);
	
	//skips header of stl file
	stlFile.seekg(80);
		
	//read number of triangles in stl file, and converts it to usigned int
	stlFile.read((char*)(&num_tri), sizeof(uint32_t));

	for(size_t j=0; j<num_tri; j++)
	{
		read_triangle_bin(triangle_list, stlFile);
	}
	stlFile.close();
}


void read_triangle_bin(std::vector<Triangle<Point3,float>>& triangle_list, std::ifstream & stlFile)
{
	float point[3];
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
