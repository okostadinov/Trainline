/*                              DISCLAIMER:
**
**  Most of the functions are taken from the provided linked list library.
**  Some new functions are defined for the use case of this assignment.
**  In the descriptions I sometimes use "pointer to ListNode" instead of "pointer to list" although the are the same.
**  The reason for this is simply for comprehension. It makes more sense to say "pointer to list" when referring to the whole list,
**  while "pointer to ListNode" when referring to only one node in the linked list.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "GraphLib.h"

/* Purpose: As per function name.
 * Output:  null pointer.
 */
List newEmptyList() {
    return NULL;
}

/* Purpose: Creates a new list node and adds it to the front of the list.
 * Input:   node index n, edge weight w, and a pointer to a list.
 * Output:  Pointer to the new node at the front of the list.
 */
List addNode(int n, int w, List li) {
    List newNode = malloc(sizeof(struct ListNode));
    assert(newNode != NULL);
    newNode->node = n;
    newNode->weight = w;
    newNode->next = li;
    return newNode;
}

/* Purpose: Checks if the list in empty.
 * Input:   Pointer to a list.
 * Output:  1 if the list is empty, otherwise 0.
 */
int isEmptyList(List li) {
    return (li == NULL);
}

/* Purpose: Frees the whole linked list.
 * Input:   Pointer to a list.
 * Result:  All the nodes starting from the pointer are freed.
 */
void freeList(List li) {
    List li1;
    while (li != NULL) {
        li1 = li->next;
        free(li);
        li = li1;
    }
}

/* Purpose: Prints the city's name by accessing it in the cities array.
 * Input:   int index if a city.
 * Result:  The city's name is printed.
 */
void printCityName(int n) {
    printf("%s\n", cities[n]);
}

/* Purpose: As per function name.
 * Input:   Pointer to a list.
 * Output:  Pointer to the list starting from the second node. First one is freed.
 */
List removeFirstNode(List li) {
    List returnList;
    if (li == NULL) {
        abort();
    }
    returnList = li->next;
    free(li);
    return returnList;
}

/* Purpose: Removes a node from a list based on its data.
 * Input:   Pointer to a list and the data stored in the node which is to be removed.
 * Output:  Pointer to the same list without the node.
 */
List removeNode(List li, int n) {
    if (li == NULL) {
        return li;
    }
    if (li->node == n) {
        return removeFirstNode(li);
    }
    li->next = removeNode(li->next, n);
    return li;
}
