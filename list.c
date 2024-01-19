// Importacoes das bibliotecas e do arquivo cabecalho
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

// Função para inserir um novo elemento ordenado na lista.
void inserirOrdenado(lista **proximo, lista *novo) {
    // Se a lista estiver vazia ou o novo elemento deve ser o primeiro,
    // ajusta os ponteiros para inserção no início.
    if (*proximo == NULL || strcmp((*proximo)->placa, novo->placa) > 0) {
        novo->proximo = *proximo;
        *proximo = novo;
    } else {
        // Caso contrário, encontra a posição correta na lista
        // mantendo a ordem crescente com base na placa.
        lista *atual = *proximo;
        while (atual->proximo != NULL && strcmp(atual->proximo->placa, novo->placa) < 0) {
            atual = atual->proximo;
        }
        novo->proximo = atual->proximo;
        atual->proximo = novo;
    }
}

// Função para inserir um novo dado na lista.
void inserirDado(lista **proximo, const char *placa) {
    char veiculo[50];
    
    printf("Insira o nome do veiculo: ");
    scanf("%49s", veiculo);

    // Cria um novo elemento e o insere na lista mantendo a ordem.
    lista *novo = novaLista(veiculo, placa);
    inserirOrdenado(proximo, novo);
}

// Função para remover um dado da lista.
void removerDado(lista **proximo, const char *placa) {
    // Verifica se a lista está vazia.
    if (*proximo == NULL) {
        printf("A lista esta vazia. Nada a remover.\n");
        return;
    }

    lista *atual = *proximo;
    lista *anterior = NULL;

    // Procura o elemento na lista.
    while (atual != NULL && strcmp(atual->placa, placa) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    // Se não encontrou o elemento na lista.
    if (atual == NULL) {
        printf("Veiculo com placa %s nao encontrado.\n", placa);
        return;
    }

    // Remove o elemento da lista.
    if (anterior == NULL) {
        // Remover o primeiro elemento
        *proximo = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    printf("Veiculo removido: %s\n", atual->veiculo);
    free(atual);
}

// Função recursiva para exibir dados de um elemento específico.
void exibirDadoRecursivo(lista *atual, const char *placa) {
    // Caso base: se o elemento não foi encontrado.
    if (atual == NULL) {
        printf("Veiculo com placa %s nao encontrado.\n", placa);
        return;
    }

    // Caso recursivo: se o elemento foi encontrado.
    if (strcmp(atual->placa, placa) == 0) {
        printf("Veiculo encontrado: %s %s\n", atual->veiculo, atual->placa);
        return;
    }

    // Chama recursivamente para o próximo elemento na lista.
    exibirDadoRecursivo(atual->proximo, placa);
}

// Função principal que inicializa a chamada recursiva.
void exibirDado(lista *proximo, const char *placa) {
    exibirDadoRecursivo(proximo, placa);
}


// Função para criar um novo nó na lista.
lista *novaLista(const char *veiculo, const char *placa) {
    lista *novo = (lista *)malloc(sizeof(lista));
    if (novo == NULL) {
        fprintf(stderr, "Erro ao alocar memória para novo elemento.\n");
        exit(EXIT_FAILURE);
    }

    // Copia os dados para o novo elemento.
    strncpy(novo->veiculo, veiculo, sizeof(novo->veiculo) - 1);
    novo->veiculo[sizeof(novo->veiculo) - 1] = '\0';
    strncpy(novo->placa, placa, sizeof(novo->placa) - 1);
    novo->placa[sizeof(novo->placa) - 1] = '\0';
    novo->proximo = NULL;

    return novo;
}

// Função para gravar a lista em um arquivo de texto.
void gravarEmArquivoTexto(const char *nomeArquivo, lista *proximo) {
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo de texto para escrita");
        exit(EXIT_FAILURE);
    }

    // Percorre a lista e escreve cada elemento no arquivo.
    for (lista *atual = proximo; atual != NULL; atual = atual->proximo) {
        fprintf(arquivo, "%s %s\n", atual->veiculo, atual->placa);
    }

    fclose(arquivo);
}

// Função para ler dados de um arquivo de texto e inserir na lista.
void lerDadosDoArquivoTexto(const char *nomeArquivo, lista **proximo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo de texto para leitura");
        exit(EXIT_FAILURE);
    }

    char veiculo[50], placa[TAMANHO_PLACA];

    // Lê os dados do arquivo e insere na lista mantendo a ordem.
    while (fscanf(arquivo, "%49s %6s", veiculo, placa) == 2) {
        lista *novo = novaLista(veiculo, placa);
        inserirOrdenado(proximo, novo);
    }

    fclose(arquivo);
}

// Função para ler dados de um arquivo binário e inserir na lista.
void lerDadosDoArquivoBinario(const char *nomeArquivo, lista **proximo) {
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo binário para leitura");
        exit(EXIT_FAILURE);
    }

    // Lê os dados do arquivo e insere na lista mantendo a ordem.
    while (1) {
        lista *novo = (lista *)malloc(sizeof(lista));
        if (fread(novo, sizeof(lista), 1, arquivo) != 1) {
            free(novo);
            break;  // Se não conseguir ler mais, saia do loop
        }
        novo->proximo = NULL;
        inserirOrdenado(proximo, novo);
    }

    fclose(arquivo);
}

// Função para gravar a lista em um arquivo de texto (versão exportador).
void gravarEmArquivoTextoExportador(const char *nomeArquivo, lista *proximo) {
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo de texto para escrita");
        exit(EXIT_FAILURE);
    }

    // Percorre a lista e escreve cada elemento no arquivo.
    for (lista *atual = proximo; atual != NULL; atual = atual->proximo) {
        fprintf(arquivo, "%s %s\n", atual->veiculo, atual->placa);
    }

    fclose(arquivo);
}

// Função para gravar a lista em um arquivo binário.
void gravarEmArquivoBinario(const char *nomeArquivo, lista *proximo) {
    FILE *arquivo = fopen(nomeArquivo, "wb");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo binário para escrita");
        exit(EXIT_FAILURE);
    }

    // Percorre a lista e escreve cada elemento no arquivo.
    for (lista *atual = proximo; atual != NULL; atual = atual->proximo) {
        if (fwrite(atual, sizeof(lista), 1, arquivo) != 1) {
            perror("Erro ao escrever no arquivo binário");
            fclose(arquivo);
            exit(EXIT_FAILURE);
        }
    }

    fclose(arquivo);
}

// Função para liberar a memória ocupada pela lista.
void liberarLista(lista *proximo) {
    while (proximo != NULL) {
        lista *temp = proximo;
        proximo = proximo->proximo;
        free(temp);
    }
}
