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
#include <boost/tokenizer.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/lexical_cast.hpp>
#include "Cluster.hpp"


/***********************************************************************************
 **Function : Constructor
 **Description : 
 **Parameters : 
 **Pre-Conditions : 
 **Post-Conditions : 
 **********************************************************************************/
Cluster::Cluster(int n){
	clusterId = n;			// set ID number when object is created

	// std::pair<double, double> centroid;					// centroid is (x, y) value - center of Cluster
	// std::vector<pair<double, double>> clusterPoints;		// vector of (x, y) values in a specific Cluster
}

/***********************************************************************************
 **Function : setClusters
 **Description : set initial centroids which Clusters will form around. Use k-means++ method.
 **Parameters : 
 **Pre-Conditions : 
 **Post-Conditions : 
 **********************************************************************************/
void Cluster::setClusters(){
	// select one point at random as first centroid

	// loop k-1 times (k = # of centroids) - find the next Centroid in each loop
		// for each data point, x, compute D(x), the squared distance between x and the nearest center that has already been chosen.
			// keep a totalSum of all distances
		// normalize D as ND: divide each squared distance / totalSum (save this in a new array or overwrite old value??)
		// choose a random number 'r' [0-1] (will be float)
		// loop through ND - add each element until sum >= r, stop - this is new Centroid point (use index to choose point
	// end loop

}		

/***********************************************************************************
 **Function : getCentroid
 **Description : get current Centroid (x, y) value
 **Parameters : Cluster c
 **Pre-Conditions : 
 **Post-Conditions : 
 **********************************************************************************/	
std::pair<double, double> Cluster::getCentroid(Cluster c){

	return c.centroid;

}	

/***********************************************************************************
 **Function : sumPoints
 **Description : sum of point distances (x or y / first or second) from a centroid in a Cluster
 **Parameters : 
 **Pre-Conditions : 
 **Post-Conditions : 
 **********************************************************************************/
double Cluster::sumPoints(Cluster c, int choice){

	double sum;

	// if choice == 1
		// sum = loop through (vector) c.clusterPoints.first 
	// else if choice == 2
		// sum = loop through (vector) c.clusterPoints.second 

	return sum;

}					

/***********************************************************************************
 **Function : avgPoints
 **Description : get avg distance of points from a centroid.first or centroid.second in a Cluster
 **Parameters : 
 **Pre-Conditions : 
 **Post-Conditions : 
 **********************************************************************************/
double Cluster::avgPoints(Cluster c, int choice){

	double average;
	double sum;

	// sum = sumPoints(c, choice);
	// average = sum / (total num of pairs in c.clusterPoints)

	return average;

}				

/***********************************************************************************
 **Function : distanceFromCentroid
 **Description : get distance from a point to a centroid
 **Parameters : Cluster c, pair data point
 **Pre-Conditions : 
 **Post-Conditions : 
 **********************************************************************************/
double Cluster::distanceFromCentroid(Cluster c, std::pair<double, double> point){

	double distance;

	// formula for euclidean distance squared from (c.centroid.first to point.first) + (c.centroid.second to point.second)

	return distance;
}

/***********************************************************************************
 **Function : relocateCentroid
 **Description : move a centroid to a different position
 **Parameters : 
 **Pre-Conditions : 
 **Post-Conditions : 
 **********************************************************************************/
void Cluster::relocateCentroid(Cluster c){

	bool firstFlag;			// check if unchanged
	bool secondFlag;		// check if unchanged
	double avgFirst;
	double avgSecond;
	int choice1 = 1;
	int choice2 = 2;

	// calculate new c.centroid.first
	avgFirst = avgPoints(c, choice1);
	// if c.centroid.first == avgFirst
		// set firstFlag to True -- this point didn't move
	// else
		// c.centroid.first = avgFirst;

	// calculate new c.centroid.second
	avgSecond = avgPoints(c, choice2);
	// if c.centroid.second == avgSecond
		// set secondFlag to True -- this point didn't move
	// else
		// c.centroid.second = avgSecond;

	// if firstFlag && secondFlag both == True
		// Centroids are done being relocated!
		// program should stop forming clusters!

}	
/***********************************************************************************
 **Function : relocatePoint
 **Description : move a point to a different (closer) Cluster
 **Parameters : 
 **Pre-Conditions : 
 **Post-Conditions : 
 **********************************************************************************/
void Cluster::relocatePoint(Cluster c, std::pair<double, double> point){

	double currDistance;
	double newDistance;
	int currID;
	int newID;

	// currDistance = get distance from point to its current cluster
	// does Point class have a label so it knows what Cluster it's in? This would help
	// then I could grab current Cluster ID to save in currID

	// newID = currID 

	// need to loop through (1...k) Clusters -- skip cluster the point is currently in
		// newDistance = distanceFromCentroid(c, point);	--current distance
		// if newDistance < currDistance
			// newID = current Cluster.clusterID

	// if currID != newID
		// remove point from current Cluster.clusterPoints
		// add point to new Cluster.clusterPoints (cluster with Cluster.clusterID == newID)
}				
















