#include "../include/geometry_elems.hpp"
#include <cassert>

bool isZero (float x) {

    // printf("\nx - %f, res - %d\n", x, x < flt_tolerance);
    return std::fabs(x) < flt_tolerance;
}

bool proportional(const point_t &p1, const point_t &p2) {

    point_t zero(0.f, 0.f, 0.f);

    float coeff = 1;
    if ((p1.x != 0 && p2.x != 0)) coeff = p1.x / p2.x;
    if ((p1.y != 0 && p2.y != 0)) coeff = p1.y / p2.y;
    if ((p1.z != 0 && p2.z != 0)) coeff = p1.z / p2.z;

    // printf("\n prop coeff - %f\n", coeff);
    // (p2 * coeff).print();

    return (p1 - p2 * coeff).equal(zero);
}

CrossType cross_surfaces (surface_t &first, surface_t &second, line_t &crossL) {

    linear_equation eq1(first.a, first.b, first.c, first.d);
    linear_equation eq2(second.a, second.b, second.c, second.d);

    // first.dump();   second.dump();

    if (eq2.is_match(eq1)) {

        return MATCH;
    }
    
    else if (eq2.is_parallel(eq1)) {

        return PARALLEL;
    }

    float x0, y0, z0 = 0.f;

    // if (isZero(eq1.a)) {

    //     printf("\n1\n");
    //     y0 = - eq1.d / eq1.b;
    // }
    // else if (isZero(eq2.a)) {

    //     printf("\n2\n");
    //     y0 = - eq2.d / eq2.b;
    // }
    // else {

    //     printf("\n3\n");
    //     y0 = ( eq1.d * eq2.a - eq2.d * eq1.a ) / ( eq2.b * eq1.a - eq1.b * eq2.a );
    // }
    
    // if (isZero(eq1.b)) {

    //     printf("\n4\n");
    //     x0 = - eq1.d / eq1.a;
    // }

    // else if (isZero(eq2.b)) {

    //     printf("\n5\n");
    //     x0 = - eq2.d / eq2.a;
    // }

    // else {

    //     printf("\n6\n");
    //     x0 = ( eq1.d * eq2.b - eq2.d * eq1.b ) / ( eq2.a * eq1.b - eq1.a * eq2.b );
    // }


    if (isZero(eq1.a)) {

        y0 = eq1.d / eq2.b;
    }
    else if (isZero(eq2.a)) {

        y0 = eq2.d / eq1.b;
    }
    else {

        y0 = ( eq1.d * eq2.a - eq2.d * eq1.a ) / ( eq2.b * eq1.a - eq1.b * eq2.a );
    }
    
    // printf("\ny0 - %f\n", y0);
                                                                // возможно стоит выкидывать параметр с 0 коэффицентами, если такой есть
    if (isZero(eq1.a)) {

        x0 = ( - eq2.d - eq2.b * y0 ) / eq2.a;
    }

    else /* if (isZero(eq2.a)) */{

        x0 = ( - eq1.d - eq1.b * y0 ) / eq1.a;
    }

    assert(!isnanf(x0));
    assert(!isnanf(y0));

    // printf("\nx0 - %f y0 - %f\n", x0, y0);

    point_t zeroP(x0, y0, z0);

    point_t dVec( eq1.b * eq2.c - eq2.b * eq1.c,
                  - eq1.a * eq2.c + eq2.a * eq1.c,
                  eq1.a * eq2.b - eq2.a * eq1.b );

    line_t result;
    result.set(zeroP, dVec);

    crossL = result;
    return CROSS;
}

bool is_point_in_interval (point_t &p, point_t &pA, point_t &pB) {

    // pA.print(); pB.print(); p.print();
    
    // printf("\nx - %d y - %d z - %d\n", is_num_in_internal(p.x, pA.x, pB.x),
    //        is_num_in_internal(p.y, pA.y, pB.y),
    //        is_num_in_internal(p.z, pA.z, pB.z));
    return is_num_in_internal(p.x, pA.x, pB.x) && 
           is_num_in_internal(p.y, pA.y, pB.y) && 
           is_num_in_internal(p.z, pA.z, pB.z); 
}

bool is_num_in_internal (float &x, float &a, float &b) {
    
    // if (a - b > flt_tolerance) {

    //     return a - x >= flt_tolerance && x - b >= flt_tolerance;
    // }
    // else {

    //     return x - a >= flt_tolerance && b - x >= flt_tolerance;
    // }


    if (a > b) {

        return a > x && x > b;
    }
    else if (a < b){

        return x > a && b > x;
    }
    else {

        return std::fabs(x - a) < flt_tolerance;
    }
}

