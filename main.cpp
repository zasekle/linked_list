#include <iostream>
#include <list>
#include "custom_list.h"



int main() {

    CustomList<int> list_test;

    std::cout << list_test.size() << '\n';

    list_test.print();
    return 0;
}
