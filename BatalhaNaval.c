

#include <stdio.h>

// Definição de constantes para facilitar manutenção e legibilidade
#define TAMANHO_TABULEIRO 10  // Tamanho fixo do tabuleiro (10x10)
#define TAMANHO_NAVIO 3       // Tamanho fixo de cada navio (3 posições)
#define AGUA 0                // Valor que representa água no tabuleiro
#define NAVIO 3               // Valor que representa parte de um navio

/*
 * Função: inicializarTabuleiro
 * Propósito: Inicializa todas as posições do tabuleiro com o valor 0 (água)
 * Parâmetros:
 *   - tabuleiro: matriz 10x10 que representa o tabuleiro do jogo
 * Retorno: void (não retorna valor)
 */
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    // Loop aninhado para percorrer todas as linhas e colunas
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;  // Inicializa cada posição com água
        }
    }
}

/*
 * Função: validarPosicao
 * Propósito: Verifica se um navio cabe dentro dos limites do tabuleiro
 * Parâmetros:
 *   - linha: linha inicial do navio
 *   - coluna: coluna inicial do navio
 *   - tamanho: quantidade de posições que o navio ocupa
 *   - orientacao: 'H' para horizontal, 'V' para vertical
 * Retorno: 1 se a posição é válida, 0 se é inválida
 */
int validarPosicao(int linha, int coluna, int tamanho, char orientacao) {
    // Valida se a linha e coluna iniciais estão dentro do tabuleiro
    if (linha < 0 || linha >= TAMANHO_TABULEIRO ||
        coluna < 0 || coluna >= TAMANHO_TABULEIRO) {
        return 0;  // Posição inicial inválida
    }

    // Valida orientação horizontal
    if (orientacao == 'H' || orientacao == 'h') {
        // Verifica se o navio cabe horizontalmente
        if (coluna + tamanho > TAMANHO_TABULEIRO) {
            return 0;  // Navio ultrapassa o limite à direita
        }
    }
    // Valida orientação vertical
    else if (orientacao == 'V' || orientacao == 'v') {
        // Verifica se o navio cabe verticalmente
        if (linha + tamanho > TAMANHO_TABULEIRO) {
            return 0;  // Navio ultrapassa o limite inferior
        }
    }
    else {
        return 0;  // Orientação inválida
    }

    return 1;  // Posição válida
}

/*
 * Função: verificarSobreposicao
 * Propósito: Verifica se as posições que o navio ocupará já estão ocupadas
 * Parâmetros:
 *   - tabuleiro: matriz 10x10 que representa o tabuleiro do jogo
 *   - linha: linha inicial do navio
 *   - coluna: coluna inicial do navio
 *   - tamanho: quantidade de posições que o navio ocupa
 *   - orientacao: 'H' para horizontal, 'V' para vertical
 * Retorno: 1 se houver sobreposição, 0 se estiver livre
 */
int verificarSobreposicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                          int linha, int coluna, int tamanho, char orientacao) {
    // Verifica sobreposição para navio horizontal
    if (orientacao == 'H' || orientacao == 'h') {
        // Percorre todas as colunas que o navio ocupará
        for (int j = coluna; j < coluna + tamanho; j++) {
            if (tabuleiro[linha][j] != AGUA) {
                return 1;  // Há sobreposição
            }
        }
    }
    // Verifica sobreposição para navio vertical
    else if (orientacao == 'V' || orientacao == 'v') {
        // Percorre todas as linhas que o navio ocupará
        for (int i = linha; i < linha + tamanho; i++) {
            if (tabuleiro[i][coluna] != AGUA) {
                return 1;  // Há sobreposição
            }
        }
    }

    return 0;  // Não há sobreposição
}

/*
 * Função: posicionarNavio
 * Propósito: Posiciona um navio no tabuleiro, marcando suas posições com o valor 3
 * Parâmetros:
 *   - tabuleiro: matriz 10x10 que representa o tabuleiro do jogo
 *   - linha: linha inicial do navio
 *   - coluna: coluna inicial do navio
 *   - orientacao: 'H' para horizontal, 'V' para vertical
 * Retorno: void (não retorna valor)
 * Nota: Assume que a validação já foi feita antes de chamar esta função
 */
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                     int linha, int coluna, char orientacao) {
    // Posiciona navio horizontal
    if (orientacao == 'H' || orientacao == 'h') {
        // Marca cada posição do navio horizontalmente
        for (int j = coluna; j < coluna + TAMANHO_NAVIO; j++) {
            tabuleiro[linha][j] = NAVIO;
        }
    }
    // Posiciona navio vertical
    else if (orientacao == 'V' || orientacao == 'v') {
        // Marca cada posição do navio verticalmente
        for (int i = linha; i < linha + TAMANHO_NAVIO; i++) {
            tabuleiro[i][coluna] = NAVIO;
        }
    }
}

