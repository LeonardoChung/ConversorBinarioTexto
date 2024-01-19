//Incluimos as bibliotecas e o arquivo cabecalho
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(int argc, char *argv[]) {
    // Verifica se a quantidade de argumentos é correta
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <veiculo.txt> <dados.bin>\n", argv[0]);
        return 1;
    }

    // Inicializa a lista
    lista *proximo = NULL;

    // Abre o arquivo de texto para leitura
    FILE *arquivoTexto = fopen(argv[1], "r");
    if (arquivoTexto == NULL) {
        perror("Erro ao abrir o arquivo de texto para leitura");
        return 1;
    }

    // Variáveis para armazenar os dados lidos do arquivo de texto
    char veiculo[50], placa[TAMANHO_PLACA];

    // Lê os dados do arquivo de texto e os insere ordenadamente na lista
    while (fscanf(arquivoTexto, "%49s %6s", veiculo, placa) == 2) {
        lista *novo = novaLista(veiculo, placa);
        inserirOrdenado(&proximo, novo);
    }

    // Fecha o arquivo de texto
    fclose(arquivoTexto);

    // Grava os dados em um arquivo binário
    gravarEmArquivoBinario(argv[2], proximo);

    // Libera a memória ocupada pela lista
    liberarLista(proximo);

    return 0;
}
