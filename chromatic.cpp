#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include "graph.h"



class Chromatic_polynomial {  //// niumerujemy od najwyższej potęgi do 0 : 3x^3 + 2x^2 + 1x^1 + 0x^0 = 3,2,1,0 dla coefficients
private:
    int degree;
    std::vector<int> coefficients;
public:
    Chromatic_polynomial(int deg);
    ~Chromatic_polynomial();
    void multiply(Chromatic_polynomial &poly);
    void subtract(Chromatic_polynomial &poly);
    void print_chromatic();
    void set_coefficient(int deg, int value);
    int get_coefficient(int deg);
    int get_degree();
    int check_if_possible();
    unsigned long long int count_number_of_colorings(long long unsigned int number_of_colors);
};
unsigned long long int  Chromatic_polynomial::count_number_of_colorings(unsigned long long int number_of_colors) {
    long long int result = 0;
    for(int i = 0; i<=degree;i++)
    {
        result += coefficients[i]*pow(number_of_colors,i); //liczymy wartość wielomianu dla liczby kolorów - metoda hornera Ean wing wing
    }
    return result;
}

Chromatic_polynomial::Chromatic_polynomial(int deg) {
    degree = deg;
    coefficients.resize(degree + 1);
}
Chromatic_polynomial::~Chromatic_polynomial() {
    coefficients.clear();
}

void Chromatic_polynomial::multiply(Chromatic_polynomial &poly) {
    int new_degree = degree + poly.get_degree();
    if (new_degree < 0) {
        std::cerr << "Error: Invalid polynomial degree during multiplication." << std::endl;
        return;
    }

    std::vector<int> new_coefficients(new_degree + 1, 0);
    for (int i = 0; i <= degree; ++i) {
        for (int j = 0; j <= poly.get_degree(); ++j) {
            if (i + j <= new_degree) {
                new_coefficients[i + j] += coefficients[i] * poly.get_coefficient(j);
            }
        }
    }

    degree = new_degree;
    coefficients = new_coefficients;
}
int Chromatic_polynomial::get_degree() {
    return degree;
}
int Chromatic_polynomial::get_coefficient(int deg) {
    if (deg >= 0 && deg <= degree) {
        return coefficients[deg];
    } else if (deg > degree) {
        return 0;
    } else {
        std::cerr << "Error: Coefficient index out of bounds." << std::endl;
        return 0;
    }
}
void Chromatic_polynomial::set_coefficient(int deg, int value) {
    if (deg < 0) {
        std::cerr << "Error: Coefficient index out of bounds (negative)." << std::endl;
        return;
    }
    if (deg > degree) {
        coefficients.resize(deg + 1, 0);
        degree = deg;
    }
    coefficients[deg] = value;
}

void Chromatic_polynomial::subtract(Chromatic_polynomial &poly) {
    int new_degree = std::max(degree, poly.get_degree());
    
    // Resize if necessary to avoid out-of-bounds access
    if (degree < new_degree) {
        coefficients.resize(new_degree + 1, 0);
        degree = new_degree;
    }
    
    std::vector<int> new_coefficients(new_degree + 1, 0);
    for (int i = 0; i <= new_degree; ++i) {
        new_coefficients[i] = get_coefficient(i) - poly.get_coefficient(i);
    }
    coefficients = new_coefficients;
}


void Chromatic_polynomial::print_chromatic() {
    for (int i = degree; i >= 0; --i) {
            if (i == 0) {
                std::cout << coefficients[i] << std::endl;
            } else if (i == 1) {
                std::cout << coefficients[i] << "x + ";
            } else {
                std::cout << coefficients[i] << "x^" << i << " + ";
            }
    }
    std::cout << std::endl;
}
int Chromatic_polynomial::check_if_possible() {
    return 1; 
} 

