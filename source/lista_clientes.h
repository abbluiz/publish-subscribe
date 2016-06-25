#ifndef LISTA_CLIENTES_H
#define LISTA_CLIENTES_H

#include "lista_subscriber.h"

typedef struct tipocliente TipoC;
typedef struct tipolistacliente TipoLC;

/* ----- Funções elementares abaixo ----- */
    
/* Inicializa o sentinela da lista de clientes
 * inputs: nenhum
 * output: sentinela da lista de clientes inicializada
 * pre-condicao: nenhuma
 * pos-condicao: sentinela da lista de clientes de retorno existe e os campos primeiro e ultimo 
 apontam para NULL
 */
TipoLC* InicializaListaCliente();

/* Inicializa o tipo cliente
 * inputs: nome do cliente, nome do broker no qual pertence, lista de publicações ou subscrições e
 caractere identificador de Publisher / Subscriber
 * output: tipo cliente inicializado
 * pre-condicao: nenhuma
 * pos-condicao: tipo cliente de retorno existe e os campos são devidamente inicializados
 */
TipoC* InicializaTipoCliente(char* nome, char* broker, void* Lpubsub, char pubsub);
    
/* Insere um cliente na lista de clientes
 * inputs: tipo cliente a ser inserido e lista na qual será inserido
 * output: nenhum
 * pre-condicao: nenhuma
 * pos-condicao: cliente é inserido corretamente no final da lista de clientes
 */
void CriaCliente(TipoC* cliente, TipoLC* lista_clientes);

/* Retira um cliente da lista de cliente e todas as listas ligadas a ele
 * inputs: lista de clientes e nome do cliente a ser retirado
 * output: nenhum
 * pre-condicao: nenhuma
 * pos-condicao: cliente com nome especificado é retirado da lista de clientes
 */
int ExcluiCliente(TipoLC* lista_clientes, char* nome);

/* Imprime toda a lista de clientes e listas ligadas a eles no arquivo de saída
 * inputs: lista de clientes e arquivo de saída
 * output: nenhum
 * pre-condicao: arquivo de saída válido
 * pos-condicao: toda a lista de clientes é impressa no arquivo de saída
 */
void ImprimeCliente(TipoLC* lista_cliente, FILE* ArqSaida);

/* Libera toda memória alocada pela lista de clientes
 * inputs: lista de clientes
 * output: nenhum
 * pre-condicao: nenhuma
 * pos-condicao: toda memória alocada pela lista de clientes é desalocada
 */
void LiberaListaCliente(TipoLC* lista_clientes) ;

/* ----- Funções auxiliares abaixo ----- */

/* Função auxiliar para pesquisar e retornar um cliente específico
 * inputs: lista de clientes e nome do cliente a ser pesquisado
 * output: tipo cliente a ser pesquisado ou tipo cliente NULL caso não exista
 * pre-condicao: nenhuma
 * pos-condicao: tipo cliente é retornado caso encontrado ou NULL caso não exista
 */
TipoC* PesquisaCliente(char* nome_cliente, TipoLC* lista_cliente);

/* Função auxiliar necessária para a criação de uma subscrição, chamando a função elementar
  implementada em lista_subscriber.c
 * inputs: lista de clientes, id da subscrição, nome do cliente na qual ela pertence e tópico
 * output: nenhum
 * pre-condicao: nenhuma
 * pos-condicao: a lista de clientes é percorrida até que o Subscriber correto é encontrado e tipo 
 subscriber é inicializado e criado com funções elementares do TAD subscriber na lista encontrada
 */
int AdicionaSubscricaoCliente(TipoLC* lista_clientes, int id_sub, char* nome_cliente, char* topico);

