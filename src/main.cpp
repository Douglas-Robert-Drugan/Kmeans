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
#include "../lib/Kmeans.hpp"
#include "../utils/utils.hpp"


int main(int argc, char *argv[]) {
    
    auto x = argv[2];
    auto y = argv[3];
    auto numLines = std::stoi(argv[4]);
    std::pair <int, int> xy;
    auto xyCol = std::make_pair(std::stoi(argv[5]), std::stoi(argv[6]));
    auto num_clusters = std::stoi(argv[7]);
    auto num_iters = std::stoi(argv[8]);

    std::vector<Point*> p;
    utils nUtility;
    std::ifstream inputFile(argv[1]);
    if (inputFile.is_open()) {
        std::string headerLine;			//create variable for header line
        nUtility.safeGetline(inputFile, headerLine);	//getline to remove header line in .csv
        std::string line;
        int pointID = 0;
        
        while (!nUtility.safeGetline(inputFile, line).eof()) {
            Point *ptr = new Point(pointID, headerLine, line, xyCol);
            p.emplace_back(ptr);
            pointID++;
        }
    }
    
    //create clusters for #of clusters by creating kmeans obj
    Kmeans *K = new Kmeans(num_clusters, num_iters);
    K->run_Kmeans(p);
    //K->printResults(p);

    delete K;

    return 0;
}