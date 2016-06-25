#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista_vizinhos.h"

/* ----- Definição das structs abaixo ----- */

typedef struct celulavizinho CelulaV;

// Somente o typedef da célula fica no arquivo de implementação do TAD

struct celulavizinho {
    
    TipoV* Vizinho;
    CelulaV* Ant;
    CelulaV* Prox;

};

struct tipovizinho {
    
    char* nome;
    TipoB* broker;

};

struct tipolistavizinho {
    
    CelulaV* Primeiro, *Ultimo;

};

/* ----- Funções elementares abaixo ----- */

TipoLV* InicializaListaVizinho() {

    TipoLV* lista_vizinhos = (TipoLV*) malloc(sizeof (TipoLV));

    lista_vizinhos->Primeiro = NULL;
    lista_vizinhos->Ultimo = NULL;

    return lista_vizinhos;

}

TipoV* InicializaTipoVizinho(char* nome, TipoLB* lista_brokers) {

    TipoV* novo_vizinho = (TipoV*) malloc(sizeof (TipoV));

    novo_vizinho->nome = (char*) malloc(sizeof (char)*strlen(nome) + 1);

    novo_vizinho->broker = PesquisaBroker(nome, lista_brokers);

    strcpy(novo_vizinho->nome, nome);

    return novo_vizinho;

}

void CriaVizinho(TipoV* vizinho, TipoLV* lista_vizinhos) {

    CelulaV* novo_vizinho = (CelulaV*) malloc(sizeof (CelulaV));

    if (lista_vizinhos->Primeiro == NULL) {

        lista_vizinhos->Primeiro = lista_vizinhos->Ultimo = novo_vizinho;
        lista_vizinhos->Primeiro->Prox = NULL;
        lista_vizinhos->Primeiro->Ant = NULL;
        lista_vizinhos->Ultimo->Prox = NULL;
        lista_vizinhos->Ultimo->Ant = NULL;

    } else {

        lista_vizinhos->Ultimo->Prox = novo_vizinho;
        lista_vizinhos->Ultimo->Prox->Ant = lista_vizinhos->Ultimo;
        lista_vizinhos->Ultimo = lista_vizinhos->Ultimo->Prox;
        lista_vizinhos->Ultimo->Prox = NULL;

    }

    lista_vizinhos->Ultimo->Vizinho = vizinho;

}

void ExcluiVizinhos(TipoLV* lista_vizinhos, char * nome) {

    CelulaV* vizinho = lista_vizinhos->Primeiro;

    while (vizinho != NULL && strcmp(vizinho->Vizinho->nome, nome) != 0) {

        vizinho = vizinho->Prox;

    }

    if (vizinho == NULL)
        return;

    if (vizinho == lista_vizinhos->Primeiro && vizinho == lista_vizinhos->Ultimo) {

        lista_vizinhos->Primeiro = NULL;
        lista_vizinhos->Ultimo = NULL;

        free(vizinho->Vizinho->nome);
        free(vizinho->Vizinho);
        free(vizinho);

        return;

    }

    if (vizinho == lista_vizinhos->Primeiro) {

        lista_vizinhos->Primeiro = lista_vizinhos->Primeiro->Prox;
        lista_vizinhos->Primeiro->Ant = NULL;

        free(vizinho->Vizinho->nome);
        free(vizinho->Vizinho);
        free(vizinho);

        return;

    }

    if (vizinho == lista_vizinhos->Ultimo) {

        lista_vizinhos->Ultimo = lista_vizinhos->Ultimo->Ant;
        lista_vizinhos->Ultimo->Prox = NULL;

        free(vizinho->Vizinho->nome);
        free(vizinho->Vizinho);
        free(vizinho);

        return;

    } else {

        vizinho->Ant->Prox = vizinho->Prox;
        vizinho->Prox->Ant = vizinho->Ant;

        free(vizinho->Vizinho->nome);
        free(vizinho->Vizinho);
        free(vizinho);

        return;

    }

}

