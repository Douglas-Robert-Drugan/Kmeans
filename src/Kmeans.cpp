/*
* Kmeans.cpp - Kmeans class implementation
*
* Cite : http://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
         http://en.cppreference.com/w/cpp/algorithm/min_element
*/

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
#include "Kmeans.hpp"
#include "Cluster.hpp"
#include "Point.hpp"

/***********************************************************************************
 **Function: Constructor  
 **Description: initializes k and maxInterations
 **Parameters: int, int
 **Pre-Conditions: The parameters must be ints and must exist
 **Post-Conditions: Kmeans class object is initialized
 **********************************************************************************/
Kmeans::Kmeans(int n, int max)
{
    setK(n);                    // set # of clusters
    setMaxIterations(max);      // set # of iterations -- can also be hardcoded

    for(int i=0; i < n; i++){                       // create Cluster objects
        Cluster *ptr = new Cluster(i+1);            // cluster ID's set to 1-n
        this->clusterList.emplace_back(ptr);
    }
}

/***********************************************************************************
 **Function: Destructor  
 **Description: 
 **Parameters: 
 **Pre-Conditions: 
 **Post-Conditions: 
 **********************************************************************************/
Kmeans::~Kmeans()
{
    for(int i=0; i < n; i++){                       // delete Cluster objects
        delete this->clusterList[i];
    }
}

/***********************************************************************************
 **Function: Kmeans::setK
 **Description: initializes the k value (total number of clusters)
 **Parameters: an integer representing the number of clusters
 **Pre-Conditions: 
 **Post-Conditions: K value is set with integer passed to function
 **********************************************************************************/
 void Kmeans::setK(int n)
 {
    if (n > 0)
        k = n;
    else
        k = 3;      //set to default value of 3
 }
 
 /***********************************************************************************
 **Function: Kmeans::maxIterations
 **Description: initializes the maximum iterations (relocating centroid and 
 *      reassigning points) for Kmeans process
 **Parameters: an integer representing the maximum number of iterations
 **Pre-Conditions: 
 **Post-Conditions: maxIterations value is set with integer passed to function
 **********************************************************************************/
 void Kmeans::setMaxIterations(int n)
 {
    if (n > 0)
        maxIterations = n;
    else
        maxIterations = 12;      //set to default value of 12
 }

/***********************************************************************************
 **Function: getMaxIterations
 **Description: 
 **Parameters: 
 **Pre-Conditions: 
 **Post-Conditions: 
 **********************************************************************************/
 int Kmeans::getMaxIterations()
 {
    return this->maxIterations;
 }

/***********************************************************************************
 **Function : setClusters 
 **Description : sets initial centroids which Clusters will form around. Use k-means++ method.
 **Parameters : std::vector<Point*> datapoints
 **Pre-Conditions : 
 **Post-Conditions : 
 **********************************************************************************/
void Kmeans::setClusters(std::vector<Point*> datapoints){

    // find max and min x value
    auto x_small = std::min_element(std::begin(datapoints->xy.first), std::end(datapoints->xy.first));
    min_x = *x_small;

    auto x_big = std::max_element(std::begin(datapoints->xy.first), std::end(datapoints->xy.first));
    max_x = *x_big;

    // find max and min y value
    auto y_small = std::min_element(std::begin(datapoints->xy.second), std::end(datapoints->xy.second));
    min_y = *y_small;
    auto y_big = std::max_element(std::begin(datapoints->xy.second), std::end(datapoints->xy.second));
    max_y = *y_big;

    std::random_device rd;                                  // obtain seed
    std::mt19937 gen(rd());                                 // Standard mersenne_twister_engine seeded with rd()

    /* Set all x values for centroids randomly */
    std::uniform_real_distribution<> dis(min_x, max_x);     
    for (auto&& v : this->clusterList) {                    // is this auto right?
        v->centroid.first = dis(gen);
    }
   
   /* Set all y values for centroids randomly */
    std::uniform_real_distribution<> dis(min_y, max_y);      
    for (auto&& v : this->clusterList) {                    // is this auto right?
        v->centroid.second = dis(gen);
    }
}       

/***********************************************************************************
 **Function : reassignClusters
 **Description : moves a point to a different (closer) Cluster
 **Parameters : 
 **Pre-Conditions : 
 **Post-Conditions : returns True if even one centroid changed location.
    returns False if no centroids changed location.
 **********************************************************************************/
