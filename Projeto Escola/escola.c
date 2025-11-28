#ifndef ESCOLA_H
#define ESCOLA_H

// Inclusão das bibliotecas:

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

// Definição das constantes:

#define TAM 3
#define MAX_N 50 // máximo de caracteres
#define CPF 16
#define LISTA_CHEIA 1
#define LISTA_VAZIA 0

// ------ STRUCTS ---------
typedef struct data{
    int dia, mes, ano;
} data;

typedef struct pessoa{
    int matricula;
    char nome[MAX_N];
    char sexo;
    data data_nascimento;
    char cpf[CPF];
    int qtd_displinas;
} pessoa;

typedef struct disciplina{
    char nome[MAX_N];
    int codigo;
    int semestre;
    int vagas;
    pessoa professor;
    pessoa *alunos;
    int qtd_alunos;
} disciplina;


// ----------- FUNÇÕES AUXLIARES ----------------

// Transforma as letras da string em minusculo
void minusculo(char *c, int tam){
	for(int i = 0; i < tam; i++){
		c[i] = tolower(c[i]);
	}
}

// pega a data atual
void pegar_data(data *d){
	// pegando o mes atual
	struct tm *data_atual; //ponteiro que vai armazenar data e hora
	time_t tempo; // variavel que vai armazenar os segundos
	time(&tempo); // obtendo o tempo em segundos
	data_atual = localtime(&tempo); // convetendo de segundos para o tempo local
	d->ano = data_atual->tm_year+1900;
	d->mes = data_atual->tm_mon+1; // pegando o mes atual
	d->dia = data_atual->tm_mday;
}

// faz a troca de pessoa
void troca(pessoa *a, pessoa *b){
	pessoa aux;
	aux = *a;
	*a = *b;
	*b = aux;
}

void copia_vetor(pessoa *a, pessoa *b, int qtd) {
	for (int i = 0; i < qtd; i++)
		b[i] = a[i];
}

// retorna a posição da pessoa no vetor, se não achar, retorna -1:
int buscar_pessoa(pessoa *a, int qtd, int mat_busc){
	for (int i = 0; i < qtd; i++) {
		if (mat_busc == a[i].matricula) {
			return i;
		}
	}
	return -1;
}

// retorna a posição da disciplina no vetor, se não achar, retorna -1:
int buscar_disciplina(disciplina d[TAM], int qtd, int codigo) {
	for (int i = 0; i < qtd; i++) {
		if (codigo == d[i].codigo)
			return i;
	}
	return -1;
}

// Indica se a lista está cheia ou vazia
int tam_lista(int qtd) {
	if (qtd == TAM)
		return LISTA_CHEIA;
	if (qtd == 0)
		return LISTA_VAZIA;
	return 2;
}

// Gera uma matrícula única para aluno/professor
int gerar_matricula(pessoa *g, int qtd){
	data atual;
	pegar_data(&atual);
	int pos, matricula;
	do{
		matricula = (atual.ano*1000) + qtd;
		pos = buscar_pessoa(g, qtd, matricula);
		if(pos >= 0)
			qtd++;
	} while(pos >= 0);
	return matricula;
}

// Gera um codigo único para a disciplina
int gerar_codigo(disciplina *d, int qtd){
	int pos, codigo;
	do{
		srand(time(NULL));
		codigo = rand() % 1000;
		pos = buscar_disciplina(d, qtd, codigo);
	} while(pos >= 0);
	return codigo;
}

// Une dois vetores do tipo pessoa
void unir_vetor(pessoa a[TAM], pessoa b[TAM], pessoa *U, int qtd_a, int qtd_b) {
	int i, j, k = 0;
	while (k < qtd_a + qtd_b) {
		for (i = 0; i < qtd_a; i++){
			U[k] = a[i];
			k++;
		}
		for (j = 0; j < qtd_b; j++) {
			U[k] = b[j];
			k++;
		}
	}
}
void gerar_linha() {
	for (int i = 0; i < 25; i++)
		printf("-");
	printf("\n");
}

// ---------- MENUS ----------
int menu_geral(){
	int opcao;
	gerar_linha();
	printf("Insira as opções:\n");
	printf("0 - SAIR\n");
	printf("1 - Menu Aluno\n");
	printf("2 - Menu Professor\n");
	printf("3 - Menu Disciplina\n");
	printf("4 - Outros Relatórios\n");
	gerar_linha();
	scanf("%d", &opcao);
	return opcao;
}

int menu_pessoa(char c[15]){
	int opcao;
	gerar_linha();
	printf("0 - SAIR\n");
	printf("1 - Cadastrar %s\n", c);
	printf("2 - Listar %s\n", c);
	printf("3 - Atualizar %s\n", c);
	printf("4 - Excluir %s\n", c);
	gerar_linha();
	scanf("%d", &opcao);
	return opcao;
}

