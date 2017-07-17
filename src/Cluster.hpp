/*
 * Cluster.hpp - Cluster class declaration
 */

#ifndef CLUSTER_HPP
#define CLUSTER_HPP

#include <boost/lockfree/queue.hpp>     
#include <utility>                      // need for type pair
#include <vector>

class Cluster{
public:
	std::pair<double, double> centroid;					// centroid is (x, y) value - center of Cluster
	std::vector<pair<double, double>> clusterPoints;    // vector of (x, y) values in a specific Cluster * should we change it to pointers to pairs?
    int clusterID;										

    Cluster(int n);						                           // constructor
    void setClusters();					                            // set initial centroids - randomly - which Clusters will form around
    std::pair<double, double> Cluster::getCentroid(Cluster c);      // get current Centroid (x, y) value
    double sumPoints(Cluster c, int choice);					   // sum of point distances from a centroid in a Cluster
    double avgPoints(Cluster c, int choice);					   // get avg distance of points from a centroid in a Cluster
    double distanceFromCentroid(std::pair<double, double> centroid, std::pair<double, double> point);	// get distance from a point to a centroid
    void Cluster::relocateCentroid(Cluster c);                      // move Centroid based on mean of its current clusterPoints
    void relocatePoint(Cluster c, std::pair<double, double> point);	// move a point to a different (closer) Cluster

}

#endif