bool Kmeans::reassignClusters(std::vector<Point*> p){

    double sumX, sumY, avgX, avgY, count;
    bool moreChanges = 0;                                  // all centroids flag; set to False
    bool centroidChanged;                                  // current centroid flag; set to False below

    for (auto&& t : this->clusterList){                     // for t in ClusterList (t is a Cluster object)
        sumX = 0;                                           // reset var
        sumY = 0;
        count = 0;
        avgX = 0;
        avgY = 0;
        centroidChanged = 0;                               
        for (auto&& v : p){                             // for v in points (v is a point)
            if(t->clusterID == v->cluster_id){          // point is in this Cluster
                sumX = sumX + v->xy.first;
                sumY = sumY + v->xy.second;
                count++;
            }
        }
        avgX = sumX / count;                            // find average
        avgY = sumY / count;
        if(t->centroid.first == avgX && t->centroid.second == avgY){    // no changes made for this centroid
            centroidChanged = 1;                           
        }
        else{
            t->centroid.first = avgX;                   // set centroid's x and y values
            t->centroid.second = avgY;
        }
        if(centroidChanged == 1){                          // if even one centroidChanged flag is True, 
            moreChanges = 1;                            // moreChanges must also be True
        }
    }
    return moreChanges;
} 

/***********************************************************************************
 **Function : assignPoints
 **Description : sets the point_id to the closest Cluster object's cluster_id
 **Parameters : 
 **Pre-Conditions : 
 **Post-Conditions : 
 **********************************************************************************/
void Kmeans::assignPoints(std::vector<Point*> p){

    double distance, minDistance;                                   

     for (auto&& v : p) {                                           // for v in points (v is a point)
        minDistance = std::numeric_limits<double>::max();           // reset minDistance for each point
        for (auto&& t : this->clusterList) {                        // for t in ClusterList (t is a Cluster object)
            distance = computeDistance(v->xy, t->centroid);         // calculate distance
            if(distance == 0){                                      // point IS a centroid
                v->cluster_id = t->clusterID;                       // should I be using setters and getters here?
                // break from inner loop?
            }
            else if(distance < minDistance){                        
                minDistance = distance;                             // set minDistance
                v->cluster_id = t->clusterID;                       // should I be using setters and getters here?
            }
        }
    }
}               

/***********************************************************************************
 **Function : computeDistance
 **Description : get distance between two points using Euclidean distance squared
 **Parameters : pair<double, double> a, pair<double, double> b
 **Pre-Conditions : 
 **Post-Conditions : 
 **********************************************************************************/
double Kmeans::computeDistance(pair<double, double> a, pair<double, double> b){        

    double distance;
    double xDistance;
    double yDistance;

    xDistance = a.first - b.first;
    yDistance = a.second - b.second;

    distance = pow(xDistance, 2) + pow(yDistance, 2);
    // do not take sqrt to save time, but we can if we want to

    return distance;
}

/***********************************************************************************
 **Function: run_Kmeans
 **Description: 
 **Parameters: std::vector<Point*> dataPoints, int k
 **Pre-Conditions: 
 **Post-Conditions: 
 **********************************************************************************/
void Kmeans::run_Kmeans(std::vector<Point*> dataPoints, int k){

    setClusters(dataPoints);                            // randomly initialize k cluster centroids

    int count = this->getMaxIterations;
    bool changedFlag = 1;                               // set to true                   

    while(count > 0 || changedFlag = 0){
        changedFlag = 0;                                // set to false - no change yet
        assignPoints(dataPoints);                       // set each point's cluster_id to the closest Cluster
        changedFlag = reassignClusters(dataPoints);     // move centroids based on current location of points
        count--;
    }
}

// /* Functions that I commented out are below - I believe they are not necessary */

// /***********************************************************************************
//  **Function : setClusters 
//  **Description : sets initial centroids which Clusters will form around. Use k-means++ method.
//  **Parameters : std::vector<Point*> datapoints
//  **Pre-Conditions : 
//  **Post-Conditions : 
//  **********************************************************************************/
// void Kmeans::setClusters(std::vector<Point*> datapoints){

//     std::vector<int *> distanceList;
//     double distance;
//     double minDistance = std::numeric_limits<double>::max();
//     double totalDistance = 0;
//     double sum;
//     int d;

//     // find max and min point value in vector
//     std::vector<int>::iterator min_x = std::min_element(std::begin(datapoints.first), std::end(datapoints.first));
//     std::vector<int>::iterator max_x = std::max_element(std::begin(datapoints.first), std::end(datapoints.first));

//     std::vector<int>::iterator min_y = std::min_element(std::begin(datapoints.second), std::end(datapoints.second));
//     std::vector<int>::iterator max_y = std::max_element(std::begin(datapoints.second), std::end(datapoints.second));

//                                                             // select two points at random as first centroid (x, y values)
//     std::random_device rd;                                  // obtain seed
//     std::mt19937 gen(rd());                                 // Standard mersenne_twister_engine seeded with rd()

