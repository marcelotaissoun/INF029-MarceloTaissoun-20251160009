#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LINHAS 10
#define COLUNAS 10
#define NUM_NAVIOS 7

typedef struct {
    char tabuleiro[LINHAS][COLUNAS]; 
    int celulasNavio;         
} Player;

void montarListaTamanhos(int nShips, int sizes[]) {
    if (nShips < 5) nShips = 5;
    int index = 0;
    sizes[index++] = 4;
    sizes[index++] = 3;
    sizes[index++] = 1; 
    sizes[index++] = 1;
    sizes[index++] = 1;
    while (index < nShips) {
        sizes[index++] = 2; 
    }
}

void initPlayer(Player *p) {
    for (int i = 0; i < LINHAS; ++i)
        for (int j = 0; j < COLUNAS; ++j)
            p->tabuleiro[i][j] = ' ';
    p->celulasNavio = 0;
}

void mostrarTabuleiroProprio(Player *p) {
    printf("\n    ");
    for (int c = 1; c <= COLUNAS; ++c) printf("%2d ", c);
    printf("\n");
    for (int r = 0; r < LINHAS; ++r) {
        printf(" %c  ", 'A' + r);
        for (int c = 0; c < COLUNAS; ++c) {
            char ch = p->tabuleiro[r][c];
            if (ch == ' ') printf("[ ]");
            else printf("[%c]", ch); 
        }
        printf("\n");
    }
}

void mostrarTabuleiroAdversario(Player *adv) {
    printf("\n    ");
    for (int c = 1; c <= COLUNAS; ++c) printf("%2d ", c);
    printf("\n");
    for (int r = 0; r < LINHAS; ++r) {
        printf(" %c  ", 'A' + r);
        for (int c = 0; c < COLUNAS; ++c) {
            char ch = adv->tabuleiro[r][c];
            if (ch == '0') printf("[0]");
            else if (ch == 'X') printf("[X]"); 
            else printf("[ ]"); 
        }
        printf("\n");
    }
}

int parseCoord(const char *input, int *row, int *col) {
    if (!input || strlen(input) < 2) return 0;

    int i = 0;
    while (input[i] && isspace((unsigned char)input[i])) i++;

    if (!isalpha((unsigned char)input[i])) return 0;
    char letter = toupper((unsigned char)input[i]);
    if (letter < 'A' || letter > 'A' + LINHAS - 1) return 0;
    i++;

    if (!isdigit((unsigned char)input[i])) return 0;
    int number = 0;
    while (input[i] && isdigit((unsigned char)input[i])) {
        number = number * 10 + (input[i] - '0');
        i++;
    }
    if (number < 1 || number > COLUNAS) return 0;

    *row = letter - 'A';
    *col = number - 1;
    return 1;
}

int podePosicionar(Player *p, int r, int c, int len, int horiz) {
    if (horiz) {
        if (c + len > COLUNAS) return 0;
        for (int j = c; j < c + len; ++j)
            if (p->tabuleiro[r][j] != ' ') return 0;
    } else {
        if (r + len > LINHAS) return 0;
        for (int i = r; i < r + len; ++i)
            if (p->tabuleiro[i][c] != ' ') return 0;
    }
    return 1;
}

void posicionarNavio(Player *p, int r, int c, int len, int horiz) {
    if (horiz) {
        for (int j = c; j < c + len; ++j) p->tabueiro[r][j] = 'N';
    } else {
        for (int i = r; i < r + len; ++i) p->tabuleiro[i][c] = 'N';
    }
    p->celulasNavio += len;
}

