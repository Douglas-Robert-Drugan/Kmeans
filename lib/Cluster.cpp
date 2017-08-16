/*
* Cluster.cpp - Cluster class implementation
*/

#include "Cluster.hpp"


Cluster::Cluster(int n) {

    setClusterID(n);			// set ID number when object is created
}

Cluster::~Cluster()
{
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

int Cluster::getClusterID() const {

    return this->clusterID;
}

std::pair<double, double> Cluster::getCentroid() const {

    return this->centroid;
}