int menu_disciplina(){
	int opcao;
	gerar_linha();
	printf("0 - SAIR\n");
	printf("1 - Cadastrar Disciplina\n");
	printf("2 - Listar Disciplinas\n");
	printf("3 - Atualizar Disciplina\n");
	printf("4 - Excluir Disciplina\n");
	printf("5 - Incluir aluno\n");
	printf("6 - Excluir aluno\n");
	gerar_linha();

	scanf("%d", &opcao);
	fflush(stdin);
	return opcao;
}

int menu_relatorio() {
	int opcao;
	gerar_linha();
	printf("0 - SAIR\n");
	printf("1 - Lista de Aniversariantes do mês\n");
	printf("2 - Buscar pessoas\n");
	gerar_linha();
	scanf("%d", &opcao);
	fflush(stdin);
	return opcao;
}

int menu_listar(char c[MAX_N]) {
	int opcao;
	gerar_linha();
	printf("1 - Listar todos os %s\n", c);
	printf("2 - Listar %s ordenados por nome\n", c);
	printf("3 - Listar %s ordenados por data de nascimento\n", c);
	printf("4 - Listar %s por sexo\n", c);
	if (!strcmp(c, "Alunos"))
		printf("5 - Listar %s matriculados em menos de 3 disciplinas\n", c);
	gerar_linha();
	scanf("%d", &opcao);
	fflush(stdin);
	return opcao;
}

// ---------- FUNÇÕES DE VALIDAÇÃO ----------


// Formatar nome
void formatar_nome(char nome[MAX_N]) {
	int i = 0;

	while (nome[i] != '\0') {
		if (nome[i] >= 'A' && nome[i] <= 'Z') {
			nome[i] = nome[i] + 32;
		}
		i++;
	}

	if (nome[0] >= 'a' && nome[0] <= 'z') {
		nome[0] = nome[0] - 32;
	}

	for (i = 1; nome[i] != '\0'; i++) {
		if (nome[i - 1] == ' ' && nome[i] >= 'a' && nome[i] <= 'z') {
			nome[i] = nome[i] - 32;
		}
	}
}

// Gênero (F/M/O)
char validar_genero() {
	char sexo;
	do {
		printf("Insira o sexo [F/M/O]: ");
		scanf(" %c", &sexo);
		fflush(stdin);

		if (sexo >= 'a' && sexo <= 'z') {
			sexo -= 32;
		}

		if (sexo != 'F' && sexo != 'M' && sexo != 'O') {
			printf("Opção inválida! Use apenas F (Feminino), M (Masculino) ou O (Outro).\n");
		}
	} while (sexo != 'F' && sexo != 'M' && sexo != 'O');
	return sexo;
}

