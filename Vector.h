//Header file for class V and Q
//Tested

#pragma once

#include<cmath>
#include <sstream>

class V{
//Class "Vector"
//A class of variables that defines a three component Vector
public:

//Member Variables
	double x; //x-component
	double y; //y-component
	double z; //z-component


//Default Constructor
V():x(0), y(0), z(0) {}

//Overloading Constriuctor
V(double x, double y, double z):x(x), y(y), z(z){}


   std::string info() const {
        std::ostringstream o;
        o << "(" <<x << ", " << y << ", " << z <<")";
        return o.str();
    }

    std::string infoRaw() const {
        std::ostringstream o;
        o <<x << " " << y << " " << z;
        return o.str();
    }

    /**
     * @brief Return a norm of Vector
     * @return
     */
    inline double size() const {
        return sqrt( pow(this->x,2) + pow(this->y,2) + pow(this->z,2));
    }

    /**
     * @brief normalise Normalise a vector to have unit length.  For speed during heavy use, it is
       not checked that the supplied vector has non-zero length.
     */
    inline void normalise() {
        double tot = size();
        if (tot !=0.0) {
            tot = 1.0 / tot;
            x *= tot;
            y *= tot;
            z *= tot;
        }
    }

    /**
     * @brief isUnit is vector unit vector
     * @return
     */
    bool isUnit() {
        if ( this->size() > 1.000001 || this->size() < 0.999999 )
            return false;
        return true;
    }

    /**
     * @brief dotProduct == Scallar product
     * @param other
     * @return
     */
    inline double dot(const V& other)  {
        return x*other.x + y*other.y + z*other.z;
    }

    inline void scale(double scale) {
        x=x*scale; y=y*scale, z=z*scale;
    }

    inline V operator- (const V& o) const {
        return V(x-o.x, y-o.y,z-o.z);
    }

    inline V operator+ ( const V &o ){
        return V( x + o.x, y + o.y, z + o.z );
    }

    inline void operator-= (const V& o) {
        x-=o.x;
        y-=o.y;
        z-=o.z;
    }

    inline void operator+= (const V& o) {
        x+=o.x;
        y+=o.y;
        z+=o.z;
    }

    inline bool operator==(V& o) {
        if(x == o.x && y == o.y && z == o.z) return true;
        else return false;
    }

    inline bool operator!= (V& o) {
        if(o.x != x || o.y != y || o.z != z ) return true;
        return false;
    }

    inline V operator* (double scale) {
        return V(this->x*scale, this->y*scale, this->z*scale);
    }

    inline void operator*= (double scale) {
        this->x*=scale, this->y*=scale, this->z*=scale;
    }

    /*inline V operator* (double, const V&)
    {
        
    }*/

    inline V cross(const V& B) const {
        return V(this->y*B.z - this->z*B.y, -this->x*B.z + this->z*B.x, this->x*B.y - this->y*B.x);
    }

    inline void ortogonalise(V& B) {
        double dp(dot(B));    this->x -= dp*B.x;    this->y -= dp*B.y;    this->z -= dp*B.z;
    }
	


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
