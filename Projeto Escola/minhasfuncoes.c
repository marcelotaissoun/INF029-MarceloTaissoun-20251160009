void cadastrar_disciplina(disciplina *d, int *qtd, pessoa prof[TAM], int qtd_p) {
	int mat_prof, pos; 
	if (tam_lista(*qtd) == LISTA_CHEIA) { 
		printf("Lista de disciplinas cheia!\n");
	} else {
		printf("Insira o nome da disciplina: ");
		fgets(d->nome, MAX_N, stdin);
		fflush(stdin); 
		formatar_nome(d->nome);
		printf("Insira o codigo da disciplina: ");
		scanf("%d", &(d->codigo));
		fflush(stdin); 

		printf("Insira o semestre: ");
		scanf("%d", &(d->semestre));
		fflush(stdin);

		printf("Insira a quantidade de vagas: ");
		scanf("%d", &(d->vagas));
		fflush(stdin);
		do { 
			printf("Insira a matrícula do professor: ");
			scanf("%d", &mat_prof);
			fflush(stdin);
			pos = buscar_pessoa(prof, qtd_p, mat_prof); 
			if (pos < 0)
				printf("Não foi possível achar o professor!");
			else
				strcpy(d->professor.nome, prof[pos].nome); 
		} while (pos < 0);
    *qtd = *qtd + 1;
		printf("Disciplina cadastrada com sucesso!\n");
	}
}

void atualizar_disciplina(disciplina d[TAM], int qtd, pessoa prof[TAM], int qtd_p) {
    int pos, opcao, codigo, mat_prof, pos_prof;
    char nome[MAX_N]; 
    
    if (tam_lista(qtd) == LISTA_VAZIA) { 
        printf("Lista Vazia!\n");
    } else {
        do { 
            printf("Insira o código da disciplina: ");
            scanf("%d", &codigo);
            fflush(stdin);
            
            pos = -1;
            for (int i = 0; i < qtd; i++) { 
                if (codigo == d[i].codigo) {
                    pos = i; 
                    break;
                }
            }
            
            if (pos < 0) {
                printf("Código não encontrado.\n");
            } else {
                printf("Selecione o dado a ser alterado:\n"); 
                printf("1 - Nome\n");
                printf("2 - Código\n");
                printf("3 - Semestre\n");
                printf("4 - Vagas\n");
                printf("5 - Professor\n");
                scanf("%d", &opcao);
                fflush(stdin);
                
                switch (opcao) {
                    case 1:
                        printf("Insira o novo nome: ");
                        fgets(nome, MAX_N, stdin);
                        fflush(stdin);
                        strcpy(d[pos].nome, nome);
                        break;
                    case 2:
                        printf("Insira o novo código: ");
                        scanf("%d", &d[pos].codigo);
                        fflush(stdin);
                        break;
                    case 3:
                        printf("Insira o novo semestre: ");
                        scanf("%d", &d[pos].semestre);
                        fflush(stdin);
                        break;
                    case 4:
                        printf("Insira a nova quantidade de vagas: ");
                        scanf("%d", &d[pos].vagas);
                        fflush(stdin);
                        break;
                    case 5:
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
                        break;
                    default: 
                        printf("Opção inválida!\n");
                }
            }
        } while (pos < 0 && (opcao < 1 || opcao > 5)); 
        printf("\nDados alterados com sucesso!\n");
    }
}
void excluir_disciplina(disciplina *d, int *qtd_d, pessoa *a, int qtd_a) {

 int pos, pos_a, codigo;
 if (!tam_lista(*qtd_d)) {
     printf("Lista Vazia!\n");
     } else {
         do {
            printf("Informe o código da disciplina: ");
            scanf("%d", &codigo);
            pos = buscar_disciplina(d, *qtd_d, codigo);
            if (pos < 0) {
                printf("Não foi possível encontrar a disciplina.\n");
            } else {             
                printf("Disciplina encontrada: [%d] %s\n", d[pos].codigo, d[pos].nome);
                printf("Semestre: %d | Vagas: %d | Matriculados: %d\n", d[pos].semestre, d[pos].vagas, d[pos].qtd_alunos);
                printf("Deseja realmente excluir esta disciplina? (S/N): ");
                while (getchar() != '\n');
                char resp = getchar();
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

listar_disciplinas_extrapolam_40_vagas(disciplina d[TAM], int qtd) {
    int encontrou = 0;

    if (tam_lista(qtd) == LISTA_VAZIA) {
        printf("Lista Vazia!\n");
    } else {
        printf("Disciplinas com mais de 40 vagas\n\n");
        for (int i = 0; i < qtd; i++) {
            if (d[i].vagas > 40) {
                printf("Nome: %s\n", d[i].nome);
                printf("Código: %d\n", d[i].codigo);
                printf("Semestre: %d\n", d[i].semestre);
                printf("Vagas: %d\n", d[i].vagas);
                printf("Professor: %s\n", d[i].professor.nome);
                printf("---------------------------------------------\n");
                encontrou = 1;
            }
        }
        if (!encontrou) {
            printf("Nenhuma disciplina possui mais de 40 vagas.\n");
        }
    }
}