// Data de nascimento válida
int validar_data(data d) {
	data atual;
	pegar_data(&atual);
	int dias_mes[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

	if ((d.ano % 4 == 0 && d.ano % 100 != 0) || (d.ano % 400 == 0)) {
		dias_mes[2] = 29;
	}

	if (d.mes < 1 || d.mes > 12) return 0;
	if (d.dia < 1 || d.dia > dias_mes[d.mes]) return 0;
	if (d.ano < 1900 || d.ano > atual.ano || (d.ano == atual.ano && d.mes >= atual.mes)) return 0;

	return 1;
}

// CPF válido
void formatar_cpf(char cpf_formatado[CPF], const char cpf_digitado[CPF]) {
	char numeros[12];
	int j = 0;


	for (int i = 0; cpf_digitado[i] != '\0'; i++) {
		if (cpf_digitado[i] >= '0' && cpf_digitado[i] <= '9') {
			numeros[j++] = cpf_digitado[i];
		}
	}
	numeros[j] = '\0';

	if (strlen(numeros) == 11) {
		sprintf(cpf_formatado, "%c%c%c.%c%c%c.%c%c%c-%c%c",
				numeros[0], numeros[1], numeros[2],
				numeros[3], numeros[4], numeros[5],
				numeros[6], numeros[7], numeros[8],
				numeros[9], numeros[10]);
	} else {
		strcpy(cpf_formatado, cpf_digitado);
	}
}

int validar_cpf(char cpf[CPF]) {
	int i, j, soma, resto;
	int digitos[11], qtd = 0;
	formatar_cpf(cpf, cpf);
	for (i = 0; cpf[i] != '\0' && qtd < 11; i++) {
		if (cpf[i] >= '0' && cpf[i] <= '9') {
			digitos[qtd++] = cpf[i] - '0';
		}
	}

	if (qtd != 11) return 0;

	int iguais = 1;
	for (i = 1; i < 11; i++) {
		if (digitos[i] != digitos[0]) {
			iguais = 0;
			break;
		}
	}
	if (iguais) return 0;

	soma = 0;
	for (i = 0, j = 10; i < 9; i++, j--) soma += digitos[i] * j;
	resto = soma % 11;
	int digito1 = (resto < 2) ? 0 : 11 - resto;
	if (digito1 != digitos[9]) return 0;

	soma = 0;
	for (i = 0, j = 11; i < 10; i++, j--) soma += digitos[i] * j;
	resto = soma % 11;
	int digito2 = (resto < 2) ? 0 : 11 - resto;
	if (digito2 != digitos[10]) return 0;

	return 1;
}

int buscar_cpf(pessoa *a, int qtd,char cpf[CPF]) {
	for (int i = 0; i < qtd; i++) {
		if (strcmp(a[i].cpf, cpf) == 0)
			return i;
	}
	return -1;
}

// ---------- FUNÇÕES CRUD -------------

//---------- CRUD PESSOA -------------

void cadastrar_pessoa(pessoa *a, pessoa *lista, int *qtd, int qtd2){
	if (tam_lista(*qtd) == LISTA_CHEIA) {
		printf("Lista cheia!\n");
	} else {
		gerar_linha();
		a->matricula = gerar_matricula(lista, *qtd+qtd2);
		fflush(stdin);
		printf("Matricula: %d\n", a->matricula);

		printf("Insira o nome: ");
		fgets(a->nome, MAX_N, stdin);
		fflush(stdin);
		formatar_nome(a->nome);

		a->sexo = validar_genero();

		do {
			printf("Insira a data de nascimento (dd mm aaaa): ");
			scanf("%d %d %d", &(a->data_nascimento.dia), &(a->data_nascimento.mes), &(a->data_nascimento.ano));
			fflush(stdin);
			if (!validar_data(a->data_nascimento)) {
				printf("Data inválida! Digite novamente.\n");
			}
		} while (!validar_data(a->data_nascimento));

		do {
			printf("Insira o CPF: ");
			fgets(a->cpf, CPF, stdin);
			fflush(stdin);
			if (!validar_cpf(a->cpf)) {
				printf("CPF inválido! Digite novamente.\n");
			}
			if (buscar_cpf(lista, *qtd+qtd2, a->cpf) >= 0) {
				printf("CPF já cadastrado!\n");
			}
		} while (!validar_cpf(a->cpf) || buscar_cpf(lista, *qtd+qtd2, a->cpf) >= 0);

		a->qtd_displinas = 0;

		printf("\nCadastro realizado com sucesso!\n");
		*qtd = *qtd + 1;
	}
}
//todas a funções de listar pessoa

//imprime pessoa a partir do inicio e fim
void imprimir_pessoa(pessoa a[TAM], int qtd, int ini) {
	for (int i = ini; i < qtd; i++) {
		gerar_linha();
		printf("Matricula: %d\n", a[i].matricula);
		printf("Nome: %s", a[i].nome);
		printf("Sexo: %c\n", a[i].sexo);
		printf("Data de nascimento: %02d/%02d/%02d\n", a[i].data_nascimento.dia, a[i].data_nascimento.mes, a[i].data_nascimento.ano);
		printf("CPF: %s\n", a[i].cpf);
		printf("\n");
	}
}
//lista professor/aluno por ordem alfabética
void ord_por_nome(pessoa a[TAM], int qtd) {
	// ordena por nome com o selection sort
	char menor[MAX_N];
	char minusc[MAX_N];
	int k;
	for(int i = 0; i < qtd - 1; i++){
		strcpy(menor, a[i].nome);
		minusculo(menor, strlen(menor));
		int pos = i;
		for(int j = i + 1; j < qtd; j++){
			strcpy(minusc, a[j].nome);
			minusculo(minusc, strlen(minusc));
			k = 0;
			while(minusc[k] == menor[k])
				k++;
			if(menor[k] > minusc[k]){
				strcpy(menor, minusc);
				pos = j;
			}
		}
		troca(&a[i], &a[pos]);
	}
	imprimir_pessoa(a, qtd, 0);
}
//lista professor/aluno por data de nascimento(mais antigo -> mais atual)
void ord_por_data(pessoa a[TAM], int qtd) {
	data menor;
	for (int i = 0; i < qtd; i++) {
		menor.ano = a[i].data_nascimento.ano;
		menor.mes = a[i].data_nascimento.mes;
		menor.dia = a[i].data_nascimento.dia;
		int pos = i;
		for(int j = i + 1; j < qtd; j++) {
			if(menor.ano == a[j].data_nascimento.ano) {
				if(menor.mes == a[j].data_nascimento.mes) {
					if(menor.dia > a[j].data_nascimento.dia) {
						menor.ano = a[j].data_nascimento.ano;
						menor.mes = a[j].data_nascimento.mes;
						menor.dia = a[j].data_nascimento.dia;
						pos = j;
					}
				} else if(menor.mes > a[j].data_nascimento.mes) {
					menor.ano = a[j].data_nascimento.ano;
					menor.mes = a[j].data_nascimento.mes;
					menor.dia = a[j].data_nascimento.dia;
					pos = j;
				}
			} else if(menor.ano > a[j].data_nascimento.ano) {
				menor.ano = a[j].data_nascimento.ano;
				menor.mes = a[j].data_nascimento.mes;
				menor.dia = a[j].data_nascimento.dia;
				pos = j;
			}
		}
		troca(&a[i], &a[pos]);
	}
	imprimir_pessoa(a, qtd, 0);
}
//lista professor/aluno por sexo selecionado pelo usuario
void filtrar_sexo(pessoa a[TAM], int qtd, char c[MAX_N]){
	char busc_sex;
	int achou;
	do{
		printf("\nInsira o sexo que você quer listar[F/M/O]: ");
		scanf("%c", &busc_sex);
		fflush(stdin);
		busc_sex = toupper(busc_sex);
		if(busc_sex == 'F' || busc_sex == 'M' || busc_sex == 'O'){
			achou = 0;
			for(int i = 0; i < qtd; i++){
				if(a[i].sexo == busc_sex){
					imprimir_pessoa(a, i+1, i);
					achou++;
				}
			}
			if(achou == 0){
				printf("Não foram encontrados %s com o sexo digitado.\n", c);
			}
		} else {
			printf("Opção Inválida!\n");
		}
	} while(busc_sex != 'F' && busc_sex != 'M' && busc_sex != 'O');
}
//lista aluno matriculado em menos de 3 disciplinas
void listar_alunos_menos_de_3_disciplinas(pessoa alunos[TAM], int qtd) {
	int encontrou = 0;

	if (qtd == 0) {
		printf("Nenhum aluno cadastrado.\n");
		return;
	}

	printf("Alunos matriculados em menos de 3 disciplinas:\n\n");

	for (int i = 0; i < qtd; i++) {
		if (alunos[i].qtd_displinas < 3) {
			printf("Nome: %s", alunos[i].nome);
			printf("Matrícula: %d\n", alunos[i].matricula);
			printf("Quantidade de Disciplinas: %d\n", alunos[i].qtd_displinas);
			printf("-----------------------------\n");
			encontrou = 1;
		}
	}

	if (!encontrou) {
		printf("Nenhum aluno está matriculado em menos de 3 disciplinas.\n");
	}
}
// modulo de listar
void listar_pessoa(pessoa a[TAM], int qtd, char c[MAX_N]) {
	int op_lista;
	int aluno = strcmp(c, "Alunos");
	pessoa copia[qtd];
	copia_vetor(a, copia, qtd);
	if (tam_lista(qtd) == LISTA_VAZIA) {
		printf("Lista Vazia!\n");
	} else {
		do {
			op_lista = menu_listar(c);
			switch (op_lista) {
				case 1:
					gerar_linha();
					printf("Listar todos os %s\n", c);
					imprimir_pessoa(a, qtd, 0);
					break;
				case 2:
					gerar_linha();
					printf("Listar %s ordenados por nome\n", c);
					ord_por_nome(copia, qtd);
					break;
				case 3:
					gerar_linha();
					printf("Listar %s ordenados por data de nascimento\n", c);
					ord_por_data(copia, qtd);
					break;
				case 4:
					gerar_linha();
					printf("Listar %s por sexo [M/F/O]\n", c);
					filtrar_sexo(a, qtd, c);
					break;
				case 5:
					if (!strcmp(c, "Alunos")) {
						gerar_linha();
						printf("%s matriculados em menos de 3 disciplinas\n", c);
						listar_alunos_menos_de_3_disciplinas(a, qtd);
					} else {
						printf("Opção inválida!\n");
					}
					break;
				default: printf("Opção inválida!\n");
			}
		} while (op_lista < 1 || (op_lista > 4 && aluno != 0) || (op_lista > 5 && aluno == 0));
	}

}

// atualiza professor/aluno a partir da matricula
void atualizar_pessoa(pessoa a[TAM], int qtd) {
	int pos, opcao, matricula;
	char nome[MAX_N];
	if (tam_lista(qtd) == LISTA_VAZIA) {
		printf("Lista Vazia!\n");
	} else {
		do {
			gerar_linha();
			printf("Insira a matrícula: ");
			scanf("%d", &matricula);
			pos = buscar_pessoa(a, qtd, matricula);
			if (pos < 0) {
				printf("Matrícula não encontrada.\n");
			} else {
				gerar_linha();
				printf("Selecione o dado a ser alterado:\n");
				printf("1 - Nome\n");
				printf("2 - Sexo\n");
				printf("3 - Data de Nascimento\n");
				printf("4 - CPF\n");
				gerar_linha();
				scanf("%d", &opcao);
				fflush(stdin);
				switch (opcao) {
					case 1:
						printf("Insira o novo nome: ");
						fgets(nome, MAX_N, stdin);
						fflush(stdin);
						formatar_nome(nome);
						strcpy(a[pos].nome, nome);
						break;
					case 2:
						a[pos].sexo = validar_genero();
						break;
					case 3:
						do {
							printf("Insira a data de nascimento (dd mm aaaa): ");
							scanf("%d %d %d", &(a[pos].data_nascimento.dia), &(a[pos].data_nascimento.mes), &(a[pos].data_nascimento.ano));
							fflush(stdin);
							if (!validar_data(a[pos].data_nascimento)) {
								printf("Data inválida! Digite novamente.\n");
							}
						} while (!validar_data(a[pos].data_nascimento));
						break;
					case 4:
						do {
							printf("Insira o CPF: ");
							fgets(a[pos].cpf, CPF, stdin);
							fflush(stdin);
							if (!validar_cpf(a[pos].cpf)) {
								printf("CPF inválido! Digite novamente.\n");
							}
						} while (!validar_cpf(a[pos].cpf));
						break;
					default: printf("Opção inválida!\n");
				}
			}
		} while (pos < 0 && (opcao < 1 || opcao > 4));
		printf("\nDados alterados com sucesso!\n");
	}

}

// exclui professor/aluno a partir da matrícula
void excluir_pessoa(pessoa *a, int *qtd_a, disciplina *d, int qtd_d) {
	int pos, pos_a, matricula;
	char resp;
	if (tam_lista(*qtd_a) == LISTA_VAZIA) {
		printf("Lista Vazia!\n");
	} else {
		do {
			printf("Insira a matrícula: ");
			scanf("%d", &matricula);
			pos = buscar_pessoa(a, *qtd_a, matricula);
			if (pos < 0) {
				printf("Matrícula não encontrada.\n");
			} else {
				for (int i = pos; i < *qtd_a - 1; i++) {
					a[i] = a[i + 1];
				}
				for(int j = 0; j < qtd_d; j++){
					// se for professor
					if(d[j].professor.matricula == matricula){
						strcpy(d[j].professor.nome, "Professor Excluído");
					}
					// se for aluno
					pos_a = buscar_pessoa(d[j].alunos, d[j].qtd_alunos, matricula);
					if(pos_a >= 0){
						for(int k = pos_a; k < d[j].qtd_alunos - 1; k++){
							d[j].alunos[k] = d[j].alunos[k + 1];
						}
						d[j].qtd_alunos--;
						d[j].vagas++;
					}
				}
				printf("\nMatrícula Excluída com sucesso!\n");
			}
		} while (pos < 0);
		*qtd_a = *qtd_a - 1;
	}
}

// -------- CRUD DISCIPLINA ------------------
//cadastra disciplina
void cadastrar_disciplina(disciplina *d, int *qtd, pessoa prof[TAM], int qtd_p) {
	int mat_prof, pos;
	if (qtd_p == 0) {
		printf("Lista de Professores Vazia.\n");
	} else {
		if (tam_lista(*qtd) == LISTA_CHEIA) {
			printf("Lista de disciplinas cheia!\n");
		} else {
			gerar_linha();
			d->codigo = gerar_codigo(d, *qtd);
			printf("Código: %d\n", d->codigo);

			printf("Insira o nome da disciplina: ");
			fgets(d->nome, MAX_N, stdin);
			fflush(stdin);
			formatar_nome(d->nome);

			do {
				printf("Insira o semestre: ");
				scanf("%d", &(d->semestre));
				fflush(stdin);
				if (d->semestre <= 0 || d->semestre > 13)
					printf("Insira um semestre válido!\n");
			}while (d->semestre <= 0 || d->semestre > 13);

			do {
				printf("Insira a quantidade de vagas: ");
				scanf("%d", &(d->vagas));
				fflush(stdin);
				if (d->vagas < 0 || d->vagas > 150)
					printf("Insira uma quantidade de vagas válida!\n");
			} while (d->vagas < 0 || d->vagas > 150);

			do {
				printf("Insira a matrícula do professor: ");
				scanf("%d", &mat_prof);
				fflush(stdin);
				pos = buscar_pessoa(prof, qtd_p, mat_prof);
				if (pos < 0)
					printf("Não foi possível achar o professor!\n");
				else
					d->professor = prof[pos];
			} while (pos < 0);
			d -> qtd_alunos = 0;
			d->alunos = malloc(d->vagas * sizeof(pessoa));
			*qtd = *qtd + 1;
			printf("Disciplina cadastrada com sucesso!\n");
		}
	}
}

// funções listar disciplina
// imprime a disciplinas a partir de um inicio até um fim
void imprimir_disciplina(disciplina d[TAM], int ini, int fim) {
	for (int i = ini; i < fim; i++) {
		gerar_linha();
		printf("Nome: %s", d[i].nome);
		printf("Codigo: %d\n", d[i].codigo);
		printf("Semestre: %d\n", d[i].semestre);
		printf("Vagas: %d\n", d[i].vagas);
		printf("Professor: %s\n", d[i].professor.nome);
	}
}
// lista disciplina + alunos
void obter_displina(disciplina d[TAM], int qtd) {
	int codigo, pos;
	do {
		printf("Insira o codigo da disciplina: ");
		scanf("%d", &codigo);
		pos = buscar_disciplina(d, qtd, codigo);
		if (pos < 0) {
			printf("Disciplina não encontrada\n");
		} else {
			imprimir_disciplina(d, pos, pos+1);
			if (!tam_lista(d[pos].qtd_alunos)) {
				printf("Nenhum aluno matriculado nessa disciplina\n");
			} else {
				printf("Alunos:\n");
				for (int i = 0; i < d[pos].qtd_alunos; i++)
					printf("- [%d] %s", d[pos].alunos[i].matricula, d[pos].alunos[i].nome);
			}
		}
	}while (pos < 0);
}
void listar_disciplinas_extrapolam_40_vagas(disciplina d[TAM], int qtd) {
	int encontrou = 0;

	if (tam_lista(qtd) == LISTA_VAZIA) {
		printf("Lista Vazia!\n");
	} else {
		for (int i = 0; i < qtd; i++) {
			if (d[i].vagas > 40) {
				imprimir_disciplina(d, i, i+1);
				encontrou = 1;
			}
		}
		if (!encontrou) {
			printf("Nenhuma disciplina possui mais de 40 vagas.\n");
		}
	}
}
void listar_disciplina(disciplina d[TAM], int qtd) {
	int op_lista;
	if (!tam_lista(qtd)) {
		printf("Lista Vazia!\n");
	} else {
		do {
			gerar_linha();
			printf("1 - Listar Disciplinas [dados]\n");
			printf("2 - Listar uma Disciplina [dados + alunos]\n");
			printf("3 - Listar Disciplinas que extrapolam 40 vagas\n");
			gerar_linha();
			scanf("%d", &op_lista);
			fflush(stdin);
			switch (op_lista) {
				case 1:
					gerar_linha();
					printf("Listando Disciplinas\n");
					imprimir_disciplina(d, 0, qtd);
					break;
				case 2:
					gerar_linha();
					printf("Listando uma disciplina [dados + alunos]\n");
					obter_displina(d, qtd);
					break;
				case 3:
					gerar_linha();
					printf("Disciplinas que extrapolam 40 vagas\n");
					listar_disciplinas_extrapolam_40_vagas(d, qtd);
					break;
				default: printf("Opção inválida!\n");
			}
		}while (op_lista < 1 || op_lista > 3);
	}
}

// atualiza disciplina a partir do codigo
void atualizar_disciplina(disciplina d[TAM], int qtd, pessoa prof[TAM], int qtd_p) {
    int pos, opcao, codigo, mat_prof, pos_prof;
    char nome[MAX_N];

    if (tam_lista(qtd) == LISTA_VAZIA) {
        printf("Lista Vazia!\n");
    } else {
        do {
        	gerar_linha();
            printf("Insira o código da disciplina: ");
            scanf("%d", &codigo);
            fflush(stdin);

            // Buscar disciplina pelo código
            pos = buscar_disciplina(d, qtd, codigo);
            if (pos < 0) {
                printf("Código não encontrado.\n");
            } else {
            	do {
            		printf("Disciplina: [%d] %s", d[pos].codigo, d[pos].nome);
            		gerar_linha();
            		printf("Selecione o dado a ser alterado:\n");
            		printf("1 - Nome\n");
            		printf("2 - Semestre\n");
            		printf("3 - Vagas\n");
            		printf("4 - Professor\n");
            		gerar_linha();
            		scanf("%d", &opcao);
            		fflush(stdin);
            		switch (opcao) {
            			case 1:
            				printf("Insira o novo nome: ");
            				fgets(nome, MAX_N, stdin);
            				fflush(stdin);
            				formatar_nome(nome);
            				strcpy(d[pos].nome, nome);
            				break;
            			case 2:
            				do{
            					printf("Insira o novo semestre: ");
            					scanf("%d", &d[pos].semestre);
            					fflush(stdin);
            					if (d[pos].semestre <= 0)
            						printf("Insira um semestre válido!\n");
            				}while (d[pos].semestre <= 0);
            				break;
            			case 3:
            				do {
            					printf("Insira a nova quantidade de vagas: ");
            					scanf("%d", &d[pos].vagas);
            					fflush(stdin);
            					if (d[pos].vagas < 0)
            						printf("Insira uma quantidade de vagas válida!\n");
            					else
            						realloc(d[pos].alunos, d[pos].vagas * sizeof(pessoa));
            				}while (d[pos].vagas < 0);
            				d[pos].vagas -= d[pos].qtd_alunos;
            				break;
            			case 4:
            				if (qtd_p == 0) {
            					printf("Lista de professores vazia.\n");
            				} else {
            					do {
            						printf("Insira a matrícula do novo professor: ");
            						scanf("%d", &mat_prof);
            						fflush(stdin);
            						pos_prof = buscar_pessoa(prof, qtd_p, mat_prof);
            						if (pos_prof < 0)
            							printf("Não foi possível achar o professor!\n");
            						else
            							d[pos].professor = prof[pos_prof];
            					} while (pos_prof < 0);
            				}
            				break;
            			default:
            				printf("Opção inválida!\n");
            		}
            	}while (opcao < 1 ||opcao > 4);
            }
        } while (pos < 0);
        printf("\nDados alterados com sucesso!\n");
	}
}

// Exclui a disciplina
void excluir_disciplina(disciplina *d, int *qtd_d, pessoa *a, int qtd_a) {
	int pos, pos_a, codigo;
	char resp;
	if (!tam_lista(*qtd_d)) {
		printf("Lista Vazia!\n");
	} else {
		do {
			gerar_linha();
			printf("Informe o código da disciplina: ");
			scanf("%d", &codigo);
			fflush(stdin);
			pos = buscar_disciplina(d, *qtd_d, codigo);
			if (pos < 0) {
				printf("Não foi possível encontrar a disciplina.\n");
			} else {
				printf("Disciplina encontrada: [%d] %s\n", d[pos].codigo, d[pos].nome);
				printf("Semestre: %d | Vagas: %d | Matriculados: %d\n", d[pos].semestre, d[pos].vagas, d[pos].qtd_alunos);
				printf("Deseja realmente excluir esta disciplina? (S ou s para confirmar): ");
				scanf("%c", &resp);
				fflush(stdin);
				if (resp == 'S' || resp == 's') {
					for (int i = 0; i < d[pos].qtd_alunos; i++) {
						int mat = d[pos].alunos[i].matricula;
						pos_a = buscar_pessoa(a, qtd_a, mat);
						if (pos_a >= 0) {
							if (a[pos_a].qtd_displinas > 0)
								a[pos_a].qtd_displinas--;
						}
					}
					if (d[pos].alunos != NULL) {
						free(d[pos].alunos);
						d[pos].alunos = NULL;
					}
					for (int j = pos; j < *qtd_d - 1; j++) {
						d[j] = d[j + 1];
					}
					*qtd_d = *qtd_d - 1;
					printf("Disciplina excluída com sucesso!\n");
				} else {
					printf("Operação cancelada.\n");
				}
			}
		} while (pos < 0);
	}
}

// Inclui aluno na disciplina
void incluir_aluno(disciplina *d, int qtd_d, pessoa *a, int qtd_a) {
	int pos_d, pos_a, pos, codigo, matricula;
	if (tam_lista(qtd_d) == LISTA_VAZIA || tam_lista(qtd_a) == LISTA_VAZIA) {
		printf("Lista Vazia!\n");
	} else {
		do {
			gerar_linha();
			printf("Informe o código da disciplina: ");
			scanf("%d", &codigo);
			fflush(stdin);
			pos_d = buscar_disciplina(d, qtd_d, codigo);
			if (pos_d < 0) {
				printf("Não foi possível encontrar a disciplina.\n");
			} else {
				if (d[pos_d].vagas == 0) {
					printf("Sem vagas para essa disciplina.\n");
				} else {
					do {
						gerar_linha();
						printf("Disciplina: [%d] %s\n", d[pos_d].codigo, d[pos_d].nome);
						printf("Insira a matrícula do aluno a ser incluido: ");
						scanf("%d", &matricula);
						fflush(stdin);
						pos_a = buscar_pessoa(a, qtd_a, matricula);
						if (pos_a < 0) {
							printf("Aluno não encontrado.\n");
						} else {
							pos = buscar_pessoa(d[pos_d].alunos, d[pos_d].qtd_alunos, matricula);
							if (pos >= 0) {
								printf("Aluno já incluído.\n");
							} else {
								d[pos_d].alunos[d[pos_d].qtd_alunos] = a[pos_a];
								a[pos_a].qtd_displinas++;
								d[pos_d].vagas--;
								d[pos_d].qtd_alunos++;
								printf("Aluno Inserido com sucesso!\n");
							}
						}
					} while (pos_a < 0);
				}
			}
		} while (pos_d < 0);
	}
}

// Exclui aluno da disciplina
void excluir_aluno(disciplina *d, int qtd_d, pessoa *a, int qtd_a) {
	int pos_d, pos_a, codigo, matricula;
	if (!tam_lista(qtd_d)) {
		printf("Lista Vazia!\n");
	} else {
		do {
			gerar_linha();
			printf("Informe o código da disciplina: ");
			scanf("%d", &codigo);
			pos_d = buscar_disciplina(d, qtd_d, codigo);
			if (pos_d < 0) {
				printf("Não foi possível encontrar a disciplina.\n");
			} else if (d[pos_d].qtd_alunos == 0) {
				printf("Não há alunos matriculados nessa disciplina.\n");
			}else {
				do {
					gerar_linha();
					printf("Disciplina: [%d] %s\n", d[pos_d].codigo, d[pos_d].nome);
					printf("Informe a matricula do aluno a ser excluído: ");
					scanf("%d", &matricula);
					pos_a = buscar_pessoa(d[pos_d].alunos, d[pos_d].qtd_alunos, matricula);
					if (pos_a < 0) {
						printf("Aluno não encontrado.\n");
					} else {
						for (int j = pos_a; j < d[pos_d].qtd_alunos - 1; j++)
							d[pos_d].alunos[j] = d[pos_d].alunos[j + 1];
						d[pos_d].qtd_alunos--;
						d[pos_d].vagas++;
						pos_a = buscar_pessoa(a, qtd_a, matricula);
						a[pos_a].qtd_displinas--;
						printf("Aluno %s excluído da disciplina com sucesso!\n", a[pos_a].nome);
					}
				} while (pos_a < 0);
			}
		} while (pos_d < 0);
	}
}

// ------ OUTROS RELATÓRIOS ---------
void listar_aniversariantes(pessoa lista[TAM], int qtd) {
	data atual;
	pegar_data(&atual);

	if (tam_lista(qtd) == LISTA_VAZIA){
		printf("Lista vazia!\n");
	} else {
		int achou = 0;
		gerar_linha();
		printf("\nAniversariantes do mês %d:\n", atual.mes);
		gerar_linha();
		for (int i = 0; i < qtd; i++) {
			if (lista[i].data_nascimento.mes == atual.mes) {
				printf("- %s (Dia: %02d/%02d/%04d)\n",
					   lista[i].nome,
					   lista[i].data_nascimento.dia,
					   lista[i].data_nascimento.mes,
					   lista[i].data_nascimento.ano);
				achou = 1;
			}
		}
		if (!achou)
			printf("Nenhum aniversariante encontrado neste mês.\n");
	}
}

void buscar_por_nome(pessoa lista[TAM], int qtd) {
	if (qtd == 0) {
		printf("Lista vazia!\n");
		return;
	}

	char busca[MAX_N];
	int tamanho;

	do {
		printf("Digite pelo menos 3 letras do nome para buscar: ");
		fgets(busca, MAX_N, stdin);
		fflush(stdin);
		tamanho = strlen(busca);
		if (busca[tamanho - 1] == '\n') {
			busca[tamanho - 1] = '\0';
			tamanho--;
		}

		if (tamanho < 3) {
			printf("Digite pelo menos 3 letras.\n");
		}
	} while (tamanho < 3);

	int achou = 0;
	char nome_lower[MAX_N];
	char busca_lower[MAX_N];

	// converte a busca para minúsculo
	strcpy(busca_lower, busca);
	for (int i = 0; busca_lower[i]; i++) busca_lower[i] = tolower(busca_lower[i]);

	printf("\nResultados da busca:\n");
	for (int i = 0; i < qtd; i++) {
		strcpy(nome_lower, lista[i].nome);
		for (int j = 0; nome_lower[j]; j++) nome_lower[j] = tolower(nome_lower[j]);

		if (strstr(nome_lower, busca_lower) != NULL) {
			imprimir_pessoa(lista, i+1, i);
			achou = 1;
		}
	}
	if (!achou) {
		printf("Nenhum resultado encontrado para \"%s\".\n", busca);
	}
}

#endif
