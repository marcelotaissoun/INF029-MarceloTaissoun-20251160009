#include <stdio.h>
#include <ctype.h>

#define TAM 3

void tabuleiro(char tab[TAM][TAM]) {
    printf("\n    1   2   3\n");
    for (int i = 0; i < TAM; i++) {
        printf("%c ", 'A' + i);
        for (int j = 0; j < TAM; j++) {
            printf(" %c ", tab[i][j]);
            if (j < TAM - 1) printf("|");
        }
        printf("\n");
        if (i < TAM - 1) printf(" -------- \n");
    }
    printf("\n");
}

char ganhador(char tab[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        if (tab[i][0] != ' ' && tab[i][0] == tab[i][1] && tab[i][1] == tab[i][2])
            return tab[i][0];
        if (tab[0][i] != ' ' && tab[0][i] == tab[1][i] && tab[1][i] == tab[2][i])
            return tab[0][i];
    }
    if (tab[0][0] != ' ' && tab[0][0] == tab[1][1] && tab[1][1] == tab[2][2])
        return tab[0][0];
    if (tab[0][2] != ' ' && tab[0][2] == tab[1][1] && tab[1][1] == tab[2][0])
        return tab[0][2];

    return ' '; 
}

void jogoDaVelha() {
    char tab[TAM][TAM];
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tab[i][j] = ' ';

    int jogadas = 0;
    char jogador = 'X';
    char vencedor = ' ';
    char linha;
    int coluna;

    printf("Jogador 1 = X\n");
    printf("Jogador 2 = O\n\n");

    while (vencedor == ' ' && jogadas < 9) {
        tabuleiro(tab);
        printf("Jogador %c, informe sua jogada (ex: A1, B3): ", jogador);
        scanf(" %c%d", &linha, &coluna);

        linha = toupper(linha);
        int i = linha - 'A';
        int j = coluna - 1;

        if (i < 0 || i >= TAM || j < 0 || j >= TAM) {
            printf("Posição inválida!\n");
            continue;
        }

        if (tab[i][j] != ' ') {
            printf("Essa posição já está ocupada!\n");
            continue;
        }

        tab[i][j] = jogador;
        jogadas++;

        vencedor = ganhador(tab);

        jogador = (jogador == 'X') ? 'O' : 'X';
    }

    tabuleiro(tab);

    if (vencedor != ' ')
        printf("Jogador %c venceu!\n", vencedor);
    else
        printf("Empate!\n");
}

int main() {
    jogoDaVelha();
    return 0;
}
