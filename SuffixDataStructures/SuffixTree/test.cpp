#include "suffix_tree.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
using namespace std::chrono;

int main(int argc, char **argv) {
    int tamanhoPadraoGrande = 1'000, tamanhoTextoGrande = 10'000'000;
    std::string padraoGrande = string(tamanhoPadraoGrande - 1, 'A') + "B";
    std::string textoGrande = string(tamanhoTextoGrande - 1, 'A') + "B";
    // padrão será encontrado no último índice possível do texto (9999000)

    // std::string padraoGrande = "ana";
    // std::string textoGrande = "banana";

    auto inicioTempo = high_resolution_clock::now();
    suffix_tree arvore = suffix_tree(textoGrande);
    auto fimTempo = high_resolution_clock::now();

    auto duracao = duration_cast<microseconds>(fimTempo - inicioTempo);
    cout << "Duração da construção do Suffix Tree: " << duracao.count()
             << " microsegundos\n"
             << endl;

    // printf("\n");
    // arvore.show();
    // printf("\n");

    inicioTempo = high_resolution_clock::now();
    arvore.stringMatching(padraoGrande);
    fimTempo = high_resolution_clock::now();

    duracao = duration_cast<microseconds>(fimTempo - inicioTempo);
    cout << "Duração de String Matching utilizando Suffix Tree: "
             << duracao.count() << " microsegundos\n"
             << endl;

    return 0;
}
