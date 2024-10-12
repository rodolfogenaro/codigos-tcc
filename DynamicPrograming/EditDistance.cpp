#include <bits/stdc++.h>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
using namespace std::chrono;

void editDistance(std::string palavra1, std::string palavra2)
{
    int tamanhoPalavra1 = palavra1.length();
    int tamanhoPalavra2 = palavra2.length();
    // pd (programacao dinamica) é a matriz que armazena o numero
    // minimo de operacoes ate entao, durante comparacao de
    // caracteres entre palavra1 e palavra2
    int pd[tamanhoPalavra1+1][tamanhoPalavra2+1];

    int i, j, minOperacoesAteEntao;

    // casos base, onde so e necessario remover os caracteres da palavra maior
    for (j=0; j<=tamanhoPalavra2; j++)
        pd[tamanhoPalavra1][j] = tamanhoPalavra2 - j;
    for (i=0; i<=tamanhoPalavra1; i++)
        pd[i][tamanhoPalavra2] = tamanhoPalavra1 - i;
    
    for (i=tamanhoPalavra1-1; i>=0; i--) {
        for (j=tamanhoPalavra2-1; j>=0; j--) {
            if (palavra1[i] == palavra2[j])
                pd[i][j] = pd[i+1][j+1];
            else {
                minOperacoesAteEntao = min(pd[i+1][j], pd[i][j+1]);
                minOperacoesAteEntao = min(minOperacoesAteEntao, pd[i+1][j+1]);

                pd[i][j] = 1 + minOperacoesAteEntao;
            }
        }
    }
    
    printf("O número mínimo de operações para transformar palavra1 em palavra2 é: %d\n", pd[0][0]);
}

int main() {
    std::string palavra1 = "intencao", palavra2 = "execucao";
  
    auto start = high_resolution_clock::now();
    editDistance(palavra1, palavra2);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Duração de Edit Distance: " << duration.count() << " microsegundos\n" << endl;

  return 0;
}
