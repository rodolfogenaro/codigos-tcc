#define MAX_CHAR 256

struct NoSuffixTree {
    NoSuffixTree* filhos[MAX_CHAR];
    NoSuffixTree* suffixLink;
    int inicio;
    int* fim;
    int indiceSufixo;
};
typedef NoSuffixTree No;

int comprimentoAresta(No* n);
No* novoNo(int inicio, int* fim);
void imprimir(std::string texto, int i, int j);
int descer(std::string texto, No* noAtual);
void adicionarSufixos(std::string texto, int posicao);
void liberarSuffixTree(No* n);
void definirIndiceSufixoPorDFS(std::string texto, No* n, int altura);
No* construirSuffixTree(std::string texto);
