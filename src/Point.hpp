/*
 *   Point HPP interface file for implementation in Point.cpp
 */

#include <boost/lockfree/queue.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include "utils.hpp"

#ifndef PONT_HPP
#define POINT_HPP

class Point {
private:
    int cluster_id, point_id;
    std::pair<double, double> xy;
    struct data {
        std::vector<std::string> headers;
        std::vector<std::string> childData;
    };
    data pointData;

public:
    //reassign point may be trivial as we can get/set the point in other class
    //constructor
    Point(int, std::string, std::string);
    //need trivial copy constructor for non locking objs
    //Point(const Point &pObj);   //copy constructor fix implementation for parallel
    //need trivial destructor
    //~Point();
    //getters
    int getClusterId() const;
    std::vector<std::string> getHeaders() const;
    std::vector<std::string> getData() const;
    std::pair<double, double> getXY() const;
    //setters
    void setXY(std::pair<int, int>);
    void setClusterId(int);
    void setHeaders(std::string);
    void setData(std::string);
    void printPointAttributes();

};

#endif
