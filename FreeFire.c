#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // Para usar o tipo bool

// Capacidade máxima da mochila
#define CAPACIDADE_MAXIMA 10
// Tamanho máximo das strings
#define TAM_NOME 50
#define TAM_TIPO 30

// Estrutura para representar um item da mochila
typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
} Item;

// Vetor estático que representa a mochila
Item mochila[CAPACIDADE_MAXIMA];
// Variável para rastrear o número atual de itens na mochila
int num_itens = 0;

// --- Protótipos das Funções ---
void exibir_menu();
void adicionar_item();
void remover_item();
void listar_itens();
void buscar_item();
void limpar_buffer();
int encontrar_indice_por_nome(const char *nome_busca);


// --- Implementação das Funções ---

// Função para limpar o buffer de entrada (necessário após scanf)
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

/**
 * @brief Encontra o índice de um item na mochila pelo nome (Busca Sequencial).
 * * @param nome_busca O nome do item a ser buscado.
 * @return O índice do item se encontrado, ou -1 se não encontrado.
 */
int encontrar_indice_por_nome(const char *nome_busca) {
    for (int i = 0; i < num_itens; i++) {
        // Usa strcmp para comparar strings. Retorna 0 se forem iguais.
        if (strcmp(mochila[i].nome, nome_busca) == 0) {
            return i; // Item encontrado
        }
    }
    return -1; // Item não encontrado
}

// Função para adicionar um novo item à mochila
void adicionar_item() {
    if (num_itens >= CAPACIDADE_MAXIMA) {
        printf("\n🚫 Mochila Cheia! Capacidade máxima de %d itens atingida.\n", CAPACIDADE_MAXIMA);
        return;
    }

    Item novo_item;
    printf("\n--- Adicionar Novo Item ---\n");
    
    // Entrada do Nome
    printf("Nome do item (ex: agua, casaco): ");
    limpar_buffer(); // Limpa o buffer antes de ler a string com fgets
    if (fgets(novo_item.nome, TAM_NOME, stdin) != NULL) {
        // Remove o newline (\n) capturado por fgets, se houver
        novo_item.nome[strcspn(novo_item.nome, "\n")] = 0;
    }

    // Verifica se o item já existe para evitar duplicatas (opcional, mas bom para Aventureiro)
    if (encontrar_indice_por_nome(novo_item.nome) != -1) {
        printf("⚠️ O item '%s' já está na mochila. Considere apenas aumentar a quantidade.\n", novo_item.nome);
        return;
    }

    // Entrada do Tipo
    printf("Tipo do item (ex: alimento, roupas, equipamentos): ");
    if (fgets(novo_item.tipo, TAM_TIPO, stdin) != NULL) {
        novo_item.tipo[strcspn(novo_item.tipo, "\n")] = 0;
    }
    
    // Entrada da Quantidade
    printf("Quantidade: ");
    if (scanf("%d", &novo_item.quantidade) != 1 || novo_item.quantidade <= 0) {
        printf("❌ Entrada inválida para a quantidade. Ação cancelada.\n");
        limpar_buffer();
        return;
    }

    // Adiciona o item ao vetor
    mochila[num_itens] = novo_item;
    num_itens++;

    printf("✅ Item '%s' (x%d) adicionado à mochila.\n", novo_item.nome, novo_item.quantidade);
    limpar_buffer(); // Limpa o buffer após o scanf
}

