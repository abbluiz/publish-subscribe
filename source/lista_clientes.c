#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista_clientes.h"
#include "lista_publisher.h"

/* ----- Definição das structs abaixo ----- */

struct tipocliente {
    
    char* broker;
    char* nome;
    char pubsub;
    void* Lpubsub;

};

typedef struct celulacliente CelulaC;

struct celulacliente {
    
    TipoC* cliente;
    CelulaC* Ant;
    CelulaC* Prox;

};

struct tipolistacliente {
    
    CelulaC* Primeiro, *Ultimo;

};

/* ----- Funções elementares abaixo ----- */

TipoLC* InicializaListaCliente() {

    TipoLC* lista_cliente = (TipoLC*) malloc(sizeof (TipoLC));

    lista_cliente->Primeiro = NULL;
    lista_cliente->Ultimo = NULL;

    return lista_cliente;

}

TipoC* InicializaTipoCliente(char* nome, char* broker, void* Lpubsub, char pubsub) {

    TipoC* cliente = (TipoC*) malloc(sizeof (TipoC));

    cliente->nome = (char*) malloc(sizeof (char)*strlen(nome) + 1);
    cliente->broker = (char*) malloc(sizeof (char)*strlen(broker) + 1);

    if (pubsub == 'S') {

        Lpubsub = (TipoLS*) Lpubsub;
        cliente->Lpubsub = Lpubsub;
        ;

    } else {

        Lpubsub = (TipoLP*) Lpubsub;
        cliente->Lpubsub = Lpubsub;
        ;

    }

    strcpy(cliente->nome, nome);
    strcpy(cliente->broker, broker);

    cliente->pubsub = pubsub;


    return cliente;

}

void CriaCliente(TipoC* cliente, TipoLC* lista_clientes) {

    CelulaC* novo_cliente = (CelulaC*) malloc(sizeof (CelulaC));

    if (lista_clientes->Primeiro == NULL) {

        lista_clientes->Primeiro = lista_clientes->Ultimo = novo_cliente;
        lista_clientes->Primeiro->Prox = NULL;
        lista_clientes->Primeiro->Ant = NULL;
        lista_clientes->Ultimo->Prox = NULL;
        lista_clientes->Ultimo->Ant = NULL;

    } else {

        lista_clientes->Ultimo->Prox = novo_cliente;
        lista_clientes->Ultimo->Prox->Ant = lista_clientes->Ultimo;
        lista_clientes->Ultimo = lista_clientes->Ultimo->Prox;
        lista_clientes->Ultimo->Prox = NULL;

    }

    lista_clientes->Ultimo->cliente = cliente;

}

int ExcluiCliente(TipoLC* lista_clientes, char* nome) {

    CelulaC* aux = lista_clientes->Primeiro;

    while (aux != NULL && strcmp(aux->cliente->nome, nome) != 0) {

        aux = aux->Prox;

    }

    if (aux == NULL) {

        return 0;

    }

    if (aux == lista_clientes->Primeiro && aux == lista_clientes->Ultimo) {

        lista_clientes->Primeiro = NULL;
        lista_clientes->Ultimo = NULL;

        free(aux->cliente->nome);
        free(aux->cliente->broker);

        if (aux->cliente->pubsub == 'S') {

            LiberaListaSubscriber(aux->cliente->Lpubsub);

        } else {

            LiberaListaPublisher(aux->cliente->Lpubsub);

        }

        free(aux->cliente);
        free(aux);

        return 1;

    }

    if (aux == lista_clientes->Primeiro) {

        lista_clientes->Primeiro = lista_clientes->Primeiro->Prox;
        lista_clientes->Primeiro->Ant = NULL;

        free(aux->cliente->nome);
        free(aux->cliente->broker);

        if (aux->cliente->pubsub == 'S') {

            LiberaListaSubscriber(aux->cliente->Lpubsub);

        } else {

            LiberaListaPublisher(aux->cliente->Lpubsub);

        }

        free(aux->cliente);
        free(aux);

        return 1;

    }

    if (aux == lista_clientes->Ultimo) {
        ;

        lista_clientes->Ultimo = lista_clientes->Ultimo->Ant;
        lista_clientes->Ultimo->Prox = NULL;

        free(aux->cliente->nome);
        free(aux->cliente->broker);

        if (aux->cliente->pubsub == 'S') {

            LiberaListaSubscriber(aux->cliente->Lpubsub);

        } else {

            LiberaListaPublisher(aux->cliente->Lpubsub);

        }


        free(aux->cliente);
        free(aux);

        return 1;

    } else {

        aux->Prox->Ant = aux->Ant;
        aux->Ant->Prox = aux->Prox;

        free(aux->cliente->nome);
        free(aux->cliente->broker);

        if (aux->cliente->pubsub == 'S') {

            LiberaListaSubscriber(aux->cliente->Lpubsub);

        } else {

            LiberaListaPublisher(aux->cliente->Lpubsub);

        }


        free(aux->cliente);
        free(aux);

        return 1;

    }

}

