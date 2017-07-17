/*
* Kmeans clustering main file
*/

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <atomic>
#include <boost/tokenizer.hpp>
#include <boost/lockfree/queue.hpp>
#include "Point.hpp"
//#include <omp.h>
//#define NUMT 2

int main(int argc, char *argv[]) {
    /*
    #ifndef _OPENMP
    fprintf(stderr, "OpenMP is not supported here -- sorry.\n");
    return 1;
    #endif
    omp_set_num_threads(NUMT);
    fprintf(stderr, "Using %d threads\n", NUMT);
    */

    /*
    * DEBUG
    */
    fprintf(stdout, "%d arguments.\n", argc - 1);
    for (int i = 0; i < argc - 1; i++) {
        int ct = i + 1;
        std::cout << ct << "st argument: " << argv[ct] << std::endl;
    }

    auto x = argv[2];
    auto y = argv[3];
    auto numLines = std::stoi(argv[4]);
    std::pair <int, int> xy;
    auto xyCol = std::make_pair(std::stoi(argv[5]), std::stoi(argv[6]));

    fprintf(stdout, "%d\n%d\n", xyCol.first, xyCol.second);

    /* find way to only parse x, y header columns into vectors*/

    //boost::lockfree::queue<double> xx(numLines);
    //boost::lockfree::queue<double> yy(numLines);

    //switch to lockfree queue when bugs are fixed
    std::vector<Point*> p;

    std::ifstream inputFile(argv[1]);
    if (inputFile.is_open()) {
        std::string headerLine;			//create variable for header line
        std::getline(inputFile, headerLine);	//getline to remove header line in .csv
        std::string line;
        int pointID = 0;
        //#pragma omp parallel for default(none)
        while (std::getline(inputFile, line)) {
            Point *ptr = new Point(pointID, headerLine, line);
            p.emplace_back(ptr);
            pointID++;
        }
    }
    //DEBUG: Task Scheduler performing out of order operations in read from csv while loop
    //instantiated new auto loop below to iterate through points in vector and set xy
    for (auto&& v : p) {
        v->setXY(xyCol);
    }

    return 0;
}
