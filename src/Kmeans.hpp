/*
* Kmeans.hpp - Kmeans class declaration
*/
#ifndef KMEANS_HPP
#define KMEANS_HPP

#include <iostream>
#include <math.h>
#include <algorithm>
#include <limits>
#include <cstddef>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <utility>                  //need for type pair
#include <vector>
#include <random>
#include <boost/tokenizer.hpp>
#include <boost/lockfree/queue.hpp> //container still TBD
#include <boost/lexical_cast.hpp>
#include "Cluster.hpp"

//class Cluster;

class Kmeans
{
private:
    int k;                                  // number of clusters
<<<<<<< HEAD
                                            // int total_points;                    // total number of data points (stored as x,y coordinate pairs) --- not necessary
    int iter = 1;                           // counts iteratiions - ??? What is this for ???
    int maxIterations;                      // number of iterations (from user input or preset)
    bool done;                              // done relocating? True if done; false if not done.
=======
    int maxIterations;                      // number of iterations (from user input or preset)
>>>>>>> 454c708bffdbf0efd1ff19fbb638e4dbca06779b
    std::vector<Cluster *> clusterList;     // vector of pointers to Cluster objects 		

public:
    Kmeans(int n, int max);             // constructor  
    ~Kmeans();                         // delete all ptrs in clusterList

    //setters
    void setClusters(std::vector<Point*> p);   // set initial centroids for each Cluster
    void setK(int);
    void setMaxIterations(int);

    //getters
    int getK() const;
    int getMaxIterations() const;
    Cluster * getCluster(int id) const;
    
    //functions
    void run_Kmeans(std::vector<Point*> dataPoints);                 // should be a very simple function
    bool reassignClusters(std::vector<Point*> p);                  // reassign centroids for each Cluster
    void assignPoints(std::vector<Point*> p);                               // assign a point to a Cluster 
    double computeDistance(std::pair<double, double> a, std::pair<double, double> b); // get distance between two points
<<<<<<< HEAD
    void printResults();
=======
    void printResults(std::vector<Point*> points);
    void saveResults(std::vector<Point*> p);
>>>>>>> 454c708bffdbf0efd1ff19fbb638e4dbca06779b
};

#endif