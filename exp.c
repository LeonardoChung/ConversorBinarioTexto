//Incluimos as bibliotecas e o arquivo cabecalho
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

//Funcao principal do exportador
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <saida.bin> <exportador.txt>\n", argv[0]);
        return 1;
    }

    lista *proximo = NULL;

    // Ler dados do arquivo binário
    lerDadosDoArquivoBinario(argv[1], &proximo);

    // Gravar em arquivo de texto
    gravarEmArquivoTexto(argv[2], proximo);

    // Liberar memória
    liberarLista(proximo);

    return 0;
}
