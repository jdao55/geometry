#ifndef GEOMENTRY_READ_STL_BIN_H
#define GEOMENTRY_READ_STL_BIN_H

#include <fstream>
#include "Point3.h"
#include "Triangle.h"
#include <vector>
#include <iostream>

void read_stl_bin(std::vector<Triangle<Point3,float>>& triangle_list, const char * file);

#endif