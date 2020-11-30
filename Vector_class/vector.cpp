#include "vector.h"

//using namespace std;

//default
vector::vector()
{
    x = 0;
    y = 0;
    z = 0;
}



vector::vector(double xc, double yc, double zc)
{
    x = xc;
    y = yc;
    z = zc;
}

//setters
void vector::setx(double xc){ x = xc; };
void vector::sety(double yc){ y = yc; };
void vector::setz(double zc){ z = zc; };

//getters
/*double vector::getx(){ return x; }
double vector::gety(){ return y; }
double vector::getz(){ return z; }*/


//operations-----------------------------------------------------------------------

//addition
vector vector::operator+(const vector &vec)
{
	return vector(this->x + vec.x, this->y + vec.y, this->z + vec.z);
}
	
//subtraction
vector vector::operator-(const vector &vec)
{
	return vector(this->x - vec.x, this->y - vec.y, this->z - vec.z);	
}

//dot product
double vector::dot_product(const vector &vec)
{
	return vector(this->x*vec.x + this->y*vec.y + this->z*vec.z);
}

//cross product
vector vector::cross_product(const vector &vec)
{
	vector ans;
	ans.x = this->y*vec.z - this->z*vec.y;
	ans.y = this->z*vec.x - this->x*vec.z;
	ans.z = this->x*vec.y - this->y*vec.x;
	
	return ans
}

//-----------------------------------------------------------------------------------

//destructor
vector::~vector()



