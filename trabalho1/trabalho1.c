// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome: Marcelo Taissoun de Anunciação
//  email:marcelotaissoun@gmail.com
//  Matrícula: 20251160009
//  Semestre: 2025.2

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016 - 17/10/2025

// #################################################

#include "trabalho1.h"
#include <stdio.h>
#include <string.h>

int q1(int dia, int mes, int ano){
    if(ano < 0 || mes < 1 || mes > 12 || dia < 1){
       return 0;
    }

    int diasMes;

    switch(mes){
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            diasMes = 31; break;
        case 4: case 6: case 9: case 11:
            diasMes = 30; break;
        case 2:
            if ((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0)
                diasMes = 29;
            else
                diasMes = 28;
            break;
        default:
            return 0;
    }

    return (dia <= diasMes);
}

int q2(int d1, int m1, int a1, int d2, int m2, int a2){
    int contador = 0;

    if(!q1(d1, m1, a1) || !q1(d2, m2, a2)){
       return -1;
    }
    
    long total1 = a1 * 365 + d1;
    long total2 = a2 * 365 + d2;

    for(int i = 1; i < m1; i++){
        int dias = 31;
        if(i == 4 || i == 6 || i == 9 || i == 11){
           dias = 30;
        }
        if(i == 2){
           dias = ((a1 % 4 == 0 && a1 % 100 != 0) || a1 % 400 == 0) ? 29 : 28;
        }
     total1 += dias;
    }

    for(int i = 1; i < m2; i++){
        int dias = 31;
        if(i == 4 || i == 6 || i == 9 || i == 11){
           dias = 30;
        }
        if(i == 2){
           dias = ((a2 % 4 == 0 && a2 % 100 != 0) || a2 % 400 == 0) ? 29 : 28;
        }
        total2 += dias;
    }

    long dif = total2 - total1;
    if(dif < 0){
       dif = -dif;
    }

    return dif;
}

int q3(char *str, char *dataFormatada){
    int dia, mes, ano;

    if(sscanf(str, "%d/%d/%d", &dia, &mes, &ano) != 3){
       return 0;
    }

    if(!q1(dia, mes, ano)){
       return 0;
    }

    char *meses[] = { "", "janeiro", "fevereiro", "março", "abril", "maio", "junho",
                      "julho", "agosto", "setembro", "outubro", "novembro", "dezembro" };

    sprintf(dataFormatada, "%02d de %s de %04d", dia, meses[mes], ano);
    return 1;
}

int q4(char *texto, char *palavra, int resultados[][2]){
    int t = strlen(texto);
    int p = strlen(palavra);
    int count = 0;

    for(int i = 0; i <= t - p; i++){
        int igual = 1;

        for(int j = 0; j < p; j++){
            if(texto[i + j] != palavra[j]){
               igual = 0;
               break;
            }
        }

        if(igual){
           resultados[count][0] = i;
           resultados[count][1] = i + p - 1;
           count++;
        }
    }

    return count;
}

int q5(int n){
    int invertido = 0;

    while(n > 0){
       invertido = invertido * 10 + (n % 10);
       n /= 10;
    }

    return invertido;
}

int q6(long long N, long long K){
    char sn[50], sk[50];
    sprintf(sn, "%lld", N);
    sprintf(sk, "%lld", K);

    int ln = strlen(sn), lk = strlen(sk);
    int cont = 0;

    for(int i = 0; i <= ln - lk; i++){
        int ok = 1;
        for(int j = 0; j < lk; j++){
            if(sn[i + j] != sk[j]){
               ok = 0;
               break;
            }
        }
        if(ok){
           cont++;
        }
    }

    return cont;
}

int verificaDirecao(char mat[][100], int l, int c, int linhas, int colunas,
                    char *palavra, int dl, int dc){

    int tam = strlen(palavra);

    for(int k = 0; k < tam; k++){
        int nl = l + k * dl;
        int nc = c + k * dc;

        if(nl < 0 || nl >= linhas || nc < 0 || nc >= colunas){
           return 0;
        }

        if(mat[nl][nc] != palavra[k]){
           return 0;
        }
    }

    return 1;
}

int q7(char matriz[][100], int linhas, int colunas, char *palavra){
    int direcoes[8][2] = {
        {0,1}, {0,-1}, {1,0}, {-1,0},
        {1,1}, {1,-1}, {-1,1}, {-1,-1}
    };

    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){

            if(matriz[i][j] == palavra[0]){
               for(int d = 0; d < 8; d++){
                    if(verificaDirecao(matriz, i, j, linhas, colunas, palavra,
                                        direcoes[d][0], direcoes[d][1])){
                        return 1;
                    }
                }
            }
        }
    }

    return 0;
}
