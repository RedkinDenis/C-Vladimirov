#ifndef GEOMETRY_ELEMS_HPP
#define GEOMETRY_ELEMS_HPP

#include <cmath>
#include <stdio.h>

static float flt_tolerance = 1e-6;

bool is_num_in_internal (float &x, float &a, float &b);

enum CrossType {

    CROSS = 1,
    PARALLEL = 2,
    MATCH = 3, 
    NOT_CROSS = 4
};

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

bool proportional(const point_t &p1, const point_t &p2) {

    point_t zero(0.f, 0.f, 0.f);

    return (p1 - p2 * (p1.x / p2.x)).equal(zero);
}


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

CrossType cross_surfaces (surface_t &first, surface_t &second, line_t &crossL) {

    linear_equation eq1(first.a, first.b, first.c, first.d);
    linear_equation eq2(second.a, second.b, second.c, second.d);

    if (eq2.is_match(eq1)) {

        return MATCH;
    }
    
    else if (eq2.is_parallel(eq1)) {

        return PARALLEL;
    }

    eq2 = eq2 - eq1 * (eq2.a / eq1.a);     
    eq1 = eq1 - eq2 * (eq1.b / eq2.b);

    point_t dVec( - eq1.c, - eq2.c, (float)1);
    point_t zeroP( eq1.d, eq2.d, float(0) );

    line_t result;
    result.set(zeroP, dVec);

    crossL = result;
    return CROSS;
}

bool is_point_in_interval (point_t &p, point_t &pA, point_t &pB) {

    return is_num_in_internal(p.x, pA.x, pB.x) && 
           is_num_in_internal(p.y, pA.y, pB.y) && 
           is_num_in_internal(p.z, pA.z, pB.z); 
}

bool is_num_in_internal (float &x, float &a, float &b) {
    
    if (a - b > flt_tolerance) {

        return a - x >= flt_tolerance && x - b >= flt_tolerance;
    }
    else {

        return x - a >= flt_tolerance && b - x >= flt_tolerance;
    }
}

CrossType lines_cross_point (line_t &line1, line_t &line2, point_t &crossP) {

    if (proportional(line1.directionVector, line2.directionVector)) { 
        
        if (proportional(line1.zeroPoint - line2.zeroPoint, line1.directionVector) ) {

            return MATCH; 
        }

        else {
            
            return PARALLEL;
        }
    }

    linear_equation eqX(line1.directionVector.x, -line2.directionVector.x, float(0), line2.zeroPoint.x - line1.zeroPoint.x);
    linear_equation eqY(line1.directionVector.y, -line2.directionVector.y, float(0), line2.zeroPoint.y - line1.zeroPoint.y);
    linear_equation eqZ(line1.directionVector.z, -line2.directionVector.z, float(0), line2.zeroPoint.z - line1.zeroPoint.z);

    linear_equation eqMu = eqX - eqY * (eqX.a / eqY.a);
    float mu = -eqMu.d / eqMu.b; 
    float gamma = (-eqX.d - mu * eqX.b) - eqX.a;

    if (eqZ.a * gamma + eqZ.b * mu + eqZ.d == 0) {

        point_t result (line1.zeroPoint.x + gamma * line1.directionVector.x,
                        line1.zeroPoint.y + gamma * line1.directionVector.y, 
                        line1.zeroPoint.z + gamma * line1.directionVector.z);
        crossP = result;
        return CROSS;
    }

    return NOT_CROSS;
}

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

bool cross_lines (line_t &l1, point_t &A1, point_t &B1, 
                  line_t &l2, point_t &A2, point_t &B2) {

    bool result;

    point_t crossPoint;
    CrossType lineCrossType;
                                                                    
    lineCrossType = lines_cross_point(l1, l2, crossPoint);            
                                                                        
    if (lineCrossType == CROSS) {                                       
                                                                        
        result = is_point_in_interval(crossPoint, A1, B1) && is_point_in_interval(crossPoint, A2, B2);                
                                                                        
        if (result == true) {                                           
                                                                        
            return true;                                                
        }                                                               
    }

    else if (lineCrossType == MATCH) {

        return true;
    }
    
    return false;
}

bool is_triangles_cross (triangle_t &t1, triangle_t &t2) {

    bool result = false;

    line_t crossLine;
    CrossType surfCrossType = cross_surfaces(t1.surfABC, t2.surfABC, crossLine);

    if (surfCrossType == CROSS) {

        if (t1.cross_with_line(crossLine) && t2.cross_with_line(crossLine)) {

            return true;
        }
    }

    else if (surfCrossType == MATCH) {
        return cross_lines(t1.AB, t1.A, t1.B, t2.AB, t2.A, t2.B) && 
               cross_lines(t1.AB, t1.A, t1.B, t2.BC, t2.B, t2.C) && 
               cross_lines(t1.BC, t1.B, t1.C, t2.AB, t2.A, t2.B) && 
               cross_lines(t1.BC, t1.B, t1.C, t2.BC, t2.B, t2.C);
    }

    return false;
}

#endif // GEOMETRY_ELEMS_HPP