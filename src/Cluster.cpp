/*
* Cluster.cpp - Cluster class implementation
*/

#include "Cluster.hpp"

/***********************************************************************************
**Function : Constructor
**Description :
**Parameters : int
**Pre-Conditions :
**Post-Conditions :
**********************************************************************************/
Cluster::Cluster(int n) {

    setClusterID(n);			// set ID number when object is created
}

Cluster::~Cluster()
{
<<<<<<< HEAD
    for (auto&& p : this->clusterPoints) {
        delete p;
    }
=======
>>>>>>> 454c708bffdbf0efd1ff19fbb638e4dbca06779b
}

void Cluster::setClusterID(int id)
{
    this->clusterID = id;
}

void Cluster::setCentroid(double x, double y)
{
    this->centroid.first = x;
    this->centroid.second = y;
}

/***********************************************************************************
**Function : getClusterID
**Description : get current cluster's ID
**Parameters : none
**Pre-Conditions :
**Post-Conditions :
**********************************************************************************/
int Cluster::getClusterID() const {

    return this->clusterID;
}

/***********************************************************************************
**Function : getCentroid
**Description : get current Centroid (x, y) value
**Parameters : none
**Pre-Conditions :
**Post-Conditions :
**********************************************************************************/
std::pair<double, double> Cluster::getCentroid() const {

    return this->centroid;
}
























<<<<<<< HEAD


=======
>>>>>>> 454c708bffdbf0efd1ff19fbb638e4dbca06779b
