#ifndef LISTA_PUBLISHER_H
#define	LISTA_PUBLISHER_H

#include "lista_publisher.h"
#include "lista_subscriber.h"

typedef struct tipopublisher TipoP;
typedef struct tipolistapublisher TipoLP;

/* ----- Funções elementares abaixo ----- */

/* Inicializa o sentinela da lista de publicações
 * inputs: nenhum
 * output: sentinela da lista de publicações inicializada
 * pre-condicao: nenhuma
 * pos-condicao: sentinela da lista de publicações de retorno existe e os campos primeiro e ultimo 
 apontam para NULL
 */
TipoLP* InicializaListaPublisher();

/* Inicializa o tipo pub
 * inputs: inteiro de identificação da publicação, tópico, conteúdo e nome do Publisher a qual
 pertence
 * output: tipo pub inicializado
 * pre-condicao: nenhuma
 * pos-condicao: tipo pub de retorno existe e os campos são devidamente inicializados
 */
TipoP* InicializaTipoPublisher(int id_pub, char* topico, char* conteudo, char* cliente);

/* Insere uma publicação na lista de publicações
 * inputs: tipo pub a ser inserido e lista na qual será inserido
 * output: nenhum
 * pre-condicao: nenhuma
 * pos-condicao: publicação é inserida corretamente no final da lista de publicações
 */ 
void CriaPublisher(TipoP* publisher, TipoLP* lista_publisher);

/* Imprime toda a lista de publicações no arquivo de saída
 * inputs: lista de publicações e arquivo de saída
 * output: nenhum
 * pre-condicao: arquivo de saída válido
 * pos-condicao: toda a lista de publicações é impressa no arquivo de saída
 */
void ImprimePublisher(TipoLP* lista_publisher, FILE* ArqSaida);

/* Libera toda memória alocada pela lista de publicações
 * inputs: lista de publicações
 * output: nenhum
 * pre-condicao: nenhuma
 * pos-condicao: toda memória alocada pela lista de publicações é desalocada
 */
void LiberaListaPublisher(TipoLP* lista_publisher);

/* ----- Funções auxiliares abaixo ----- */

/* Percorre a lista de publicações para verificar a existência de uma publicação com id específico
 * inputs: lista de publicações e id da publicação a ser verificada
 * output: 1 para publicação já existente e 0 para publicação não existente
 * pre-condicao: nenhuma
 * pos-condicao: valores 1 ou 0 retornados de acordo com a existência da publicação
 */
int VerificaExistenciaPublicacao(TipoLP* lista_publisher, int id_pub);

/* Função auxiliar para pesquisar e retornar uma publicação específica
 * inputs: lista de publicações e id da publicação a ser pesquisada
 * output: tipo pub a ser pesquisado ou tipo pub NULL caso não exista
 * pre-condicao: nenhuma
 * pos-condicao: tipo pub é retornado caso encontrado ou NULL caso não exista
 */
TipoP* PesquisaPublicacao(int id_pub, TipoLP* lista_publisher);

/* ----- Funções do matching abaixo ----- */

/* Função que cria um conteúdo caso ocorra um matching entre a subscrição e alguma publicação
 * inputs: lista de publicações, subscriber para onde será copiado o conteúdo
 e o tópico
 * output: nenhuma
 * pre-condicao: nenhuma
 * pos-condicao: caso o tópico da subscrição seja o mesmo da publicação e a publicação
 já não exista na subscrição, é criado um conteúdo com a mensagem publicada
 */
void PesquisaVizinhoPublisher(TipoLP* lista_publisher, TipoS* subscriber, char * topico);

#endif	/* LISTA_PUBLISHER_H */