/*
 * Função: exibirTabuleiro
 * Propósito: Exibe o tabuleiro no console de forma organizada e legível
 * Parâmetros:
 *   - tabuleiro: matriz 10x10 que representa o tabuleiro do jogo
 * Retorno: void (não retorna valor)
 */
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n=== TABULEIRO DE BATALHA NAVAL ===\n\n");

    // Exibe cabeçalho com números das colunas
    printf("   ");  // Espaço para alinhamento
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf(" %d", j);
    }
    printf("\n");

    // Exibe cada linha do tabuleiro
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d  ", i);  // Número da linha

        // Exibe cada coluna da linha atual
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf(" %d", tabuleiro[i][j]);
        }
        printf("\n");
    }

    printf("\n");
    printf("Legenda: 0 = Agua, 3 = Navio\n");
}

/*
 * Função: main
 * Propósito: Função principal que coordena a execução do programa
 * Fluxo:
 *   1. Inicializa o tabuleiro
 *   2. Posiciona primeiro navio (horizontal)
 *   3. Posiciona segundo navio (vertical)
 *   4. Exibe o tabuleiro final
 */
int main() {
    // Declaração da matriz que representa o tabuleiro
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Passo 1: Inicializar tabuleiro com água em todas as posições
    inicializarTabuleiro(tabuleiro);
    printf("Tabuleiro inicializado com sucesso!\n");

    // ========== POSICIONAMENTO DO PRIMEIRO NAVIO (HORIZONTAL) ==========

    // Definição das coordenadas do primeiro navio
    int navio1_linha = 2;
    int navio1_coluna = 1;
    char navio1_orientacao = 'H';  // H = Horizontal

    printf("\nPosicionando Navio 1 (Horizontal)...\n");
    printf("  Posicao inicial: linha %d, coluna %d\n", navio1_linha, navio1_coluna);

    // Validar se o navio cabe no tabuleiro
    if (!validarPosicao(navio1_linha, navio1_coluna, TAMANHO_NAVIO, navio1_orientacao)) {
        printf("  ERRO: Posicao invalida! Navio ultrapassa os limites do tabuleiro.\n");
        return 1;  // Encerra o programa com código de erro
    }

    // Verificar se há sobreposição
    if (verificarSobreposicao(tabuleiro, navio1_linha, navio1_coluna,
                              TAMANHO_NAVIO, navio1_orientacao)) {
        printf("  ERRO: Sobreposicao detectada!\n");
        return 1;  // Encerra o programa com código de erro
    }

    // Posicionar o navio
    posicionarNavio(tabuleiro, navio1_linha, navio1_coluna, navio1_orientacao);
    printf("  Navio 1 posicionado com sucesso!\n");
    printf("  Ocupa as posicoes: (%d,%d), (%d,%d), (%d,%d)\n",
           navio1_linha, navio1_coluna,
           navio1_linha, navio1_coluna + 1,
           navio1_linha, navio1_coluna + 2);

    // ========== POSICIONAMENTO DO SEGUNDO NAVIO (VERTICAL) ==========

    // Definição das coordenadas do segundo navio
    int navio2_linha = 5;
    int navio2_coluna = 7;
    char navio2_orientacao = 'V';  // V = Vertical

    printf("\nPosicionando Navio 2 (Vertical)...\n");
    printf("  Posicao inicial: linha %d, coluna %d\n", navio2_linha, navio2_coluna);

    // Validar se o navio cabe no tabuleiro
    if (!validarPosicao(navio2_linha, navio2_coluna, TAMANHO_NAVIO, navio2_orientacao)) {
        printf("  ERRO: Posicao invalida! Navio ultrapassa os limites do tabuleiro.\n");
        return 1;  // Encerra o programa com código de erro
    }

    // Verificar se há sobreposição com navios já posicionados
    if (verificarSobreposicao(tabuleiro, navio2_linha, navio2_coluna,
                              TAMANHO_NAVIO, navio2_orientacao)) {
        printf("  ERRO: Sobreposicao detectada! Navio conflita com outro navio.\n");
        return 1;  // Encerra o programa com código de erro
    }

    // Posicionar o navio
    posicionarNavio(tabuleiro, navio2_linha, navio2_coluna, navio2_orientacao);
    printf("  Navio 2 posicionado com sucesso!\n");
    printf("  Ocupa as posicoes: (%d,%d), (%d,%d), (%d,%d)\n",
           navio2_linha, navio2_coluna,
           navio2_linha + 1, navio2_coluna,
           navio2_linha + 2, navio2_coluna);

    // ========== EXIBIÇÃO DO TABULEIRO FINAL ==========

    exibirTabuleiro(tabuleiro);

    printf("Programa executado com sucesso!\n");
    printf("Total de navios posicionados: 2\n");

    return 0;  // Encerra o programa com sucesso
}
