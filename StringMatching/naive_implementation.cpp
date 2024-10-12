#include <bits/stdc++.h>
#include "naive_implementation.hpp"

void naiveImplementation(std::string texto, std::string padrao)
{ 
    int tamanhoPadrao = padrao.length(); 
    int tamanhoTexto = texto.length(); 
  
    // percorre texto
    for (int i = 0; i <= tamanhoTexto - tamanhoPadrao; i++) { 
        int j;
        // verifica se padrao comeca a partir de indice i
        for (j = 0; j < tamanhoPadrao; j++) 
            if (texto[i + j] != padrao[j]) 
                break; 
  
        if (j == tamanhoPadrao)
            printf("Padrão foi encontrado no índice %d do texto\n", i);
    } 
}
