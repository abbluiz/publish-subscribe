#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "comandos.h"

void Manipulador(int qtd_parametros, char* entrada, char* saida) {

    if(qtd_parametros < 3) { // Verifica se foi passada a quantidade correta de parâmetros na execução do programa
        
        printf("\n\t> Erro: necessario passar como parametro os arquivos de entrada e saida!\n");
        return;
        
    }
    
    TipoLB* lista_brokers = NULL;
    lista_brokers = InicializaListaBroker();

    char comando[101] = "\0";
    FILE * ArqEntrada = fopen(entrada, "r");
    FILE * ArqSaida = fopen(saida, "w");

    if (!ArqEntrada)
        printf("\n\t> Erro ao abrir arquivo de entrada!\n");
    else if (!ArqSaida)
        printf("\n\t> Erro ao abrir arquivo de saida!\n");
    else {
        
        printf("| Programa iniciado |\n");

        while (!feof(ArqEntrada)) { // Lê os comandos do arquivo de entrada até o mesmo acabar

            fscanf(ArqEntrada, "%s", comando);

            if (strcmp(comando, "FIM") == 0) // Para de ler quando detecta o comando FIM
                break;

            VerificaComando(lista_brokers, comando, ArqEntrada, ArqSaida); // Trata corretamente cada comando
            
            if (strcmp(comando, "ERRO") == 0) // Verifica se foi utilizado um comando invalido
                break;

        }

        fclose(ArqEntrada);
        fclose(ArqSaida);

    }

    FIM(lista_brokers);
    
    printf("\n| Programa finalizado |\n");

}

void VerificaComando(TipoLB* lista_brokers, char* comando, FILE* ArqEntrada, FILE* ArqSaida) {

    if (strcmp(comando, "CRIABROKER") == 0) {

        char nome_broker[1001] = "\0";

        fscanf(ArqEntrada, " %[^\n]\n", nome_broker);

        CRIABROKER(lista_brokers, nome_broker);

        return;

    } else  if (strcmp(comando, "INSEREVIZINHO") == 0) {

        char broker_destino[1001];
        char broker_origem[1001];

        fscanf(ArqEntrada, " %s %[^\n]\n", broker_destino, broker_origem);

        INSEREVIZINHO(lista_brokers, broker_destino, broker_origem);

        return;

    } else if (strcmp(comando, "CRIACLIENTE") == 0) {

        char nome_cliente[1001];
        char pubsub;
        char nome_broker[1001];

        fscanf(ArqEntrada, " %s %c %[^\n]\n", nome_cliente, &pubsub, nome_broker);

        CRIACLIENTE(lista_brokers, nome_cliente, pubsub, nome_broker);

        return;

    } else if (strcmp(comando, "IMPRIMEREDE") == 0) {

        IMPRIMEREDE(lista_brokers, ArqSaida);

        return;

    } else  if (strcmp(comando, "PUBLICA") == 0) {

        int id_pub = 0;
        char nome_cliente[1001];
        char topico[1001];
        char mensagem[1001];

        fscanf(ArqEntrada, " %d %s %s %[^\n]\n", &id_pub, nome_cliente, topico, mensagem);

        PUBLICA(lista_brokers, id_pub, nome_cliente, topico, mensagem);

        return;

    } else if (strcmp(comando, "SUBSCREVE") == 0) {

        int id_sub = 0;
        char nome_cliente[1001];
        char topico[1001];

        fscanf(ArqEntrada, " %d %s %[^\n]\n", &id_sub, nome_cliente, topico);

        SUBSCREVE(lista_brokers, id_sub, nome_cliente, topico);

        return;

    } else if (strcmp(comando, "EXCLUIBROKER") == 0) {

        char nome_broker[1001];

        fscanf(ArqEntrada, " %[^\n]\n", nome_broker);

        EXCLUIBROKER(lista_brokers, nome_broker);

        return;

    } else if (strcmp(comando, "CANCELAVIZINHO") == 0) {

        char broker_origem[1001];
        char broker_destino[1001];

        fscanf(ArqEntrada, "%s %[^\n]\n", broker_origem, broker_destino);

        CANCELAVIZINHO(lista_brokers, broker_origem, broker_destino);

        return;

    } else if (strcmp(comando, "EXCLUICLIENTE") == 0) {

        char nome_cliente[1001];

        fscanf(ArqEntrada, " %[^\n]\n", nome_cliente);

        EXCLUICLIENTE(lista_brokers, nome_cliente);

        return;

    } else if (strcmp(comando, "EXCLUISUBSCRICAO") == 0) {

        int id_sub;

        fscanf(ArqEntrada, " %d[^\n]\n", &id_sub);

        EXCLUISUBSCRICAO(lista_brokers, id_sub);

        return;

    } else if (strcmp(comando, "VERIFICAMATCHING") == 0) {

        VERIFICAMATCHING(lista_brokers, ArqSaida);

        return;

    } else { // Verifica se foi utilizado um comando invalido
        
        comando = "ERRO";
        printf("\n\t> Erro: arquivo de entrada possui comandos invalidos ou nao possui comandos!\n");
        
        return;
        
    }

}

