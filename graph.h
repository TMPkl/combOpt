#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <list>

class Graph {
private:
    int numVertices; // Liczba wierzchołków

public:
    // Konstruktor
    Graph(int vertices);
    
    // Destruktor
    ~Graph();

    // Metody publiczne
    void addEdge(int src, int dest);  // Dodanie krawędzi
    void printGraph();                // Wydrukowanie grafu
    void deleteEdge(int edge1, int edge2);
    void mergeVertices(int vertex1, int vertex2);
    int number_of_vertices();
    std::vector<std::vector<int>> adjLists; // Lista sąsiedztwa


};

#endif // GRAPH_H
