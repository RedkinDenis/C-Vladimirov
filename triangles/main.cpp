#include "include/geometry_elems.hpp"
#include "input_t.hpp"
#include "octotree.hpp"
#include <iostream>


int main () {

    // scanf("%f %f %f %f %f %f", &A1, &B1, &C1, 
    //                            &A2, &B2, &C2);
    triangles t = input_triangles();

    // t.arr[0].dump();
    // t.arr[1].dump();

    octotree_t tree = make_octotree(t);
    printf("\ntree is made\n");
    printf("%d\n", is_triangles_cross(t[0], t[1]));

}