#include <iostream>
#include <vector>

#ifndef VECTOR_H
#define VECTOR_H

class vector
{
public:
    double x, y, z;

    //default
    vector();

    //constructor
    vector(double xc, yc, zc);

    //destructor
    ~vector();

    //setters
    void setx(double xc);
    void sety(double yc);
    void setz(double zc);

    //getters
    /*double getx(){return x};
    double gety(){return y};
    double getz(){return z};*/


    //operations
    vector (const vector &vec);
    vector operator+(const vector &vec); //addition
    vector operator-(const vector &vec); //subtraction
    double dot_product(const vector &vec); //scalar product
    double cross_product(const vector &vec); //vector product

    //destructor
    ~vector();
};

#endif // VECTOR_H
