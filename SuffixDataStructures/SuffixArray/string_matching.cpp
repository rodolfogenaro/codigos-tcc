#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <bits/stdc++.h>
#include <stdio.h>
using namespace std;

// busca de string em O(m log n)
pair<int, int> stringMatching(int* suffixArray, std::string texto, std::string padrao) {
    int tamanhoTexto = texto.length(), tamanhoPadrao = padrao.length();

    // busca binária
    // correspondência válida = [0..tamanhoTexto-1]
    int limiteInferior = 0, limiteSuperior = tamanhoTexto - 1, meio = limiteInferior;
    while (limiteInferior < limiteSuperior) { // encontra o limite inferior
        meio = (limiteInferior + limiteSuperior) / 2; // arredondamento para baixo
        // tenta encontrar P no sufixo 'meio'
        int res = texto.compare(suffixArray[meio], tamanhoPadrao, padrao);
        if (res >= 0)
            limiteSuperior = meio; // remove a metade superior (observe o sinal >=)
        else
            limiteInferior = meio + 1; // remove a metade inferior incluindo o meio
    } // observe o '=' em "res >= 0" acima

    // se não encontrado
    if (texto.compare(suffixArray[limiteInferior], tamanhoPadrao, padrao) != 0)
        return pair<int, int>(-1, -1);

    pair<int, int> LimitesSuffixArray; LimitesSuffixArray.first = limiteInferior;
    limiteInferior = 0; limiteSuperior = tamanhoTexto - 1; meio = limiteInferior;
    // se o limite inferior foi encontrado, encontra o limite superior
    while (limiteInferior < limiteSuperior) {
        meio = (limiteInferior + limiteSuperior) / 2;
        int res = texto.compare(suffixArray[meio], tamanhoPadrao, padrao);
        if (res > 0)
            limiteSuperior = meio; // remove a metade superior
        else
            limiteInferior = meio + 1; // remove a metade inferior incluindo o meio
    } // (observe o ramo selecionado quando res == 0)

    // caso especial
    if (texto.compare(suffixArray[limiteSuperior], tamanhoPadrao, padrao) != 0)
        limiteSuperior--;

    LimitesSuffixArray.second = limiteSuperior;

    for (
        int indiceResposta = LimitesSuffixArray.first;
        indiceResposta <= LimitesSuffixArray.second;
        indiceResposta++
    )
        printf("Padrão foi encontrado no índice %d do texto\n", suffixArray[indiceResposta]);

    return LimitesSuffixArray;
} // retorna limiteInferior/limiteSuperior como primeiro/segundo item do par, respectivamente
