#include <cstring>
#include <cstdlib>
#include <iostream>
#include "suffix_tree.hpp"
using namespace std;

int contador = 0;
int arestaAtiva = -1;
int comprimentoArestaAtiva = 0;
int* fimRaiz = nullptr;
int* fimNoInterno = nullptr;
int tamanhoTexto = -1;
No* raiz = nullptr;

int posicaoFolha = -1;
int sufixosRestantes = 0;
No* ultimoNoCriado = nullptr;
No* noAtivo = nullptr;

int comprimentoAresta(No* n) {
    return *(n->fim) - (n->inicio) + 1;
}

No* novoNo(int inicio, int* fim) {
    contador++;
    No* no = new No;
    for (int i = 0; i < MAX_CHAR; i++)
        no->filhos[i] = nullptr;

    no->suffixLink = raiz;
    no->inicio = inicio;
    no->fim = fim;
    no->indiceSufixo = -1;
    return no;
}

void imprimir(std::string texto, int i, int j) {
    for (int k = i; k <= j; k++)
        std::cout << texto[k];
}

int descer(std::string texto, No* noAtual) {
    if (comprimentoArestaAtiva >= comprimentoAresta(noAtual)) {
        arestaAtiva = static_cast<int>(texto[arestaAtiva + comprimentoAresta(noAtual)]) - static_cast<int>(' ');
        comprimentoArestaAtiva -= comprimentoAresta(noAtual);
        noAtivo = noAtual;
        return 1;
    }
    return 0;
}

void adicionarSufixos(std::string texto, int posicao) {
    posicaoFolha = posicao;
    sufixosRestantes++;
    ultimoNoCriado = nullptr;

    while (sufixosRestantes > 0) {
        if (comprimentoArestaAtiva == 0) {
            arestaAtiva = static_cast<int>(texto[posicao]) - static_cast<int>(' ');
        }

        if (noAtivo->filhos[arestaAtiva] == nullptr) {
            noAtivo->filhos[arestaAtiva] = novoNo(posicao, &posicaoFolha);
            noAtivo->filhos[arestaAtiva]->indiceSufixo = posicao;

            if (ultimoNoCriado != nullptr) {
                ultimoNoCriado->suffixLink = noAtivo;
                ultimoNoCriado = nullptr;
            }
        }
        else {
            No* prox = noAtivo->filhos[arestaAtiva];
            if (descer(texto, prox)) {
                continue;
            }

            if (texto[prox->inicio + comprimentoArestaAtiva] == texto[posicao]) {
                if (ultimoNoCriado != nullptr && noAtivo != raiz) {
                    ultimoNoCriado->suffixLink = noAtivo;
                    ultimoNoCriado = nullptr;
                }

                comprimentoArestaAtiva++;
                break;
            }

            fimNoInterno = new int;
            *fimNoInterno = prox->inicio + comprimentoArestaAtiva - 1;

            No* divisao = novoNo(prox->inicio, fimNoInterno);
            noAtivo->filhos[arestaAtiva] = divisao;

            divisao->filhos[static_cast<int>(texto[posicao]) - static_cast<int>(' ')] = novoNo(posicao, &posicaoFolha);
            divisao->filhos[static_cast<int>(texto[posicao]) - static_cast<int>(' ')]->indiceSufixo = posicao;

            prox->inicio += comprimentoArestaAtiva;
            divisao->filhos[arestaAtiva] = prox;

            if (ultimoNoCriado != nullptr) {
                ultimoNoCriado->suffixLink = divisao;
            }

            ultimoNoCriado = divisao;
        }

        sufixosRestantes--;
        if (noAtivo == raiz && comprimentoArestaAtiva > 0) {
            comprimentoArestaAtiva--;
            arestaAtiva = static_cast<int>(texto[posicao - sufixosRestantes + 1]) - static_cast<int>(' ');
        }
        else if (noAtivo != raiz) {
            noAtivo = noAtivo->suffixLink;
        }
    }
}

void liberarSuffixTree(No* n) {
    if (n == nullptr)
        return;

    for (int i = 0; i < MAX_CHAR; i++)
        if (n->filhos[i] != nullptr)
            liberarSuffixTree(n->filhos[i]);

    if (n->indiceSufixo == -1)
        delete n->fim;
    delete n;
}

void definirIndiceSufixoPorDFS(std::string texto, No* n, int alturaEtiqueta) {
    if (n == nullptr) return;

    if (n->inicio != -1) {
        imprimir(texto, n->inicio, *(n->fim));
    }
    int folha = 1;
    for (int i = 0; i < MAX_CHAR; i++) {
        if (n->filhos[i] != nullptr) {
            if (folha == 1 && n->inicio != -1)
                std::cout << " [" << n->indiceSufixo << "]\n";

            folha = 0;
            definirIndiceSufixoPorDFS(texto, n->filhos[i], alturaEtiqueta + comprimentoAresta(n->filhos[i]));
        }
    }
    if (folha == 1) {
        n->indiceSufixo = tamanhoTexto - alturaEtiqueta;
        std::cout << " [" << n->indiceSufixo << "]\n";
    }
}

No* construirSuffixTree(std::string texto) {
    tamanhoTexto = texto.length();
    fimRaiz = new int;
    *fimRaiz = -1;

    raiz = novoNo(-1, fimRaiz);

    noAtivo = raiz;
    for (int i = 0; i < tamanhoTexto; i++)
        adicionarSufixos(texto, i);
    int alturaEtiqueta = 0;
    definirIndiceSufixoPorDFS(texto, raiz, alturaEtiqueta);

    return raiz;
}
