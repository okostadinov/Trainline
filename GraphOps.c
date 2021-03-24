#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "GraphLib.h"

/* For each city, we create a pointer to a list which contains its neightbours.
** We start alphabeticaly as defined in the cities array and create the lists.
**
**          0 | Amsterdam       4 | Enschede        8 | Meppel
**          1 | Den Haag        5 | Groningen       9 | Nijmegen
**          2 | Den Helder      6 | Leeuwarden     10 | Utrecht
**          3 | Eindhoven       7 | Maastricht     11 | Zwolle
**
********************************************************************************/

/* Purpose: Creates the edge between two nodes bilaterally.
 * Input:   Source node index, destination node index and weight value of the edge.
 * Result:  The edge is added to both nodes' adjacency lists.
 */
void addEdge(int source, int destination, int weight) {
    adjacencyList[source] = addNode(destination, weight, adjacencyList[source]);
    adjacencyList[destination] = addNode(source, weight, adjacencyList[destination]);
}

/* Purpose: Creates the graph by filling the adjacency lists of each city.
 * Result:  All node have been connected bilaterally and each has its neighbours in its adjacency list.
 */
void makeGraph() {
    /* Populate the list with empty pointers first. */
    for (int i = 0; i < AMOUNTNODES; i++) {
        adjacencyList[i] = newEmptyList();
    }

    /* Add all the edges into each city's adjacency list. */
    addEdge(0, 1, 46);
    addEdge(0, 2, 77);
    addEdge(0, 10, 26);
    addEdge(1, 3, 89);
    addEdge(3, 7, 63);
    addEdge(3, 9, 55);
    addEdge(3, 10, 47);
    addEdge(4, 11, 50);
    addEdge(5, 6, 34);
    addEdge(5, 8, 49);
    addEdge(6, 8, 40);
    addEdge(7, 9, 111);
    addEdge(8, 11, 15);
    addEdge(9, 11, 77);
    addEdge(10, 11, 51);
}

/* Purpose: Frees the memory allocated to the graph by iterating over the list pointer array
 *          and freeing each adjancency list storing the neighbours of each city.
 */
void freeGraph() {
    for (int i = 0; i < AMOUNTNODES; i++) {
        freeList(adjacencyList[i]);
    }
}

/* Purpose: Retrieves the indices of the cities from the cities array and stores them.
 * Input:   The cities' names as strings and the int pointers where the values of the indices will be stored.
 */
void findCityIndices(const char* city1, const char* city2, int* cindex1, int* cindex2) {
    /* Iterate over the cities array and compare the provided strings with the names of the cities. */
    for (int i = 0; i < AMOUNTNODES; i++) {
        if (strcmp(cities[i], city1) == 0) {
            *cindex1 = i;
        }
        if (strcmp(cities[i], city2) == 0) {
            *cindex2 = i;
        }
    }
}

/* Purpose: Removes the connection between two adjacent nodes.
 * Input:   The indices of the cities from the cities array.
 */
void applyDisruption(int cindex1, int cindex2) {
    /* For both cities, remove the other from its adjacency list. */
    adjacencyList[cindex1] = removeNode(adjacencyList[cindex1], cindex2);
    adjacencyList[cindex2] = removeNode(adjacencyList[cindex2], cindex1);
}

/* Purpose: Accepts from the user the quantity of disruptions, followed by the cities.
            For each pair, the function removes the edge by calling applyDisrution function.
 * Result:  The nodes of the cities have been removed from the adjacency lists of the cities.
 */
void acceptDisruptions() {
    int i, n; /* n stores total amount of disruptions. */
    int cindex1, cindex2;
    char city1[15], city2[15], linebreak;
    scanf("%d", &n);

    /* Iterate n times accepting the cities and applying disruption. */
    for (i = 0; i < n; i++) {
        scanf("%c", &linebreak); /* Store the newline. */
        scanf("%[^\n]", city1); /* Store the city name string until a newline is reached (i.e. don't stop at whitespace). */
        scanf("%c", &linebreak);
        scanf("%[^\n]", city2);
        findCityIndices(city1, city2, &cindex1, &cindex2);
        applyDisruption(cindex1, cindex2);
    }
}

