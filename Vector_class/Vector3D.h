#include <iostream>
#include <vector>

#ifndef VECTOR3D_H
#define VECTOR3D_H

class Vector3D
{
public:
    double x, y, z;

    //default
    Vector3D();

    //constructor
    Vector3D(double xc, yc, zc);

    //destructor
    ~Vector3D();

    //setters
    void setx(double xc);
    void sety(double yc);
    void setz(double zc);

    //getters
    /*double getx(){return x};
    double gety(){return y};
    double getz(){return z};*/


    //operations
    vector (const Vector3D &vec);
    vector operator+(const Vector3D &vec); //addition
    vector operator-(const Vector3D &vec); //subtraction
    double dot_product(const Vector3D &vec); //scalar product
    vector cross_product(const Vector3D &vec); //vector product

};

#endif // VECTOR3D_H
