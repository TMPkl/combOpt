#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <queue>
#include <unordered_set>

class Graph {
    
public:
    int numVertices;
    std::vector<std::vector<int>> adjLists;
    Graph(int vertices);
    ~Graph();  // Deklaracja destruktora
    void addEdge(int src, int dest);
    void printGraph();
    void deleteEdge(int edge1, int edge2);
    void mergeVertices(int vertex1, int vertex2);
    int number_of_vertices();
    int number_of_edges();
    int find_max_degree_vertice();
    bool is_tree();
    bool is_edge(int src, int dest);
    Graph* extract_neighboring_subgraph(int vertex);
    std::vector<int> DFS();
};

Graph::Graph(int vertices) {
    numVertices = vertices;
    adjLists.resize(vertices);
    adjLists.shrink_to_fit();  
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
bool Graph::is_edge(int src, int dest) {
    if (src >= 0 && src < numVertices && dest >= 0 && dest < numVertices) {
        for (auto it = adjLists[src].begin(); it != adjLists[src].end(); ++it) {
            if (*it == dest) {
                std::cerr << "Edge " << src << " -- " << dest << " exists." << std::endl;
                return 1;
            }
        }
        std::cerr << "Edge " << src << " -- " << dest << " does not exist." << std::endl;
        return 0;
    } else {
        std::cerr << "Error: Vertex index out of bounds." << std::endl;
        return 0;
    }
}

void Graph::printGraph() {
   // std::cout << "debugigng seg fault" << std::endl;
    for (int i = 0; i < numVertices; ++i) {

        for (auto it = adjLists[i].begin(); it != adjLists[i].end(); ++it) {
            if (i < *it) {
                std::cout <<  i<<" -- " << *it<<";"<< std::endl;
            }
        }
    }
    //std::cout << "debugigng seg fault, uff it is not here" << std::endl;

}
void Graph::deleteEdge(int edge1, int edge2)
{
    if(edge1 == edge2 || !this->is_edge(edge1,edge2))
    {
        std::cerr<<"Deleting edge that isnt possible to exist (a = b)"<<std::endl;
        return;
    }


    auto it1 = std::find(adjLists[edge1].begin(), adjLists[edge1].end(), edge2);
    if (it1 != adjLists[edge1].end()) {
        adjLists[edge1].erase(it1);
        adjLists[edge1].shrink_to_fit();

    }

    auto it2 = std::find(adjLists[edge2].begin(), adjLists[edge2].end(), edge1);
    if (it2 != adjLists[edge2].end()) {
        adjLists[edge2].erase(it2);
        adjLists[edge2].shrink_to_fit();
    }
    return;
}



void Graph::mergeVertices(int vertex_to_merge, int vertex_to_delete) {
    if (vertex_to_merge >= numVertices || vertex_to_delete >= numVertices || vertex_to_merge < 0 || vertex_to_delete < 0) {
        std::cerr << "Invalid vertex index in mergeVertices." << std::endl;
        return;
    }

    std::vector<int> neighbors_to_process(adjLists[vertex_to_delete]);
    for (int neighbor : neighbors_to_process) {
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

    for (int i = 0; i < adjLists.size(); ++i) {
        for (int &neighbor : adjLists[i]) {
            if (neighbor > vertex_to_delete) {
                neighbor--;
            }
        }
    }

    numVertices = adjLists.size();
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

int Graph::find_max_degree_vertice(){
    adjLists.shrink_to_fit();
    for(int i = 0; i < numVertices; i++)
    {
        adjLists[i].shrink_to_fit();
    }
    adjLists.shrink_to_fit();

    int max_degree = 0;
    int vertice = 0;
    if (this->adjLists.size()==0)
    {
    std::cerr << "Error: Graph is empty." << std::endl;
        
    return -1;
    }
    
    if(numVertices == 0)
    {
        std::cerr << "Error: Graph is empty." << std::endl;
        
        return -1;
    }
    for(int i = 0; i < numVertices; i++)
    {
        if(adjLists[i].size() > max_degree)
        {
            max_degree = adjLists[i].size();
            vertice = i;
        }
    }
    return vertice;
}


Graph* Graph::extract_neighboring_subgraph(int vertex) {
    if (vertex < 0 || vertex >= numVertices) {
        std::cerr << "Invalid vertex index." << std::endl;
        return nullptr;
    }

    std::vector<bool> visited(numVertices, false);
    std::queue<int> q;
    q.push(vertex);
    visited[vertex] = true;

    std::vector<int> component;
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        component.push_back(current);

        for (int neighbor : adjLists[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    // Identify vertices to keep (not part of the component containing 'vertex')
    std::vector<int> vertices_to_keep;
    for (int i = 0; i < numVertices; ++i) {
        if (!visited[i]) {
            vertices_to_keep.push_back(i);
        }
    }

    // Create the new graph with remapped vertices
    Graph* new_graph = new Graph(vertices_to_keep.size());
    std::unordered_map<int, int> vertex_map; // Map old to new indices
    for (int i = 0; i < vertices_to_keep.size(); ++i) {
        vertex_map[vertices_to_keep[i]] = i;
    }

    for (int old_vertex : vertices_to_keep) {
        std::unordered_set<int> added_edges; // To avoid duplicates
        for (int neighbor : adjLists[old_vertex]) {
            if (vertex_map.find(neighbor) != vertex_map.end() && added_edges.find(neighbor) == added_edges.end()) {
                if(old_vertex > neighbor || new_graph->is_edge(vertex_map[neighbor], vertex_map[old_vertex]))
                {
                    continue;
                }
                new_graph->addEdge(vertex_map[old_vertex], vertex_map[neighbor]);
                added_edges.insert(neighbor);
            }
        }
    }

    if(new_graph->adjLists.size() == 0)
    {
        Graph* empty_graph = new Graph(0);
        return empty_graph;
    }

    this->adjLists.resize(this->adjLists.size()-new_graph->adjLists.size());
    this->adjLists.shrink_to_fit();
    this->numVertices = this->adjLists.size();
    return new_graph;
}

std::vector<int> Graph::DFS()
{
    std::vector<int> visited;
    std::vector<int> stack;
    stack.push_back(0);
    while(stack.size() > 0)
    {
        int current = stack.back();
        stack.pop_back();
        visited.push_back(current);
        for(int i = 0; i < adjLists[current].size(); i++)
        {
            stack.push_back(adjLists[current][i]);
        }
    }
    return visited;
}

bool Graph::is_tree() {
    if (number_of_edges() != numVertices - 1) {
        return false;
    }

    std::vector<bool> visited(numVertices, false);

    // Helper function for DFS
    std::function<bool(int, int)> dfs = [&](int vertex, int parent) {
        visited[vertex] = true;
        for (int neighbor : adjLists[vertex]) {
            if (!visited[neighbor]) {
                if (!dfs(neighbor, vertex)) {
                    return false;  // Found a cycle
                }
            } else if (neighbor != parent) {
                return false;  // Cycle detected
            }
        }
        return true;
    };

    // Check for cycle and connectivity from vertex 0
    if (!dfs(0, -1)) {
        return false;
    }

    // Check if all vertices were visited (graph is connected)
    for (bool v : visited) {
        if (!v) {
            return false;
        }
    }

    return true;
}





