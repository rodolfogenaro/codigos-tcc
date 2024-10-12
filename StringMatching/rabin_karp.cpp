#include <bits/stdc++.h> 
#include "rabin_karp.hpp"
using namespace std; 

// este valor representa o numero de caracteres de ASCII
#define alphabetCharCount 256
// este valor representa um numero primo muito grande para que não
// tenha problemas na hora do calculo de valor hash
#define numeroPrimoAlto INT_MAX

int calculaHashValue(int prevHashValue, int currCharValue)
{
    return (
        (alphabetCharCount * prevHashValue + currCharValue)
        % numeroPrimoAlto
    );
}

void rabinKarp(std::string texto, std::string padrao) 
{ 
	int tamanhoPadrao = padrao.length(); 
	int tamanhoTexto = texto.length();
    // valor hash de todos os caracteres de padrao
	int valorHashPadrao = 0;
    // valor hash de caracteres dentro da janela de texto,
    // a qual possui mesmo tamanho de padrao
	int valorHashTexto = 0;

    int i, j;

	// ... pow(alphabetCharCount, tamanhoPadrao-1)%numeroPrimoAlto 
    int h = 1;
	for (i = 0; i < tamanhoPadrao - 1; i++)
		h = calculaHashValue(h, 0);

	for (i = 0; i < tamanhoPadrao; i++) {
        // calcula valor hash de todos os caracteres de padrao
		valorHashPadrao = calculaHashValue(valorHashPadrao, padrao[i]);
        // calcula valor hash de caracteres dentro da primeira janela
        // de texto, comencando no indice 0
		valorHashTexto = calculaHashValue(valorHashTexto, texto[i]);
	} 

	// classico problema de Sliding Window
	for (i = 0; i <= tamanhoTexto - tamanhoPadrao; i++) { 

		if (valorHashPadrao == valorHashTexto) {
            // para garantir que que a equivalencia de valores
            // hash nao seja apenas coincidencia, e necessario
            // comparar cada caractere manualmente
			for (j = 0; j < tamanhoPadrao; j++) { 
				if (texto[i + j] != padrao[j]) { 
					break; 
				} 
			}

			if (j == tamanhoPadrao)
				printf("Padrão foi encontrado no índice %d do texto\n", i);
		} 

        // para calcular valor hash de proxima janela é necessario
        // ignorar valor do primeiro caractere atual e considerar
        // valor do caractere sucessor ao ultimo de janela atual
		if (i < tamanhoTexto - tamanhoPadrao) { 
			valorHashTexto = calculaHashValue(
                valorHashTexto - texto[i] * h,
                texto[i + tamanhoPadrao]
            );

            // garante que valor hash calculado nao sera negativo
			if (valorHashTexto < 0) 
				valorHashTexto = valorHashTexto + numeroPrimoAlto; 
		} 
	} 
}
