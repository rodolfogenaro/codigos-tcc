#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <bits/stdc++.h>
#include <stdio.h>
using namespace std;
#define MAX_TEXT_SIZE 10'000'010 // tamanho máximo do texto é 10'000'000

// RA: Ranking Array
// SA: Suffix Array
int RA[MAX_TEXT_SIZE], SA[MAX_TEXT_SIZE];
int sortAux[MAX_TEXT_SIZE];
int tempRA[MAX_TEXT_SIZE], tempSA[MAX_TEXT_SIZE];

void imprimirSuffixArray(std::string texto) {
    printf(" índice\tsufixo\n");
    int tamanhoTexto = texto.length();
    for (int i = 0; i < tamanhoTexto; i++) {
        printf(" %d\t", SA[i]);
        for (int j = SA[i]; j < tamanhoTexto; j++)
            printf("%c", texto[j]);
        printf("\n");
    }
    printf("\n");
}

// segunda abordagem: O(n log n)
// a string de entrada, até 100K caracteres
// o comprimento da string de entrada
// ranking array e ranking array temporário
// suffix array e suffix array temporário
// para contagem/sort por base
void countingSort(int k, int tamanhoTexto) {
    // O(n)
    int i, soma, maximo = max(300, tamanhoTexto);
    // até 255 caracteres ASCII ou tamanho do texto
    memset(sortAux, 0, sizeof sortAux);
    // limpa a tabela de frequência
    for (i = 0; i < tamanhoTexto; i++) // conta a frequência de cada ranking inteiro
        sortAux[i + k < tamanhoTexto ? RA[i + k] : 0]++;

    int t;
    for (i = soma = 0; i < maximo; i++) {
        t = sortAux[i];
        sortAux[i] = soma;
        soma += t;
    }

    for (i = 0; i < tamanhoTexto; i++) // embaralha o suffix array se necessário
        tempSA[sortAux[SA[i] + k < tamanhoTexto ? RA[SA[i] + k] : 0]++] = SA[i];

    for (i = 0; i < tamanhoTexto; i++) // atualiza o suffix array SA
        SA[i] = tempSA[i];
}

int* construirSuffixArray(std::string texto) {
    int tamanhoTexto = texto.length();
    texto.append("$");
    tamanhoTexto++;

    // essa versão pode processar até 100000 caracteres
    int i, k, r;
    for (i = 0; i < tamanhoTexto; i++)
        RA[i] = texto[i];

    // rankings iniciais
    for (i = 0; i < tamanhoTexto; i++)
        SA[i] = i;

    // SA inicial: {0, 1, 2, ..., tamanhoTexto-1}
    for (k = 1; k < tamanhoTexto; k <<= 1) {
        // repete o processo de ordenação log tamanhoTexto vezes
        // ordenação por base: ordena com base no segundo item
        countingSort(k, tamanhoTexto);
        // depois ordena de forma estável com base no primeiro item
        countingSort(0, tamanhoTexto);

        tempRA[SA[0]] = r = 0;
        // reordenamento; começa do ranking r = 0
        for (i = 1; i < tamanhoTexto; i++) {
            // compara sufixos adjacentes
            tempRA[SA[i]] = (
                (RA[SA[i]] == RA[SA[i - 1]] && RA[SA[i] + k] == RA[SA[i - 1] + k])
                ? r : ++r
            );
            // se mesmo par => mesmo ranking r; caso contrário, aumenta r
        }

        for (i = 0; i < tamanhoTexto; i++) // atualiza o ranking array RA
            RA[i] = tempRA[i];

        if (RA[SA[tamanhoTexto - 1]] == tamanhoTexto - 1) // truque de otimização
            break;
    }

    // imprimirSuffixArray(texto);

    return SA;
}
