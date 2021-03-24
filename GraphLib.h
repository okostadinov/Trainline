/* For this graph we use an adjacency list representation and an array of strings for the node names.
** This means that each node is accessed via indexing its value stored in the string array.
** And more importantly, we create a second array storing pointers to linked lists - the adjacency lists.
** Each pointer at a specific index is associated with the same index in the string array.
** Furthermore, each pointer points to the head of a linked list which contains the neighbours of the given node.
** Each item is defined as a ListNode and contains its respective index in the string array,
** the weight of the edge between it and the starting node, as well as a pointer to the next item in the linked list.
*/

#ifndef GRAPHLIB_H
#define GRAPHLIB_H

#define AMOUNTNODES 12  /* There are 12 cities used in the graph. */
#define INFTY 1000000 /* Unrealistically high number to represent infinity. Used in Dijkstra's Algorithm. */
extern char *cities[AMOUNTNODES]; /* Array of strings which stores each city's name. */

typedef struct ListNode* List;

struct ListNode {
    int node;   /* This is the index of the city stored in the cities array. */
    int weight; /* Since we are accessing these nodes from some starting node, this value specifies the weight of the edge between them. */
    List next;  /* The adjacency list is a linked list, hence we need a pointer to the next neighbour of the starting node. */
};

List adjacencyList[AMOUNTNODES];    /* For 12 cities there will be 12 pointers to each city's direct neighbours. */

List newEmptyList();
List addNode(int n, int w, List li);
int isEmptyList(List li);
void freeList(List li);
void printCityName(int n);
List removeFirstNode(List li);
List removeNode(List li, int n);

#endif