void ImprimeVizinho(TipoLV* lista_vizinho, FILE* ArqSaida) {

    CelulaV* aux;
    aux = lista_vizinho->Primeiro;

    while (aux != NULL) {

        fprintf(ArqSaida, "\n\tVIZINHO %s", aux->Vizinho->nome);

        aux = aux->Prox;

    }

}

void LiberaListaVizinho(TipoLV* lista_vizinhos) {

    CelulaV* aux = lista_vizinhos->Primeiro;

    if (aux == NULL) {

        free(lista_vizinhos);

        return;

    }

    while (aux != lista_vizinhos->Ultimo) {

        aux = aux->Prox;

        free(aux->Ant->Vizinho->nome);
        free(aux->Ant->Vizinho);
        free(aux->Ant);

    }

    free(aux->Vizinho->nome);
    free(aux->Vizinho);
    free(aux);

    free(lista_vizinhos);

    return;

}

/* ----- Funções auxiliares abaixo ----- */

int VerificaExistenciaVizinho(TipoLV* lista_vizinhos, char* nome_vizinho) {

    CelulaV* aux = NULL;
    aux = lista_vizinhos->Primeiro;

    while (aux != NULL) {

        if (strcmp(aux->Vizinho->nome, nome_vizinho) == 0)
            return 1;

        if (aux == lista_vizinhos->Ultimo) {
            break;
        }
        aux = aux->Prox;

    }

    return 0;

}

void ExcluiVizinhoU(TipoLV* lista_vizinhos, char* nome_vizinho) {

    CelulaV* aux = NULL;
    aux = lista_vizinhos->Primeiro;

    while (aux != NULL) {

        if (strcmp(aux->Vizinho->nome, nome_vizinho) == 0) {

            ExcluiVizinhos(lista_vizinhos, nome_vizinho);
            
            return;

        }

        aux = aux->Prox;

    }

}

/* ----- Funções do matching abaixo ----- */

void PesquisaVizinhos(TipoLV* lista_vizinhos, TipoS* subscriber, char* topico) {

    CelulaV* aux = NULL;
    aux = lista_vizinhos->Primeiro;

    while (aux != NULL) { 

       /* Pesquisa na lista de clientes de todos os vizinhos do broker atual a procura
         de um publisher */
        
        if (RtnClientesVisitado(aux->Vizinho->broker) == 0) {

            PesquisaVizinhoCliente(RtnListaClientes(aux->Vizinho->broker), subscriber, topico);

            AlteraClientesVisitadosBroker(aux->Vizinho->broker, 1);

        }

        aux = aux->Prox;

    }

    aux = NULL;
    aux = lista_vizinhos->Primeiro;

    if (aux == NULL) { // Verifica se a lista de vizinhos é vazia

        return;

    }

    if (RtnVizinhosVisitado(aux->Vizinho->broker) == 1) {
        
        /* Verifica se a lista de vizinhos do broker atual já foi percorrida */

        while (aux != NULL) {

            if (RtnVizinhosVisitado(aux->Vizinho->broker) == 0)
                break;

            aux = aux->Prox;

        }

    }

    if (aux == NULL) {
        
        /* Verificação se não existe nenhum vizinho em que a lista não tenha sido pesquisada */

        return;
        
    }

    AlteraVizinhosVisitadosBroker(aux->Vizinho->broker, 1);

    while (aux != NULL) {
        
        /* Início da recursão para que a pesquisa seja feita ao longo de toda rede de brokers */

        CelulaV* aux_2 = NULL;
        aux_2 = RtnListaVizinhos(aux->Vizinho->broker)->Primeiro;

        while (aux_2 != NULL) {

            while (RtnVizinhosVisitado(aux_2->Vizinho->broker) == 0) {

                if (RtnVizinhosVisitado(aux_2->Vizinho->broker) == 0) {

                    AlteraVizinhosVisitadosBroker(aux_2->Vizinho->broker, 1);

                    PesquisaVizinhoCliente(RtnListaClientes(aux_2->Vizinho->broker), subscriber, topico);

                    PesquisaVizinhos(RtnListaVizinhos(aux_2->Vizinho->broker), subscriber, topico);

                }

            }

            aux_2 = aux_2->Prox;

        }

        aux = aux->Prox;

    }

}