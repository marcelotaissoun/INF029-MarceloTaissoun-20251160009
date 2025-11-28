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
#include <stdlib.h>
#include <ctype.h>

#define MAX 100   

int ehBissexto(int ano){
    if((ano % 400 == 0) || (ano % 4 == 0 && ano % 100 != 0)){
        return 1;
    return 0;
    }
}


int q1(char data[]){
    int dia, mes, ano;

    char copia[20];
    strcpy(copia, data);

    char *p = strtok(copia, "/");
    if(!p){
       return 0;
    }  
    dia = atoi(p);

    p = strtok(NULL, "/");
    if(!p){
       return 0;
    }
    mes = atoi(p);

    p = strtok(NULL, "/");
    if(!p){
       return 0;
    }
    ano = atoi(p);

    if(ano < 100){
       ano += (ano < 50 ? 2000 : 1900);
    }
  
    if(mes < 1 || mes > 12){
       return 0;
    }
    if(dia < 1){
       return 0;
    }
  
    int diasMes;
    switch(mes){
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            diasMes = 31; break;
        case 4: case 6: case 9: case 11:
            diasMes = 30; break;
        case 2:
            diasMes = ehBissexto(ano) ? 29 : 28; break;
        default:
            return 0;
    }

    if(dia > diasMes){
       return 0;
    }
  
    return 1;
}

int diasNoMes(int mes, int ano){
    switch (mes){
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return ehBissexto(ano) ? 29 : 28;
    }
    return 0;
}

int q2(char dataInicial[], char dataFinal[], int *anos, int *meses, int *dias){
    if(!q1(dataInicial) || !q1(dataFinal)){
       return 0;
    }
  
    int d1, m1, a1;
    int d2, m2, a2;

    sscanf(dataInicial, "%d/%d/%d", &d1, &m1, &a1);
    sscanf(dataFinal, "%d/%d/%d", &d2, &m2, &a2);

    if(a1 < 100){
       a1 += (a1 < 50 ? 2000 : 1900);
    }
    if(a2 < 100){
       a2 += (a2 < 50 ? 2000 : 1900);
    }
  
    if(a2 < a1){
       return 0;
    }
    
    if(a2 == a1 && m2 < m1){
       return 0;
    }
  
    if(a2 == a1 && m2 == m1 && d2 < d1){
       return 0;
    }
  
    *anos  = a2 - a1;
    *meses = m2 - m1;
    *dias  = d2 - d1;

    if(*dias < 0){
       *meses -= 1;
       *dias += diasNoMes(m2 == 1 ? 12 : m2 - 1,
                           m2 == 1 ? a2 - 1 : a2);
    }

    if(*meses < 0){
       *anos -= 1;
       *meses += 12;
    }

    return 1;
}

char semAcento(char c){
    unsigned char x = (unsigned char)c;

    if(x==0xE1||x==0xE0||x==0xE2||x==0xE3||x==0xE4){
       return 'a';
    }
    if(x==0xE9||x==0xE8||x==0xEA||x==0xEB){
       return 'e';
    }
    if(x==0xED||x==0xEC||x==0xEE||x==0xEF){
       return 'i';
    }
    if(x==0xF3||x==0xF2||x==0xF4||x==0xF5||x==0xF6){
       return 'o';
    }
    if(x==0xFA||x==0xF9||x==0xFB||x==0xFC){
       return 'u';
    }
    if(x==0xE7){
       return 'c';
    }

    if(x==0xC1||x==0xC0||x==0xC2||x==0xC3||x==0xC4){
       return 'A';
    }
    if(x==0xC9||x==0xC8||x==0xCA||x==0xCB){
       return 'E';
    }
    if(x==0xCD||x==0xCC||x==0xCE||x==0xCF){
       return 'I';
    }
    if(x==0xD3||x==0xD2||x==0xD4||x==0xD5||x==0xD6){
       return 'O';
    }
    if(x==0xDA||x==0xD9||x==0xDB||x==0xDC){
       return 'U';
    }
    if(x==0xC7){
       return 'C';
    }

    return c;
}

int q3(char texto[], char letra){
    int count = 0;

    char alvo = tolower(semAcento(letra));

    for(int i = 0; texto[i] != '\0'; i++){
        char c = semAcento(texto[i]);
        if(tolower(c) == alvo){
           count++;
        }
    }

    return count;
}

int q4(char texto[], char palavra[], int posicoes[][2]){
    int tamT = strlen(texto);
    int tamP = strlen(palavra);
    int qtd = 0;

    for(int i = 0; i <= tamT - tamP; i++){
        int igual = 1;

        for(int j = 0; j < tamP; j++){
            if(texto[i + j] != palavra[j]){
               igual = 0;
               break;
            }
        }

        if(igual){
           posicoes[qtd][0] = i + 1;
           posicoes[qtd][1] = i + tamP;
           qtd++;
        }
    }

    return qtd;
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
    char sN[50];
    char sK[50];

    sprintf(sN, "%lld", N);
    sprintf(sK, "%lld", K);

    int tamN = strlen(sN);
    int tamK = strlen(sK);

    int count = 0;

    for(int i = 0; i <= tamN - tamK; i++){
        int igual = 1;

        for(int j = 0; j < tamK; j++){
            if(sN[i + j] != sK[j]){
               igual = 0;
               break;
            }
        }

        if(igual){
           count++;
        }
    }

    return count;
}

int verificaDirecao(char mat[][MAX], int lin, int col,
                    int x, int y, int dx, int dy, char palavra[]){

    int tam = strlen(palavra);

    for(int i = 0; i < tam; i++){
        int nx = x + i*dx;
        int ny = y + i*dy;

        if(nx < 0 || nx >= lin || ny < 0 || ny >= col){
           return 0;
        }

        if(mat[nx][ny] != palavra[i]){
           return 0;
        }
    }

    return 1;
}

int q7(char mat[][MAX], int lin, int col, char palavra[]){

    int direcoes[8][2] = {
        { 0,  1},  
        { 0, -1},  
        { 1,  0},  
        {-1,  0},  
        { 1,  1},  
        {-1, -1},  
        { 1, -1},  
        {-1,  1}   
    };

    int count = 0;

    for(int i = 0; i < lin; i++){
        for(int j = 0; j < col; j++){

            if(mat[i][j] == palavra[0]){

                for(int d = 0; d < 8; d++){
                    int dx = direcoes[d][0];
                    int dy = direcoes[d][1];

                    if(verificaDirecao(mat, lin, col, i, j, dx, dy, palavra)){
                       count++;
                    }
                }
            }
        }
    }

    return count;
}
