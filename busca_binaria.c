/*
  INTEGRANTES:
  Lázaro Joabe Nunes Soares - 12211BCC022
  Leonardo Henrique Carvalho Oliveira - 12311BCC003
  Moisés Marques de Oliviera - 12021BCC031
  Sergio Henrique Ribeiro Matos - 12211BCC038
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cidade {
  char cep[10];
  char sigla[4];
  char nomeCidade[100];
  char nomeRua[100];
} Cidade;

int buscaBinariaRecursiva(Cidade cidade[], int ini, int fim,
                          const char *chave) {
  if (ini > fim) {
    return -1;
  }
  int meio = (ini + fim) / 2;
  int cmp = strcmp(cidade[meio].cep, chave);
  if (cmp == 0) {
    return meio;
  } else if (cmp > 0) {
    return buscaBinariaRecursiva(cidade, ini, meio - 1, chave);
  } else {
    return buscaBinariaRecursiva(cidade, meio + 1, fim, chave);
  }
}

void lerArq(Cidade **vetor, int *tam) {
  FILE *arquivo = fopen("cep ponto e virgula.txt", "r");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  char cep[15], sigla[4], nomeCidade[100], nomeRua[100];
  int tamanho = 0;
  *vetor = malloc(1 * sizeof(Cidade));

  while (fscanf(arquivo, "%[^;];%[^;];%[^;];%[^\n]\n", cep, sigla, nomeCidade,
                nomeRua) != EOF) {
    tamanho++;
    *vetor = realloc(*vetor, tamanho * sizeof(Cidade));
    if (*vetor == NULL) {
      printf("Erro ao alocar memoria\n");
      fclose(arquivo);
      return;
    }
    strcpy((*vetor)[tamanho - 1].cep, cep);
    strcpy((*vetor)[tamanho - 1].sigla, sigla);
    strcpy((*vetor)[tamanho - 1].nomeCidade, nomeCidade);
    strcpy((*vetor)[tamanho - 1].nomeRua, nomeRua);
  }
  *tam = tamanho;
  fclose(arquivo);
}

void mostrarCidadeDesejada(Cidade cidade[], int posicao) {
  printf("\nA seguir, a cidade com o CEP desejado:\n");
  printf("CEP: %s\n", cidade[posicao].cep);
  printf("Sigla Do Estado: %s\n", cidade[posicao].sigla);
  printf("Nome Da Cidade: %s\n", cidade[posicao].nomeCidade);
  printf("Nome Da Rua: %s\n", cidade[posicao].nomeRua);
}

void shellSortCidade(Cidade cidade[], int tam) {
  int i, j, h = 1;
  Cidade aux;
  do {
    h = h * 3 + 1;
  } while (h < tam);

  do {
    h /= 3;
    for (i = h; i < tam; i++) {
      aux = cidade[i];
      j = i;
      while (j >= h && strcmp(cidade[j - h].cep, aux.cep) > 0) {
        cidade[j] = cidade[j - h];
        j -= h;
      }
      cidade[j] = aux;
    }
  } while (h > 1);
}

int main() {
  int tam;
  Cidade *cidade;

  lerArq(&cidade, &tam);

  if (tam == 0) {
    printf("Nenhuma cidade carregada.\n");
    return 1;
  }

  char cepProcurado[10];
  printf("Informe o CEP da cidade que deseja buscar: ");
  scanf("%9s", cepProcurado);

  shellSortCidade(cidade, tam);
  int encontrado = buscaBinariaRecursiva(cidade, 0, tam - 1, cepProcurado);

  if (encontrado != -1) {
    mostrarCidadeDesejada(cidade, encontrado);
  } else {
    printf("Cidade com o CEP %s não encontrada.\n", cepProcurado);
  }

  free(cidade);
  return 0;
}
