#include <iostream>
#include <vector>
#include <list>
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
};

Chromatic_polynomial::Chromatic_polynomial(int deg) {
    degree = deg;
    coefficients.resize(degree + 1);
}
Chromatic_polynomial::~Chromatic_polynomial() {
    coefficients.clear();
}

void Chromatic_polynomial::multiply(Chromatic_polynomial &poly) {
    int new_degree = degree + poly.get_degree();
    std::vector<int> new_coefficients(new_degree + 1, 0);
    for (int i = 0; i <= degree; ++i) {
        for (int j = 0; j <= poly.get_degree(); ++j) {
            new_coefficients[i + j] += coefficients[i] * poly.get_coefficient(j);
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
    } else {
        std::cerr << "Error: Coefficient index out of bounds." << std::endl;
        return 0;
    }
}
void Chromatic_polynomial::set_coefficient(int deg, int value) {
    if (deg >= 0 && deg <= degree) {
        coefficients[deg] = value;
    } else {
        std::cerr << "Error: Coefficient index out of bounds." << std::endl;
    }
}
void Chromatic_polynomial::subtract(Chromatic_polynomial &poly) {
    int new_degree = std::max(degree, poly.get_degree());
    std::vector<int> new_coefficients(new_degree + 1, 0);
    for (int i = 0; i <= new_degree; ++i) {
        new_coefficients[i] = get_coefficient(i) - poly.get_coefficient(i);
    }
    degree = new_degree;
    coefficients = new_coefficients;
}
void Chromatic_polynomial::print_chromatic() {
    for (int i = degree; i >= 0; --i) {
        if (coefficients[i] != 0) {
            if (i == 0) {
                std::cout << coefficients[i];
            } else if (i == 1) {
                std::cout << coefficients[i] << "x + ";
            } else {
                std::cout << coefficients[i] << "x^" << i << " + ";
            }
        }
    }
    std::cout << std::endl;
}
int Chromatic_polynomial::check_if_possible() {
    return 1; 
} 

Chromatic_polynomial recusive_chromatic_counting(Graph graph){

    if(graph.number_of_vertices() == 1)
    {   Chromatic_polynomial res(1);
        res.set_coefficient(0,1);
        return res;
    }
    if (graph.number_of_edges() == 0)
    {
        Chromatic_polynomial res(graph.number_of_vertices());
        res.set_coefficient(graph.number_of_vertices(),1);
        for(int i = 0; i<graph.number_of_vertices();i++)
        {
            res.set_coefficient(i,0);

        }
        return res;
    }
    else
        std::cerr << "Error: Graph has edges, recursive counting not implemented." << std::endl;
        exit(EXIT_FAILURE);}
