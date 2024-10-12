#include <bits/stdc++.h> 
#include "kmp.hpp"
  
void geraLPS(std::string P, int tamanhoP, int* lps) 
{ 
    lps[0] = 0;
  
    // representa tamanho de "Longest Proper Prefix which is also Suffix"
    int tamanhoAnteriorLPS = 0; 
    int p = 1; // indice de padrao P
    while (p < tamanhoP) {
        // confere se caractere atual (sufixo) e igual ao anterior (prefixo)
        if (P[p] == P[tamanhoAnteriorLPS]) { 
            tamanhoAnteriorLPS++; 
            lps[p] = tamanhoAnteriorLPS; 
            p++; 
        } else { 
            if (tamanhoAnteriorLPS != 0) { 
                // Diminui tamanho do prefixo a ser comparado
                tamanhoAnteriorLPS = lps[tamanhoAnteriorLPS - 1]; 
            } else {
                // Desiste da comparar, e torna agora novo caracter como prefixo
                lps[p] = 0; 
                p++; 
            } 
        } 
    } 
}
  
void kmp(std::string T, std::string P) 
{ 
    int tamanhoP = P.length();
    int tamanhoT = T.length();
  
    int lps[tamanhoP];
    geraLPS(P, tamanhoP, lps);
  
    int t = 0; // indice de texto T
    int p = 0; // indice de padrao P
    while ((tamanhoT - t) >= (tamanhoP - p)) { 
        if (P[p] == T[t]) { 
            p++; 
            t++; 
        } 
  
        if (p == tamanhoP) { 
            printf("Padrão foi encontrado no índice %d do texto\n", t - p); 
            p = lps[p - 1]; 
        } else if (t < tamanhoT && P[p] != T[t]) {
            // aqui e onde percebe que nao conseguiu completar
            // o padrao, e entao pula alguns indices de acordo
            // com LPS para poupar comparacoes desnecessarias
            if (p != 0) 
                p = lps[p - 1]; 
            else
                t = t + 1; 
        } 
    } 
}
