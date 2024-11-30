#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <list>

class Graph {
private:

public:
    int numVertices; // Liczba wierzchołków

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
    int number_of_edges();
    int find_max_degree_vertice();
    std::vector<std::vector<int>> adjLists; // Lista sąsiedztwa
    bool is_tree();
    Graph* extract_neighboring_subgraph(int vertex);
    std::vector<int> DFS();
    bool is_edge(int src, int dest);


};

#endif // GRAPH_H
