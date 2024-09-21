#ifndef GEOMETRY_ELEMS_HPP
#define GEOMETRY_ELEMS_HPP

#include <cmath>
#include <stdio.h>

static float flt_tolerance = 1e-6;

enum CrossType {

    CROSS = 1,
    PARALLEL = 2,
    MATCH = 3, 
    NOT_CROSS = 4
};

CrossType lines_cross_point (line_t &line1, line_t &line2, point_t &crossP);

bool is_point_in_interval (point_t &p, point_t &pA, point_t &pB);

bool is_num_in_internal (float &x, float &a, float &b);

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

        return (std::abs(x - rhs.x) < flt_tolerance && std::abs(y - rhs.y) < flt_tolerance && std::abs(z - rhs.z) < flt_tolerance);
    };

    point_t operator-(const point_t &rhs) const {

        point_t result = point_t(x - rhs.x, y - rhs.y, z - rhs.z);
        return result;
    }

    point_t operator*(const int &num) const {

        point_t result = point_t(x * num, y * num, z * num);
        return result;
    }
};

struct line_t {
 
    point_t zeroPoint;

    point_t directionVector;

    line_t(const point_t &p1, const point_t &p2) {

        zeroPoint = p1;
        directionVector = p2 - p1;
    }

    void set (const point_t &setZeroP, const point_t &setDVec) {
     
        zeroPoint = setZeroP;
        directionVector = setDVec;
    }
    line_t () {}
    
    void print() const {

        printf("a - %f b -%f c - %f", zeroPoint.x, zeroPoint.y, zeroPoint.z);
    };
 
    // bool valid() const;
};

// surface_t -- surface from ax + by + cz + d = 0;

// linear_equation -- ax + by + cz + d = 0;
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

    bool is_match (const linear_equation &eq) {
        
        linear_equation eq_t = eq - *this * (eq.a / a); 
        return  eq_t.a < flt_tolerance && eq_t.b < flt_tolerance && eq_t.c < flt_tolerance && eq_t.d < flt_tolerance;
    }

    bool is_parallel (const linear_equation &eq) {
        
        linear_equation eq_t = eq - *this * (eq.a / a); 
        return  eq_t.a < flt_tolerance && eq_t.b < flt_tolerance && eq_t.c < flt_tolerance;
    }
};

struct surface_t {

    float a = -1.0f, b = 1.0f, c = 0.0f, d = 0.0f;   

    surface_t () {}

    surface_t (const point_t &p1, const point_t &p2, const point_t &p3) :

        a( (p2.y - p1.y) * (p3.z - p1.z) - (p2.z - p1.z) * (p3.y - p1.y) ),
        b( (p2.z - p1.z) * (p3.x - p1.x) - (p2.x - p1.x) * (p3.z - p1.z) ),
        c( (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x) ),
        d( - a * p1.x - b * p1.y - c * p1.z )
        {}

};

struct triangle_t {

    point_t A; point_t B; point_t C;

    line_t AB; line_t BC; line_t AC;

    surface_t surfABC;

    triangle_t() {}

    triangle_t(point_t &a, point_t &b, point_t &c) {

        A = a; B = b; C = c;
        
        line_t ABcp(A, B); line_t BCcp(B, C); line_t ACcp(A, C);
        AB = ABcp;         BC = BCcp;         AC = ACcp;

        surface_t surfABCcp(A, B, C);
        surfABC = surfABCcp;
    }

    bool cross_with_line (line_t &line) {

        bool result;

        point_t crossPoint;
        CrossType lineCrossType;

        #define CROSS_WITH_LINE(A, B, AB)                                   \
                                                                            \
        lineCrossType = lines_cross_point(line, AB, crossPoint);            \
                                                                            \
        if (lineCrossType == MATCH) {                                       \
                                                                            \
            return true;                                                    \
        }                                                                   \
                                                                            \
        if (lineCrossType == CROSS) {                                       \
                                                                            \
            result = is_point_in_interval(crossPoint, A, B);                \
                                                                            \
            if (result == true) {                                           \
                                                                            \
                return true;                                                \
            }                                                               \
        }

        CROSS_WITH_LINE(A, B, AB)
        CROSS_WITH_LINE(B, C, BC)
        CROSS_WITH_LINE(A, C, AC)

        #undef CROSS_WITH_LINE
        return false;
    }
};

#endif // GEOMETRY_ELEMS_HPP