#include <stdio.h>
#include <string.h>

#define MAX_TAREFAS 100
#define CAMPOS 4
#define TAM_CAMPO 50

// Funções
void cadastrarTarefa(char tarefas[][CAMPOS][TAM_CAMPO], int *quantidade);
void listarTarefas(char tarefas[][CAMPOS][TAM_CAMPO], int quantidade);
void editarTarefa(char tarefas[][CAMPOS][TAM_CAMPO], int indice);
void excluirTarefa(char tarefas[][CAMPOS][TAM_CAMPO], int *quantidade, int indice);
void salvarTarefasEmArquivo(char tarefas[][CAMPOS][TAM_CAMPO], int quantidade);

int main() {
    char tarefas[MAX_TAREFAS][CAMPOS][TAM_CAMPO];
    int quantidade = 0;
    int opcao;

    do {
        printf("\n===== GERENCIADOR DE TAREFAS =====\n");
        printf("1. Cadastrar tarefa\n");
        printf("2. Listar tarefas\n");
        printf("3. Editar tarefa\n");
        printf("4. Excluir tarefa\n");
        printf("5. Salvar tarefas em arquivo\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // limpa o buffer do teclado

        switch(opcao) {
            case 1:
                cadastrarTarefa(tarefas, &quantidade);
                break;
            case 2:
                listarTarefas(tarefas, quantidade);
                break;
            case 3: {
                int indice;
                printf("Digite o índice da tarefa a editar: ");
                scanf("%d", &indice);
                getchar();
                editarTarefa(tarefas, indice);
                break;
            }
            case 4: {
                int indice;
                printf("Digite o índice da tarefa a excluir: ");
                scanf("%d", &indice);
                getchar();
                excluirTarefa(tarefas, &quantidade, indice);
                break;
            }
            case 5:
                salvarTarefasEmArquivo(tarefas, quantidade);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}

void cadastrarTarefa(char tarefas[][CAMPOS][TAM_CAMPO], int *quantidade) {
    if (*quantidade >= MAX_TAREFAS) {
        printf("Limite de tarefas atingido!\n");
        return;
    }

    printf("Título: ");
    fgets(tarefas[*quantidade][0], TAM_CAMPO, stdin);
    tarefas[*quantidade][0][strcspn(tarefas[*quantidade][0], "\n")] = '\0';

    printf("Descrição: ");
    fgets(tarefas[*quantidade][1], TAM_CAMPO, stdin);
    tarefas[*quantidade][1][strcspn(tarefas[*quantidade][1], "\n")] = '\0';

    printf("Prioridade (Alta, Média, Baixa): ");
    fgets(tarefas[*quantidade][2], TAM_CAMPO, stdin);
    tarefas[*quantidade][2][strcspn(tarefas[*quantidade][2], "\n")] = '\0';

    printf("Status (Pendente, Em andamento, Concluída): ");
    fgets(tarefas[*quantidade][3], TAM_CAMPO, stdin);
    tarefas[*quantidade][3][strcspn(tarefas[*quantidade][3], "\n")] = '\0';

    (*quantidade)++;
    printf("Tarefa cadastrada com sucesso!\n");
}

void listarTarefas(char tarefas[][CAMPOS][TAM_CAMPO], int quantidade) {
    if (quantidade == 0) {
        printf("Nenhuma tarefa cadastrada.\n");
        return;
    }

    for (int i = 0; i < quantidade; i++) {
        printf("\nTarefa %d:\n", i);
        printf("Título: %s\n", tarefas[i][0]);
        printf("Descrição: %s\n", tarefas[i][1]);
        printf("Prioridade: %s\n", tarefas[i][2]);
        printf("Status: %s\n", tarefas[i][3]);
    }
}

void editarTarefa(char tarefas[][CAMPOS][TAM_CAMPO], int indice) {
    if (indice < 0 || indice >= MAX_TAREFAS) {
        printf("Índice inválido!\n");
        return;
    }

    printf("Novo título: ");
    fgets(tarefas[indice][0], TAM_CAMPO, stdin);
    tarefas[indice][0][strcspn(tarefas[indice][0], "\n")] = '\0';

    printf("Nova descrição: ");
    fgets(tarefas[indice][1], TAM_CAMPO, stdin);
    tarefas[indice][1][strcspn(tarefas[indice][1], "\n")] = '\0';

    printf("Nova prioridade: ");
    fgets(tarefas[indice][2], TAM_CAMPO, stdin);
    tarefas[indice][2][strcspn(tarefas[indice][2], "\n")] = '\0';

    printf("Novo status: ");
    fgets(tarefas[indice][3], TAM_CAMPO, stdin);
    tarefas[indice][3][strcspn(tarefas[indice][3], "\n")] = '\0';

    printf("Tarefa editada com sucesso!\n");
}

void excluirTarefa(char tarefas[][CAMPOS][TAM_CAMPO], int *quantidade, int indice) {
    if (indice < 0 || indice >= *quantidade) {
        printf("Índice inválido!\n");
        return;
    }

    for (int i = indice; i < *quantidade - 1; i++) {
        for (int j = 0; j < CAMPOS; j++) {
            strcpy(tarefas[i][j], tarefas[i + 1][j]);
        }
    }

    (*quantidade)--;
    printf("Tarefa excluída com sucesso!\n");
}

void salvarTarefasEmArquivo(char tarefas[][CAMPOS][TAM_CAMPO], int quantidade) {
    FILE *arquivo = fopen("tarefas.txt", "w");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    for (int i = 0; i < quantidade; i++) {
        fprintf(arquivo, "Tarefa %d:\n", i);
        fprintf(arquivo, "Título: %s\n", tarefas[i][0]);
        fprintf(arquivo, "Descrição: %s\n", tarefas[i][1]);
        fprintf(arquivo, "Prioridade: %s\n", tarefas[i][2]);
        fprintf(arquivo, "Status: %s\n\n", tarefas[i][3]);
    }

    fclose(arquivo);
    printf("Tarefas salvas em 'tarefas.txt' com sucesso!\n");
}