/* ----- Funções referentes aos comandos dos arquivos de entrada ----- */

void CRIABROKER(TipoLB* lista_brokers, char* nome_broker) {

    if (!VerificaExistenciaBroker(lista_brokers, nome_broker)) {

        TipoB* novo_broker = NULL;
        novo_broker = InicializaTipoBroker(nome_broker);

        CriaBroker(novo_broker, lista_brokers);

        return;

    }

}

void INSEREVIZINHO(TipoLB* lista_brokers, char* broker_destino, char* broker_origem) {

    AdicionaVizinhoBroker(lista_brokers, broker_destino, broker_origem);

}

void CRIACLIENTE(TipoLB* lista_brokers, char* nome_cliente, char pubsub, char* nome_broker) {

    AdicionaClienteBroker(lista_brokers, nome_cliente, pubsub, nome_broker);

}

void IMPRIMEREDE(TipoLB* lista_broker, FILE* ArqSaida) {

    fprintf(ArqSaida, "IMPRIMEREDE\n\n");

    ImprimeBroker(lista_broker, ArqSaida);

}

void PUBLICA(TipoLB* lista_brokers, int id_pub, char* nome_cliente, char* topico, char* mensagem) {

    AdicionaPublicacaoBroker(lista_brokers, id_pub, nome_cliente, topico, mensagem);

}

void SUBSCREVE(TipoLB* lista_brokers, int id_sub, char* nome_cliente, char* topico) {

    AdicionaSubscricaoBroker(lista_brokers, id_sub, nome_cliente, topico);

}

void EXCLUIBROKER(TipoLB* lista_brokers, char* nome_broker) {

    ExcluiVizinhoBrokerUnico(lista_brokers, nome_broker);
    ExcluiBroker(lista_brokers, nome_broker);

}

void CANCELAVIZINHO(TipoLB* lista_brokers, char* broker_origem, char* broker_destino) {

    ExcluiVizinhoBroker(lista_brokers, broker_origem, broker_destino);

}

void EXCLUICLIENTE(TipoLB* lista_brokers, char* nome_cliente) {

    ExcluiClienteBroker(lista_brokers, nome_cliente);

}

void EXCLUISUBSCRICAO(TipoLB* lista_brokers, int id_sub) {

    ExcluiSubscricaoBroker(lista_brokers, id_sub);

}

void VERIFICAMATCHING(TipoLB* lista_brokers, FILE* ArqSaida) {

    fprintf(ArqSaida, "VERIFICACAO MATCHING\n\n");
    PesquisaSubscriberBroker(lista_brokers, 1);
    VerificaMatchingBroker(lista_brokers, ArqSaida);
    PesquisaSubscriberBroker(lista_brokers, 0);

}

void FIM(TipoLB* lista_brokers) {

    LiberaListaBroker(lista_brokers);

}