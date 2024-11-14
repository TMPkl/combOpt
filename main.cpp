#include <iostream>
#include <list>
#include "graph.h"
#include "chromatic.h"
using namespace std;



int main() {
    Graph g(5);
    g.addEdge(0, 2);
    g.addEdge(0, 4);
    g.addEdge(4, 2);
    g.addEdge(2, 3);
    g.addEdge(2, 1);
    //for this data the answe should be 1x^5 + -5x^4 + 9x^3 + -7x^2 + 2x + 0
    
    // a.set_coefficient(1, 1);
    // a.set_coefficient(0, -1);

    // b.set_coefficient(1, 1);
    // b.set_coefficient(0, 0);

    // a.multiply(b);
    // a.print_chromatic();

    
    Chromatic_polynomial poly = recusive_chromatic_counting(g);
    poly.print_chromatic();
   unsigned long long int i = 1;
    while (i<1000){

    cout <<"for "<<i<<" colors there are :" <<poly.count_number_of_colorings(i)<<" posible ways to lagaly colour" << endl;
    i++;
    }
    
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