void ImprimeCliente(TipoLC* lista_cliente, FILE* ArqSaida) {

    CelulaC* aux = NULL;
    aux = lista_cliente->Primeiro;

    while (aux != NULL) {

        fprintf(ArqSaida, "\n\tCLIENTE %c %s", aux->cliente->pubsub, aux->cliente->nome);

        if (aux->cliente->pubsub == 'P') {

            ImprimePublisher(aux->cliente->Lpubsub, ArqSaida);

        } else {

            ImprimeSubscriber(aux->cliente->Lpubsub, ArqSaida);

        }

        aux = aux->Prox;

    }

}

void LiberaListaCliente(TipoLC* lista_clientes) {

    CelulaC* aux = NULL;
    aux = lista_clientes->Primeiro;

    if (aux == NULL) {

        free(lista_clientes);
        return;

    }

    while (aux != lista_clientes->Ultimo) {

        aux = aux->Prox;

        free(aux->Ant->cliente->nome);
        free(aux->Ant->cliente->broker);

        if (aux->Ant->cliente->pubsub == 'S') {

            LiberaListaSubscriber(aux->Ant->cliente->Lpubsub);

        } else {

            LiberaListaPublisher(aux->Ant->cliente->Lpubsub);

        }

        free(aux->Ant->cliente);
        free(aux->Ant);

    }

    free(aux->cliente->nome);
    free(aux->cliente->broker);

    if (aux->cliente->pubsub == 'S') {

        LiberaListaSubscriber(aux->cliente->Lpubsub);

    } else {

        LiberaListaPublisher(aux->cliente->Lpubsub);

    }

    free(aux->cliente);
    free(aux);

    free(lista_clientes);
}

/* ----- Funções auxiliares abaixo ----- */

TipoC* PesquisaCliente(char* nome_cliente, TipoLC* lista_cliente) {

    CelulaC* aux = lista_cliente->Primeiro;

    while (aux != NULL && strcmp(aux->cliente->nome, nome_cliente) != 0) {

        aux = aux->Prox;

    }

    if (aux == NULL) {

        TipoC* cliente_null = NULL;

        return cliente_null;

    } else {

        return aux->cliente;

    }

}

int AdicionaSubscricaoCliente(TipoLC* lista_clientes, int id_sub, char* nome_cliente, char* topico) {

    CelulaC* cliente_aux = NULL;
    cliente_aux = lista_clientes->Primeiro;
    TipoS* novo_subscriber = NULL;

    while (cliente_aux != NULL) {

        if (strcmp(cliente_aux->cliente->nome, nome_cliente) == 0) {

            novo_subscriber = NULL;
            novo_subscriber = InicializaTipoSubscriber(id_sub, topico, nome_cliente);

            CriaSubscriber(novo_subscriber, cliente_aux->cliente->Lpubsub);

            return 1;

        }

        cliente_aux = cliente_aux->Prox;

    }

    return 0;

}

