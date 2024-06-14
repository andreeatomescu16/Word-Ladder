//
// Created by Andreea on 16.04.2024.
//
#include <iostream>
#include <iterator>
#include <map>
#include <fstream>
#include "wildcard.h"

void create_map(std::multimap<std::string, std::string>& dictionary, std::ifstream &f, std::vector<std::string>& words) {
    std::string line;
    std::multimap<std::string, std::string> my_dict;
    if (f.is_open()) {
        while (std::getline(f, line)) {
            bool ok = false;
//            std::cout << line << '\n';
            words.push_back(line);
            for (auto it = dictionary.begin(); it != dictionary.end(); ++it){
                if (isMatch(line, it->first)) {
                    my_dict.insert({it->first, line});
                    ok = true;
                }
            }

            if (!ok) {
                for (int i = 0; i < line.length(); i++) {
                    std::string aux = line;
                    aux[i] = '*';
                    my_dict.insert({aux, line});
                }
            }
//            std::cout << ok;
        }
    }
    dictionary.insert(my_dict.begin(), my_dict.end());
//    for (auto it = dictionary.begin(); it != dictionary.end(); ++it)
//        std::cout << it->first << ' ' << it->second << ' ';
}