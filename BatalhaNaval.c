

/*
 * Programa: Batalha Naval - Nível Aventureiro
 * Descrição: Implementa um tabuleiro 10x10 para o jogo Batalha Naval,
 *            posicionando quatro navios (horizontal, vertical e dois diagonais)
 *            com validação de limites e sobreposição.
 * Autor: Desenvolvido como desafio de programação
 * Data: 2026
 */

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
 *   - orientacao: 'H' para horizontal, 'V' para vertical,
 *                 'D' para diagonal baixo-direita, 'E' para diagonal baixo-esquerda
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
    // Valida orientação diagonal para baixo-direita (↘)
    else if (orientacao == 'D' || orientacao == 'd') {
        // Verifica se o navio cabe na diagonal (linha e coluna aumentam)
        if (linha + tamanho > TAMANHO_TABULEIRO ||
            coluna + tamanho > TAMANHO_TABULEIRO) {
            return 0;  // Navio ultrapassa os limites
        }
    }
    // Valida orientação diagonal para baixo-esquerda (↙)
    else if (orientacao == 'E' || orientacao == 'e') {
        // Verifica se o navio cabe na diagonal (linha aumenta, coluna diminui)
        if (linha + tamanho > TAMANHO_TABULEIRO ||
            coluna - tamanho + 1 < 0) {
            return 0;  // Navio ultrapassa os limites
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
 *   - orientacao: 'H' para horizontal, 'V' para vertical,
 *                 'D' para diagonal baixo-direita, 'E' para diagonal baixo-esquerda
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
    // Verifica sobreposição para navio diagonal baixo-direita (↘)
    else if (orientacao == 'D' || orientacao == 'd') {
        // Percorre as posições na diagonal (linha e coluna aumentam)
        for (int i = 0; i < tamanho; i++) {
            if (tabuleiro[linha + i][coluna + i] != AGUA) {
                return 1;  // Há sobreposição
            }
        }
    }
    // Verifica sobreposição para navio diagonal baixo-esquerda (↙)
    else if (orientacao == 'E' || orientacao == 'e') {
        // Percorre as posições na diagonal (linha aumenta, coluna diminui)
        for (int i = 0; i < tamanho; i++) {
            if (tabuleiro[linha + i][coluna - i] != AGUA) {
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
 *   - orientacao: 'H' para horizontal, 'V' para vertical,
 *                 'D' para diagonal baixo-direita, 'E' para diagonal baixo-esquerda
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
    // Posiciona navio diagonal para baixo-direita (↘)
    else if (orientacao == 'D' || orientacao == 'd') {
        // Marca cada posição do navio na diagonal (linha e coluna aumentam)
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linha + i][coluna + i] = NAVIO;
        }
    }
    // Posiciona navio diagonal para baixo-esquerda (↙)
    else if (orientacao == 'E' || orientacao == 'e') {
        // Marca cada posição do navio na diagonal (linha aumenta, coluna diminui)
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linha + i][coluna - i] = NAVIO;
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
 *   4. Posiciona terceiro navio (diagonal baixo-direita)
 *   5. Posiciona quarto navio (diagonal baixo-esquerda)
 *   6. Exibe o tabuleiro final
 */
int main() {
    // Declaração da matriz que representa o tabuleiro
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Passo 1: Inicializar tabuleiro com água em todas as posições
    inicializarTabuleiro(tabuleiro);
    printf("Tabuleiro inicializado com sucesso!\n");

    // ========== POSICIONAMENTO DO PRIMEIRO NAVIO (HORIZONTAL) ==========

    // Definição das coordenadas do primeiro navio
    int navio1_linha = 4;
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

    // ========== POSICIONAMENTO DO TERCEIRO NAVIO (DIAGONAL BAIXO-DIREITA) ==========

    // Definição das coordenadas do terceiro navio
    int navio3_linha = 0;
    int navio3_coluna = 0;
    char navio3_orientacao = 'D';  // D = Diagonal baixo-direita (↘)

    printf("\nPosicionando Navio 3 (Diagonal Baixo-Direita)...\n");
    printf("  Posicao inicial: linha %d, coluna %d\n", navio3_linha, navio3_coluna);

    // Validar se o navio cabe no tabuleiro
    if (!validarPosicao(navio3_linha, navio3_coluna, TAMANHO_NAVIO, navio3_orientacao)) {
        printf("  ERRO: Posicao invalida! Navio ultrapassa os limites do tabuleiro.\n");
        return 1;  // Encerra o programa com código de erro
    }

    // Verificar se há sobreposição com navios já posicionados
    if (verificarSobreposicao(tabuleiro, navio3_linha, navio3_coluna,
                              TAMANHO_NAVIO, navio3_orientacao)) {
        printf("  ERRO: Sobreposicao detectada! Navio conflita com outro navio.\n");
        return 1;  // Encerra o programa com código de erro
    }

    // Posicionar o navio
    posicionarNavio(tabuleiro, navio3_linha, navio3_coluna, navio3_orientacao);
    printf("  Navio 3 posicionado com sucesso!\n");
    printf("  Ocupa as posicoes: (%d,%d), (%d,%d), (%d,%d)\n",
           navio3_linha, navio3_coluna,
           navio3_linha + 1, navio3_coluna + 1,
           navio3_linha + 2, navio3_coluna + 2);

    // ========== POSICIONAMENTO DO QUARTO NAVIO (DIAGONAL BAIXO-ESQUERDA) ==========

    // Definição das coordenadas do quarto navio
    int navio4_linha = 0;
    int navio4_coluna = 9;
    char navio4_orientacao = 'E';  // E = Diagonal baixo-esquerda (↙)

    printf("\nPosicionando Navio 4 (Diagonal Baixo-Esquerda)...\n");
    printf("  Posicao inicial: linha %d, coluna %d\n", navio4_linha, navio4_coluna);

    // Validar se o navio cabe no tabuleiro
    if (!validarPosicao(navio4_linha, navio4_coluna, TAMANHO_NAVIO, navio4_orientacao)) {
        printf("  ERRO: Posicao invalida! Navio ultrapassa os limites do tabuleiro.\n");
        return 1;  // Encerra o programa com código de erro
    }

    // Verificar se há sobreposição com navios já posicionados
    if (verificarSobreposicao(tabuleiro, navio4_linha, navio4_coluna,
                              TAMANHO_NAVIO, navio4_orientacao)) {
        printf("  ERRO: Sobreposicao detectada! Navio conflita com outro navio.\n");
        return 1;  // Encerra o programa com código de erro
    }

    // Posicionar o navio
    posicionarNavio(tabuleiro, navio4_linha, navio4_coluna, navio4_orientacao);
    printf("  Navio 4 posicionado com sucesso!\n");
    printf("  Ocupa as posicoes: (%d,%d), (%d,%d), (%d,%d)\n",
           navio4_linha, navio4_coluna,
           navio4_linha + 1, navio4_coluna - 1,
           navio4_linha + 2, navio4_coluna - 2);

    // ========== EXIBIÇÃO DO TABULEIRO FINAL ==========

    exibirTabuleiro(tabuleiro);

    printf("Programa executado com sucesso!\n");
    printf("Total de navios posicionados: 4\n");
    printf("  - 1 Horizontal\n");
    printf("  - 1 Vertical\n");
    printf("  - 2 Diagonais\n");

    return 0;  // Encerra o programa com sucesso
}
