#include "octotree.hpp"

static long find_space_size (triangles &t);

static void fill_tree (octotree_t *tree);


long find_space_size (triangles &t) {

    float maxCoord = 0;
    float maxTrCoord = 0;

    for (auto tr : t) {

        maxTrCoord = tr.max_coord();
        maxCoord = std::max(maxCoord, maxTrCoord);
    }

    int pow = 0;
    int coord = (int)maxCoord;

    while (coord / 2 != 0) {

        coord /= 2;
        pow ++;
    }
    pow ++;

    return std::pow(2, pow);
}

octotree_t make_octotree (triangles &t) {

    octotree_t treeHead;
    treeHead.m_triangles = t;
    treeHead.m_region.set(0, 0, 0, find_space_size(t));

    printf ("\nSTART FILL TREE\n");

    fill_tree(&treeHead);
    printf ("\nEND FILL TREE\n");

    return treeHead;
}

void fill_tree (octotree_t *tree) {

    if (tree->m_triangles.size() <= 1 || tree->set_children() == false) {

        printf("\nsize - %d exit\n", tree->m_triangles.size());
        return;
    }
    printf("\nhere\n");
    
    for (auto child : tree->m_childs) {

        auto it =  tree->m_triangles.begin();
        while (it != tree->m_triangles.end()) {

            if (child->m_region.is_triangle_in(*it)) {

                child->m_triangles.push_back(*it);
                tree->m_triangles.erase(it);
                continue;
            }
            it++;
        }
    }

    for (auto child : tree->m_childs) {

        fill_tree(child);
    }
}

void tree_dump (octotree_t* tree) {

    tree->m_region.dump();
}
