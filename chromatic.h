#ifndef chromatic_H
#define chromatic_H

#include <iostream>
#include <vector>
#include <list>
#include "graph.h"




class Chromatic_polynomial {
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
    unsigned long long int  count_number_of_colorings(unsigned long long int  number_of_colors);
};

Chromatic_polynomial recusive_chromatic_counting(Graph graph);

#endif // chromatic_H