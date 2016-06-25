#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista_publisher.h"

/* ----- Definição das structs abaixo ----- */

struct tipopublisher {
    
    int id_pub;
    char* cliente;
    char* topico;
    char* conteudo;

};

typedef struct celulapublisher CelulaP;

struct celulapublisher {
    TipoP* publisher;
    CelulaP* Ant;
    CelulaP* Prox;

};

struct tipolistapublisher {
    CelulaP* Primeiro, *Ultimo;

};

/* ----- Funções elementares abaixo ----- */

TipoLP* InicializaListaPublisher() {

    TipoLP* lista_publisher = (TipoLP*) malloc(sizeof (TipoLP));

    lista_publisher->Primeiro = NULL;
    lista_publisher->Ultimo = NULL;

    return lista_publisher;

}

TipoP* InicializaTipoPublisher(int id_pub, char* topico, char* conteudo, char* cliente) {

    TipoP* publisher = (TipoP*) malloc(sizeof (TipoP));

    publisher->topico = (char*) malloc(sizeof (char)*(strlen(topico) + 1));

    publisher->conteudo = (char*) malloc(sizeof (char)*(strlen(conteudo) + 1));

    publisher->cliente = (char*) malloc(sizeof (char)*(strlen(cliente) + 1));

    strcpy(publisher->conteudo, conteudo);
    strcpy(publisher->topico, topico);
    strcpy(publisher->cliente, cliente);
    publisher->id_pub = id_pub;

    return publisher;

}

void CriaPublisher(TipoP* publisher, TipoLP* lista_publisher) {

    CelulaP* novo_publisher = (CelulaP*) malloc(sizeof (CelulaP));


    if (lista_publisher->Primeiro == NULL){
      
        lista_publisher->Primeiro = lista_publisher->Ultimo = novo_publisher;
        lista_publisher->Primeiro->Prox = NULL;
        lista_publisher->Primeiro->Ant = NULL;
        lista_publisher->Ultimo->Prox = NULL;
        lista_publisher->Ultimo->Ant = NULL;
        
    }

    else {

        lista_publisher->Ultimo->Prox = novo_publisher;
        lista_publisher->Ultimo->Prox->Ant = lista_publisher->Ultimo;
        lista_publisher->Ultimo = lista_publisher->Ultimo->Prox;
        lista_publisher->Ultimo->Prox = NULL;

    }

    lista_publisher->Ultimo->publisher = publisher;


}

void ImprimePublisher(TipoLP* lista_publisher, FILE* ArqSaida) {

    CelulaP* aux = lista_publisher->Primeiro;

    while (aux != NULL) {

        fprintf(ArqSaida, "\n\t\tEVENTO P%d %s %s", aux->publisher->id_pub, aux->publisher->topico, aux->publisher->conteudo);

        if(aux == lista_publisher->Ultimo)
            break;
        
        aux = aux->Prox;
        
    }

}

void LiberaListaPublisher(TipoLP* lista_publisher) {

    CelulaP* aux = lista_publisher->Primeiro;

    if (aux == NULL) {

        free(lista_publisher);
        return;

    }

    while (aux != lista_publisher->Ultimo) {

        aux = aux->Prox;

        free(aux->Ant->publisher->conteudo);
        free(aux->Ant->publisher->cliente);
        free(aux->Ant->publisher->topico);
        free(aux->Ant->publisher);
        free(aux->Ant);

    }

    free(aux->publisher->conteudo);
    free(aux->publisher->cliente);
    free(aux->publisher->topico);
    free(aux->publisher);
    free(aux);

    free(lista_publisher);

}

/* ----- Funções auxiliares abaixo ----- */

TipoP* PesquisaPublicacao(int id_pub, TipoLP* lista_publisher) {

    CelulaP* aux = lista_publisher->Primeiro;

    while (aux != NULL && aux->publisher->id_pub != id_pub) {

        aux = aux->Prox;

    }

    if (aux == NULL) {

        TipoP* pub_null = NULL;

        return pub_null;

    } else {

        return aux->publisher;

    }

}

int VerificaExistenciaPublicacao(TipoLP* lista_publisher, int id_pub) {

    CelulaP* aux = lista_publisher->Primeiro;

    while (aux != NULL) {

        if (aux->publisher->id_pub == id_pub)
            return 1;

        if(aux == lista_publisher->Ultimo)
            break;
        
        aux = aux->Prox;                

    }

    return 0;

}

/* ----- Funções do matching abaixo ----- */

void PesquisaVizinhoPublisher(TipoLP* lista_publisher, TipoS* subscriber, char * topico) {

    CelulaP* aux = NULL;
    aux = lista_publisher->Primeiro;
    
    int flag = 0;
    
    while (aux != NULL) {

        TipoP* publisher = NULL;
        publisher = aux->publisher;
        
        flag = VerificaExistenciaConteudo(RtnListaConteudo(subscriber), publisher->id_pub);
        
        if (strcmp(aux->publisher->topico, topico) == 0 && flag == 1) {
            
            TipoCT* cont = InicializaTipoConteudo(publisher->conteudo, publisher->id_pub);

            CriaConteudo(cont, RtnListaConteudo(subscriber));

        }

        aux = aux->Prox;
    }
}