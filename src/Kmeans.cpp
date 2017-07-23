/*
* Kmeans.cpp - Kmeans class implementation
*
* Cite : http://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
http://en.cppreference.com/w/cpp/algorithm/min_element
*/

#include "Kmeans.hpp"

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

    for (int i = 0; i < n; i++) {                       // create Cluster objects
        Cluster *ptr = new Cluster(i + 1);            // cluster ID's set to 1-n
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
    for (auto&& t : clusterList) {                       // delete Cluster objects
        delete t;
    }
}

/***********************************************************************************
**Function : setClusters
**Description : sets initial centroids which Clusters will form around. Use k-means++ method.
**Parameters : std::vector<Point*> datapoints
**Pre-Conditions :
**Post-Conditions :
**********************************************************************************/
void Kmeans::setClusters(std::vector<Point*> p) {

    //put x and y in vectors from each point
    std::vector<double> x;
    std::vector<double> y;

    for (const auto& z : p) {
        x.emplace_back(z->getXY().first);
        y.emplace_back(z->getXY().second);
    }

    // find max and min x value
    auto xs = std::min_element(std::begin(x), std::end(x));
    auto min_x = *xs;

    auto x_big = std::max_element(std::begin(x), std::end(x));
    auto max_x = *x_big;

    // find max and min y value
    auto y_small = std::min_element(std::begin(y), std::end(y));
    auto min_y = *y_small;
    auto y_big = std::max_element(std::begin(y), std::end(y));
    auto max_y = *y_big;

    std::random_device rd;                                  // obtain seed
    std::mt19937 gen(rd());                                 // Standard mersenne_twister_engine seeded with rd()

                                                            /* Set all x values for centroids randomly */           // may be able to get these two into one loop 
    std::uniform_real_distribution<> Xdis(min_x, max_x);
    std::uniform_real_distribution<> Ydis(min_y, max_y);
    for (auto&& v : clusterList) {                          // is this auto right?
        v->setCentroid(Xdis(gen), Ydis(gen));
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

int Kmeans::getK() const
{
    return this->k;
}

int Kmeans::getMaxIterations() const
{
    return this->iter;
}

Cluster * Kmeans::getCluster(int id) const
{
    return nullptr;
}


/***********************************************************************************
**Function : reassignClusters
**Description : moves a point to a different (closer) Cluster
**Parameters :
**Pre-Conditions :
**Post-Conditions : returns True if even one centroid changed location.
returns False if no centroids changed location.
**********************************************************************************/
bool Kmeans::reassignClusters(std::vector<Point*> p) {

    double sumX, sumY, avgX, avgY, count;
    bool moreChanges = 0;                                  // all centroids flag; set to False
    bool centroidChanged;                                  // current centroid flag; set to False below

    for (auto&& t : clusterList) {                           // for t in ClusterList (t is a Cluster object)
        sumX = 0;                                           // reset var
        sumY = 0;
        count = 0;
        avgX = 0;
        avgY = 0;
        centroidChanged = 0;
        for (auto&& v : p) {                             // for v in points (v is a point)
            if (t->getClusterID() == v->getClusterId()) {          // point is in this Cluster
                sumX = sumX + v->getXY().first;
                sumY = sumY + v->getXY().second;
                count++;
            }
        }
        avgX = sumX / count;                            // find average
        avgY = sumY / count;
        if ((t->getCentroid().first == avgX) && (t->getCentroid().second == avgY)) {    // no changes made for this centroid
            centroidChanged = 1;
        }
        else {
            t->setCentroid(avgX, avgY);                   // set centroid's x and y values
        }
        if (centroidChanged == 1) {                          // if even one centroidChanged flag is True, 
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
void Kmeans::assignPoints(std::vector<Point*> p) {

    double distance, minDistance;

    for (auto&& v : p) {                                           // for v in points (v is a point)
        minDistance = std::numeric_limits<double>::max();           // reset minDistance for each point
        for (auto&& t : clusterList) {                              // for t in ClusterList (t is a Cluster object)
            distance = computeDistance(v->getXY(), t->getCentroid());         // calculate distance
            if (distance == 0) {                                      // point IS a centroid
                v->setClusterId(t->getClusterID());                       // should I be using setters and getters here?
                break;                                              // only want to break from inner loop
            }
            else if (distance < minDistance) {
                minDistance = distance;                             // set minDistance
                v->setClusterId(t->getClusterID());                       // should I be using setters and getters here?
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
double Kmeans::computeDistance(std::pair<double, double> a, std::pair<double, double> b) {

    double distance;
    double xDistance;
    double yDistance;

    xDistance = a.first - b.first;
    yDistance = a.second - b.second;

    distance = pow(xDistance, 2) + pow(yDistance, 2);
    // do not take sqrt to save time, but we can if we want to

    return distance;
}

void Kmeans::printResults()
{
    int ct = 1;
    //for right now just print centroids
    std::cout << "**FINAL CENTROIDS**" << std::endl;
    for (const auto& p : this->clusterList) {
        std::cout << "Cluster " << ct << " Centroid: " << p->getCentroid().first << "\t" << p->getCentroid().second << std::endl;
        ct++;
    }
}

/***********************************************************************************
**Function: run_Kmeans
**Description:
**Parameters: std::vector<Point*> dataPoints, int k
**Pre-Conditions:
**Post-Conditions:
**********************************************************************************/
void Kmeans::run_Kmeans(std::vector<Point*> dataPoints) {

    setClusters(dataPoints);                            // randomly initialize k cluster centroids
    int ct = 1;
    std::cout << "**INITIAL CENTROIDS**" << std::endl;
    for (const auto& p : this->clusterList) {
        std::cout << "Cluster " << ct << " Centroid: " << p->getCentroid().first << "\t" << p->getCentroid().second << std::endl;
        ct++;
    }
    std::cout << std::endl;

    int count = getMaxIterations();
    bool changedFlag = 1;                               // set to true                   

    while (count > 0 || changedFlag == 0) {
        changedFlag = 0;                                // set to false - no change yet
        assignPoints(dataPoints);                       // set each point's cluster_id to the closest Cluster
        changedFlag = reassignClusters(dataPoints);     // move centroids based on current location of points
        count--;
    }

}