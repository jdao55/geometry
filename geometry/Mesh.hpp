#ifndef GEOMENTRY_MESH_H
#define GEOMENTRY_MESH_H


#include <vector>
#include <cmath>
#include <algorithm>
#include "Triangle.hpp"
#include <unordered_map>

#define pi 3.1415926

template<template<typename ComponentT> typename PointT,typename ComponentT>
class Mesh
{
public:
	std::unordered_map<PointT<ComponentT>, std::vector<PointT<ComponentT>> > connectivity;


	explicit Mesh(std::vector<Triangle<PointT, ComponentT>>& tris)
	{
		size_t numTris = tris.size();
        //resize hash map
		connectivity.rehash(numTris);
        //get connectivity map
		getConectivity(tris);
        //get nn out of map
		getNearestNeighborsMap();
	}
private:
	void getConectivity(std::vector<Triangle<PointT, ComponentT>>& tris)
	{
        //iterate thru each triangle
		for (size_t i = 0; i < tris.size(); i++)
		{
            //iterate thru points in traingle
			for (size_t j = 0; j < 3; j++)
			{
				auto mapPair = connectivity.find(tris[i].points[j]);
                //if point is fount in map
				if (mapPair != connectivity.end())
				{
					for (size_t k = 0; k < 3; k++)
					{
                        //insert new connectivity points to map
						if(k!=j)
						mapPair->second.push_back(tris[i].points[k]);
					}
				}
                //create new tuple and insert if point is not found
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
	void getNearestNeighborsMap()
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
        //find north south east west points add to neighbourList_vec
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
        //swap map vector with neighbor_list_vec which gets deconstructed when it goes out of scope
		std::swap(point_list, neighborList_vec);
	}
    //return trues if dist of lhs is closer to point than rhs
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
    //retruns the angle between 2 points
	double get_angle(const PointT<ComponentT>& origin, const PointT<ComponentT>& other)
	{
		double deltaY = other.components[1]-origin.components[1];
	    double deltaX = other.components[0]-origin.components[0];
	    return angle_trunc(atan2(deltaY, deltaX));
	}
    //trancate angle given by atan2(from 0 to 2pi)
	double angle_trunc(double angle)
	{
		while (angle < 0.0)
	        angle += pi * 2;
	    return angle;
	}

};

#endif

