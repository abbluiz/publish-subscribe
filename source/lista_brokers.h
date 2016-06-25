#ifndef LISTA_BROKERS_H
#define LISTA_BROKERS_H

#include "lista_vizinhos.h"
#include "lista_clientes.h"

/* ----- typedef das structs abaixo ----- */

typedef struct tipobroker TipoB;
typedef struct tipolistabroker TipoLB;

typedef struct tipocliente TipoC;
typedef struct tipolistacliente TipoLC;

/* ----- Funções elementares abaixo ----- */
    
/* Inicializa o sentinela da lista de brokers
 * inputs: nenhum
 * output: sentinela da lista de brokers inicializado
 * pre-condicao: nenhuma
 * pos-condicao: sentinela da lista de brokers de retorno existe e os campos primeiro e ultimo 
 apontam para NULL
 */    
TipoLB* InicializaListaBroker();

/* Inicializa o tipo broker
 * inputs: nome do broker
 * output: tipo broker inicializado
 * pre-condicao: nenhuma
 * pos-condicao: tipo broker de retorno existe e os campos são devidamente inicializados
 */
TipoB* InicializaTipoBroker(char* nome);
    
/* Insere um broker na lista de brokers
 * inputs: tipo broker a ser inserido e lista na qual será inserido
 * output: nenhum
 * pre-condicao: nenhuma
 * pos-condicao: broker é inserido corretamente no final da lista de brokers
 */
void CriaBroker(TipoB* broker, TipoLB* lista_broker);

/* Retira um broker da lista de brokers
 * inputs: lista de brokers e nome do broker a ser retirado
 * output: nenhum
 * pre-condicao: nenhuma
 * pos-condicao: broker com nome especificado é retirado da lista de brokers
 */
void ExcluiBroker(TipoLB* lista_broker, char* nome);

/* Imprime toda a rede de brokers representada na lista de brokers no arquivo de saída
 * inputs: lista de brokers e arquivo de saída
 * output: nenhum
 * pre-condicao: arquivo de saída válido
 * pos-condicao: toda a rede de brokers é impressa no arquivo de saída
 */
void ImprimeBroker(TipoLB* lista_broker, FILE* ArqSaida);

/* Libera toda memória alocada pela rede de brokers
 * inputs: lista de brokers
 * output: nenhum
 * pre-condicao: nenhuma
 * pos-condicao: toda memória alocada pelo programa quando diz respeito aos brokers e sua rede é 
 desalocada
 */
void LiberaListaBroker(TipoLB* lista_broker);

/* ----- Funções auxiliares abaixo ----- */

/* Percorre a lista de brokers para verificar a existência de um broker de nome específico
 * inputs: lista de brokers e nome do broker a ser verificado
 * output: 1 para broker já existente e 0 para broker não existente
 * pre-condicao: nenhuma
 * pos-condicao: valores 1 ou 0 retornados de acordo com a existência do broker
 */
int VerificaExistenciaBroker(TipoLB* lista_brokers, char* nome_broker);

/* Percorre a lista de brokers, cada cliente e cada subscrição ou publicação para verificar a existência 
 de um ou outro
 * inputs: lista de brokers e a id da publicação ou subscrição
 * output: 1 para publicação/subscrição já existente e 0 para não existente
 * pre-condicao: nenhuma
 * pos-condicao: valores 1 ou 0 retornados de acordo com a existência da publicação/subscrição
 */
int VerificaExistenciaPubsubBroker(TipoLB* lista_broker, int id_pubsub);

/* Função auxiliar necessária para a criação de uma vizinhança, chamando a função correspondente
  implementada em lista_vizinhos.c
 * inputs: lista de brokers, nome do broker de destino e nome do broker de origem
 * output: nenhum
 * pre-condicao: nenhum
 * pos-condicao: existência dos brokers é verificada, existência da vizinhança é verificada e caso 
 brokers existam e vizinhança não as funções para criar a vizinhança são chamadas corretamente
 */
void AdicionaVizinhoBroker(TipoLB* lista_brokers, char* broker_destino, char* broker_origem);

/* Função auxiliar necessária para a criação de um cliente, chamando a função correspondente
  implementada em lista_clientes.c
 * inputs: lista de brokers, nome do cliente a ser criado, caractere que identifica se é publisher ou
 subscriber e nome do broker no qual o cliente pertence
 * output: nenhum
 * pre-condicao: nenhuma
 * pos-condicao: existência do broker é verificada, existência do cliente é verificada e caso 
 broker exista e cliente não as funções para criar o cliente são chamadas corretamente
 */
void AdicionaClienteBroker(TipoLB* lista_brokers, char* nome_cliente, char pubsub, char* nome_broker);

/* Função auxiliar necessária para a criação de uma publicação, chamando a função correspondente
  implementada em lista_clientes.c
 * inputs: lista de brokers, id da publicação, nome do cliente na qual ela pertence, tópico da
 mensagem e a mensagem publicada
 * output: nenhum
 * pre-condicao: nenhuma
 * pos-condicao: existência do broker, cliente e publicação são verificadas e caso broker exista e 
 cliente exista e publicação não as funções para criar a publicação são chamadas corretamente
 */
void AdicionaPublicacaoBroker(TipoLB* lista_brokers, int id_pub, char* nome_cliente, char* topico, 
        char* mensagem);

/* Função auxiliar necessária para a criação de uma subscrição, chamando a função correspondente
  implementada em lista_clientes.c
 * inputs: lista de brokers, id da subscrição, nome do cliente na qual ela pertence e tópico
 * output: nenhum
 * pre-condicao: nenhuma
 * pos-condicao: existência do broker, cliente e subscrição são verificadas e caso broker exista e 
 cliente exista e subscrição não as funções para criar a subscrição são chamadas corretamente
 */
