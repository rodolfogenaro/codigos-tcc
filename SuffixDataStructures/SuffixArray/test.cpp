#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <bits/stdc++.h>
#include <stdio.h>
#include <chrono>
#include "suffix_array.hpp"
#include "string_matching.hpp"
using namespace std;
using namespace std::chrono;

int main() {
    int tamanhoPadraoGrande = 1'000, tamanhoTextoGrande = 10'000'000;
    std::string padraoGrande = string(tamanhoPadraoGrande - 1, 'A') + "B";
    std::string textoGrande = string(tamanhoTextoGrande - 1, 'A') + "B";
    // padrão será encontrado no último índice possível do texto (9999000)

    auto inicioTempo = high_resolution_clock::now();
    int *suffixArray = construirSuffixArray(textoGrande);
    auto fimTempo = high_resolution_clock::now();

    auto duracao = duration_cast<microseconds>(fimTempo - inicioTempo);
    cout << "Duração da construção do Suffix Array: " << duracao.count() << " microsegundos\n" << endl;

    inicioTempo = high_resolution_clock::now();
    stringMatching(suffixArray, textoGrande, padraoGrande);
    fimTempo = high_resolution_clock::now();

    duracao = duration_cast<microseconds>(fimTempo - inicioTempo);
    cout << "Duração de String Matching utilizando Suffix Array: " << duracao.count() << " microsegundos\n" << endl;

    return 0;
}
