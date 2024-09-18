#ifndef GEOMETRY_ELEMS_HPP
#define GEOMETRY_ELEMS_HPP

#include <cmath>
#include <stdio.h>

struct point_t {
    
    float x = NAN, y = NAN, z = NAN;
    
    point_t () {;}
    
    point_t (float setX, float setY, float setZ)/*: x(setX), y(setY), z(setZ)*/ {

        x = setX; y = setY; z = setZ;
    }

    void print () const {

        printf("\nx - %f y - %f z - %f\n", x, y, z);
    }
    
    // bool valid() const;
    
    bool equal (const point_t &rhs) const {

        float flt_tolerance = 1e-6;
        return (std::abs(x - rhs.x) < flt_tolerance && std::abs(y - rhs.y) < flt_tolerance && std::abs(z - rhs.z) < flt_tolerance);
    };

    point_t operator-(const point_t &rhs) const {

        point_t result = point_t(x - rhs.x, y - rhs.y, z - rhs.z);
        // point_t result; result.x = x - rhs.x; result.y = y - rhs.y; result.z = z - rhs.z;
        return result;
    }
};

// line_t -- line in form of ax + by + c = 0
struct line_t {
 
    point_t zeroPoint;

    point_t directionVector;

    line_t(const point_t &p1, const point_t &p2, const point_t &p3) {

        zeroPoint = p1;
        directionVector = p3 - p2;
    }

    line_t () {}
    
    void print() const {

        printf("a - %f b -%f c - %f", zeroPoint.x, zeroPoint.y, zeroPoint.z);
    };
 
    // bool valid() const;
};

// surface_t -- surface from ax + by + cz + d = 0;

struct linear_equation {

    float a = -1.0f, b = 1.0f, c = 0.0f, d = 0.0f;   

    linear_equation (float setA, float setB, float setC, float setD) : a(setA), b(setB), c(setC), d(setD) {}

    linear_equation operator- (const linear_equation rhs) const {

        linear_equation res(a - rhs.a, b - rhs.b, c - rhs.c, d - rhs.d);
        return res;
    }

    linear_equation operator* (const float num) const {

        linear_equation res(a * num, b * num, c * num, d * num);
        return res;
    }
};

struct surface_t {

    float a = -1.0f, b = 1.0f, c = 0.0f, d = 0.0f;   

    surface_t (const point_t &p1, const point_t &p2, const point_t &p3) :

        a( (p2.y - p1.y) * (p3.z - p1.z) - (p2.z - p1.z) * (p3.y - p1.y) ),
        b( (p2.z - p1.z) * (p3.x - p1.x) - (p2.x - p1.x) * (p3.z - p1.z) ),
        c( (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x) ),
        d( - a * p1.x - b * p1.y - c * p1.z )
        {}

};

line_t cross_surfaces (surface_t &first, surface_t &second) {

    point_t result(first.b * second.c - first.c * second.b, first.a * second.c - first.c * second.a, first.a * second.b - first.b * second.a);

    linear_equation eq1(first.a, first.b, first.c, first.d);
    linear_equation eq2(second.a, second.b, second.c, second.d);

    eq1 = eq1 - eq2 * (eq1.a / eq2.a);            // все это можно реализовать через вычитание матриц ...
    eq1.

}
#endif // GEOMETRY_ELEMS_HPP