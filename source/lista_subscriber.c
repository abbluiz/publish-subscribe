#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista_subscriber.h"

/* ----- Definição das structs abaixo ----- */

struct tiposubscriber {
    int id_sub;
    char* topico;
    char * cliente;
    TipoLCT* lista_conteudo;

};

typedef struct celulasubscriber CelulaS;

struct celulasubscriber {
    TipoS* subscriber;
    CelulaS* Ant;
    CelulaS* Prox;

};

struct tipolistasubscriber {
    CelulaS* Primeiro, *Ultimo;

};

struct tipoconteudo {
    char* mensagem;
    int pub;

};

typedef struct celulaconteudo CelulaCT;

struct celulaconteudo {
    TipoCT* conteudo;
    CelulaCT* Ant;
    CelulaCT* Prox;

};

struct tipolistaconteudo {
    CelulaCT* Primeiro, *Ultimo;

};

/* ----- Funções elementares abaixo ----- */

TipoLS* InicializaListaSubscriber() {

    TipoLS* lista_subscriber = (TipoLS*) malloc(sizeof (TipoLS));

    lista_subscriber->Primeiro = NULL;
    lista_subscriber->Ultimo = NULL;

    return lista_subscriber;

}

TipoS* InicializaTipoSubscriber(int id_sub, char* topico, char* cliente) {

    TipoS* subscriber = (TipoS*) malloc(sizeof (TipoS));

    subscriber->cliente = (char*) malloc(sizeof (char)*strlen(cliente) + 1);
    subscriber->topico = (char*) malloc(sizeof (char)*strlen(topico) + 1);

    TipoLCT* lista_conteudo = InicializaListaConteudo();

    strcpy(subscriber->cliente, cliente);
    strcpy(subscriber->topico, topico);
    subscriber->id_sub = id_sub;
    subscriber->lista_conteudo = lista_conteudo;

    return subscriber;

}

void CriaSubscriber(TipoS* subscriber, TipoLS* lista_subscriber) {

    CelulaS* novo_subscriber = (CelulaS*) malloc(sizeof (CelulaS));

    if (lista_subscriber->Primeiro == NULL) {

        lista_subscriber->Primeiro = lista_subscriber->Ultimo = novo_subscriber;
        lista_subscriber->Primeiro->Prox = NULL;
        lista_subscriber->Primeiro->Ant = NULL;
        lista_subscriber->Ultimo->Prox = NULL;
        lista_subscriber->Ultimo->Ant = NULL;

    } else {

        lista_subscriber->Ultimo->Prox = novo_subscriber;
        lista_subscriber->Ultimo->Prox->Ant = lista_subscriber->Ultimo;
        lista_subscriber->Ultimo = lista_subscriber->Ultimo->Prox;
        lista_subscriber->Ultimo->Prox = NULL;
    }

    lista_subscriber->Ultimo->subscriber = subscriber;
}

int ExcluiSubscriber(TipoLS* lista_subscriber, int id_sub) {

    CelulaS* aux = lista_subscriber->Primeiro;

    while (aux != NULL && aux->subscriber->id_sub != id_sub) {

        aux = aux->Prox;

    }

    if (aux == NULL) {
        
        return 0;

    }

    if (aux == lista_subscriber->Primeiro && aux == lista_subscriber->Ultimo) {

        lista_subscriber->Primeiro = lista_subscriber->Ultimo = NULL;
        free(aux->subscriber->topico);
        free(aux->subscriber->cliente);
        LiberaListaConteudo(aux->subscriber->lista_conteudo);
        free(aux->subscriber);
        free(aux);

        return 1;

    }

    if (aux == lista_subscriber->Primeiro) {

        lista_subscriber->Primeiro = lista_subscriber->Primeiro->Prox;
        lista_subscriber->Primeiro->Ant = NULL;

        free(aux->subscriber->topico);
        free(aux->subscriber->cliente);
        LiberaListaConteudo(aux->subscriber->lista_conteudo);
        free(aux->subscriber);
        free(aux);

        return 1;

    }

    if (aux == lista_subscriber->Ultimo) {

        lista_subscriber->Ultimo = lista_subscriber->Ultimo->Ant;
        lista_subscriber->Ultimo->Prox = NULL;

        free(aux->subscriber->topico);
        free(aux->subscriber->cliente);
        LiberaListaConteudo(aux->subscriber->lista_conteudo);
        free(aux->subscriber);
        free(aux);

        return 1;

    } else {

        aux->Prox->Ant = aux->Ant;
        aux->Ant->Prox = aux->Prox;

        free(aux->subscriber->topico);
        free(aux->subscriber->cliente);
        LiberaListaConteudo(aux->subscriber->lista_conteudo);
        free(aux->subscriber);
        free(aux);

        return 1;

    }


}

void LiberaListaSubscriber(TipoLS* lista_subscriber) {

    CelulaS* aux = lista_subscriber->Primeiro;

    if (aux == NULL) {

        free(lista_subscriber);
        return;

    }

    while (aux != lista_subscriber->Ultimo) {

        aux = aux->Prox;

        free(aux->Ant->subscriber->cliente);
        free(aux->Ant->subscriber->topico);
        LiberaListaConteudo(aux->Ant->subscriber->lista_conteudo);
        free(aux->Ant->subscriber);
        free(aux->Ant);

    }

    free(aux->subscriber->cliente);
    free(aux->subscriber->topico);
    LiberaListaConteudo(aux->subscriber->lista_conteudo);
    free(aux->subscriber);
    free(aux);
    free(lista_subscriber);

}

void ImprimeSubscriber(TipoLS* lista_subscriber, FILE* ArqSaida) {

    CelulaS* aux = lista_subscriber->Primeiro;

    while (aux != NULL) {

        fprintf(ArqSaida, "\n\t\tEVENTO S%d %s", aux->subscriber->id_sub, aux->subscriber->topico);

        aux = aux->Prox;

    }

}

