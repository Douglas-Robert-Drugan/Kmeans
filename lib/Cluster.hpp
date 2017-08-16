/*
* Cluster.hpp - Cluster class declaration
*/

#ifndef CLUSTER_HPP
#define CLUSTER_HPP

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <boost/tokenizer.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/lexical_cast.hpp>
#include "Point.hpp"

//class Point;

class Cluster {
private:
    //Point;
    std::pair<double, double> centroid;     // centroid is (x, y) value - center of Cluster
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
    
};

#endif