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


    Graph* j = new Graph(g.number_of_vertices());
    j->adjLists = g.adjLists;
    j->deleteEdge(0, 1);
    j->mergeVertices(0, 2);
    
    j->printGraph();
    cout << endl;
    g.printGraph();

    return 0;  
}
