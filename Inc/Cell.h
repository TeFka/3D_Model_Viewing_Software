//------------------------------------------------------------------
class cell
{
protected:
    colour col;
    int ID;
    std::vector<vertice> cellvertices

    ...centre of gracity
    material ID
    weight
    density

public:
    virtual double getvolume();
    void setcolour( colour c);
};
//------------------------------------------------------------------
//defining functions of the cell class
double cell::getvolume()
{
    return 0;//not actually calculating volume of cell here so only dummy function is needed
}

void cell::setcolour(colour c)
{
    this->col = c;//this sets the colour for all the cells
}
//------------------------------------------------------------------------
class tetrahedron : public cell
{
private:
    vector3d p1, p2, p3, p4;
public:
    tetrahedron(vector3d p1, p2, p3, p4);
    double getvolume();
};
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
//---------------------------------------------------------------
class pyramid : public cell
{
private:
    vector3d p1, p2, p3, p4, p5;
public:
    pyramid(vector3d p1, p2, p3, p4, p5);
    double getvolume();
};
//defining functions for pyramid
pyramid::pyramid(vector3d p1, p2, p3, p4, p5)
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
//---------------------------------------------------------------
class hexahedron : public cell
{
private:
    vector3d p1, p2, p3, p4, p5, p6, p7, p8;
public:
    hexahedron(vector3d p1, p2, p3, p4, p5, p6, p7, p8);
    double getvolume();
};
//defining functions for hexahedron
hexahedron::hexahedron(vector3d p1, p2, p3, p4, p5, p6, p7, p8)
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



