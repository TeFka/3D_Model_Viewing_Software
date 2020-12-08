#include <iostream>
#include <vector>

#ifndef VECTOR3D_H
#define VECTOR3D_H

class Vector3D
{
private:
    int ID;
    double x, y, z;

public:
    //default
    Vector3D();

    //constructor
    Vector3D(double,double,double);

    //destructor
    ~Vector3D();

    //settersgfjkglj
    void setID(int);
    void setx(double);
    void sety(double);
    void setz(double);

    //getters
    int getID();
    double getx();
    double gety();
    double getz();


    //operations
    //Vector3D (const Vector3D &);
    Vector3D operator+(const Vector3D &); //addition
    Vector3D operator-(const Vector3D &); //subtraction
    double dot_product(const Vector3D &); //scalar product
    Vector3D cross_product(const Vector3D &); //vector product

};

#endif // VECTOR3D_H
