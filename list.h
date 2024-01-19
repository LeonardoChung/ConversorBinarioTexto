//Evitamos inclusões duplicadas
#ifndef LIST_H
#define LIST_H

//Definimos o tamanho da placa
#define TAMANHO_PLACA 8

//Criamos a estrutura da lista
typedef struct Node {
    char veiculo[50];
    char placa[TAMANHO_PLACA];
    struct Node* proximo;
} lista;

//Declaramos as funções usadas nos códigos
void gravarEmArquivoTexto(const char* nomeArquivo, lista* proximo);
void gravarEmArquivoBinario(const char* arquivo, lista* proximo);
void liberarLista(lista* proximo);
void inserirDado(lista** proximo, const char* placa);
void removerDado(lista** proximo, const char* placa);
void exibirDado(lista* proximo, const char* placa);
void lerDadosDoArquivoTexto(const char* arquivo, lista** proximo);
lista* novaLista(const char* veiculo, const char* placa);
void inserirOrdenado(lista** proximo, lista* novo);
void lerDadosDoArquivoBinario(const char* nomeArquivo, lista** proximo);

#endif
