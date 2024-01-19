// Importações das bibliotecas e do arquivo cabeçalho
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

// Enumeração para as opções do menu
enum MenuOption {
    INSERIR_NOVO_DADO = 1,
    REMOVER_DADO = 2,
    EXIBIR_DADO = 3,
    GERAR_ARQUIVO_BINARIO = 4,
    SAIR = 5
};

// Função principal
int main(int argc, char *argv[]) {
    // Verifica se a quantidade de argumentos é correta
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <dados.bin> <saida.bin>\n", argv[0]);
        return 1;
    }

    // Inicializa a lista
    lista *proximo = NULL;
    int modificacoes = 0; // Flag para rastrear modificações

    // Ler dados do arquivo binário
    lerDadosDoArquivoBinario(argv[1], &proximo);

    // Variáveis para a interação do usuário
    int opcao;
    char placa[7];

    do {
        // Menu de opções
        printf("1. Inserir novo dado\n");
        printf("2. Remover dado\n");
        printf("3. Exibir dado\n");
        printf("4. Gerar arquivo binario\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        // Switch para as opções do menu
        switch (opcao) {
            case INSERIR_NOVO_DADO:
                // Solicita a placa do novo dado ao usuário
                printf("Insira a placa do novo dado: ");
                scanf("%6s", placa);
                // Insere o novo dado na lista
                inserirDado(&proximo, placa);
                // Modificações ocorreram
                modificacoes = 1;
                break;
            case REMOVER_DADO:
                // Solicita a placa do dado a ser removido ao usuário
                printf("Insira a placa do dado a ser removido: ");
                scanf("%6s", placa);
                // Remove o dado da lista
                removerDado(&proximo, placa);
                // Modificações ocorreram
                modificacoes = 1;
                break;
            case EXIBIR_DADO:
                // Solicita a placa do dado a ser exibido ao usuário
                printf("Insira a placa do dado a ser exibido: ");
                scanf("%6s", placa);
                // Exibe o dado da lista
                exibirDado(proximo, placa);
                break;
            case GERAR_ARQUIVO_BINARIO:
                // Verifica se houve modificações na lista
                if (modificacoes) {
                    // Gera o arquivo binário
                    gravarEmArquivoBinario(argv[2], proximo);
                    printf("Arquivo binario gerado com sucesso.\n");
                    // Reinicia a flag de modificações
                    modificacoes = 0;
                } else {
                    printf("Nenhuma modificacao a ser salva.\n");
                }
                break;
            case SAIR:
                // Mensagem de saída
                printf("Saindo...\n");
                break;
            default:
                // Mensagem de opção inválida
                printf("Opcao invalida.\n");
        }
    } while (opcao != SAIR);

    // Gera um novo arquivo binário ao final da execução se os dados foram atualizados
    if (modificacoes) {
        gravarEmArquivoBinario(argv[2], proximo);
    }

    // Libera memória ocupada pela lista
    liberarLista(proximo);

    return 0;
}
