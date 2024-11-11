#include <cstring>
#include <cstdlib>
#include <iostream>
#include "string_matching.hpp"

// ********************************
//          SUFFIX TREE
// ********************************

// Função para listar todas as ocorrências de um padrão na árvore de sufixos
void listarOcorrencias(No* n) {
    if (n == nullptr) return;

    if (n->indiceSufixo > -1) {
        std::cout << "Ocorrência encontrada na posição: " << n->indiceSufixo << std::endl;
    }
    for (int i = 0; i < MAX_CHAR; i++) {
        if (n->filhos[i] != nullptr) {
            listarOcorrencias(n->filhos[i]);
        }
    }
}

// Função para buscar um padrão na árvore de sufixos
void buscarPadrao(No* raiz, std::string texto, std::string padrao) {
    No* atual = raiz;
    int j = 0;

    while (j < padrao.size()) {
        int indice = padrao[j] - ' ';
        if (atual->filhos[indice] == nullptr) {
            std::cout << "Padrão não encontrado." << std::endl;
            return;
        }

        No* prox = atual->filhos[indice];
        int k = prox->inicio;
        while (k <= *(prox->fim) && j < padrao.size() && texto[k] == padrao[j]) {
            k++;
            j++;
        }

        if (j == padrao.size()) {
            listarOcorrencias(prox); // Lista todas as ocorrências a partir deste nó
            return;
        } else if (k <= *(prox->fim)) {
            std::cout << "Padrão não encontrado." << std::endl;
            return;
        }

        atual = prox;
    }
}

// ********************************
//          SUFFIX ARRAY
// ********************************
