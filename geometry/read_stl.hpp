#ifndef GEOMENTRY_READ_STL_H
#define GEOMENTRY_READ_STL_H

#include <fstream>
#include "Point3.hpp"
#include "Triangle.hpp"
#include <vector>
#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <cstdlib>

void read_stl_bin(std::vector<Triangle<Point3,float>>& triangle_list, const std::string& file);
void read_triangle_bin(std::vector<Triangle<Point3,float>>& triangle_list,std::ifstream & stlFile);
void read_triangle(std::vector<Triangle<Point3,float>>& triangle_list, std::string str_list[]);
void read_stl(std::vector<Triangle<Point3, float>>& trangle_list, const std::string & file);
#endif
