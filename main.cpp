#include <iostream>
#include <list>
#include "graph.h"
#include "chromatic.h"
using namespace std;



int main() {
    Graph g(3);
    g.addEdge(1, 0);
    g.addEdge(1, 2);

    Chromatic_polynomial a(2);
    Chromatic_polynomial b(1);

    // a.set_coefficient(1, 1);
    // a.set_coefficient(0, -1);

    // b.set_coefficient(1, 1);
    // b.set_coefficient(0, 0);

    // a.multiply(b);
    // a.print_chromatic();

    if (g.is_tree()) {
        std::cout << "The graph is a tree." << std::endl;
    } else {
        std::cout << "The graph is not a tree." << std::endl;
    }
    Chromatic_polynomial poly = recusive_chromatic_counting(g);
    poly.print_chromatic();
    // g.addEdge(2, 5);
    // g.addEdge(2, 4);
    // g.addEdge(2, 3);


    // Graph* j = new Graph(g.number_of_vertices());
    // j->adjLists = g.adjLists;
    // j->deleteEdge(0, 1);
    // j->mergeVertices(0, 2);
    
    // j->printGraph();
    // cout << endl;
    // g.printGraph();

    // Chromatic_polynomial poly(3);
    // poly.set_coefficient(0,1);
    // poly.set_coefficient(1,3);
    // poly.set_coefficient(2,8);

    // poly.print_chromatic();

    // Chromatic_polynomial mult(2);
    // mult.set_coefficient(0,1);
    // mult.set_coefficient(1,2);

    // poly.multiply(mult);

    // poly.print_chromatic();


    return 0;  
}
