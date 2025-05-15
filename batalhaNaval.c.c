#include <stdio.h>
#include <math.h>

#define TAM 10
#define TAM_HAB 5

// Função para inicializar o tabuleiro com água (0)
void inicializaTabuleiro(int tab[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tab[i][j] = 0;
}

// Função para imprimir o tabuleiro
void imprimeTabuleiro(int tab[TAM][TAM]) {
    printf("\nTabuleiro:\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tab[i][j]);
        }
        printf("\n");
    }
}

// Posiciona um navio horizontal
void posicionaNavioHorizontal(int tab[TAM][TAM], int linha, int coluna, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (coluna + i < TAM)
            tab[linha][coluna + i] = 3;
    }
}

// Posiciona um navio vertical
void posicionaNavioVertical(int tab[TAM][TAM], int linha, int coluna, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (linha + i < TAM)
            tab[linha + i][coluna] = 3;
    }
}

// Posiciona um navio na diagonal principal
void posicionaNavioDiagonalPrincipal(int tab[TAM][TAM], int linha, int coluna, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (linha + i < TAM && coluna + i < TAM)
            tab[linha + i][coluna + i] = 3;
    }
}

// Posiciona um navio na diagonal secundária
void posicionaNavioDiagonalSecundaria(int tab[TAM][TAM], int linha, int coluna, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (linha + i < TAM && coluna - i >= 0)
            tab[linha + i][coluna - i] = 3;
    }
}

// Sobrepõe uma matriz de habilidade ao tabuleiro, com origem no centro da matriz de habilidade
void aplicaHabilidade(int tab[TAM][TAM], int hab[TAM_HAB][TAM_HAB], int origemLinha, int origemColuna) {
    int centro = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            int linha = origemLinha + (i - centro);
            int coluna = origemColuna + (j - centro);
            if (linha >= 0 && linha < TAM && coluna >= 0 && coluna < TAM && hab[i][j] == 1 && tab[linha][coluna] != 3) {
                tab[linha][coluna] = 5;
            }
        }
    }
}

// Preenche matriz Cone (forma de triângulo apontando para baixo)
void criaHabilidadeCone(int hab[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            hab[i][j] = (j >= TAM_HAB / 2 - i && j <= TAM_HAB / 2 + i) ? 1 : 0;
        }
    }
}

// Preenche matriz Cruz
void criaHabilidadeCruz(int hab[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            hab[i][j] = (i == TAM_HAB / 2 || j == TAM_HAB / 2) ? 1 : 0;
        }
    }
}

// Preenche matriz Octaedro (losango)
void criaHabilidadeOctaedro(int hab[TAM_HAB][TAM_HAB]) {
    int centro = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            hab[i][j] = (abs(centro - i) + abs(centro - j) <= centro) ? 1 : 0;
        }
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    int habilidade[TAM_HAB][TAM_HAB];

    inicializaTabuleiro(tabuleiro);

    // Posicionando 4 navios
    posicionaNavioHorizontal(tabuleiro, 1, 1, 4);
    posicionaNavioVertical(tabuleiro, 2, 5, 3);
    posicionaNavioDiagonalPrincipal(tabuleiro, 5, 0, 3);
    posicionaNavioDiagonalSecundaria(tabuleiro, 5, 9, 3);

    // Cone
    criaHabilidadeCone(habilidade);
    aplicaHabilidade(tabuleiro, habilidade, 2, 2);

    // Cruz
    criaHabilidadeCruz(habilidade);
    aplicaHabilidade(tabuleiro, habilidade, 6, 5);

    // Octaedro
    criaHabilidadeOctaedro(habilidade);
    aplicaHabilidade(tabuleiro, habilidade, 4, 8);

    // Exibir resultado final
    imprimeTabuleiro(tabuleiro);

    return 0;
}
