#include "input_t.hpp"

triangles input_triangles () {

    size_t count = 0;
    scanf("%lu", &count);

    triangles t;

    for (int i = 0; i < count; i++) {

        float* coords = (float*)calloc(9, sizeof(float));
        for (int j = 0; j < 9; j++) {

            scanf("%f", &coords[j]);
        }

        point_t A(coords[0], coords[1], coords[2]);
        point_t B(coords[3], coords[4], coords[5]);  
        point_t C(coords[6], coords[7], coords[8]);  

        triangle_t triangle(A, B, C);
        triangle.triangleNumber = i;

        t.push_back(triangle);
    }

    return t;
}


// void delete_triangles (triangles &t) {

//     free(t.arr);
//     t.count = 0;
// }