//     std::uniform_int_distribution<> dis(min_x, max_x);      // Unsure if I can use doubles here or if they have to be ints?
//     double xPoint = dis(gen);

//     std::uniform_int_distribution<> dis(min_y, max_y);      // Unsure if I am doing this correctly
//     double yPoint = dis(gen);

//     this->clusterList[0].centroid.first = xPoint;           // set first Cluster's centroid 
//     this->clusterList[0].centroid.second = yPoint;

//     for(int i = 1; i < this->k; i++){                                   // loop 1...k times - calculates the next Centroid in each loop (skips first one set above)
//         totalDistance = 0;                                              // reset totalDistance
//         sum = 0;                                                        // reset sum
//         for(int t = 0; t < datapoints.size(); t++){                     // for each data point, x, compute D(x), the squared distance between x and the nearest center that has already been chosen.
//             distance = 0;                                               // reset distance
//             double minDistance = std::numeric_limits<double>::max();    // reset minDistance
//             for(int w = 0; w < clusterList.size(); w++){
//                 distance = this->clusterList[i].getDistance(this->clusterList[i].centroid, datapoints[t].xy);  //compute distance between data point and current cluster.centroid
//                 if(distance < minDistance){
//                     minDistance = distance;
//                 }
//             }
//             //save minDistance and put in vector distanceList
//             int *ptr = new int(minDistance);
//             distanceList.emplace_back(ptr); 
//             totalDistance = totalDistance + minDistance;                // keep a totalSum of all distances
//         }
//         for(int f = 0; f < distanceList.size(); f++){                   // normalize D as ND: divide each squared distance / totalSum (overwrite old value)
//             distanceList->at(f) = distanceList->at(f) / totalDistance;
//         }
//         std::uniform_real_distribution<> dis(0, 1);                     // choose a random number 'r' between 0-1
//         double r = dis(gen);
//         for(d = 0; d < distanceList.size(); d++){                       // loop through ND 
//             while(sum <= r){    
//                 sum = sum + distanceList->at(f);                        // add each element until sum >= r, stop 
//             }
//         }
//         this->clusterList[i] = datapoints[d];                           // this is next new Centroid point (use index from ND loop to choose point)   
//     }
// }       

/***********************************************************************************
 **Function: comparePtAvg
 **Description: Compares x and y averages of current points in each cluster
 **Parameters: 
 **Pre-Conditions: 
 **Post-Conditions: 
 **********************************************************************************/
//void Kmeans::comparePtAvg(double avgPoints, double prevAvgPoints)
//{
    //relocateFlag = 0;     //assume no change to start
    //if avgPoints for previous iteration > avgPoints for current iteration:
        //relocateFlag = 1      //an improvement in average has been found for centroid k[i]
    //else
        //relocateFlag = 0      //no improvement made for centroid k[i]
//}

/***********************************************************************************
 **Function: comparePtCentroid
 **Description: If the centroids have been relocated, this function is invoked to 
 **     compare the distance between each point object and each centroid. If a point
 **     is closer to a centroid other than its currently-assigned centroid, then
 **     the point object is re-assigned to the centroid to which it is closest.
 **Parameters: Point object, vector of Cluster objects
 **Pre-Conditions: All points must be assigned to a Cluster/centroid and have a 
 **     distance from the point to its assigned centroid. 
 **Post-Conditions: If distance to any other centroid is less than the distance 
 **     to the current centroid, the point is reassigned to the closest centroid
 **     and the new distance is set as the point's distanceFromCentroid. 
 **********************************************************************************/
 
 //note: clusters vector type is 'int' for testing purposes
//int Kmeans::comparePtCentroid(std::pair<double, double> point, vector<int> clusters)
//{
    //for each centroid k_i in vector<Cluster>:
        /*****  calculate distance from point to k_i centroid   ****/
        //double distance = sqrt((centroid.x - point.x)^2 + (centroid.x - point.y)^2) 
        //if point.distanceFromCentroid > distance
            //relocatePoint(point, Cluster.centroidID)
            //point.distanceFromCentroid = distance
//}

/***********************************************************************************
 **Function: Kmeans::setTotal_points
 **Description: initializes the total points value (total number of points)
 **Parameters: an integer representing the number of points
 **Pre-Conditions: 
 **Post-Conditions: total_points value is set with integer passed to function
 **********************************************************************************/
 // void Kmeans::setTotal_points(int n)
 // {
 //    if (n > 0)                                                                           
 //        total_points = n;
 //    else
 //        total_points = 15;      //set to default value of 15
 // }
