#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <set>

using namespace std;

void generateGraph(int vertices, const string &filename) {
    srand(time(0));
    
    set<pair<int, int>> edges;
    int maxEdges = vertices * (vertices - 1) / 2; 
    int numEdges = rand() % (maxEdges + 1);     

    while (edges.size() < numEdges) {
        int u = rand() % vertices;
        int v = rand() % vertices;
        

        if (u != v && edges.find({min(u, v), max(u, v)}) == edges.end()) {
            edges.insert({min(u, v), max(u, v)});
        }
    }

    ofstream file(filename);
    file << vertices << " " << edges.size() << "\n"; 
    for (const auto &edge : edges) {
        file << edge.first << " " << edge.second << "\n";
    }

    file.close();
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <number_of_vertices>" << endl;
        return 1;
    }

    int vertices = atoi(argv[1]);
    if (vertices < 1) {
        cout << "Number of vertices must be at least 1." << endl;
        return 1;
    }

    // File to output the graph
    string filename = "graph_output.txt";
    generateGraph(vertices, filename);

    cout << "Graph generated and written to " << filename << endl;
    return 0;
}