void AdicionaSubscricaoBroker(TipoLB* lista_brokers, int id_sub, char* nome_cliente, char* topico);

/* Função auxiliar necessária para o cancelamento de vizinhança, chamando a função correspondente
  implementada em lista_vizinhos.c
 * inputs: lista de brokers, nome do broker de origem e nome do broker de destino
 * output: nenhum
 * pre-condicao: nenhuma
 * pos-condicao: existência de ambos os vizinhos é verificada, caso exista o programa chama as
 funções necessárias para cancelar a vizinhança
 */
void ExcluiVizinhoBroker(TipoLB* lista_brokers, char* broker_origem, char* broker_destino);

/* Função auxiliar necessária para o cancelamento de vizinhança caso um broker seja excluído, 
 chamando a função correspondente implementada em lista_vizinhos.c
 * inputs: lista de brokers, nome do broker de origem
 * output: nenhum
 * pre-condicao: nenhuma
 * pos-condicao: existência do vizinho é verificada, caso exista o programa chama as funções 
 necessárias para cancelar a vizinhança
 */
void ExcluiVizinhoBrokerUnico(TipoLB* lista_brokers, char* broker_origem);

/* Função auxiliar necessária para excluir um cliente, chamando a função correspondente
  implementada em lista_clientes.c
 * inputs: lista de brokers e nome do cliente a ser excluído
 * output: nenhum
 * pre-condicao: nenhuma
 * pos-condicao: caso o cliente exista o programa chama as funções necessárias para excluir o
 cliente
 */
void ExcluiClienteBroker(TipoLB* lista_brokers, char* nome_cliente);

/* Função auxiliar necessária para o cancelamento de subscrição, chamando a função correspondente
  implementada em lista_clientes.c
 * inputs: lista de brokers e id da subscrição a ser excluída
 * output: nenhum
 * pre-condicao: nenhuma
 * pos-condicao: percorre os brokers chamando a função implementada em lista_clientes.c
 */
void ExcluiSubscricaoBroker(TipoLB* lista_brokers, int id_sub);

/* Função auxiliar para pesquisar e retornar um broker específico
 * inputs: lista de brokers e nome do broker a ser pesquisado
 * output: tipo broker a ser pesquisado ou tipo broker NULL caso não exista
 * pre-condicao: nenhuma
 * pos-condicao: tipo broker é retornado caso encontrado ou NULL caso não exista
 */
TipoB* PesquisaBroker(char* broker, TipoLB* lista_broker);

/* ----- Funções do matching ----- */

/* Função auxiliar que retorna a lista de vizinhos de um broker
 * inputs: tipo broker
 * output: lista de vizinhos do broker
 * pre-condicao: nenhuma
 * pos-condicao: lista de vizinhos é retornada
 */
TipoLV* RtnListaVizinhos(TipoB* broker);

/* Função auxiliar que retorna a lista de clientes de um broker
 * inputs: tipo broker
 * output: lista de clientes do broker
 * pre-condicao: nenhuma
 * pos-condicao: lista de clientes é retornada
 */
TipoLC* RtnListaClientes(TipoB* broker);

/* Função auxiliar que retorna o inteiro do broker vizinhos_visitados
 * inputs: tipo broker
 * output: inteiro do broker vizinhos_visitados
 * pre-condicao: nenhuma
 * pos-condicao: inteiro é retornado corretamente
 */
int RtnVizinhosVisitado(TipoB* broker);

/* Função auxiliar que retorna o inteiro do broker clientes_visitados
 * inputs: tipo broker
 * output: inteiro do broker clientes_visitados
 * pre-condicao: nenhuma
 * pos-condicao: inteiro é retornado corretamente
 */
int RtnClientesVisitado(TipoB* broker);

/* Função auxiliar que altera o inteiro do broker vizinhos_visitados
 * inputs: tipo broker e valor do inteiro
 * output: inteiro do broker vizinhos_visitados
 * pre-condicao: nenhuma
 * pos-condicao: inteiro é modificado corretamente com o valor passado
 */
void AlteraVizinhosVisitadosBroker(TipoB* broker, int visitado);

/* Função auxiliar que altera o inteiro do broker clientes_visitados
 * inputs: tipo broker e valor do inteiro
 * output: inteiro do broker clientes_visitados
 * pre-condicao: nenhuma
 * pos-condicao: inteiro é modificado corretamente com o valor passado
 */
void AlteraClientesVisitadosBroker(TipoB* broker, int visitado);

/* Função auxiliar que altera os campos vizinhos_visitados e clientes_visitados para 0
 * inputs: lista de brokers
 * output: nenhum
 * pre-condicao: nenhuma
 * pos-condicao: campos vizinhos_visitados e clientes_visitados todos os brokers da lista são resetados
 */
void ResetaBrokers(TipoLB* lista_brokers);

/* Função auxiliar necessária para a impressão do matching, chamando a função correspondente
  implementada em lista_clientes.c
 * inputs: lista de brokers e arquivo de saída
 * output: nenhum
 * pre-condicao: nenhuma
 * pos-condicao: percorre os brokers chamando a função implementada em lista_clientes.c
 */
void VerificaMatchingBroker(TipoLB* lista_brokers, FILE* ArqSaida);

/* Função auxiliar necessária para pesquisar o subcriber, chamando a função correspondente
  implementada em lista_clientes.c
 * inputs: lista de brokers e inteiro flag
 * output: nenhum
 * pre-condicao: nenhuma
 * pos-condicao: percorre os brokers chamando a função implementada em lista_clientes.c e passa o
 flag para a próxima função
 */
void PesquisaSubscriberBroker(TipoLB* lista_broker, int flag);

#endif	/* LISTA_BROKERS_H */