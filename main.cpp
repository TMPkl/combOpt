#include <iostream>
#include <list>
#include "graph.h"
#include "chromatic.h"
using namespace std;



int main() {
    Graph g(4);
   
    g.addEdge(0,1);
    g.addEdge(0,2);
    g.addEdge(1,3);
    g.addEdge(0,3);
    g.addEdge(3,2);

    cout << endl;
    g.printGraph();

    Chromatic_polynomial a = recusive_chromatic_counting(g);
    a.print_chromatic();
    
    return 0;  
}
