/*
 * Cluster.hpp - Cluster class declaration
 */

#ifndef CLUSTER_HPP
#define CLUSTER_HPP

#include <boost/lockfree/queue.hpp>     
#include <utility>                      // need for type pair
#include <vector>

class Cluster{
private:
    std::pair<double, double> centroid;                                 // centroid is (x, y) value - center of Cluster
    std::vector<Point*> clusterPoints;                                  // vector of pointers to Point objects - points currently in this Cluster
    int clusterID;                                      
public:
    Cluster(int n);                                                     // constructor
    std::pair<double, double> getCentroid();                            // get current Centroid (x, y) value
    int getClusterID();     
    // double sumPoints(int choice);                                       // sum of point distances from a centroid in a Cluster
    // double avgPoints(int choice);                                       // get avg distance of points from a centroid in a Cluster
    // double getDistance(pair<double, double> a, pair<double, double> b); // get distance between two points
    // void Cluster::relocateCentroid();                                   // move Centroid based on mean of its current clusterPoints
}

#endif