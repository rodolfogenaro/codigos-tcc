#include <bits/stdc++.h>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
using namespace std::chrono;

void lcs(std::string palavra1, std::string palavra2)
{
    int tamanhoPalavra1 = palavra1.length();
    int tamanhoPalavra2 = palavra2.length();
    // pd (programacao dinamica) é a matriz que armazena o tamanho
    // da maior subsequencia ate entao, durante comparacao de
    // caracteres entre palavra1 e palavra2
    int pd[tamanhoPalavra1+1][tamanhoPalavra2+1];

    int i, j, maxSubsequenciaAteEntao;

    // casos base, onde so e necessario remover os caracteres da palavra maior
    for (j=0; j<=tamanhoPalavra2; j++)
        pd[tamanhoPalavra1][j] = 0;
    for (i=0; i<=tamanhoPalavra1; i++)
        pd[i][tamanhoPalavra2] = 0;
    
    for (i=tamanhoPalavra1-1; i>=0; i--) {
        for (j=tamanhoPalavra2-1; j>=0; j--) {
            if (palavra1[i] == palavra2[j])
                pd[i][j] = 1 + pd[i+1][j+1];
            else {
                maxSubsequenciaAteEntao = max(pd[i+1][j], pd[i][j+1]);
                pd[i][j] = maxSubsequenciaAteEntao;
            }
        }
    }
    
    printf("O tamanho da maior subsequência em comum é: %d\n", pd[0][0]);
    for (i=0; i<=tamanhoPalavra1; i++) {
        for (j=0; j<=tamanhoPalavra2; j++) {
            printf("%d ", pd[i][j]);
        }
        printf("\n");
    }
}

int main() {
    std::string palavra1 = "abcde", palavra2 = "ace";
  
    auto start = high_resolution_clock::now();
    lcs(palavra1, palavra2);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Duração de LCS: " << duration.count() << " microsegundos\n" << endl;

  return 0;
}
