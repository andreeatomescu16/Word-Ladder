#include <iostream>
#include "Graph.h"
#include "wildcard.h"
#include <map>
#include <iterator>
#include "mapCreator.cpp"
#include <fstream>
#include <vector>

//std::ifstream f("/Users/Asus/seminar3/extra3new/dictionary.txt");
//std::ofstream f1("/Users/Asus/seminar3/extra3new/words1.txt");
//std::ofstream f2("/Users/Asus/seminar3/extra3new/words2.txt");
//std::ofstream f3("/Users/Asus/seminar3/extra3new/words3.txt");
//std::ofstream f4("/Users/Asus/seminar3/extra3new/words4.txt");
//std::ofstream f5("/Users/Asus/seminar3/extra3new/words5.txt");
//std::ofstream f6("/Users/Asus/seminar3/extra3new/words6.txt");

void create_files(std::vector<std::string> & words, std::ifstream &f, std::ofstream &f1, std::ofstream &f2, std::ofstream &f3, std::ofstream &f4, std::ofstream &f5, std::ofstream &f6) {
    std::string line;
    while (std::getline(f, line)) {
        int n = line.length();
        if (n == 1)
            f1 << line <<'\n';
        if (n == 2) {
            f2 << line << '\n';
        }
        if (n == 3)
            f3 << line <<'\n';
        if (n == 4) {
            f4 << line << '\n';
        }
        if (n == 5)
            f5 << line <<'\n';
        if (n == 6)
            f6 << line <<'\n';
    }
    f.clear();
    f.seekg(0);
}

template <typename T>
void bfs(Graph<T>& g, T startNode, T endNode,
         std::unordered_map<T, bool>& visited, std::unordered_map<T, T>& parent)
{
    queue<T> q;

    visited[startNode] = true;
    q.push(startNode);

    while (!q.empty()) {
        T currentNode = q.front();
        q.pop();
        //std::cout << currentNode << " ";

        for (T neighbour : g.getNeighbours(currentNode)) {
            if (!visited[neighbour]) {
                parent[neighbour] = currentNode;
//                std::cout << neighbour << ' ' << isMatch(neighbour, endNode) << '\n';
                if (isMatch(neighbour, endNode))
                    return;
                visited[neighbour] = true;
                q.push(neighbour);
            }
        }
    }
}

void read_from_file(std::ifstream &f) {
    std::string line;
    if (f.is_open()) {
        while (std::getline(f, line)) {
            std::cout << line << '\n';
        }
        f.clear();
        f.seekg(0);
    }
}


int main() {


    std::ifstream newf1("/Users/Asus/seminar3/extra3new/words1.txt");
    std::ifstream newf2("/Users/Asus/seminar3/extra3new/words2.txt");
    std::ifstream newf3("/Users/Asus/seminar3/extra3new/words3.txt");
    std::ifstream newf4("/Users/Asus/seminar3/extra3new/words4.txt");
    std::ifstream newf5("/Users/Asus/seminar3/extra3new/words5.txt");
    std::ifstream newf6("/Users/Asus/seminar3/extra3new/words6.txt");

    std::cout << "\033[0;31m";
    std::cout << ("Welcome to the word ladder game!\n");
    std::cout << ("The rules are simple: you have to change the start word into the end word by changing one letter at a time.\n");
    std::cout << ("You can use the command 'help#' whenever you don't know how to continue.\n");
    std::cout << ("Let's start!\n");
    std::cout << "\033[0m";

    int n;
    std::cout << "Enter the length of the words: ";
    std::cin >> n;

    Graph<std::string> g = Graph<std::string> ();
    std::multimap<std::string, std::string> my;

    std::vector<std::string> words;
    if (n == 1)
        create_map(my, newf1, words);
    if (n == 2)
        create_map(my, newf2, words);
    if (n == 3)
        create_map(my, newf3, words);
    if (n == 4)
        create_map(my, newf4, words);
    if (n == 5)
        create_map(my, newf5, words);
    if (n == 6)
        create_map(my, newf6, words);

    for (auto it = my.begin(); it != my.end(); ++it) {
        g.add_edge(it->first, it->second);
    }


    std::unordered_map<std::string, bool> visited;
    for (int i = 0; i < g.get_size(); i++) {
        visited[g.getList()[i][0]] = false;
        visited[g.getList()[i][1]] = false;
    }
    std::unordered_map<std::string, std::string> parent;

    bool found1 = false;
    bool found2 = false;

    std::string s1;
    std::string s2;

    while (!found1 || !found2) {
        std::cout << "Enter the start word: ";
        std::cin >> s1;
        std::cout << "Enter the end word: ";
        std::cin >> s2;


        for (int i = 0 ; i < words.size(); i++) {
            if (words[i] == s1)
                found1 = true;
            if (words[i] == s2)
                found2 = true;
        }
        if (!found1)
            std::cout << "not valid start word\n";

        if (!found2)
            std::cout << "not valid end word\n";
    }


    std::string prev = s1;
    std::string str;


    bool found = false;
    while (!found) {
        std::cin >> str;

        if (strcmp(str.c_str(), "help#") == 0) {
            bfs(g, s1, s2, visited, parent);
            std::vector<std::string> shortestPath;
            std::string currentNode = s2;
            int nr = 0;
            std::string result;
            while (currentNode != s1) {
                bool ok = false;
                for (int i = 0; i < currentNode.length() && !ok; i++)
                    if (currentNode[i] == '*')
                        ok = true;

                if (!ok)
                    shortestPath.push_back(currentNode);
                currentNode = parent[currentNode];
            }
            shortestPath.push_back(s1);
            std::reverse(shortestPath.begin(), shortestPath.end());

            for (const auto &node: shortestPath) {
                if (nr == 1) {
                    result = node;
                }
                nr++;
            }

            for (int i = 0; i < result.length(); i++)
                if (result[i] != s1[i]) {
                    std::cout << "\033[0;34m";
                    std::cout << result[i];
                    std::cout << "\033[0m";
                }
                else
                    std::cout << result[i];
            std::cout << '\n';

        } else {

            bool ok = false;
            for (int i = 0; i < words.size(); i++) {
                bool ok2 = true;
                for (int j = 0; j < words[i].length() && ok2; j++)
                    if (words[i][j] != str[j])
                        ok2 = false;
                if (ok2) {
                    ok = true;
                    break;
                }
            }

            if (!ok)
                std::cout << "not a valid word\n";

            else {

                s1 = str;

            int nr = 0;
            for (int i = 0; i < s1.length(); i++)
                if (s1[i] != prev[i])
                    nr++;


            if (nr <= 1)
                prev = s1;

            else {
                std::cout << "not a valid word\n";
                continue;
            }

            if (prev == s2)
                found = true;
            }
        }
    }

    std::cout << "\033[0;31m";
    std::cout << "Congrats!";
    std::cout << "\033[0m";
    return 0;

}