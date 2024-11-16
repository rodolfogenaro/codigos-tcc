#ifndef SUFFIX_TREE
#define SUFFIX_TREE
#include <string>
#include <unordered_map>
#include <vector>

// Constante para indicar o final atual
const static int FINAL_ATUAL = -1;

class PontoAtivo;

class Aresta {
public:
    Aresta(int, int, int, int);
    int start_index, end_index;
    int origin_node, destination_node;
    int length();
};

class node {
public:
    node();
    int value;
    int suffix_link; // points to the longest proper suffix of this node
    std::unordered_map<char, Aresta> Arestas;
};

class PontoAtivo {
public:
    PontoAtivo();
    int active_node, active_Aresta, active_length;
};

class suffix_tree {
public:
    suffix_tree(const std::string &);
    void show();
    // functions to search in the tree
    void stringMatching(const std::string &query);
    int buscaPadrao(const std::string &query);
    std::vector<int> find_leaves(int);

private:
    std::vector<node> nodes;
    const std::string text;
    PontoAtivo ponto;
    // private methods for tree construction
    int add_leaf_node(int, int);
    int split_Aresta(Aresta &, int, int, int);
    bool suffix_already_exists(int);
    char PontoAtivo_character();
    // functions to use the active point
    Aresta &active_Aresta();
    node &active_node();
    void canonize();
};

#endif