/* Purpose: Prints the shortest path between two cities.
 * Input:   An array containing for every node its previous node with shortest path, starting city index and end city index.
 * Result:  A printed list of city names to visit while travelling from the starting city to the destination city.
 */
void printPath(int previousNode[], int startCity, int endCity) {
    if (startCity == endCity) { /* Destination is reached. */
        printCityName(startCity);
        return;
    }
    /* Call recursively providing the previous node as the destination. */
    printPath(previousNode, startCity, previousNode[endCity]);
    printCityName(endCity);
}

/* Purpose: Given an array with distances, find the shortest distance given that index is in List S.
 * Input:   The array with distance from source to index node and a list of nodes to be handled.
 * Output:  The index of the node having the minimal distance from source (and not handled yet).
 */
int findMinDistance(int distances[], List S) {
    int u = -1; /* Negative value is used as placeholder and returned only in case there is no direct path from the current node. */
    int min = INFTY;
    List copy = S;
    while (copy != NULL) {
        if (distances[copy->node] < min) {
            min = distances[copy->node];
            u = copy->node;
        }
        copy = copy->next;
    }
    return u;
}

/* Purpose: Computes the shortest path from some node to all other nodes using Dijkstra's Algorithm
            and prints the path and distance to the specified destination.
 * Input:   Indices of the starting city and the destination city.
 * Result:  Shortest path is computed and printed to terminal. In case it was not computed, prints unreachable.
 */
void findShortestPath(int startIndex, int endIndex) {
    int i, u;
    int distances[AMOUNTNODES]; /* Keeps track of distances from starting node to all other nodes. */
    int visited[AMOUNTNODES]; /* Keeps track of visited nodes when applying Dijkstra's Algo. */
    int previousNode[AMOUNTNODES];  /* Indices of the array are the cities, while the values are the indices of the previous cities within the shortest path. */

    List S = newEmptyList();    /* ToDo list used to keep track of nodes not visited yet during algorithm execution. */
    for (i = 0; i < AMOUNTNODES; i++) {
        distances[i] = (i == startIndex) ? 0 : INFTY; /* Set all initial distances to infinity, except for self. */
        S = addNode(i, 0, S);
    }

    while (!isEmptyList(S)) {
        u = findMinDistance(distances, S);
        if (u == -1) {  /* Index has remained negative, hence no city is reacheable from the current node. */
            break;
        }

        S = removeNode(S, u);   /* Remove the current node from ToDo list, since we are visiting it now. */
        List nodeNeighbours = adjacencyList[u]; /* Access the adjacency list of the current node. */
        while (nodeNeighbours != NULL) {    /* Iterate over all of the current visited node's neighbours in order to update the distances. */
            int temp = distances[u] + nodeNeighbours->weight;   /* Add the distances from start to current node and from current to the neighbour. */
            if (temp < distances[nodeNeighbours->node]) {   /* Check if the newly computed distance is less than the already established distance to that neighbours. */
                distances[nodeNeighbours->node] = temp; /* If so, update that distance to the shorter one. */
                previousNode[nodeNeighbours->node] = u; /* Set the current node as the previous for the neighbour, since we have update the route. */
            }
            nodeNeighbours = nodeNeighbours->next;
        }
    }
    freeList(S);

    if (distances[endIndex] == INFTY) { /* No path was found to the specified city. */
        printf("UNREACHABLE\n");
    } else {    /* Otherwise print the path and the distance. */
        printPath(previousNode, startIndex, endIndex);
        printf("%d\n", distances[endIndex]);
    }
}

/* Purpose: Similar to acceptDisruptions, we prompt the user for the cities which he/she wants to find the shortest path.
 * Result:  The shortest path (if existent) is printed to terminal.
 */
void acceptQueries() {
    int startIndex, endIndex;
    char startCity[15], endCity[15], linebreak;

    scanf("%c", &linebreak);
    scanf("%[^\n]", startCity);
    while (*startCity != '!') { /* After each pair of cities, we check for exclamation mark. */
        scanf("%c", &linebreak);
        scanf("%[^\n]", endCity);
        findCityIndices(startCity, endCity, &startIndex, &endIndex);
        findShortestPath(startIndex, endIndex);
        scanf("%c", &linebreak);
        scanf("%[^\n]", startCity);
    }
}
