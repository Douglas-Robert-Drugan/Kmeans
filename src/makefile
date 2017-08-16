CXX = g++
CXXFLAGS = -g -std=c++11

OBJS = main.o Point.o utils.o Cluster.o Kmeans.o
SRCS = main.cpp ../lib/Point.cpp ../utils/utils.cpp ../lib/Cluster.cpp ../lib/Kmeans.cpp
HEADERS = ../lib/Point.hpp ../utils/utils.hpp ../lib/Cluster.hpp ../lib/Kmeans.hpp

all: main

main: $(SRCS) $(HEADERS)
		$(CXX) $(CXXFLAGS) $(SRCS) -o kmeansclustering
	   
Point.o: ../lib/Point.cpp
		$(CXX) $(CXXFLAGS) Point.cpp

utils.o: ../utils/utils.cpp
		$(CXX) $(CXXFLAGS) utils.cpp
        
Cluster.o: ../lib/Cluster.cpp
		$(CXX) $(CXXFLAGS) Cluster.cpp
	  
Kmeans.o: ../lib/Kmeans.cpp
		$(CXX) $(CXXFLAGS) Kmeans.cpp
        
main.o: main.cpp
		$(CXX) $(CXXFLAGS) main.cpp
		
clean:
		rm *o kmeansclustering