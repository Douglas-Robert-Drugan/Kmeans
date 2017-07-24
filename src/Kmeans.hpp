/*
 * Kmeans.hpp - Kmeans class declaration
 */

#ifndef KMEANS_HPP
#define KMEANS_HPP

#include <boost/lockfree/queue.hpp>     
#include <utility>                              // need for type pair
#include <vector>
#include "Cluster.hpp"

class Kmeans
{
    private:
        int k;                                  // number of clusters
        // int total_points;                    // total number of data points (stored as x,y coordinate pairs) --- not necessary
        int iter = 1;                           // counts iteratiions - ??? What is this for ???
        int maxIterations;                      // number of iterations (from user input or preset)
        bool done;                              // done relocating? True if done; false if not done.
        std::vector<Cluster *> clusterList;     // vector of pointers to Cluster objects 		
        
    public:
        Kmeans(int n, int max);                         // constructor  
        ~Kmeans()                                       // delete all ptrs in clusterList
        void setK(int);
        void setMaxIterations(int);
        int getK();
        int getMaxIterations();

        Cluster * getCluster(int id);
        double getDistance(pair<double, double> a, pair<double, double> b);     // get distance between two points
        void run_KMeans(std::vector<Point*> dataPoints, int k);                 // should be a very simple function
        void setClusters(std::vector<Point*> datapoints);                       // set initial centroids for each Cluster
        bool reassignClusters(std::vector<Point*> p);                  // reassign centroids for each Cluster
        void assignPoints(std::vector<Point*> p);                               // assign a point to a Cluster 
        double computeDistance(pair<double, double> a, pair<double, double> b); // get distance between two points
};

#endif