Chromatic_polynomial recusive_chromatic_counting(Graph input_graph) {
    input_graph.adjLists.shrink_to_fit();

    for (int i = 0; i < input_graph.number_of_vertices(); i++) {
        input_graph.adjLists[i].shrink_to_fit();
    }
    input_graph.adjLists.shrink_to_fit();

    std::cerr << "Processing graph:\n";
    input_graph.printGraph();

    if (input_graph.number_of_edges() == 0 && input_graph.number_of_vertices() == 0) {
        Chromatic_polynomial res(0);
        res.set_coefficient(0, 1);
        return res;
    }

    if (input_graph.number_of_vertices() == 2 && input_graph.number_of_edges() == 1) {
        Chromatic_polynomial res(2);
        res.set_coefficient(2, 1);
        res.set_coefficient(1, -1);
        res.set_coefficient(0, 0);
        return res;
    }

    if (input_graph.number_of_vertices() == 1) {
        Chromatic_polynomial res(1);
        res.set_coefficient(1, 1);
        res.set_coefficient(0, 0);
        return res;
    }

    if (input_graph.number_of_edges() == 0) {
        Chromatic_polynomial res(input_graph.number_of_vertices());
        res.set_coefficient(input_graph.number_of_vertices(), 1);
        for (int i = 0; i < input_graph.number_of_vertices(); i++) {
            res.set_coefficient(i, 0);
        }
        return res;
    }

    if (input_graph.is_tree()) {
        Chromatic_polynomial res(1);
        Chromatic_polynomial multiplier(1);
        res.set_coefficient(1, 1);
        res.set_coefficient(0, 0);
        multiplier.set_coefficient(1, 1);
        multiplier.set_coefficient(0, -1);

        std::cerr << "Graph is a tree with " << input_graph.number_of_vertices() << " vertices.\n";

        for (int i = 0; i < input_graph.number_of_vertices() - 1; i++) {
            res.multiply(multiplier);
        }

        return res;
    }

    // Extract unconnected subgraph
    Graph *unconnected = input_graph.extract_neighboring_subgraph(0);
    if (!unconnected) {
        std::cerr << "Error: Failed to extract unconnected subgraph.\n";
        exit(EXIT_FAILURE);
    }
    Chromatic_polynomial unconnected_poly = recusive_chromatic_counting(*unconnected);
    delete unconnected;

    // Merge vertices
    Graph *merged_vertices = new Graph(input_graph.number_of_vertices());
    merged_vertices->adjLists = input_graph.adjLists;

    int max_degree_vertice = merged_vertices->find_max_degree_vertice();
    if (max_degree_vertice >= 0 && !merged_vertices->adjLists[max_degree_vertice].empty()) {
        merged_vertices->mergeVertices(max_degree_vertice, merged_vertices->adjLists[max_degree_vertice][0]);
    } else {
        std::cerr << "Error: Invalid vertex for merging.\n";
        exit(EXIT_FAILURE);
    }

    // Delete edge
    Graph *deleted_edge = new Graph(input_graph.number_of_vertices());
    deleted_edge->adjLists = input_graph.adjLists;

    if (max_degree_vertice >= 0 && !deleted_edge->adjLists[max_degree_vertice].empty()) {
        deleted_edge->deleteEdge(max_degree_vertice, deleted_edge->adjLists[max_degree_vertice][0]);
    } else {
        std::cerr << "Error: Invalid edge for deletion.\n";
        exit(EXIT_FAILURE);
    }

    // Recursive calls
    std::cerr << "Recursively calling for deleted_edge...\n";
    Chromatic_polynomial main_de = recusive_chromatic_counting(*deleted_edge);
    delete deleted_edge;

    std::cerr << "Recursively calling for merged_vertices...\n";
    Chromatic_polynomial main_mv = recusive_chromatic_counting(*merged_vertices);
    delete merged_vertices;

    main_de.subtract(main_mv);
    main_de.multiply(unconnected_poly);

    return main_de;
}
