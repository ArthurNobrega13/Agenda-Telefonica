#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct agenda_telefonica{
  char nome[40];
  char telefone[15];
  char celular[15];
  char email[40];
  struct agenda_telefonica *proximo;
};
typedef struct agenda_telefonica agenda;

agenda *criar_agenda(){
  return NULL;
}

agenda *insere_contato(agenda *contatos){
  agenda *novo_contato = (agenda *) malloc(sizeof(agenda));

  printf("Nome: ");
  getchar();
  fgets(novo_contato -> nome, sizeof(novo_contato -> nome), stdin);
  novo_contato -> nome[strcspn(novo_contato -> nome, "\n")] = 0;
  printf("Telefone: ");
  scanf("%s", novo_contato -> telefone);
  printf("Celular: ");
  scanf("%s", novo_contato -> celular);
  printf("E-mail: ");
  scanf("%s", novo_contato -> email);

  novo_contato -> proximo = contatos;
  return novo_contato;
}

void lista_contatos(agenda *contatos){
  while (contatos != NULL){
    printf("Nome: %s\n", contatos -> nome);
    printf("Telefone: %s\n", contatos -> telefone);
    printf("Celular: %s\n", contatos -> celular);
    printf("E-mail: %s\n", contatos -> email);
    
    contatos = contatos -> proximo;
    printf("\n");
  }
}

agenda *busca_contato(agenda *contatos, char nome_buscado[30]){
  while (contatos != NULL){
    
   if (strcmp(nome_buscado, contatos -> nome) == 0){
     return contatos;
   }
   contatos = contatos -> proximo;
  }
  
  return NULL;
}

agenda *remover_contato(agenda *contatos){
  char nome_removido[40] = "";
  
  printf("Nome do contato: ");
  getchar();
  fgets(nome_removido, sizeof(nome_removido), stdin);
  nome_removido[strcspn(nome_removido, "\n")] = 0;
  
  agenda *ponteiro_contato = contatos;
  agenda *gancho = NULL;
  
  while (ponteiro_contato != NULL && strcmp(ponteiro_contato -> nome, nome_removido) != 0){
    gancho = ponteiro_contato;
    ponteiro_contato = ponteiro_contato -> proximo;
  }
  if (ponteiro_contato == NULL){
    return contatos;
  }
  if (gancho == NULL){
    contatos = ponteiro_contato -> proximo;
  }else{
    gancho -> proximo = ponteiro_contato -> proximo;
  }
  free(ponteiro_contato);
  return contatos;
}

int main(void) {
  agenda *contatos, aux, *p_aux;
  char acao_menu[40] = "1";
  FILE *arquivos_append, *arquivos_leitura;
  char nome_buscado[40] = "";

  arquivos_append = fopen("contatos.txt", "ab");
  arquivos_leitura = fopen("contatos.txt", "rb");
  
  contatos = criar_agenda();
  
  while (strcmp(acao_menu, "5") != 0){
    printf("|-----| Agenda Telefônica |-----|\n");
    printf("\n1 – Inserir Contato\n");
    printf("2 – Listar Contatos\n");
    printf("3 – Buscar Contato\n");
    printf("4 – Remover Contato\n");
    printf("5 – Sair\n");
    printf("Insira sua tecla: ");
    scanf("%s", acao_menu);
    printf("\n");
    
    if (strcmp(acao_menu, "1") == 0){
      contatos = insere_contato(contatos);
      fwrite(contatos, sizeof(agenda), 1, arquivos_append);
    }
      
    else if(strcmp(acao_menu, "2") == 0){
      while (fread(&aux, sizeof(agenda), 1, arquivos_leitura) == 1){
        printf("Nome: %s\n", aux.nome);
        printf("Telefone: %s\n", aux.telefone);
        printf("Celular: %s\n", aux.celular);
        printf("E-mail: %s\n", aux.email);
        
        printf("\n");
      }
      rewind(arquivos_leitura);
      
      lista_contatos(contatos);
    }
      
    else if(strcmp(acao_menu, "3") == 0){
      p_aux = NULL;
        
      printf("Nome do contato: ");
      getchar();
      fgets(nome_buscado, sizeof(nome_buscado), stdin);
      nome_buscado[strcspn(nome_buscado, "\n")] = 0;
      
      while (fread(&aux, sizeof(agenda), 1, arquivos_leitura) == 1 && p_aux == NULL){
        if (strcmp(nome_buscado, aux.nome) == 0){
          p_aux = &aux;
          
          printf("\nNome: %s\n", aux.nome);
          printf("Telefone: %s\n", aux.telefone);
          printf("Celular: %s\n", aux.celular);
          printf("E-mail: %s\n", aux.email);
        }
      }

      rewind(arquivos_leitura);
      
      if (p_aux == NULL){
        p_aux = busca_contato(contatos, nome_buscado);  

        if (p_aux == NULL){
          printf("\nEsse contato NÃO está na lista");
        }else{
          printf("\nNome: %s\n", p_aux -> nome);
          printf("Telefone: %s\n", p_aux -> telefone);
          printf("Celular: %s\n", p_aux -> celular);
          printf("E-mail: %s\n", p_aux -> email);
        }
      }
      printf("\n");
    }

      
    else if(strcmp(acao_menu, "4") == 0){
      contatos = remover_contato(contatos);
    }

    else if(strcmp(acao_menu, "5") == 0){
      printf("Desligando...\n");
    }
  
    else{
      printf("Tecla inválida\n");
    }
    printf("\n");
  }

  fclose(arquivos_append);
  fclose(arquivos_leitura);

  return 0;
}
