#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define FIND(x, y) find(x, sizeof(x), sizeof(x[0]), &y, sizeof(y))

int find(void* array, size_t array_sz, size_t element_sz, void* searchable, size_t searchable_sz) {
    if (element_sz != searchable_sz)
        return -1;

    for (unsigned int i = 0; i < array_sz * element_sz; i += element_sz) {
        if(!memcmp(array + i, searchable, element_sz))
            return i/element_sz;
    }
    return -1;
}

struct Message {
    int i;
    char c1;
    char c2;
    short si;
    double d;
};

int main() {
    int index = -1;

    int i_array[] = {0,1,2,3,4};
    int i = 2;
    index = FIND(i_array, i);
    assert(index == 2);

    float f_array[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    float f = 5.0;
    index = FIND(f_array, f);
    assert(index == 4);

    // string "time:value"
    char message[] = "120:653";
    char time_value_separator = ':';
    int separator_index =  FIND(message, time_value_separator);
    int time = 0;
    if (separator_index > 0) {
        for (int i = 0; i < separator_index; ++i) {
            time += ((message[i] - '0')*pow(10, (separator_index - i -1)));
        }
    }
    assert(time == 120);

    //по идее структуры нельзя сравнивать с помощью memcmp, но тут структура выровнена
    struct Message m_array[] = {{1, 'A', 'B', 2, 1.0}, {2, 'C', 'D', 3, 2.0}, {3, 'E', 'F', 4, 3.0}};
    struct Message m = {1, 'A', 'B', 2, 1.0};
    index = FIND(m_array, m);
    assert(index == 0);
}



