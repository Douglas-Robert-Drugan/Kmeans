/*
 * Cluster.cpp - Cluster class implementation
 */

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <utility>
#include <vector>
#include <ctime>
#include <cmath>
#include <boost/tokenizer.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/lexical_cast.hpp>
#include "Cluster.hpp"
#include "Point.hpp"


/***********************************************************************************
 **Function : Constructor
 **Description : 
 **Parameters : int
 **Pre-Conditions : 
 **Post-Conditions : 
 **********************************************************************************/
Cluster::Cluster(int n){
	
	this->clusterId = n;			// set ID number when object is created
}

/***********************************************************************************
 **Function : getClusterID
 **Description : get current cluster's ID
 **Parameters : none
 **Pre-Conditions : 
 **Post-Conditions : 
 **********************************************************************************/
int Cluster::getClusterID(){

	return this->clusterID;
} 

/***********************************************************************************
 **Function : getCentroid
 **Description : get current Centroid (x, y) value
 **Parameters : none
 **Pre-Conditions : 
 **Post-Conditions : 
 **********************************************************************************/	
std::pair<double, double> Cluster::getCentroid(){

	return this->centroid;
}	

/***********************************************************************************
 **Function : sumPoints
 **Description : sum of point distances (x or y / first or second) from a centroid in a Cluster
 **Parameters : std::vector<Point*>, int 
 **Pre-Conditions : 
 **Post-Conditions : 
 **********************************************************************************/
// double Cluster::sumPoints(int choice){

// 	double sum;
	
// 	if(choice == 1){
// 		for (auto&& v : this->clusterPoints) {			// is this right?
//         	sum += v->xy.first;
//         }
// 	}

// 	else if(choice == 2){
// 		for (auto&& v : this->clusterPoints) {			// is this right?
//         	sum += v->xy.second;
//         }
// 	}

// 	return sum;
// }					

/***********************************************************************************
 **Function : avgPoints
 **Description : get avg distance of points from a centroid.first -or- centroid.second in a Cluster
 **Parameters : std::vector<Point*>, int 
 **Pre-Conditions : 
 **Post-Conditions : 
 **********************************************************************************/
// double Cluster::avgPoints(std::vector<Point*> p, int choice){

// 	double average;
// 	double sum;

// 	sum = sumPoints(p, choice);
// 	average = sum / p.size();				

// 	return average;
// }				

/***********************************************************************************
 **Function : getDistance
 **Description : get distance between two points using Euclidean distance squared
 **Parameters : pair<double, double> a, pair<double, double> b
 **Pre-Conditions : 
 **Post-Conditions : 
 **********************************************************************************/
// double Cluster::getDistance(pair<double, double> a, pair<double, double> b){		

// 	double distance;
// 	double xDistance;
// 	double yDistance;

// 	xDistance = a.first - b.first;
// 	yDistance = a.second - b.second;

// 	distance = pow(xDistance, 2) + pow(yDistance, 2);
// 	// do not take sqrt to save time, but we can if we want to

// 	return distance;
// }

/***********************************************************************************
 **Function : relocateCentroid
 **Description : move a centroid to a different position based on mean of points in its vector
 **Parameters : 
 **Pre-Conditions : 
 **Post-Conditions : 
 **********************************************************************************/
// void Cluster::relocateCentroid(){

// 	bool firstFlag;			// check if unchanged
// 	bool secondFlag;		// check if unchanged
// 	double avgFirst;
// 	double avgSecond;
// 	int choice1 = 1;
// 	int choice2 = 2;

// 	// calculate new c.centroid.first
// 	avgFirst = avgPoints(c.clusterPoints, choice1);

// 	if(c.centroid.first == avgFirst){
// 		firstFlag = 1;								// 	set firstFlag to True -- x point did not move
// 	}
// 	else{
// 		c.centroid.first = avgFirst;
// 	}

// 	// calculate new c.centroid.second
// 	avgSecond = avgPoints(c.clusterPoints, choice2);
// 	if(c.centroid.second == avgSecond){
// 		secondFlag = 1;								// set secondFlag to True -- y point did not move
// 	}
// 	else{
// 		c.centroid.second = avgSecond;
// 	}

// 	if(firstFlag && secondFlag){
// 		// Centroids are done being relocated
// 		// program should stop soon! Should we make a return value to notify calling program?
// 	}
// }	














