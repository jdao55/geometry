#ifndef GEOMENTRY_MESH_H
#define GEOMENTRY_MESH_H


#include <vector>
#include "Triangle.h"
#include <unordered_map>

template<template<typename ComponentT> typename PointT,typename ComponentT>
class Mesh
{
public:
	std::unordered_map<PointT<ComponentT>, std::vector<uint32_t> > connectivity;


	Mesh(std::vector<Triangle<PointT, ComponentT>> tris)
	{
		uint32_t numTris = tris.size();
		connectivity.rehash(numTris);

		for (uint32_t i = 0; i < numTris; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				auto mapPair = connectivity.find(tris[i].points[j]);

				if (mapPair != connectivity.end())
				{
					mapPair->second.push_back(i);
				}
				else
				{
					std::vector<uint32_t> newVec = { i };
					connectivity.insert(std::make_pair(tris[i].points[j], newVec));
				}
			}
		}

	}
	
};

#endif

