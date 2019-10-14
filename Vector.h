//Header file for class V and Q
//Tested

#pragma once

#include<cmath>
#include <sstream>

class Q{
//Class "Quaternion"
//A class of variables that defines a four component Quaternion
public:
    
    double a; //real component of quart
    double b; //imaginary component 1
    double c; //imaginary component 2
    double d; //imaginary component 3

    Q():a(0), b(0), c(0), d(0){}

    Q(double a,double b, double c, double d): a(a), b(b), c(c), d(d) {}

   std::string info() const {
        std::ostringstream o;
        o << "(" <<a << ", " << b << ", " << c << ", "<< d<<")";
        return o.str();
    }

    std::string infoRaw() const {
        std::ostringstream o;
        o <<a << " " << b << " " << c <<" "<< d;
        return o.str();
    }

};//End of class Q


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

    inline void orthogonalise(V& B) {
        double dp(dot(B));    this->x -= dp*B.x;    this->y -= dp*B.y;    this->z -= dp*B.z;
    }
	

    //Input -- azia and two angles
    // using Vector&, double, double instead of Quat -> circular include
    inline void rotate(V& axis, double cosAngle, double sinAngle) {
        double t2,t3,t4,t5,t6,t7,t8,t9,t10,newx,newy,newz;
        double qw = cosAngle, qx = (axis.x * sinAngle), qy = (axis.y * sinAngle), qz = (axis.z * sinAngle);

        //    t1 = quat.w * quat.w;
        t2 =  qw * qx;
        t3 =  qw * qy;
        t4 =  qw * qz;
        t5 = -qx * qx;
        t6 =  qx * qy;
        t7 =  qx * qz;
        t8 = -qy * qy;
        t9 =  qy * qz;
        t10 = -qz * qz;

        newx = 2.0 * ( (t8+t10) * x + (t6-t4)  * y + (t3+t7) * z ) + x;
        newy = 2.0 * ( (t4+t6)  * x + (t5+t10) * y + (t9-t2) * z ) + y;
        newz = 2.0 * ( (t7-t3)  * x + (t2+t9)  * y + (t5+t8) * z ) + z;

        x = newx;
        y = newy;
        z = newz;
    }

    inline void rotate(Q &q) {
        double t2,t3,t4,t5,t6,t7,t8,t9,t10,newx,newy,newz;

        //    t1 = quat.w * quat.w;
        t2 =  q.a * q.b;
        t3 =  q.a * q.c;
        t4 =  q.a * q.d;
        t5 = -q.b * q.b;
        t6 =  q.b * q.c;
        t7 =  q.b * q.d;
        t8 = -q.c * q.c;
        t9 =  q.c * q.d;
        t10 = -q.d * q.d;

        newx = 2.0 * ( (t8+t10) * x + (t6-t4)  * y + (t3+t7) * z ) + x;
        newy = 2.0 * ( (t4+t6)  * x + (t5+t10) * y + (t9-t2) * z ) + y;
        newz = 2.0 * ( (t7-t3)  * x + (t2+t9)  * y + (t5+t8) * z ) + z;

        x = newx;
        y = newy;
        z = newz;
    }


}; //end of class V



