#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Fruta {
    int codigo;
    char nome[30];
    int quantidade;
    float preco;
    struct Fruta* prox;
} Fruta;

Fruta* lista = NULL;

int verificarCodigoUnico(int codigo) {
    Fruta* atual = lista;
    while (atual != NULL) {
        if (atual->codigo == codigo) {
            return 0;
        }
        atual = atual->prox;
    }
    return 1;
}

Fruta* encontrarFruta(int codigo) {
    Fruta* atual = lista;
    while (atual != NULL) {
        if (atual->codigo == codigo) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

void cadastrarFruta() {
    Fruta* novaFruta = (Fruta*)malloc(sizeof(Fruta));
    if (novaFruta == NULL) {
        printf("Erro ao alocar memoria.\n");
        return;
    }

    printf("Codigo da fruta: ");
    scanf("%d", &novaFruta->codigo);

    if (!verificarCodigoUnico(novaFruta->codigo)) {
        printf("Erro: codigo ja existe!\n");
        free(novaFruta);
        return;
    }

    printf("Nome da fruta: ");
    scanf("%s", novaFruta->nome);
    printf("Quantidade: ");
    scanf("%d", &novaFruta->quantidade);
    printf("Preco: ");
    scanf("%f", &novaFruta->preco);
    novaFruta->prox = lista;
    lista = novaFruta;
    printf("Fruta cadastrada com sucesso.\n");
}

void listarFrutas() {
    if (lista == NULL) {
        printf("Nenhuma fruta cadastrada.\n");
        return;
    }

    printf("\n--- Lista de Frutas ---\n");
    Fruta* atual = lista;
    while (atual != NULL) {
        printf("Codigo: %d, Nome: %s, Quantidade: %d, Preco: %.2f\n", atual->codigo, atual->nome, atual->quantidade, atual->preco);
        atual = atual->prox;
    }
}

void buscarFruta() {
    int codigo;
    printf("Digite o codigo da fruta: ");
    scanf("%d", &codigo);

    Fruta* fruta = encontrarFruta(codigo);
    if (fruta != NULL) {
        printf("Fruta encontrada: Codigo: %d, Nome: %s, Quantidade: %d, Preco: %.2f\n", fruta->codigo, fruta->nome, fruta->quantidade, fruta->preco);
    } else {
        printf("Fruta nao encontrada.\n");
    }
}

void alterarFruta() {
    int codigo;
    printf("Digite o codigo da fruta para alterar: ");
    scanf("%d", &codigo);

    Fruta* fruta = encontrarFruta(codigo);
    if (fruta != NULL) {
        printf("Nome atual: %s, novo nome: ", fruta->nome);
        scanf("%s", fruta->nome);
        printf("Quantidade atual: %d, nova quantidade: ", fruta->quantidade);
        scanf("%d", &fruta->quantidade);
        printf("Preco atual: %.2f, novo preco: ", fruta->preco);
        scanf("%f", &fruta->preco);
        printf("Fruta alterada com sucesso.\n");
    } else {
        printf("Fruta nao encontrada.\n");
    }
}

void excluirFruta() {
    int codigo;
    printf("Digite o codigo da fruta para excluir: ");
    scanf("%d", &codigo);

    Fruta* atual = lista;
    Fruta* anterior = NULL;

    while (atual != NULL) {
        if (atual->codigo == codigo) {
            if (atual->quantidade > 0) {
                printf("Erro: a fruta nao pode ser excluida, pois ainda tem estoque.\n");
                return;
            }
            if (anterior == NULL) {
                lista = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
            printf("Fruta excluida com sucesso.\n");
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
    printf("Fruta nao encontrada.\n");
}

void registrarVenda(int codigo, int quantidade, float precoTotal) {
    FILE* arquivo = fopen("vendas.txt", "a");
    if (arquivo != NULL) {
        fprintf(arquivo, "Codigo: %d, Quantidade: %d, Total: %.2f\n", codigo, quantidade, precoTotal);
        fclose(arquivo);
        printf("Venda registrada com sucesso.\n");
    } else {
        printf("Erro ao abrir o arquivo de vendas.\n");
    }
}

void venderFruta() {
    int codigo, quantidade;
    printf("Digite o codigo da fruta a vender: ");
    scanf("%d", &codigo);
    printf("Digite a quantidade a vender: ");
    scanf("%d", &quantidade);

    Fruta* fruta = encontrarFruta(codigo);
    if (fruta != NULL) {
        if (fruta->quantidade < quantidade) {
            printf("Erro: quantidade insuficiente em estoque.\n");
            return;
        }
        fruta->quantidade -= quantidade;
        registrarVenda(codigo, quantidade, quantidade * fruta->preco);
    } else {
        printf("Fruta nao encontrada.\n");
    }
}

void liberarMemoria() {
    Fruta* atual = lista;
    while (atual != NULL) {
        Fruta* prox = atual->prox;
        free(atual);
        atual = prox;
    }
}

void exibirMenu() {
    printf("\n--- Menu ---\n");
    printf("1. Cadastrar Fruta\n");
    printf("2. Listar Frutas\n");
    printf("3. Buscar Fruta\n");
    printf("4. Alterar Fruta\n");
    printf("5. Excluir Fruta\n");
    printf("6. Vender Fruta\n");
    printf("7. Sair\n");
    printf("Escolha uma opcao: ");
}

int main() {
    int opcao;
    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarFruta();
                break;
            case 2:
                listarFrutas();
                break;
            case 3:
                buscarFruta();
                break;
            case 4:
                alterarFruta();
                break;
            case 5:
                excluirFruta();
                break;
            case 6:
                venderFruta();
                break;
            case 7:
                liberarMemoria();
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 7);

    return 0;
}
