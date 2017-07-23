/*
* Cluster.hpp - Cluster class declaration
*/

#ifndef CLUSTER_HPP
#define CLUSTER_HPP

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
#include "Point.hpp"

//class Point;

class Cluster {
private:
    //Point;
    std::pair<double, double> centroid;     // centroid is (x, y) value - center of Cluster
    std::vector<Point*> clusterPoints;      // vector of pointers to Point objects - points currently in this Cluster
    int clusterID;
public:
    Cluster(int n);     // constructor
    ~Cluster();                 

    //setters
    void setClusterID(int);
    void setCentroid(double, double);

    //getters
    std::pair<double, double> getCentroid() const;    // get current Centroid (x, y) value
    int getClusterID() const;
    
    //functions
    //double sumPoints(int choice);   // sum of point distances from a centroid in a Cluster
    //double avgPoints(int choice);   // get avg distance of points from a centroid in a Cluster
    //double computeDistance(std::pair<double, double> a, std::pair<double, double> b); // get distance between two points
    // void Cluster::relocateCentroid();                                   // move Centroid based on mean of its current clusterPoints
};

#endif