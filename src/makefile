CXX = g++
CXXFLAGS = -g -std=c++11

OBJS = main.o Point.o utils.o Cluster.o Kmeans.o
SRCS = main.cpp Point.cpp utils.cpp Cluster.cpp Kmeans.cpp
HEADERS = Point.hpp utils.hpp Cluster.hpp Kmeans.hpp

all: main

main: $(SRCS) $(HEADERS)
		$(CXX) $(CXXFLAGS) $(SRCS) -o kmeansclustering
	   
Point.o: Point.cpp
		$(CXX) $(CXXFLAGS) Point.cpp

utils.o: utils.cpp
		$(CXX) $(CXXFLAGS) utils.cpp
        
Cluster.o: Cluster.cpp
		$(CXX) $(CXXFLAGS) Cluster.cpp
	  
Kmeans.o: Kmeans.cpp
		$(CXX) $(CXXFLAGS) Kmeans.cpp
        
main.o: main.cpp
		$(CXX) $(CXXFLAGS) main.cpp
		
clean:
		rm *o kmeansclustering