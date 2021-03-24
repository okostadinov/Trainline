#include "GraphOps.h"

/* Define our array of cities: Now each can be accessed by its respective index. E.g. cities[4] = Groningen,
and in the array of list pointers, adjacencyList[4] accessed Groningen's immediate neighbours. */
char *cities[] = { "Amsterdam", "Den Haag", "Den Helder", "Eindhoven", "Enschede", "Groningen", "Leeuwarden", "Maastricht", "Meppel", "Nijmegen", "Utrecht", "Zwolle" };

int main(int argc, char *argv[]) {
    makeGraph();
    acceptDisruptions();
    acceptQueries();
    freeGraph();
    return 0;
}