/* ----- Funções auxiliares ----- */

TipoLCT* InicializaListaConteudo() {

    TipoLCT* lista_conteudo = (TipoLCT*) malloc(sizeof (TipoLCT));

    lista_conteudo->Primeiro = NULL;
    lista_conteudo->Ultimo = NULL;

    return lista_conteudo;

}

TipoCT* InicializaTipoConteudo(char* conteudo, int pub) {

    TipoCT* tconteudo = (TipoCT*) malloc(sizeof (TipoCT));

    tconteudo->mensagem = (char*) malloc(sizeof (char)*strlen(conteudo) + 1);

    strcpy(tconteudo->mensagem, conteudo);

    tconteudo->pub = pub;

    return tconteudo;

}

void CriaConteudo(TipoCT* conteudo, TipoLCT* lista_conteudo) {

    CelulaCT* novo_conteudo = NULL;
    novo_conteudo = (CelulaCT*) malloc(sizeof (CelulaCT));

    if (lista_conteudo->Primeiro == NULL) {

        lista_conteudo->Primeiro = novo_conteudo;
        lista_conteudo->Ultimo = novo_conteudo;
        lista_conteudo->Primeiro->Ant = NULL;
        lista_conteudo->Primeiro->Prox = NULL;
        lista_conteudo->Ultimo->Ant = NULL;
        lista_conteudo->Ultimo->Prox = NULL;

    } else {

        lista_conteudo->Ultimo->Prox = novo_conteudo;
        lista_conteudo->Ultimo->Prox->Ant = lista_conteudo->Ultimo;
        lista_conteudo->Ultimo = lista_conteudo->Ultimo->Prox;
        lista_conteudo->Ultimo->Prox = NULL;

    }

    lista_conteudo->Ultimo->conteudo = conteudo;
}

void LiberaListaConteudo(TipoLCT* lista_conteudo) {

    CelulaCT* aux = lista_conteudo->Primeiro;

    if (aux == NULL) {

        free(lista_conteudo);
        return;

    }

    while (aux != lista_conteudo->Ultimo) {

        aux = aux->Prox;

        free(aux->Ant->conteudo->mensagem);
        free(aux->Ant->conteudo);
        free(aux->Ant);

    }

    free(aux->conteudo->mensagem);
    free(aux->conteudo);
    free(aux);
    free(lista_conteudo);

}

int VerificaExistenciaSubscricao(TipoLS* lista_subscriber, int id_sub) {

    CelulaS* aux = lista_subscriber->Primeiro;

    while (aux != NULL) {

        if (aux->subscriber->id_sub == id_sub)
            return 1;

        aux = aux->Prox;

    }

    return 0;

}

TipoS* PesquisaSubscricao(int id_sub, TipoLS* lista_subscriber) {

    CelulaS* aux = lista_subscriber->Primeiro;

    while (aux != NULL && aux->subscriber->id_sub != id_sub) {

        aux = aux->Prox;

    }

    if (aux == NULL) {

        TipoS* sub_null = NULL;

        return sub_null;

    } else {

        return aux->subscriber;

    }

}

int VerificaExistenciaConteudo(TipoLCT* lista_conteudo, int id_pub) {

    CelulaCT* aux = lista_conteudo->Primeiro;

    while (aux != NULL) {

        if (aux->conteudo == NULL || aux->conteudo->pub == id_pub) {

            return 0;

        }

        aux = aux->Prox;

    }

    return 1;

}

TipoLCT* RtnListaConteudo(TipoS* subscriber) {

    return subscriber->lista_conteudo;

}

void VerificaMatchingSubscriber(TipoLS* lista_subscriber, FILE* ArqSaida) {

    CelulaS* aux_sub = lista_subscriber->Primeiro;

    if (aux_sub != NULL) {

        while (aux_sub != NULL) {

            CelulaCT* aux_ct = RtnListaConteudo(aux_sub->subscriber)->Primeiro;

            while (aux_ct != NULL) {

                ImprimeMatching(aux_sub->subscriber, aux_ct->conteudo, ArqSaida);

                aux_ct = aux_ct->Prox;
            }

            aux_sub = aux_sub->Prox;
        }

    }
    fprintf(ArqSaida, "\n");
}

void ImprimeMatching(TipoS* subscriber, TipoCT* conteudo, FILE* ArqSaida) {

    if (strcmp(conteudo->mensagem, "") != 0)
        fprintf(ArqSaida, "\tS%d P%d %s %s \n", subscriber->id_sub, conteudo->pub, subscriber->topico,
            conteudo->mensagem);

}

void PesquisaSubscriber(TipoLS* lista_subscriber, TipoLV* lista_vizinhos, TipoLB* lista_broker,
        TipoB* broker, int flag) {

    CelulaS* aux = NULL;
    aux = lista_subscriber->Primeiro;
    
    while (aux != NULL) {

        if (flag) {

            PesquisaVizinhoCliente(RtnListaClientes(broker), aux->subscriber, aux->subscriber->topico);

            AlteraClientesVisitadosBroker(broker, 1);

            PesquisaVizinhos(lista_vizinhos, aux->subscriber, aux->subscriber->topico);

            ResetaBrokers(lista_broker);

        }

        if (flag == 0) {

            CelulaCT* aux2 = NULL;
            aux2 = aux->subscriber->lista_conteudo->Primeiro;

            while (aux2 != NULL) {

                strcpy(aux2->conteudo->mensagem, "");
                aux2->conteudo->pub = 0;

                aux2 = aux2->Prox;

            }

        }

        aux = aux->Prox;

    }

}