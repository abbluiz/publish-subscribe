#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista_brokers.h"
#include "lista_clientes.h"
#include "lista_subscriber.h"
#include "lista_publisher.h"

/* ----- Definição das structs abaixo ----- */

typedef struct celulabroker CelulaB;

// Somente o typedef da célula fica no arquivo de implementação do TAD

struct tipobroker {
    
    char* nome;
    int clientes_visitados;
    int vizinhos_visitados;
    TipoLV* lista_vizinhos;
    TipoLC* lista_clientes;

};

struct celulabroker {
    
    TipoB* Broker;
    CelulaB* Ant;
    CelulaB* Prox;

};

struct tipolistabroker {
    
    CelulaB* Primeiro, *Ultimo;

};

/* ----- Funções elementares abaixo ----- */

TipoLB* InicializaListaBroker() {

    TipoLB* lista_broker = (TipoLB*) malloc(sizeof (TipoLB));

    lista_broker->Primeiro = NULL;
    lista_broker->Ultimo = NULL;

    return lista_broker;

}

TipoB* InicializaTipoBroker(char* nome) {

    TipoB* broker = (TipoB*) malloc(sizeof (TipoB));

    broker->nome = (char*) malloc(sizeof (char)*strlen(nome) + 1);

    broker->lista_clientes = InicializaListaCliente();

    broker->lista_vizinhos = InicializaListaVizinho();
    
    broker->vizinhos_visitados = 0;

    broker->clientes_visitados = 0;

    strcpy(broker->nome, nome);

    return broker;

}

void CriaBroker(TipoB* broker, TipoLB* lista_broker) {

    CelulaB* novo_broker = NULL;
    novo_broker = (CelulaB*) malloc(sizeof (CelulaB));

    if (lista_broker->Primeiro == NULL) {

        lista_broker->Primeiro = lista_broker->Ultimo = novo_broker;
        lista_broker->Primeiro->Prox = NULL;
        lista_broker->Primeiro->Ant = NULL;
        lista_broker->Ultimo->Prox = NULL;
        lista_broker->Ultimo->Ant = NULL;

    } else {

        lista_broker->Ultimo->Prox = novo_broker;
        lista_broker->Ultimo->Prox->Ant = lista_broker->Ultimo;
        lista_broker->Ultimo = lista_broker->Ultimo->Prox;
        lista_broker->Ultimo->Prox = NULL;

    }

    lista_broker->Ultimo->Broker = broker;

}

void ExcluiBroker(TipoLB* lista_broker, char* nome) {

    CelulaB* aux = NULL;
    aux = lista_broker->Primeiro;

    while (aux != NULL && strcmp(aux->Broker->nome, nome) != 0) {

        aux = aux->Prox;

    }

    if (aux == NULL) {

        return;

    }

    if (aux == lista_broker->Primeiro && aux == lista_broker->Ultimo) {

        lista_broker->Primeiro = NULL;
        lista_broker->Ultimo = NULL;

        free(aux->Broker->nome);
        LiberaListaCliente(aux->Broker->lista_clientes);
        LiberaListaVizinho(aux->Broker->lista_vizinhos);
        free(aux->Broker);
        free(aux);

        return;

    }

    if (aux == lista_broker->Primeiro) {

        lista_broker->Primeiro = lista_broker->Primeiro->Prox;
        lista_broker->Primeiro->Ant = NULL;

        free(aux->Broker->nome);
        LiberaListaCliente(aux->Broker->lista_clientes);
        LiberaListaVizinho(aux->Broker->lista_vizinhos);
        free(aux->Broker);
        free(aux);

        return;

    }

    if (aux == lista_broker->Ultimo) {

        lista_broker->Ultimo = lista_broker->Ultimo->Ant;
        lista_broker->Ultimo->Prox = NULL;

        free(aux->Broker->nome);
        LiberaListaCliente(aux->Broker->lista_clientes);
        LiberaListaVizinho(aux->Broker->lista_vizinhos);
        free(aux->Broker);
        free(aux);

        return;
        
    } else {

        aux->Prox->Ant = aux->Ant;
        aux->Ant->Prox = aux->Prox;

        free(aux->Broker->nome);
        LiberaListaCliente(aux->Broker->lista_clientes);
        LiberaListaVizinho(aux->Broker->lista_vizinhos);
        free(aux->Broker);
        free(aux);

        return;
        
    }

}

