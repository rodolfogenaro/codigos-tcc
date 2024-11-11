#include <bits/stdc++.h>
#include <chrono>
#include <iostream>
#include <string>
#include <random>
#include "naive_implementation.hpp"
#include "kmp.hpp"
#include "rabin_karp.hpp"
using namespace std;
using namespace std::chrono;

int main() 
{
    // variaveis em comum
    int tamanhoPadraoGrande = 1'000, tamanhoTextoGrande = 10'000'000;
    std::string padraoGrande = string(tamanhoPadraoGrande - 1, 'A') + "B";
    std::string textoGrande = string(tamanhoTextoGrande - 1, 'A') + "B";
    // padrão será encontrado em ultimo indice possivel de texto (9999000)


    // Naive Implementation
    auto incioTempo = high_resolution_clock::now();
    naiveImplementation(textoGrande, padraoGrande);
    auto fimTempo = high_resolution_clock::now();

    auto duracao = duration_cast<microseconds>(fimTempo - incioTempo);
    cout << "Duração de Naive Implementation: " << duracao.count() << " microsegundos\n" << endl;

    // KMP
    incioTempo = high_resolution_clock::now();
    kmp(textoGrande, padraoGrande);
    fimTempo = high_resolution_clock::now();

    duracao = duration_cast<microseconds>(fimTempo - incioTempo);
    cout << "Duração de KMP: " << duracao.count() << " microsegundos\n" << endl;

    // Rabin-Karp
    incioTempo = high_resolution_clock::now();
    rabinKarp(textoGrande, padraoGrande);
    fimTempo = high_resolution_clock::now();

    duracao = duration_cast<microseconds>(fimTempo - incioTempo);
    cout << "Duração de Rabin-Karp: " << duracao.count() << " microsegundos\n" << endl;

    return 0; 
}
