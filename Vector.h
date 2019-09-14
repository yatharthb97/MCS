//Header file for class V and Q
//Comments complete

#pragma once

#include<cmath>

class V{
//Class "Vector"
//A class of variables that defines a three component Vector
public:

//Default Constructor
V():x(0), y(0), z(0) {}

//Overloading Constriuctor
V(double x, double y, double z):x(x), y(y), z(z){}



inline double size() const {
        return sqrt( pow(this->x,2) + pow(this->y,2) + pow(this->z,2));
    }
	
privte:
	double x; //x-component
	double y; //y-component
	double z; //z-component

}; //end of class V


class Q{
//Class "Quaternion"
//A class of variables that defines a four component Quaternion
public:
	

	
	
private:

	double a; //real component of quart
	double b; //imaginary component 1
	double c; //imaginary component 2
	double d; //imaginary component 3

};//End of class Q
