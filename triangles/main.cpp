#include "include/geometry_elems.hpp"
#include <iostream>

struct triangles {

    triangle_t* arr;
    size_t count;
};

triangles input_triangles ();

int main () {

    
    
    // scanf("%f %f %f %f %f %f", &A1, &B1, &C1, 
    //                            &A2, &B2, &C2);
    triangles t = input_triangles();

    // t.arr[0].dump();
    // t.arr[1].dump();

    printf("%d\n", is_triangles_cross(t.arr[0], t.arr[1]));

}

triangles input_triangles () {

    size_t count = 0;
    scanf("%lu", &count);

    triangles t;
    t.count = count;

    t.arr = (triangle_t*)calloc(count, sizeof(triangle_t));

    for (int i = 0; i < count; i++) {

        float* coords = (float*)calloc(9, sizeof(float));
        for (int j = 0; j < 9; j++) {

            scanf("%f", &coords[j]);
        }

        point_t A(coords[0], coords[1], coords[2]);
        point_t B(coords[3], coords[4], coords[5]);  
        point_t C(coords[6], coords[7], coords[8]);  

        triangle_t triangle(A, B, C);

        t.arr[i] = triangle;
    }

    return t;
}