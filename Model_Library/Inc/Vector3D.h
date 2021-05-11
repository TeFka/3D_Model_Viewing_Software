/*! \file Vector3D.h File Reference
    \author    Copyright \n Code part: Woranan Kamonlattana (Student ID: 20310814)
                         \n Documentation  part: Woranan Kamonlattana and Chen xu  (Student ID: 20187733)

    \brief     Required header files: vector.h math.h(for some mathematic functions)
*/


#include <vector>
#include <math.h>

#ifndef VECTOR3D_H
#define VECTOR3D_H

/*! \class 'Vector3D'
    \brief Creates a virtual Vector3D by storing information.
*/

class Vector3D
{
private:
    int ID;
    double x, y, z;

public:

    //! Constructor
    //! default
    Vector3D();

    //! giving values to object
    Vector3D(double,double,double);

    //! Destructor
    ~Vector3D();

    //! copy constructor
    Vector3D (const Vector3D & vec);

    //! Setters
    /*! Function of class Vector, setID(), setx(), sety(), setz() \n
        Function to set the values of vector coordinates 
        \arg setID(), setx(), sety(), setz(): none.
        \return  newID, xc, yc and zc
    */
    void setID(int);
    void setx(double);
    void sety(double);
    void setz(double);

    //! Getters
    /*! Function of class Vector, getID(), getx(), gety(), getz()  \n
        Function to get value vector coordinates 
    \arg getID(), getx(), gety(), getz(): none.
    \return ID, x, y and z
    */
    int getID();
    double getx();
    double gety();
    double getz();


//! Operations

    /*! Addition
      \n action: add 2 vectors together
      \return added results of the addition operation
    */
    Vector3D operator+(const Vector3D &vec);

    /*! Subtraction
       \n action: subtract current vector from another vector
       \return results of the subtraction operation 
    */
    Vector3D operator-(const Vector3D &vec);

	/*! Dot Product
	   \n action: perform dot product operation
       \return scalar product obtained from dot operation
    */
    double operator*(const Vector3D &vec);

/*! Functions
     \n Cross Product
     \n action: perform cross product operation
     \return the vector results from the cross product operation 
*/
    Vector3D cross_product(const Vector3D &vec);

};

#endif //! VECTOR3D_H
