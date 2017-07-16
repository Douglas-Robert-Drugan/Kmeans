/*
 * Kmeans clustering main file
 */

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <boost/tokenizer.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/lexical_cast.hpp>
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
    
    using boost::lexical_cast;
    using boost::bad_lexical_cast;
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
    auto xCol = std::stoi(argv[5]);
    auto yCol = std::stoi(argv[6]);
    auto headerCount = std::stoi(argv[7]);
    
    fprintf(stdout, "%d \n", xCol);
    fprintf(stdout, "%d \n", yCol);

     /* find way to only parse x, y header columns into vectors*/

    boost::lockfree::queue<double> xx(numLines);
    boost::lockfree::queue<double> yy(numLines);
    std::ifstream inputFile(argv[1]);
    if (inputFile.is_open()){
        std::string headerLine;			//create variable for header line
        std::getline(inputFile, headerLine);	//getline to remove header line in .csv
        std::string line;
//#pragma omp parallel for default(none)
        while (std::getline(inputFile, line)){
            typedef boost::escaped_list_separator<char> Separator;
            typedef boost::tokenizer<Separator> Tokenizer;

            Tokenizer tokenizer(line);
            int count = 0;

            for (const auto &t : tokenizer){
                if (count == xCol){
                    std::cout << t << "\t";
                    try {
                        xx.bounded_push(lexical_cast<double>(t));
                    }
                    catch (const bad_lexical_cast& e){
                        std::cout << "Exception: " << e.what() << "\n";
                    }
                }
                if (count == yCol){
                    try {
                        std::cout << t << "\t";
                        yy.bounded_push(lexical_cast<double>(t));
                    }
                    catch (const bad_lexical_cast& e) {
                        std::cout << "Exception: " << e.what() << "\n";
                    }
                }
                ++count;
            }
            std::cout << "\n";
        }
    }


    return 0;
}
