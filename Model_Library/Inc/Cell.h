/*! \file Cell.h File Reference

    \author   \n Copyright Code part: Michael Michael (StudentID: 20143147)
              \n Documentation  part: Chen xu  (StudentID: 20187733)

    \brief    Required header files: iostream(for printing with cout), vector, string, fstream,
                                     Vector3D.h, Material.h, Cell.h

*/

#include <iostream>
#include <vector>
#include "../Inc/Vector3D.h"
#include "../Inc/Material.h"

#ifndef CELL_H
#define CELL_H

/*! \class 'Cell'
    \brief cell class describes various parameters of the shape such as how many vertices it has, their positions, and the material it is made out of
*/

class Cell
{
protected:
    int ID;
    int type;
    int materialID;
    double weight;
    double volume;

    Vector3D centre_of_gravity;

    /*! array of all indices which each correspond to a vertex and its positions.  \n
        knowledge of the vertices position is requited for volume calculations.*/
    std::vector<int> indices;
public:
    //! Default.
	Cell();

    //! cell class constructor.
    Cell(int,int,int,std::vector<int>);

    //! cell class copy constructor.
    Cell(const Cell&);

    //! cell class destructor.
    ~Cell();

//! get functions:

    /*!
    function of cell class,getID  \n
    function to get ID of cell
    */
    int getID();

    /*! function of cell class,getType. \n
        function to get type of cell.
    */
    int getType();

    /*! function of cell class,getMaterialID. \n
        function to get ID of the material, to gain access of the density of material, needed for weight calculation.
    */
    int getMaterialID();

    /*! function of cell class, getIndices. \n
       function to get indice array of model.
    */
    std::vector<int> getIndices();
    /*! function of cell class, getCentreOFGravity. \n
        function to find the centre of gravity of the cell.
    */
    Vector3D getCentreOfGravity();
    /*! function of cell class, getWeight.  \n
       function to find the weight of the cell.
       \n Argument: none
       \return weight (double)
    */
   double getWeight();
    /*! function of cell class, getVolume.  \n
        function of find the volume of the cell.
        \n Argument: none
        \return volume (double)
    */
   double getVolume();

    /*! function of cell class, setID \n
       function to set ID of cell
    */
    void setID(int);

    /*! function of cell class, setID \n
       function to set type of cell
    */
    void setType(int);

    /*! function of cell class, setID \n
       function to set material ID of cell
    */
    void setMaterialID(int);

    /*! function of cell class, setID \n
       function to set indices of cell
    */
    void setIndices(std::vector<int>);

    void pushIndice(int);
    void insertIndice(int,int);
    void setIndice(int,int);

//! calculation functions:

    /*! function of class Cell calcWeight().   \n
        function to calculate weight of the cell
    */
    void calcWeight(std::vector<Material>);
    /*! function of class Cell calcCenterOfGravity().  \n
        function to calculate center of gravity position of the cell.
        \n Argument: calcCentreOfGravity(std::vector<Vector3D> vectors)
        \return Centre_of_gravity(Vector3)(model center value updated)
        \note
        \n 1) Model center of gravity will become {0,0,0} if vector array is empty.
    */
    void calcCentreOfGravity(std::vector<Vector3D>);

};


/*!  \class Tetrahedron
     \brief subclass of class cell.
*/
class Tetrahedron : public Cell
{
private:

public:


	Tetrahedron();//! Default


    Tetrahedron(int,int,int,std::vector<int>,std::vector<Vector3D>,std::vector<Material>);//! subclass tetrahedron constructor.


    Tetrahedron(const Cell&);//! copy contructor.

    ~Tetrahedron(); //! destructor.

    /*!\n              _   _    _
    \n Vtetra = 1/6|(a x b) * c|

    \n              __   __    __
    \n Vtetra = 1/6|(AB x AC) * AD|

    \n       __
    \n to get AB for example, the subtraction function should be used to subtract vector A with Vector B
    \n eg: A(2,3,4) B(5,4,3) AB = (5-2, 4-3,3-4) = (3, 1, -1)

    \n     __  __     __                                                                             __   __
    \n once AB, AC and AD have been aquired, use cross product function to achieve the calculation of AB x AC
    \n The next step is to do the dot product of (AB x AC) and AD, using the dot product function in the vector class
    \n find modulus of this value, using fabs(a) where a is the value we have at this point in the calculation
    \n finally, divide by 6 and the volume will be given.
    \n function of subclass tetrahedron.
    \n function to get the volume of the tetrahedron cell. */
    void calculateVolume(std::vector<Vector3D>);

};


/*!  \class Pyramid
     \brief subclass of class cell.
     */
class Pyramid : public Cell
{

private:

public:

//! Default.
	Pyramid();

//! subclass pyramid constructor.
    Pyramid(int,int,int,std::vector<int>,std::vector<Vector3D>,std::vector<Material>);

//! copy contructor.
    Pyramid(const Cell&);

//! destructor.
    ~Pyramid();

    /*!
     \n plan to get volume of pyramid
    \n essentially, a pyramid is just 2 tetrahedrons put together, therefore to find the volume of the pyramid, we must repeat the same method
    \n of finding the volume of a tetrahedron twice.
    \n consider the new 5th vertex is called E.
    \n the following calculation would be
    \n Vpyramid = Vtetra1+Vtetra2 where...
    \n                __   __    __                     __   __    __
    \n Vtetra1 = 1/6|(AB x AC) * AD| and Vtetra2 = 1/6|(EB x EC) * ED|
    \n function of subclass pyramid.
    \n function to get the volume of the pyramid cell. */
    void calculateVolume(std::vector<Vector3D>);

};


/*! \class Hexahedron
    \brief subclass of class cell.
*/
class Hexahedron : public Cell
{
private:

public:

//! Default.
	Hexahedron();

//! Default.
    Hexahedron(int,int,int,std::vector<int>,std::vector<Vector3D>,std::vector<Material>);

//! copy contructor.
    Hexahedron(const Cell&);


    ~Hexahedron(); //! destructor.
    /*! function of subclass hexahedron.
     function to get the volume of the hexahedron cell.
    \n plan to get volume of hexahedron
    \n a hexahedron is 6 tetrahedrons put together
    \n use the same method as the one used for finding the volume of tetrahedron but this time repeating it 6 times using the correct vertices*/
    void calculateVolume(std::vector<Vector3D>);

};
#endif


