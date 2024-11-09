#include <iostream>
#include <list>
#include "graph.h"
using namespace std;



int main() {
    Graph g(6);

    g.addEdge(0, 1);
    g.addEdge(1, 3);
    g.addEdge(0, 2);
    g.addEdge(0, 4);

    g.addEdge(2, 5);
    g.addEdge(2, 4);
    g.addEdge(2, 3);


    g.printGraph();

    g.mergeVertices(0, 2);
    cout << "Po scaleniu wierzchołków 0 i 2:" << endl;
    g.printGraph();

    return 0;  // Zwolnienie pamięci nastąpi automatycznie przy zakończeniu main()
}