void posicionamentoManual(Player *p, int playerNumber, int sizes[], int nShips) {
    char buffer[64];
    printf("\nJogador %d: posicionamento de navios\n", playerNumber);
    printf("Tabuleiro %dx%d. Informe coordenada como A1 ou J10.\n", LINHAS, COLUNAS);

    for (int s = 0; s < nShips; ++s) {
        int len = sizes[s];
        int placed = 0;
        while (!placed) {
            mostrarTabuleiroProprio(p);
            if (len == 1) {
                printf("Coloque o navio de tamanho %d (única célula). Ex: B4 -> ", len);
                fgets(buffer, sizeof(buffer), stdin);
                int r, c;
                if (!parseCoord(buffer, &r, &c)) {
                    printf("Entrada inválida. Tente novamente.\n");
                    continue;
                }
                if (!podePosicionar(p, r, c, len, 1)) { 
                    printf("Não é possível posicionar aí (sobreposição ou fora). Tente outra posição.\n");
                    continue;
                }
                posicionarNavio(p, r, c, len, 1);
                placed = 1;
            } else {
                printf("Coloque o navio de tamanho %d. Informe posição inicial e orientação (H ou V).\n", len);
                printf("Ex: A1 H  (horizontal) ou C3 V (vertical) -> ");
                fgets(buffer, sizeof(buffer), stdin);
                char coord[16] = {0};
                char orient = 0;
                int read = sscanf(buffer, " %15s %c", coord, &orient);
                if (read < 1) {
                    printf("Entrada inválida. Tente novamente.\n");
                    continue;
                }
                if (read == 1) {
                    printf("Faltou orientação H/V. Digite orientação: ");
                    char tmp[8];
                    fgets(tmp, sizeof(tmp), stdin);
                    if (sscanf(tmp, " %c", &orient) < 1) {
                        printf("Orientação inválida.\n");
                        continue;
                    }
                }
                orient = toupper((unsigned char)orient);
                if (orient != 'H' && orient != 'V') {
                    printf("Orientação inválida. Use H ou V.\n");
                    continue;
                }
                int r, c;
                if (!parseCoord(coord, &r, &c)) {
                    printf("Coordenada inválida. Tente novamente.\n");
                    continue;
                }
                int horiz = (orient == 'H') ? 1 : 0;
                if (!podePosicionar(p, r, c, len, horiz)) {
                    printf("Não é possível posicionar aí (saindo do tabuleiro ou sobrepondo). Tente outra posição.\n");
                    continue;
                }
                posicionarNavio(p, r, c, len, horiz);
                placed = 1;
            }
        } 
        printf("Navio de tamanho %d posicionado.\n", len);
    } 
    printf("Todos os navios do Jogador %d posicionados.\n", playerNumber);
    printf("Pressione ENTER para continuar e passar para o próximo jogador...");
    fgets(buffer, sizeof(buffer), stdin);
}

int executarTiro(Player *atacante, Player *alvo, int r, int c) {
    char cell = alvo->tabuleiro[r][c];
    if (cell == '0' || cell == 'X') {
        return 0;
    }
    if (cell == 'N') {
        alvo->tabuleiro[r][c] = '0'; 
        alvo->celulasNavio -= 1;
        return 1;
    } else { 
        alvo->tabuleiro[r][c] = 'X';
        return 1;
    }
}

void faseAtaque(Player *p1, Player *p2) {
    char buffer[64];
    int current = 1; 
    Player *atacante = p1;
    Player *alvo = p2;

    while (p1->celulasNavio > 0 && p2->celulasNavio > 0) {
        if (current == 1) { atacante = p1; alvo = p2; }
        else { atacante = p2; alvo = p1; }

        printf("\nTurno do Jogador %d\n", current);
        mostrarTabuleiroAdversario(alvo); 
        mostrarTabuleiroProprio(atacante);

        int validShot = 0;
        while (!validShot) {
            printf("Jogador %d, informe sua jogada (ex: B4): ", current);
            if (!fgets(buffer, sizeof(buffer), stdin)) { printf("Erro de leitura\n"); continue; }
            int r, c;
            if (!parseCoord(buffer, &r, &c)) {
                printf("Entrada inválida. Use formato A1..J10. Tente novamente.\n");
                continue;
            }
            char prev = alvo->tabuleiro[r][c];
            if (prev == '0' || prev == 'X') {
                printf("Essa célula já foi alvo antes. Tente outra.\n");
                continue;
            }
            int ok = executarTiro(atacante, alvo, r, c);
            if (!ok) {
                printf("Tiro inválido (já atingido). Tente outra posição.\n");
                continue;
            }
            validShot = 1;
            if (prev == 'N') {
                printf("Navio atingido em %c%d!\n", 'A'+r, c+1);
                if (alvo->celulasNavio == 0) {
                    printf("\nTodos os navios do jogador %d foram abatidos!\n", (current==1)?2:1);
                    return;
                }
            } else {
                printf("Água em %c%d.\n", 'A'+r, c+1);
            }
        } 

        current = (current == 1) ? 2 : 1;
    } 
}

int main() {
    int nShips = NUM_NAVIOS;
    if (nShips < 5) nShips = 5;
    int sizes[100];
    montarListaTamanhos(nShips, sizes);

    printf("Número de navios: %d\n", nShips);
    printf("Configuração de tamanhos:\n");
    for (int i = 0; i < nShips; ++i) {
        printf("%d ", sizes[i]);
    }
    printf("Tabuleiros: %dx%d\n", LINHAS, COLUNAS);

    Player player1, player2;
    initPlayer(&player1);
    initPlayer(&player2);

    posicionamentoManual(&player1, 1, sizes, nShips);

    posicionamentoManual(&player2, 2, sizes, nShips);

    faseAtaque(&player1, &player2);

    if (player1.celulasNavio == 0 && player2.celulasNavio == 0) {
        printf("Empate.\n");
    } else if (player2.celulasNavio == 0) {
        printf("\nJogador 1venceu.\n");
    } else if (player1.celulasNavio == 0) {
        printf("\nJogador 2 venceu.\n");
    } else {
        printf("\nJogo terminado.\n");
    }

    return 0;
}
