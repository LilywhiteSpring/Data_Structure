//
// Created by 85375 on 2025/11/20.
//
#include "sLinklist.h"

int main() {
    sLinklist<char> list;
    list.print_all();
    list.push_back('a');
    list.print_all();
    return 0;
}