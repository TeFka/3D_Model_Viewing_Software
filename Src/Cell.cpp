#include <iostream>
#include <stdio.h>
#include "../inc/Cell.h"
//step 1:get vertices
//step 2:count how many vertices there are, this will tell us the shape
//step 3:do calculations to find volume
using namespace std;
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