void ImprimeBroker(TipoLB* lista_broker, FILE* ArqSaida) {

    CelulaB* aux = NULL;
    aux = lista_broker->Primeiro;

    while (aux != NULL) {

        fprintf(ArqSaida, "BROKER %s", aux->Broker->nome);

        ImprimeVizinho(aux->Broker->lista_vizinhos, ArqSaida);
        ImprimeCliente(aux->Broker->lista_clientes, ArqSaida);

        fprintf(ArqSaida, "\n\n");

        aux = aux->Prox;

    }

}

void LiberaListaBroker(TipoLB* lista_broker) {

    CelulaB* aux = NULL;
    aux = lista_broker->Primeiro;

    if (aux == NULL) {

        free(lista_broker);
        return;

    }

    while (aux != lista_broker->Ultimo) {

        aux = aux->Prox;

        free(aux->Ant->Broker->nome);
        LiberaListaVizinho(aux->Ant->Broker->lista_vizinhos);
        LiberaListaCliente(aux->Ant->Broker->lista_clientes);
        free(aux->Ant->Broker);
        free(aux->Ant);

    }

    free(aux->Broker->nome);
    LiberaListaVizinho(aux->Broker->lista_vizinhos);
    LiberaListaCliente(aux->Broker->lista_clientes);
    free(aux->Broker);
    free(aux);

    free(lista_broker);

}

/* ----- Funções auxiliares abaixo ----- */

int VerificaExistenciaBroker(TipoLB* lista_brokers, char* nome_broker) {

    CelulaB* aux = NULL;
    aux = lista_brokers->Primeiro;

    int flag = 0;
    
    while (aux != NULL) {

        if (strcmp(aux->Broker->nome, nome_broker) == 0){
            
            flag = 1;
            return flag;
            
        }
            

        aux = aux->Prox;

    }

    return flag;

}

int VerificaExistenciaClienteBroker(TipoLB* lista_broker, char* nome_cliente) {

    CelulaB* aux = NULL;
    aux = lista_broker->Primeiro;

    int flag = 0;

    while (aux != NULL) {

        flag = VerificaExistenciaCliente(aux->Broker->lista_clientes, nome_cliente);

        if (flag)
            return 1;

        aux = aux->Prox;

    }

    return 0;

}

int VerificaExistenciaPubsubBroker(TipoLB* lista_broker, int id_pubsub) {

    CelulaB* aux = NULL;
    aux = lista_broker->Primeiro;

    int flag = 0;

    while (aux != NULL) {

        flag = VerificaExistenciaPubsubCliente(aux->Broker->lista_clientes, id_pubsub);

        if (flag)
            return 1;

        aux = aux->Prox;

    }

    return 0;

}