// Função para remover um item da mochila pelo nome
void remover_item() {
    if (num_itens == 0) {
        printf("\n⚠️ Mochila vazia! Não há itens para remover.\n");
        return;
    }

    char nome_remover[TAM_NOME];
    printf("\n--- Remover Item ---\n");
    printf("Digite o nome do item a ser removido: ");
    limpar_buffer();
    if (fgets(nome_remover, TAM_NOME, stdin) != NULL) {
        nome_remover[strcspn(nome_remover, "\n")] = 0;
    }

    int indice = encontrar_indice_por_nome(nome_remover);

    if (indice != -1) {
        // Item encontrado. Agora removemos ele "movendo" os itens seguintes para trás.
        for (int i = indice; i < num_itens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        num_itens--;
        printf("🗑️ Item '%s' removido da mochila.\n", nome_remover);
    } else {
        printf("❌ Erro: Item '%s' não encontrado na mochila.\n", nome_remover);
    }
}

// Função para listar todos os itens na mochila em formato de tabela
void listar_itens() {
    printf("\n--- Inventário da Mochila (Total: %d/%d) ---\n", num_itens, CAPACIDADE_MAXIMA);
    if (num_itens == 0) {
        printf("  A mochila está vazia. Adicione alguns itens!\n");
        return;
    }

    // Cabeçalho da tabela
    printf("+----------------------+----------------+-----------+\n");
    printf("| %-20s | %-14s | %-9s |\n", "Nome", "Tipo", "Quantidade");
    printf("+----------------------+----------------+-----------+\n");

    // Linhas da tabela
    for (int i = 0; i < num_itens; i++) {
        printf("| %-20s | %-14s | %-9d |\n", 
               mochila[i].nome, 
               mochila[i].tipo, 
               mochila[i].quantidade);
    }
    printf("+----------------------+----------------+-----------+\n");
}

// Função para buscar um item na mochila pelo nome (Funcionalidade Nível Aventureiro)
void buscar_item() {
    if (num_itens == 0) {
        printf("\n⚠️ Mochila vazia! Não há itens para buscar.\n");
        return;
    }

    char nome_busca[TAM_NOME];
    printf("\n--- Buscar Item por Nome (Busca Sequencial) ---\n");
    printf("Digite o nome do item que deseja buscar: ");
    limpar_buffer();
    if (fgets(nome_busca, TAM_NOME, stdin) != NULL) {
        nome_busca[strcspn(nome_busca, "\n")] = 0;
    }

    int indice = encontrar_indice_por_nome(nome_busca);

    if (indice != -1) {
        // Item encontrado
        printf("\n🔍 Item Encontrado! Detalhes:\n");
        printf("+----------------------+\n");
        printf("| Nome:       %-10s |\n", mochila[indice].nome);
        printf("| Tipo:       %-10s |\n", mochila[indice].tipo);
        printf("| Quantidade: %-10d |\n", mochila[indice].quantidade);
        printf("+----------------------+\n");
    } else {
        // Item não encontrado
        printf("\n❌ Item '%s' não encontrado na mochila. Tente novamente.\n", nome_busca);
    }
}

// Função para exibir o menu principal
void exibir_menu() {
    printf("\n============================================\n");
    printf("🏝️  Desafio Código da Ilha - Nível Aventureiro\n");
    printf("============================================\n");
    printf("1. Adicionar Item à Mochila\n");
    printf("2. Remover Item pelo Nome\n");
    printf("3. Listar Itens Cadastrados\n");
    printf("4. Buscar Item por Nome 🔍\n"); // Novidade do Nível Aventureiro
    printf("0. Sair do Jogo\n");
    printf("--------------------------------------------\n");
    printf("Escolha uma opção: ");
}

// Função principal
int main() {
    int opcao;

    // Inicialização da mochila com alguns itens pré-definidos para teste
    // (Opcional, mas útil para simular o cenário inicial)
    // Inicialização conforme o enunciado (apenas para simulação de dados iniciais)
    strcpy(mochila[num_itens].nome, "agua");
    strcpy(mochila[num_itens].tipo, "alimento");
    mochila[num_itens++].quantidade = 2;
    
    strcpy(mochila[num_itens].nome, "casaco");
    strcpy(mochila[num_itens].tipo, "roupas");
    mochila[num_itens++].quantidade = 1;
    
    strcpy(mochila[num_itens].nome, "lanterna");
    strcpy(mochila[num_itens].tipo, "equipamento");
    mochila[num_itens++].quantidade = 1;
    
    strcpy(mochila[num_itens].nome, "remedios");
    strcpy(mochila[num_itens].tipo, "farmacia");
    mochila[num_itens++].quantidade = 3;


    do {
        exibir_menu();

        // Leitura da opção e tratamento de erro
        if (scanf("%d", &opcao) != 1) {
            printf("\n❌ Opção inválida! Por favor, digite um número.\n");
            limpar_buffer();
            opcao = -1; // Garante que o loop continue
            continue;
        }

        switch (opcao) {
            case 1:
                adicionar_item();
                break;
            case 2:
                remover_item();
                break;
            case 3:
                listar_itens();
                break;
            case 4:
                buscar_item();
                break;
            case 0:
                printf("\n👋 Sobrevivente, o sistema de mochila foi encerrado. Boa sorte na ilha!\n");
                break;
            default:
                printf("\n❓ Opção desconhecida. Por favor, escolha uma opção de 0 a 4.\n");
                limpar_buffer();
                break;
        }
    } while (opcao != 0);

    return 0;
}