#include <cstring>
#include <cstdlib>
#include <chrono>
#include <iostream>
#include <string>
#include "string_matching.hpp"
using namespace std;
using namespace std::chrono;

int main() {
    int tamanhoPadraoGrande = 1'000, tamanhoTextoGrande = 10'000'000;
    std::string padraoGrande = string(tamanhoPadraoGrande - 1, 'A') + "B";
    std::string textoGrande = string(tamanhoTextoGrande - 1, 'A') + "B";

    No* raiz = construirSuffixTree(textoGrande);
    buscarPadrao(raiz, textoGrande, padraoGrande);
    
    // std::string texto = "banana";
    // No* raiz = construirSuffixTree(texto);

    // std::string padrao = "ana";
    // buscarPadrao(raiz, texto, padrao);

    liberarSuffixTree(raiz);
    return 0;
}