void AdicionaVizinhoBroker(TipoLB* lista_brokers, char* broker_destino, char* broker_origem) {

    if (strcmp(broker_destino, broker_origem) == 0)
        return;

    if (VerificaExistenciaBroker(lista_brokers, broker_destino) && VerificaExistenciaBroker(lista_brokers, broker_origem)) {

        CelulaB* broker_aux = NULL;
        broker_aux = lista_brokers->Primeiro;

        while (broker_aux != NULL) {

            if (strcmp(broker_aux->Broker->nome, broker_destino) == 0) {

                if (!VerificaExistenciaVizinho(broker_aux->Broker->lista_vizinhos, broker_origem)) {

                    TipoV* novo_vizinho_1 = NULL;
                    novo_vizinho_1 = InicializaTipoVizinho(broker_origem, lista_brokers);                                        

                    CriaVizinho(novo_vizinho_1, broker_aux->Broker->lista_vizinhos);

                }
            }

            broker_aux = broker_aux->Prox;

        }

        broker_aux = lista_brokers->Primeiro;

        while (broker_aux != NULL) {

            if (strcmp(broker_aux->Broker->nome, broker_origem) == 0) {

                if (!VerificaExistenciaVizinho(broker_aux->Broker->lista_vizinhos, broker_destino)) {

                    TipoV* novo_vizinho_2 = NULL;
                    novo_vizinho_2 = InicializaTipoVizinho(broker_destino, lista_brokers);

                    CriaVizinho(novo_vizinho_2, broker_aux->Broker->lista_vizinhos);

                    return;
                }

            }

            broker_aux = broker_aux->Prox;

        }

    }

}

void AdicionaClienteBroker(TipoLB* lista_brokers, char* nome_cliente, char pubsub, char* nome_broker) {

    if (!VerificaExistenciaClienteBroker(lista_brokers, nome_cliente)) {

        CelulaB* broker_aux = NULL;
        broker_aux = lista_brokers->Primeiro;

        while (broker_aux != NULL) {

            if (strcmp(broker_aux->Broker->nome, nome_broker) == 0) {

                if (pubsub == 'P') {

                    TipoLP* lista_publisher = NULL;
                    lista_publisher = InicializaListaPublisher();

                    TipoC* novo_cliente = NULL;
                    novo_cliente = InicializaTipoCliente(nome_cliente, nome_broker, lista_publisher, pubsub);

                    CriaCliente(novo_cliente, broker_aux->Broker->lista_clientes);

                    return;

                } else if (pubsub == 'S') {

                    TipoLS* lista_subscriber = NULL;
                    lista_subscriber = InicializaListaSubscriber();

                    TipoC* novo_cliente = NULL;
                    novo_cliente = InicializaTipoCliente(nome_cliente, nome_broker, lista_subscriber, pubsub);

                    CriaCliente(novo_cliente, broker_aux->Broker->lista_clientes);

                    return;

                } else if (pubsub != 'S' && pubsub != 'P')
                    return;

            }

            broker_aux = broker_aux->Prox;

        }

    }

}

void AdicionaPublicacaoBroker(TipoLB* lista_brokers, int id_pub, char* nome_cliente, char* topico, 
        char* mensagem) {

    CelulaB* broker_aux = NULL;
    broker_aux = lista_brokers->Primeiro;

    if (!VerificaExistenciaPubsubBroker(lista_brokers, id_pub)) {

        while (broker_aux != NULL) {

            if(AdicionaPublicacaoCliente(broker_aux->Broker->lista_clientes, id_pub, nome_cliente, topico, mensagem))                                               
                return;                    

            broker_aux = broker_aux->Prox;

        }

    }

}

void AdicionaSubscricaoBroker(TipoLB* lista_brokers, int id_sub, char* nome_cliente, char* topico) {

    CelulaB* broker_aux = NULL;
    broker_aux = lista_brokers->Primeiro;

    if (!VerificaExistenciaPubsubBroker(lista_brokers, id_sub)) {

        while (broker_aux != NULL) {

            if(VerificaSubscriberCliente(broker_aux->Broker->lista_clientes, nome_cliente)){                
                
                if(AdicionaSubscricaoCliente(broker_aux->Broker->lista_clientes, id_sub, nome_cliente, topico))               
                    return;
                
            }
            
            broker_aux = broker_aux->Prox;

        }

    }

}

