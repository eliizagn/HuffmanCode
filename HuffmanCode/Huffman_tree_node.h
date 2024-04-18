#pragma once
#include "Huffman_tree.h"
#include <cstddef>

class huffman_tree_node {
private:
    char data;             // ??????
    unsigned freq;         // ???????
    huffman_tree_node* left, * right;  // ????? ? ?????? ???????
    friend class huffman_coding;

public:
    huffman_tree_node(char _data, unsigned _freq) {
        left = right = nullptr;
        data = _data;
        freq = _freq;
    }
};