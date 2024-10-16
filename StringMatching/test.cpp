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
    auto start = high_resolution_clock::now();
    naiveImplementation(textoGrande, padraoGrande);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Duração de Naive Implementation: " << duration.count() << " microsegundos\n" << endl;

    // KMP
    start = high_resolution_clock::now();
    kmp(textoGrande, padraoGrande);
    stop = high_resolution_clock::now();

    duration = duration_cast<microseconds>(stop - start);
    cout << "Duração de KMP: " << duration.count() << " microsegundos\n" << endl;

    // Rabin-Karp
    start = high_resolution_clock::now();
    rabinKarp(textoGrande, padraoGrande);
    stop = high_resolution_clock::now();

    duration = duration_cast<microseconds>(stop - start);
    cout << "Duração de Rabin-Karp: " << duration.count() << " microsegundos\n" << endl;

    return 0; 
}
