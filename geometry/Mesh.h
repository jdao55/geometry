#ifndef GEOMENTRY_MESH_H
#define GEOMENTRY_MESH_H


#include <vector>
#include <cmath>
#include <algorithm>
#include "Triangle.h"
#include <unordered_map>

#define pi 3.1415926

template<template<typename ComponentT> typename PointT,typename ComponentT>
class Mesh
{
public:
	std::unordered_map<PointT<ComponentT>, std::vector<PointT<ComponentT>> > connectivity;


	Mesh(std::vector<Triangle<PointT, ComponentT>>& tris)
	{
		size_t numTris = tris.size();
		connectivity.rehash(numTris);
		getConectivity(tris);
		getNearestNeighborsMap(tris);
		

	}
private:
	void getConectivity(std::vector<Triangle<PointT, ComponentT>>& tris)
	{
		for (size_t i = 0; i < tris.size(); i++)
		{
			for (size_t j = 0; j < 3; j++)
			{
				auto mapPair = connectivity.find(tris[i].points[j]);

				if (mapPair != connectivity.end())
				{
					for (size_t k = 0; k < 3; k++)
					{
						if(k!=j)
						mapPair->second.push_back(tris[i].points[k]);
					}
				}
				else
				{
					std::vector<PointT<ComponentT>> newVec;
					for (size_t k = 0; k < 3; k++)
					{
						if(k!=j)
						newVec.push_back(tris[i].points[k]);
					}
	 				connectivity.insert(std::make_pair(tris[i].points[j], newVec));
				}
			}
		}
	}
	void getNearestNeighborsMap(std::vector<Triangle<PointT, ComponentT>>& tris)
	{
		for(auto point=connectivity.begin();
			point!=connectivity.end(); point++)
		{
			getNNpoint(point->first,point->second);
		}
	}
	void getNNpoint(const PointT<ComponentT>& point,std::vector<PointT<ComponentT>>& point_list)
	{
		std::vector<PointT<ComponentT>> neighborList_vec(4);
		for(auto iter:point_list)
		{
			double angle =get_angle(point, iter);
			if ((angle<pi/4 && angle >= 0) || (angle>7*pi/4))
			{
				if(less_than_distance(iter, neighborList_vec[0],point))
					neighborList_vec[0]=(iter);
			}
			else if (angle<pi*3/4)
			{
				if(less_than_distance(iter, neighborList_vec[1],point))
					neighborList_vec[1]=(iter);
			}
			else if (angle<pi*5/4)
			{
				if(less_than_distance(iter, neighborList_vec[2],point))
					neighborList_vec[2]=(iter);
			}
			else if (angle<=7*pi/4)
			{
				if(less_than_distance(iter, neighborList_vec[3],point))
					neighborList_vec[3]=(iter);
			}	
		}
		std::swap(point_list, neighborList_vec);
	}

	bool less_than_distance(const PointT<ComponentT>& lhs,const PointT<ComponentT>& rhs, const PointT<ComponentT>& point)
	{
		float lhs_d=0, rhs_d=0;
		for(int i=0; i<3;i++)
		{
			rhs_d+=(point.components[i]-rhs.components[i])*(point.components[i]-rhs.components[i]);
			lhs_d+=(point.components[i]-lhs.components[i])*(point.components[i]-lhs.components[i]);
		}
		return lhs_d<rhs_d;
	}
	double get_angle(const PointT<ComponentT>& origin, const PointT<ComponentT>& other)
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

};

#endif

