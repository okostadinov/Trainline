#ifndef GRAPHOPS_H
#define GRAPHOPS_H

#include "GraphLib.h"

void addEdge(int source, int destination, int weight);
void makeGraph();
void freeGraph();
void findCityIndices(const char* city1, const char* city2, int* cindex1, int* cindex2);
void applyDisruption(const char* city1, const char* city2);
void acceptDisruptions();
int findMinDistance(int distances[], List S);
void findShortestPath(int startIndex, int endIndex);
void acceptQueries();
void printPath(int previousNode[], int startCity, int endCity);

#endif