void ExcluiVizinhoBroker(TipoLB* lista_brokers, char* broker_origem, char* broker_destino) {

    CelulaB* aux = NULL;
    aux = lista_brokers->Primeiro;

    while (aux != NULL) {

        if (strcmp(aux->Broker->nome, broker_destino) == 0) {

            if (VerificaExistenciaVizinho(aux->Broker->lista_vizinhos, broker_origem))
                ExcluiVizinhos(aux->Broker->lista_vizinhos, broker_origem);
            
        }
        
        if (strcmp(aux->Broker->nome, broker_origem) == 0) {

            if (VerificaExistenciaVizinho(aux->Broker->lista_vizinhos, broker_destino))
                ExcluiVizinhos(aux->Broker->lista_vizinhos, broker_destino);

        }

        aux = aux->Prox;
    }

}

void ExcluiVizinhoBrokerUnico(TipoLB* lista_brokers, char* broker_origem) {

    CelulaB* aux = NULL;
    aux = lista_brokers->Primeiro;

    while (aux != NULL) {

        if (VerificaExistenciaVizinho(aux->Broker->lista_vizinhos, broker_origem))
        ExcluiVizinhoU(aux->Broker->lista_vizinhos, broker_origem);

        aux = aux->Prox;

    }

}

void ExcluiClienteBroker(TipoLB* lista_brokers, char* nome_cliente) {

    CelulaB* aux = NULL;
    aux = lista_brokers->Primeiro;

    int flag = 0;

    while (aux != NULL) {

        flag = ExcluiCliente(aux->Broker->lista_clientes, nome_cliente);

        if (flag)
            return;

        aux = aux->Prox;

    }

}

void ExcluiSubscricaoBroker(TipoLB* lista_brokers, int id_sub) {

    CelulaB* aux = NULL;
    aux = lista_brokers->Primeiro;

    int flag = 0;

    while (aux != NULL) {

        flag = ExcluiSubscriberCliente(aux->Broker->lista_clientes, id_sub);

        if (flag)
            return;

        aux = aux->Prox;

    }

}

TipoB* PesquisaBroker(char* broker, TipoLB* lista_broker) {

    CelulaB* aux = NULL;
    aux = lista_broker->Primeiro;

    while (aux != NULL && strcmp(aux->Broker->nome, broker) != 0) {

        aux = aux->Prox;

    }

    return aux->Broker;

}

/* ----- Funções do matching ----- */

TipoLV* RtnListaVizinhos(TipoB* broker) {

    return broker->lista_vizinhos;

}

TipoLC* RtnListaClientes(TipoB* broker) {

    return broker->lista_clientes;

}

int RtnVizinhosVisitado(TipoB* broker) {

    return broker->vizinhos_visitados;

}

int RtnClientesVisitado(TipoB* broker) {

    return broker->clientes_visitados;;

}

void AlteraVizinhosVisitadosBroker(TipoB* broker, int visitado) {

    broker->vizinhos_visitados = visitado;

}

void AlteraClientesVisitadosBroker(TipoB* broker, int visitado) {

    broker->clientes_visitados = visitado;

}

void ResetaBrokers(TipoLB* lista_brokers){
  
    CelulaB* aux = NULL;
    aux = lista_brokers->Primeiro;
    
    while(aux != NULL){
        
        aux->Broker->clientes_visitados = 0;
        aux->Broker->vizinhos_visitados = 0;
        
        aux = aux->Prox;
    }
    
}

void PesquisaSubscriberBroker(TipoLB* lista_broker, int flag){
    
    CelulaB* aux = NULL;
    aux = lista_broker->Primeiro;
    
    while(aux != NULL){
        
        PesquisaSubscriberCliente(aux->Broker->lista_clientes, aux->Broker->lista_vizinhos, lista_broker, aux->Broker, flag);
    
        aux = aux->Prox;
        
    }
}

void VerificaMatchingBroker(TipoLB* lista_brokers, FILE * ArqSaida){
    
    CelulaB* aux = NULL;
    aux = lista_brokers->Primeiro;
    
    while(aux != NULL){
        
        VerificaMatchingClientes(aux->Broker->lista_clientes, ArqSaida);
        
        aux = aux->Prox;
    }
    
}