//
// Created by Andreea on 16.04.2024.
//
#include <iostream>
#ifndef WILDCARD_H
#define WILDCARD_H

bool isMatch(std::string s, std::string p) {
    if (s.length() != p.length())
        return false;
    int si = 0, pi = 0;
    while (si < s.length() and pi < p.length()) {
        if (s[si] != p[pi]) {
            if (p[pi] != '*')
                return false;
        }
        si++;
        pi++;
    }

    return true;
}

#endif // WILDCARD_H