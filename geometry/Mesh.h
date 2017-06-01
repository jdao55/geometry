#pragma once
#include <vector>
#include "Triangle.h"
#include <unordered_map>

template<	template<class ComponentT> class PointT,
	class ComponentT>
class Mesh
{
public:
	std::unordered_map<PointT<ComponentT>, std::vector<size_t> > connectivity;

	
	//std::pair<std::string, double> mapPair;

	Mesh(std::vector<Triangle<PointT, ComponentT>> tris)
	{
		size_t numTris = tris.size();
		bool inMap;
		for (size_t i = 0; i < numTris; i++)
			for (int j = 0; j < 3; j++)
			{
				auto mapPair = connectivity.find(tris[i].points[j]);
				inMap = mapPair != connectivity.end();

				if (inMap)
				{
					std::vector<size_t>& list = mapPair->second;
					list.push_back(i);
				}
				else
				{
					std::vector<size_t> newVec = { i };
					connectivity.insert(std::make_pair(tris[i].points[j], newVec));
				}
			}
	}
	
};