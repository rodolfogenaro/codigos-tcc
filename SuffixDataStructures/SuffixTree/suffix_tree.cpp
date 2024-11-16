#include "suffix_tree.hpp"
#include <algorithm>
#include <assert.h>
#include <iostream>
#include <stack>
using std::cout;
using std::string;
using std::vector;

Aresta::Aresta(int start, int end, int origin, int destination) {
    start_index = start;
    end_index = end;
    origin_node = origin;
    destination_node = destination;
    if (end_index != FINAL_ATUAL)
        assert(end_index >= start_index); // sanity check
}

int Aresta::length() { return end_index - start_index + 1; }

// node class
node::node() : value(-1), suffix_link(-1) {}

// active point class
// uses three ints to represent a particular point on the growing tree
PontoAtivo::PontoAtivo() {
    active_node = 0;
    active_length = 0;
    active_Aresta = 0;
}

/*
                                this constructor for the suffix tree uses ukkonen's algorithm to
     create the tree in linear time with respect to the sequence length
*/
suffix_tree::suffix_tree(const std::string &s)
        : text(string(string(" ") + s + string("$"))), ponto(PontoAtivo()) {
    nodes.push_back(node()); // the root node
    int remainder = 0;
    // -- main loop of algorithm --
    for (unsigned int i = 0; i < text.length(); i++) {
        remainder += 1;
        int last_inserted = -1;
        int new_inserted = -1;
        bool first = true;
        // try to add suffixes while there's still suffixes to add at the current
        // position i in the string
        while (remainder > 0) {
            // check if the suffix is already contained in the tree implicitly by
            // checking if the new character appears immediately after the active
            // point. if it does, move the active point up 1 and end current step if
            // there was already an internal node marked this step as needing a suffix
            // link, link it to the active node
            if (suffix_already_exists(i)) {
                if (ponto.active_node != 0 && !first) {
                    nodes[new_inserted].suffix_link = ponto.active_node;
                }
                if (ponto.active_Aresta == 0)
                    ponto.active_Aresta = i;
                ponto.active_length += 1;
                canonize();
                break;
            }
            // if we get to here, we didn't find the suffix so it's time to update the
            // tree.
            //         we add a new leaf to the tree
            // if the leaf is added to an internal node, the internal node gets a
            // suffix link
            //         to the last internal node that got a leaf added (rule 2)
            // insert a leaf node directly if active point is at a node.
            if (ponto.active_Aresta == 0) {
                add_leaf_node(i, remainder);
                if (ponto.active_node != 0) {
                    last_inserted = new_inserted;
                    new_inserted = ponto.active_node;
                    if (!first) { // rule 2
                        nodes[last_inserted].suffix_link = ponto.active_node;
                    }
                }
            }
            // if the active point is on an Aresta, split the Aresta and add a leaf to
            // the new internal node
            else {
                assert(ponto.active_Aresta != 0 &&
                             ponto.active_length > 0); // sanity check
                last_inserted = new_inserted;
                new_inserted = split_Aresta(
                        active_Aresta(), active_Aresta().start_index + ponto.active_length,
                        i, i - remainder + 1);
                if (!first) { // rule 2
                    nodes[last_inserted].suffix_link = new_inserted;
                }
            }
            // now that we've added a new node, move the active point to the next
            // shorter suffix if we're at root, this is done by decrementing active
            // length (rule 1) we we're at a non-root node, this is done by following
            // a suffix link (rule 3)
            if (ponto.active_node == 0 && ponto.active_length > 0) { // rule 1
                ponto.active_length -= 1;
                if (ponto.active_length == 0)
                    ponto.active_Aresta = 0;
                else
                    ponto.active_Aresta += 1;
                canonize();
            } else if (ponto.active_node != 0) { // rule 3
                ponto.active_node =
                        active_node().suffix_link == -1 ? 0 : active_node().suffix_link;
                canonize();
            }
            first = false;
            remainder -= 1;
        }
    } // end main loop
}

void suffix_tree::show() { // print a representation of the suffix tree for
                                                     // debugging
    for (unsigned int i = 0; i < nodes.size(); i++) {
        if (!nodes[i].Arestas.empty()) {
            cout << "node " << i;
            if (nodes[i].suffix_link != -1)
                cout << " - - - " << nodes[i].suffix_link;
            cout << std::endl;
            for (auto it = nodes[i].Arestas.begin(); it != nodes[i].Arestas.end();
                     ++it) {
                int start = it->second.start_index;
                int end = it->second.end_index;
                if (end == FINAL_ATUAL)
                    end = text.size() - 1;
                cout << it->first << " " << text.substr(start, end - start + 1);
                if (it->second.end_index !=
                        FINAL_ATUAL) // Aresta does not point to leaf node
                    cout << " -> " << it->second.destination_node;
                else
                    cout << "(" << nodes[it->second.destination_node].value << ")";
                cout << std::endl;
            }
        }
    }
}

bool suffix_tree::suffix_already_exists(int i) {
    if (ponto.active_Aresta == 0)
        return nodes[ponto.active_node].Arestas.count(text[i]) == 1;
    else
        return text[i] == PontoAtivo_character();
}

int suffix_tree::add_leaf_node(
        int position, int remainder) // add a new leaf node to the active node
{
    nodes.push_back(node());
    nodes[ponto.active_node].Arestas.insert(std::make_pair(
            text[position],
            Aresta(position, FINAL_ATUAL, ponto.active_node, nodes.size() - 1)));
    nodes[nodes.size() - 1].value =
            position -
            remainder; // add index where the suffix represented by this leaf started
    return nodes.size() - 1;
}

