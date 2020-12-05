#include <iostream>
#include <stdio.h>
//#include "main.h"
#include "../Inc/Cell.h"
//step 1:get vertices
//step 2:count how many vertices there are, this will tell us the shape
//step 3:do calculations to find volume
using namespace std;

    double cell::getvolume()
{
    return 0;//not actually calculating volume of cell here so only dummy function is needed
}
void cell::setcolour(colour c)
{
    this->col = c;//this sets the colour for all the cells
}

//--------------------------------------------------------------------------------
//defining functions for the tetrahedron
tetrahedron::tetrahedron(vector3d p1, p2, p3, p4)
{
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    this->p4 = p4;
}
double tetrahedron::getvolume()//will overwrite original getvolume function in cell class
{
    //code to calculate volume of...
}
//--------------------------------------------------------------------------------------
//defining functions for pyramid
pyramid::pyramid(vector3d p1, p2, p3, p4, p5)//constructor
{
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    this->p4 = p4;
    this->p5 = p5;
}

pyramid::getvolume()
{
//   ...
}
//---------------------------------------------------------------------------------
//defining functions for hexahedron
hexahedron::hexahedron(vector3d p1, p2, p3, p4, p5, p6, p7, p8)//constructor
{
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    this->p4 = p4;
    this->p5 = p5;
    this->p6 = p6;
    this->p7 = p7;
    this->p8 = p8;
}

hexahedron::getvolume()
{
    //...
}
//-------------------------------------------------------------------------------
int main()
{
    cell *cells[3];//cells is an array which points to each shape class
    tetrahedron t;
    pyramid p;
    hexahedron h;
    colour col;
    int i;

    cells[0] = &t;
    cells[1] = &p;
    cells[2] = &h;

    for(i=0;i<3;i++)
    {
        cells[i]->setcolour( col );
        cout<< "volume of cell" << i << "is" << cells[i]->getvolume() << endl;
    }
}








