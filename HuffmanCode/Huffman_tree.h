#pragma once
#include "huffman_tree_node.h"
#include <string>
#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
using namespace std;

class huffman_coding
{
private:
    huffman_tree_node* root;
    unordered_map<char, string> huffman_code;
    string encode;
    string decode;
public:
    struct compare {
        bool operator()(huffman_tree_node* l, huffman_tree_node* r) {
            return l->freq > r->freq;
        }
    };

    // ?????????? ?????? ????????
    void build_huffman_tree(const string& abc, const int* frequencies, bool flag_ex) {
        priority_queue<huffman_tree_node*, vector<huffman_tree_node*>, compare> min_heap;

        for (size_t i = 0; i < abc.size(); ++i) {
            if (frequencies[i] > 0) {
                huffman_tree_node* node = new huffman_tree_node(abc[i], frequencies[i]);
                min_heap.push(node);
            }
        }

        while (min_heap.size() > 1) {
            huffman_tree_node* left = min_heap.top();
            min_heap.pop();
            huffman_tree_node* right = min_heap.top();
            min_heap.pop();

            huffman_tree_node* parent = new huffman_tree_node('$', left->freq + right->freq);
            parent->left = left;
            parent->right = right;
            min_heap.push(parent);
        }

        if (!min_heap.empty()) {
            root = min_heap.top();
        }
    }

    // ??????????? ?????????? ????? ????????
    void build_huffman_codes(huffman_tree_node* node, const string& code) {
        if (node == nullptr) {
            return;
        }

        if (node->data != '$') {
            huffman_code[node->data] = code;
        }

        build_huffman_codes(node->left, code + "0");
        build_huffman_codes(node->right, code + "1");
    }

public:
    huffman_coding() : root(nullptr) {}

    // ?????????? ????? ????????
    void HuffmanCodes(const string& abc, const int* frequencies, bool flag_ex) {
        build_huffman_tree(abc, frequencies, flag_ex);
        build_huffman_codes(root, "");
    }



    // ????????????? ??????
    string decode_text(const string& encoded_text, bool flag_ex) {
        string decoded_text;
        huffman_tree_node* current = root;

        for (char bit : encoded_text) {
            if (bit == '0') {
                current = current->left;
            }
            else {
                current = current->right;
            }

            if (current->left == nullptr && current->right == nullptr) {
                decoded_text += current->data;
                current = root;
            }
        }

        return decoded_text;
    }

    // ????????? ??????????????? ??????
    string get_encode()
    {
        return encode;
    }

    /* ?????????????? ?????? */
    void encode_text(string text)
    {
        for (int i = 0; i < text.size(); i++)
        {
            for (auto it = huffman_code.begin(); it != huffman_code.end(); ++it)
            {
                if (text[i] == it->first)
                {
                    encode += it->second;
                }
            }
        }
    }
    unordered_map<char, string> get_huffman_code() const {
        return huffman_code;
    }
    void output_file(string filename, bool flag)
    {
        fstream file;
        file.open(filename, ios::out);
        if (flag)
        {
            for (int i = 0; i < encode.size(); i++)
            {
                file << encode[i];
            }
        }
        else
        {
            for (int i = 0; i < decode.size(); i++)
            {
                file << decode[i];
            }
        }
        file.close();
    }
    double calculate_entropy(const string& abc, const int* frequencies) const {
        double entropy = 0.0;
        int total_characters = 0;

        // ??????? ?????? ????? ????????
        for (size_t i = 0; i < abc.size(); ++i) {
            total_characters += frequencies[i];
        }

        // ???????????? ???????? ?? ???????
        for (size_t i = 0; i < abc.size(); ++i) {
            if (frequencies[i] > 0) {
                double probability = static_cast<double>(frequencies[i]) / total_characters;
                entropy -= probability * log2(probability); // ????????? -p_i * log2(p_i)
            }
        }

        return entropy;
    }
    void set_decode(const string& decoded) {
        decode = decoded;
    }

};

