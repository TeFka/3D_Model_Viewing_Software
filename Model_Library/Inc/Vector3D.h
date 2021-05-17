/*! \file Vector3D.h File Reference
    \author    Copyright \n Code part: Woranan Kamonlattana (Student ID: 20310814)
                         \n Documentation  part:  Chen xu  (Student ID: 20187733)

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

    /*! Function of class Vector setID()\n
        Function to set the ID value
        \n  Argument: none.
        \return  none
    */
    void setID(int);

    /*! Function of class Vector setx()\n
        Function to set the X value
        \n  Argument: double - new X value.
        \return  none
    */
    void setx(double);

    /*! Function of class Vector sety()\n
        Function to set the Y value
        \n  Argument: double - new Y value.
        \return  none
    */
    void sety(double);

    /*! Function of class Vector setz() \n
        Function to set the Z value
        \n  Argument: double - new Z value.
        \return  none
    */
    void setz(double);

    /*! Function of class Vector getID\n
        Function to get the ID
    \n  Argument: none.
    \return int - the ID
    */
    int getID();

    /*! Function of class Vector getx\n
        Function to get the X value
    \n  Argument: none.
    \return int - the X value
    */
    double getx();

    /*! Function of class Vector gety\n
        Function to get the Y value
    \n  Argument: none.
    \return int - the Y value
    */
    double gety();

    /*! Function of class Vector getz\n
        Function to get the Z value
    \n  Argument: none.
    \return int - the Z value
    */
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
