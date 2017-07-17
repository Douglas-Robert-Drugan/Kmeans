CXX = g++
CXXFLAGS = -g -std=c++11
MPFLAGS = -lm -fopenmp

OBJS = main.o Point.o utils.o
SRCS = main.cpp Point.cpp utils.cpp
HEADERS = Point.hpp utils.hpp

all: main

main: $(SRCS) $(HEADERS)
		$(CXX) $(CXXFLAGS) $(SRCS) -o kmeansclustering $(MPFLAGS)

#testSuite.o: testSuite.cpp
#		$(CXX) $(CXXFLAGS) testSuite.cpp
	   
Point.o: Point.cpp
		$(CXX) $(CXXFLAGS) Point.cpp

utils.o: utils.cpp
		$(CXX) $(CXXFLAGS) utils.cpp
        
#Cluster.o: Cluster.cpp
#		$(CXX) $(CXXFLAGS) Cluster.cpp
	  
#Kmeans.o: Kmeans.cpp
#		$(CXX) $(CXXFLAGS) Kmeans.cpp
        
main.o: main.cpp
		$(CXX) $(CXXFLAGS) main.cpp $(MPFLAGS)
		
clean:
		rm *o kmeansclustering