#include <unordered_map>
#include <iostream>
#include <list>

using namespace std;

typedef std::unordered_map<int, list<int>::iterator> Mymap;

void new_elem(Mymap* map, list<int>* lst, int elem, int* hits);

void list_dump (list<int> lst);

int main() {
    int arr[10] = {1, 2, 3, 4, 3, 3, 5, 2, 3 , 6};
    
    list<int> lst;
    Mymap map;
    int hits = 0;

    for (int i = 0; i < 10; i++) {
        new_elem(&map, &lst, arr[i], &hits);

        cout << *lst.begin() << " " << lst.back() << endl;
    }
    printf("hits - %d\n", hits);
    // printf("here12345");
    // cout << *lst.begin() << endl;
}

void new_elem(Mymap* map, list<int>* lst, int elem, int* hits) {
    printf("elem - %d ", elem);
    if (map->count(elem) == 0)  {
        printf("push ");
        if (lst->size() < 5) {
            
            lst->push_front(elem);

            map->insert({elem, lst->begin()});   // бл€ть, ты про кнопку enter слышал (посвободнее пиши, ниху€ не читаетс€)
        }
        else {
            printf("shit ");
            lst->pop_back();
            lst->push_front(elem);
            map->insert({elem, lst->begin()});
        }
    }
    else {
        printf("count - %d move ", map->count(elem)); // при удалении элемента из списка хэш таблица указывает на старую €чейку
        *hits += 1;

        auto it = map->find(elem);

        lst->erase(map->find(elem)->second);
        map->erase(elem);

        lst->push_front(elem);
        map->insert({elem, lst->begin()});
    }
    printf("finish\n");
}

void list_dump (list<int> lst) {
    printf("LIST DUMP: ");
    list<int> lst_cpy = lst;
    for (int i = 0; i < lst_cpy.size(); i++) {
        printf("%d ", *(lst_cpy.begin()++));
        lst_cpy.pop_front();
    }
    printf("\n");
}