int AdicionaPublicacaoCliente(TipoLC* lista_clientes, int id_pub, char* nome_cliente, char* topico, char* mensagem) {

    CelulaC* cliente_aux = NULL;
    cliente_aux = lista_clientes->Primeiro;

    while (cliente_aux != NULL) {

        if (strcmp(cliente_aux->cliente->nome, nome_cliente) == 0) {

            TipoP* novo_publisher = NULL;
            novo_publisher = InicializaTipoPublisher(id_pub, topico, mensagem, nome_cliente);

            CriaPublisher(novo_publisher, cliente_aux->cliente->Lpubsub);

            return 1;

        }

        cliente_aux = cliente_aux->Prox;

    }

    return 0;

}

int VerificaSubscriberCliente(TipoLC* lista_clientes, char* nome_cliente) {

    CelulaC* cliente_aux = lista_clientes->Primeiro;

    while (cliente_aux != NULL) {

        if (strcmp(cliente_aux->cliente->nome, nome_cliente) == 0) {

            return 1;

        }

        cliente_aux = cliente_aux->Prox;

    }

    return 0;

}

int VerificaExistenciaCliente(TipoLC* lista_clientes, char* nome_cliente) {

    CelulaC* aux = NULL;
    aux = lista_clientes->Primeiro;

    while (aux != NULL) {

        if (strcmp(aux->cliente->nome, nome_cliente) == 0) {

            return 1;

        }

        aux = aux->Prox;

    }

    return 0;

}

int VerificaExistenciaPubsubCliente(TipoLC* lista_clientes, int id_pubsub) {

    CelulaC* aux = lista_clientes->Primeiro;

    int x;

    while (aux != NULL) {

        if (aux->cliente->pubsub == 'S') {
            x = VerificaExistenciaSubscricao(aux->cliente->Lpubsub, id_pubsub);

            if (x)
                return 1;

        } else if (aux->cliente->pubsub == 'P') {
            x = VerificaExistenciaPublicacao(aux->cliente->Lpubsub, id_pubsub);

            if (x)
                return 1;

        }

        aux = aux->Prox;

    }

    return 0;

}

int ExcluiSubscriberCliente(TipoLC* lista_clientes, int id_sub) {

    CelulaC* aux = NULL;
    aux = lista_clientes->Primeiro;

    int flag = 0;

    while (aux != NULL) {

        flag = ExcluiSubscriber(aux->cliente->Lpubsub, id_sub);

        if (flag)
            return 1;

        aux = aux->Prox;

    }

    return 0;

}

/* ----- Funções do matching abaixo ----- */

void PesquisaVizinhoCliente(TipoLC* lista_cliente, TipoS* subscriber, char * topico) {

    CelulaC* aux = NULL;
    aux = lista_cliente->Primeiro;

    while (aux != NULL) {

        PesquisaVizinhoPublisher(aux->cliente->Lpubsub, subscriber, topico);

        aux = aux->Prox;

    }
}

void PesquisaSubscriberCliente(TipoLC* lista_clientes, TipoLV* lista_vizinhos, TipoLB* lista_brokers,
        TipoB* broker, int flag) {

    CelulaC* aux = NULL;
    aux = lista_clientes->Primeiro;

    while (aux != NULL) {

        if (aux->cliente->pubsub == 'S') {

            PesquisaSubscriber(aux->cliente->Lpubsub, lista_vizinhos, lista_brokers, broker, flag);

        }

        aux = aux->Prox;

    }

}

void VerificaMatchingClientes(TipoLC* lista_clientes, FILE* ArqSaida) {

    CelulaC* aux = lista_clientes->Primeiro;

    while (aux != NULL) {

        if (aux->cliente->pubsub == 'S') {

            fprintf(ArqSaida, "CLIENTE %s\n", aux->cliente->nome);

            VerificaMatchingSubscriber(aux->cliente->Lpubsub, ArqSaida);

        }
        aux = aux->Prox;

    }

}