CrossType lines_cross_point (line_t &line1, line_t &line2, point_t &crossP) {

    // line1.print(); line2.print();

    if (proportional(line1.directionVector, line2.directionVector)) { 
        
        // printf("\ndirVectors is proportional\n");
        if (proportional(line1.zeroPoint - line2.zeroPoint, line1.directionVector) ) {

            return MATCH; 
        }

        else {
            
            return PARALLEL;
        }
    }

    linear_equation eqX(line1.directionVector.x, -line2.directionVector.x, float(0), line1.zeroPoint.x - line2.zeroPoint.x);
    linear_equation eqY(line1.directionVector.y, -line2.directionVector.y, float(0), line1.zeroPoint.y - line2.zeroPoint.y);
    linear_equation eqZ(line1.directionVector.z, -line2.directionVector.z, float(0), line1.zeroPoint.z - line2.zeroPoint.z);

    if (isZero(eqX.a) == true && isZero(eqX.b) == true) {

        std::swap(eqX, eqZ);
    }

    else if (isZero(eqY.a) == true && isZero(eqY.b) == true) {

        std::swap(eqY, eqZ);
    }

    else if ((isZero(eqX.a) == true && isZero(eqY.a) == true) || (isZero(eqX.b) == true && isZero(eqY.b) == true)) {

        std::swap(eqY, eqZ);
    }

    // printf("\neqX:"); eqX.dump();
    // printf("\neqY:"); eqY.dump();
    // printf("\neqZ:"); eqZ.dump();


    float x, y;

    if (isZero(eqX.a)) {

        // printf("\n1\n");
        y = - eqX.d / eqX.b;
    }
    else if (isZero(eqY.a)) {

        // printf("\n2\n");
        y = - eqY.d / eqY.b;
    }
    else {

        // printf("\n3\n");
        y = ( eqX.d * eqY.a - eqY.d * eqX.a ) / ( eqY.b * eqX.a - eqX.b * eqY.a );
    }
    
    if (isZero(eqX.b)) {

        // printf("\n4\n");
        x = - eqX.d / eqX.a;
    }

    else if (isZero(eqY.b)) {

        // printf("\n5\n");
        x = - eqY.d / eqY.a;
    }

    else {

        // printf("\n6\n");
        x = ( eqX.d * eqY.b - eqY.d * eqX.b ) / ( eqY.a * eqX.b - eqX.a * eqY.b );
    }

    // printf("\nx - %f y - %f\n", x, y);
    
    if (isZero(eqZ.a * x + eqZ.b * y + eqZ.d)) {

        // printf("\nsuccess\n");
        // line1.print(); line2.print();
        point_t result (line1.zeroPoint.x + x * line1.directionVector.x,
                        line1.zeroPoint.y + x * line1.directionVector.y, 
                        line1.zeroPoint.z + x * line1.directionVector.z);
        crossP = result;
        // crossP.print();
        return CROSS;
    }

    return NOT_CROSS;
}

bool cross_lines (line_t &l1, point_t &A1, point_t &B1, 
                  line_t &l2, point_t &A2, point_t &B2) {
                
    bool result;
    point_t crossPoint;
    CrossType lineCrossType;

    // l1.print(); l2.print();
                                                                    
    lineCrossType = lines_cross_point(l1, l2, crossPoint);            
                                                                        
    if (lineCrossType == CROSS) {                                       

        printf("\nlines crosses\n");   
        // crossPoint.print();
        result = is_point_in_interval(crossPoint, A1, B1) && is_point_in_interval(crossPoint, A2, B2);                
                                                                        
        if (result == true) {                                           
                                                                        
            return true;                                                
        }                                                               
    }

    else if (lineCrossType == MATCH) {

        printf("\nlines match\n");
        return is_point_in_interval(A2, A1, B1) || is_point_in_interval(B2, A1, B1);
    }

    else if (lineCrossType == PARALLEL) {

        printf("\nlines parallel\n");
    }
    
    // printf("\nne rabotaet govno tupoe\n");
    return false;
}

bool is_triangles_cross (triangle_t &t1, triangle_t &t2) {

    bool result = false;

    line_t crossLine;
    CrossType surfCrossType = cross_surfaces(t1.surfABC, t2.surfABC, crossLine);

    if (surfCrossType == CROSS) {

        printf("surf crosses\n");
        printf("\ncross line:\n"); crossLine.print();

        // printf("\nt1 - %d, t2 - %d\n", t1.cross_with_line(crossLine), t2.cross_with_line(crossLine));

        if (t1.cross_with_line(crossLine) && t2.cross_with_line(crossLine)) {

            return true;
        }
    }

    else if (surfCrossType == MATCH) {

        printf("surf match\n");
        return cross_lines(t1.AB, t1.A, t1.B, t2.AB, t2.A, t2.B) ||
               cross_lines(t1.AB, t1.A, t1.B, t2.BC, t2.B, t2.C) || 
               cross_lines(t1.AB, t1.A, t1.B, t2.AC, t2.A, t2.C) || // надо все пересечь 
               cross_lines(t1.BC, t1.B, t1.C, t2.AB, t2.A, t2.B) ||
               cross_lines(t1.BC, t1.B, t1.C, t2.BC, t2.B, t2.C) || 
               cross_lines(t1.BC, t1.B, t1.C, t2.AC, t2.A, t2.C) ||
               cross_lines(t1.AC, t1.A, t1.C, t2.AB, t2.A, t2.B) ||
               cross_lines(t1.AC, t1.A, t1.C, t2.BC, t2.B, t2.C) || 
               cross_lines(t1.AC, t1.A, t1.C, t2.AC, t2.A, t2.C);
    }

    return false;
}
