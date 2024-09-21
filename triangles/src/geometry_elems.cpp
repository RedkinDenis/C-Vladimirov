#include "../include/geometry_elems.hpp"

bool proportional(const point_t &p1, const point_t &p2) {

    point_t zero(0.f, 0.f, 0.f);

    return (p1 - p2 * (p1.x / p2.x)).equal(zero);
}

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
