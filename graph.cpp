#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

class Graph {
private:
    int numVertices;
    
public:
    std::vector<std::vector<int>> adjLists;
    Graph(int vertices);
    ~Graph();  // Deklaracja destruktora
    void addEdge(int src, int dest);
    void printGraph();
    void deleteEdge(int edge1, int edge2);
    void mergeVertices(int vertex1, int vertex2);
    int number_of_vertices();
    int number_of_edges();
    // int number_of_edges();

};

Graph::Graph(int vertices) {
    numVertices = vertices;
    adjLists.resize(vertices);
}

int Graph::number_of_vertices()
{
    return numVertices;
}
// int Graph::number_od_edges()
// {
//     int number_of_vertices = 0; 
//     for(int i = 0; i < numVertices; i++)
//     {
//         number_of_vertices += adjLists[i].size();
//     }
//     return number_of_vertices;
// }


// Definicja destruktora
Graph::~Graph() {
    for (int i = 0; i < numVertices; ++i) {
        adjLists[i].clear();
    }
    adjLists.clear();  
}
void Graph::addEdge(int src, int dest) {
    if (src >= 0 && src < numVertices && dest >= 0 && dest < numVertices) {
        adjLists[src].push_back(dest);
        adjLists[dest].push_back(src);
    } else {
        std::cerr << "Error: Vertex index out of bounds." << std::endl;
    }
}

void Graph::printGraph() {
    for (int i = 0; i < numVertices; ++i) {

        for (auto it = adjLists[i].begin(); it != adjLists[i].end(); ++it) {
            if (i < *it) {
                std::cout <<  i<<" -- " << *it<<";"<< std::endl;
            }
        }
    }
}
void Graph::deleteEdge(int edge1, int edge2)
{
    for (auto it = adjLists[edge1].begin(); it != adjLists[edge1].end(); ++it) {
        if (*it == edge2) {
            adjLists[edge1].erase(it);
            adjLists[edge2].erase(std::find(adjLists[edge2].begin(), adjLists[edge2].end(), edge1));
            break;
        }
    }
}


void Graph::mergeVertices(int vertex_to_merge, int vertex_to_delete) {
    for (int neighbor : adjLists[vertex_to_delete]) {
        if (neighbor != vertex_to_merge) {  
            if (std::find(adjLists[vertex_to_merge].begin(), adjLists[vertex_to_merge].end(), neighbor) == adjLists[vertex_to_merge].end()) {
                adjLists[vertex_to_merge].push_back(neighbor);
            }
            for (int &n : adjLists[neighbor]) {
                if (n == vertex_to_delete) {
                    n = vertex_to_merge;  
                }
            }
        }
    }

    for (int i = 0; i < numVertices; ++i) {
        adjLists[i].erase(std::remove(adjLists[i].begin(), adjLists[i].end(), vertex_to_delete), adjLists[i].end());
    }

    adjLists[vertex_to_delete].clear();

    adjLists.erase(adjLists.begin() + vertex_to_delete);
    numVertices--;

    for (int i = 0; i < numVertices; ++i) {
        for (int &neighbor : adjLists[i]) {
            if (neighbor > vertex_to_delete) {
                neighbor--; 
            }
        }
    }

    std::cout << "Vertices " << vertex_to_delete << " and " << vertex_to_merge << " merged and indices updated successfully." << std::endl;
}
int Graph::number_of_edges()
{
    int number_of_edges = 0; 
    for(int i = 0; i < numVertices; i++)
    {
        number_of_edges += adjLists[i].size();
    }
    return number_of_edges/2;
}