int suffix_tree::split_Aresta(Aresta &e, int position_to_split,
                                                            int current_position, int suffix_start) {
    nodes.push_back(node()); // make a new internal node
    Aresta old_Aresta = e;
    // edit the Aresta to be split to go from active node to new internal node
    e.destination_node = nodes.size() - 1;
    e.end_index = position_to_split - 1;
    // add an Aresta from the internal node to the orphan leaf node
    nodes[nodes.size() - 1].Arestas.insert(
            std::make_pair(text[position_to_split],
                                         Aresta(position_to_split, old_Aresta.end_index,
                                                        nodes.size() - 1, old_Aresta.destination_node)));
    // add a new leaf node to the internal node representing the repeated
    // character
    nodes.push_back(node());
    nodes[nodes.size() - 2].Arestas.insert(std::make_pair(
            text[current_position], Aresta(current_position, FINAL_ATUAL,
                                                                         nodes.size() - 2, nodes.size() - 1)));
    nodes[nodes.size() - 1].value = suffix_start - 1;
    return e.destination_node; // the address of the internal node
}

Aresta &suffix_tree::active_Aresta() {
    return nodes[ponto.active_node].Arestas.at(text[ponto.active_Aresta]);
}
node &suffix_tree::active_node() { return nodes[ponto.active_node]; }

char suffix_tree::PontoAtivo_character() // character immediately AFTER the
                                                                                 // active point
{
    //        assert (ponto.active_Aresta !=0);
    if (ponto.active_Aresta == 0)
        return 0;
    return text[nodes[ponto.active_node]
                                    .Arestas.at(text[ponto.active_Aresta])
                                    .start_index +
                            ponto.active_length];
}

void suffix_tree::canonize() { // fixes the active point when active_length
                                                             // grows beyond the bounds of the active_Aresta
    if (ponto.active_Aresta == 0)
        return;
    if (active_Aresta().end_index == FINAL_ATUAL)
        return;
    while (active_Aresta().start_index + ponto.active_length >
                 active_Aresta().end_index) { // maybe should be >=
        int increment = active_Aresta().end_index - active_Aresta().start_index + 1;
        ponto.active_node = active_Aresta().destination_node;
        ponto.active_length -= increment;
        if (ponto.active_length > 0)
            ponto.active_Aresta += increment;
        else {
            ponto.active_Aresta = 0;
            return;
        }
        if (ponto.active_Aresta != 0)
            if (active_Aresta().end_index == FINAL_ATUAL)
                return;
        assert(ponto.active_Aresta >= 0);
    }
}

// returns the root node of the sub-tree which represents all the suffixes of
// the query or -1 if query not found
int suffix_tree::buscaPadrao(const string &padrao) {
    ponto = PontoAtivo();
    for (unsigned int i = 0; i < padrao.size(); i++) {
        if (ponto.active_Aresta == 0) { // we are on a node
            if (nodes[ponto.active_node].Arestas.count(padrao[i]) == 0)
                return -1;
            else
                ponto.active_Aresta = i;
            ponto.active_length += 1;
        } else { // we are on an Aresta
            if (!(padrao[i] == text[nodes[ponto.active_node]
					.Arestas.at(padrao[ponto.active_Aresta])
					.start_index +
			ponto.active_length])) {
                return -1;
            } else {
                ponto.active_length += 1;
            }
        }
        // if we reached the end of an Aresta, hop to the node
        if (ponto.active_length >= nodes[ponto.active_node]
                                                                     .Arestas.at(padrao[ponto.active_Aresta])
                                                                     .length()) {
            ponto.active_node = nodes[ponto.active_node]
                                                            .Arestas.at(padrao[ponto.active_Aresta])
                                                            .destination_node;
            ponto.active_length = ponto.active_Aresta = 0;
        }
    }
    if (ponto.active_Aresta == 0)
        return ponto.active_node;
    else
        return nodes[ponto.active_node]
                .Arestas.at(ponto.active_Aresta)
                .destination_node;
}

vector<int>
suffix_tree::find_leaves(int start) { // once we locate the root of the subtree
                                                                            // which contains suffixes of the query
    // traverse the sub tree to find the leaves
    // their labels give the positions of the query in the full string
    std::stack<int> stack;
    vector<int> values;
    stack.push(start);
    while (!stack.empty()) {
        int current_node = stack.top();
        stack.pop();
        // if node has no children it is a leaf. save its start position.
        if (nodes[current_node].Arestas.empty()) {
            assert(nodes[current_node].value >
                         0); // sanity check, if its a leaf it has a positive value
            values.push_back(nodes[current_node].value);
        }
        // otherwise, put its children on the stack
        for (auto it = nodes[current_node].Arestas.begin();
                 it != nodes[current_node].Arestas.end(); ++it) {
            stack.push(it->second.destination_node);
        }
    }
    return values;
}

void suffix_tree::stringMatching(const string &padrao) {
    int subtree_root = buscaPadrao(padrao);
    if (subtree_root == -1)
        return;

    vector<int> posicoesEncontradas = find_leaves(subtree_root);
    for (int p : posicoesEncontradas)
        printf("Padrão foi encontrado no índice %d do texto\n", p);
}
