#include "../Inc/Vector3D.h"

//using namespace std;

//default
Vector3D::Vector3D()
{
    x = 0;
    y = 0;
    z = 0;
}


Vector3D::Vector3D(double xc, double yc, double zc)
{
    x = xc;
    y = yc;
    z = zc;
}

//setters
void Vector3D::setx(double xc){ x = xc; };
void Vector3D::sety(double yc){ y = yc; };
void Vector3D::setz(double zc){ z = zc; };

//getters
double Vector3D::getx(){ return x; }
double Vector3D::gety(){ return y; }
double Vector3D::getz(){ return z; }


//operations-----------------------------------------------------------------------

//addition
vector Vector3D::operator+(const Vector3D &vec)
{
	return Vector3D(this->x + vec.x, this->y + vec.y, this->z + vec.z);
}
	
//subtraction
vector Vector3D::operator-(const Vector3D &vec)
{
	return Vector3D(this->x - vec.x, this->y - vec.y, this->z - vec.z);	
}

//dot product
double Vector3D::dot_product(const Vector3D &vec)
{
	return Vector3D(this->x*vec.x + this->y*vec.y + this->z*vec.z);
}

//cross product
vector Vector3D::cross_product(const Vector3D &vec)
{
	Vector3D ans;
	ans.x = this->y*vec.z - this->z*vec.y;
	ans.y = this->z*vec.x - this->x*vec.z;
	ans.z = this->x*vec.y - this->y*vec.x;
	
	return ans
}

//-----------------------------------------------------------------------------------

//destructor
Vector3D::~Vector3D()



