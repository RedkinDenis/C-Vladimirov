#pragma once

#include <vector>
#include "geometry_elems.hpp"
#include "input_t.hpp"
#include <iostream>

struct region {

    // long upperX, lowerX;
    // long upperY, lowerY;
    // long upperZ, lowerZ;

    long centerX, centerY, centerZ;
    long a; // cube side length

    bool is_point_in (point_t &p) {
        
        return is_num_in_internal(p.x, centerX + a / 2, centerX - a / 2) &&
               is_num_in_internal(p.y, centerX + a / 2, centerX - a / 2) &&
               is_num_in_internal(p.z, centerX + a / 2, centerX - a / 2);
    }

    bool is_triangle_in (triangle_t &t) {

        return is_point_in(t.A) &&
               is_point_in(t.B) &&
               is_point_in(t.C);
    }

    void set (long x, long y, long z, long l) {

        centerX = x; centerY = y; centerZ = z; a = l;
    }

    void dump () {

        std::cout << "cube center:" << centerX << " " << centerY << " " << centerZ << std::endl;
        std::cout << "cube widht:" << a << std::endl;
    }
};

struct octotree_t {

    std::vector<octotree_t*> m_childs;

    std::vector<triangle_t> m_triangles;
    
    region m_region;

    octotree_t() {

        m_childs.resize(0);
    }

    void node_dump () {

        
    }

    bool set_children () {

        if (m_region.a == 4) {

            return false;
        }

        m_childs.resize(8);

        printf("\nset children aaaa\n");

        #define CHILD_REG(n, i, j, k)                                                         \
        m_childs[n] = (octotree_t*)calloc(1, sizeof(octotree_t));                   \
        m_childs[n]->m_region.set(m_region.centerX + i * m_region.a / 4,            \
                                  m_region.centerY + j * m_region.a / 4,            \
                                  m_region.centerZ + k * m_region.a / 4,            \
                                  m_region.a / 2);                                  
        CHILD_REG(0,  1,  1,  1)                   
        CHILD_REG(1,  1,  1, -1)                   
        CHILD_REG(2,  1, -1,  1)                   
        CHILD_REG(3,  1, -1, -1)                   
        CHILD_REG(4, -1,  1,  1)                   
        CHILD_REG(5, -1, -1,  1)                   
        CHILD_REG(6, -1,  1, -1)                   
        CHILD_REG(7, -1, -1, -1)

        // #undef CHILD_REG

        // printf("\nstart ");

        // m_childs[0] = (octotree_t*)calloc(1, sizeof(octotree_t));

        // m_childs[0]->m_region.set(m_region.centerX + 1 * m_region.a / 4,            
        //                           m_region.centerY + 1 * m_region.a / 4,            
        //                           m_region.centerZ + 1 * m_region.a / 4,            
        //                           m_region.a / 2);                                       
        //                           printf("- end\n");

        return true;                   
    }
};

octotree_t make_octotree (triangles &t);