/* Função auxiliar necessária para a criação de uma publicação, chamando a função elementar
  implementada em lista_publisher.c
 * inputs: lista de clientes, id da publicação, nome do cliente na qual ela pertence, tópico e mensagem
 * output: nenhum
 * pre-condicao: nenhuma
 * pos-condicao: a lista de clientes é percorrida até que o Publisher correto é encontrado e tipo 
 publisher é inicializado e criado com funções elementares do TAD publisher na lista encontrada
 */
int AdicionaPublicacaoCliente(TipoLC* lista_clientes, int id_pub, char* nome_cliente, char* topico, char* mensagem);

/* Percorre a lista de clientes para verificar a existência do mesmo
 * inputs: lista de clientes e o nome do cliente
 * output: 1 para Subscriber já existente e 0 para não existente
 * pre-condicao: nenhuma
 * pos-condicao: valores 1 ou 0 retornados de acordo com a existência do Subscriber
 */
int VerificaSubscriberCliente(TipoLC* lista_clientes, char* nome_cliente);

/* Percorre a lista de clientes para verificar a existência de um cliente de nome específico
 * inputs: lista de clientes e nome do cliente a ser verificado
 * output: 1 para cliente já existente e 0 para cliente não existente
 * pre-condicao: nenhuma
 * pos-condicao: valores 1 ou 0 retornados de acordo com a existência do cliente
 */
int VerificaExistenciaCliente(TipoLC* lista_clientes, char* nome_cliente);

/* Percorre a lista de clientes e cada subscrição ou publicação para verificar a existência 
 de um ou outro
 * inputs: lista de clientes e a id da publicação ou subscrição
 * output: 1 para publicação/subscrição já existente e 0 para não existente
 * pre-condicao: nenhuma
 * pos-condicao: valores 1 ou 0 retornados de acordo com a existência da publicação/subscrição
 */
int VerificaExistenciaPubsubCliente(TipoLC* lista_clientes, int id_pubsub);

/* Função auxiliar necessária para o cancelamento de subscrição, chamando a função correspondente
  implementada em lista_subscriber.c
 * inputs: lista de clientes e id da subscrição a ser excluída
 * output: nenhum
 * pre-condicao: nenhuma
 * pos-condicao: percorre os clientes chamando a função implementada em lista_subscriber.c
 */
int ExcluiSubscriberCliente(TipoLC* lista_clientes, int id_sub);

/* ----- Funções do matching abaixo ----- */

/* Pesquisa na lista de clientes as subscrições para a impressão no arquivo de saída
 * inputs: lista de clientes do broker e o arquivo de saída
 * output: nenhum
 * pre-condicao: nenhum
 * pos-condicao: percorre o cliente, caso tenha uma subscrição, imprime o nome do cliente do arquivo
 * de saída e chama a função implementada no arquivo no lista_subscriber.c
 */
void VerificaMatchingClientes(TipoLC* lista_clientes, FILE* ArqSaida);

/* Função auxiliar que pesquisa na lista de cliente e caso ache uma subscrição, chama função 
 * implementada em lista_subscriber.h
 * inputs: lista de clientes do broker, lista de vizinhos, lista de brokers, broker e a flag
 * output: nenhum
 * pre-condicao: nenhum
 * pos-condicao: percorre o cliente, caso tenha uma subscrição, chama a função implementada no 
 * arquivo no lista_subscriber.c
 */
void PesquisaSubscriberCliente(TipoLC* lista_clientes, TipoLV* lista_vizinhos, TipoLB* lista_brokers, TipoB* broker, int flag);

/* Função auxiliar que percorre a lista de clientes chamando uma função implementada em 
 * lista_publisher.c 
 * inputs: lista de clientes do broker, o subscriber e o tópico a ser pesquisado
 * output: nenhum
 * pre-condicao: nenhum
 * pos-condicao: percorre a lista de cliente, e a cada cliente chama uma função implementada em
 * lista_publisher.c
 */
void PesquisaVizinhoCliente(TipoLC* lista_cliente, TipoS* subscriber, char * topico);

#endif	/* LISTA_CLIENTES_H */