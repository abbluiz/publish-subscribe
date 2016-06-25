#ifndef LISTA_SUBSCRIBER_H
#define	LISTA_SUBSCRIBER_H

#include "lista_brokers.h"
#include "lista_vizinhos.h"

typedef struct tipoconteudo TipoCT;
typedef struct tipolistaconteudo TipoLCT;

typedef struct tiposubscriber TipoS;
typedef struct tipolistasubscriber TipoLS;

typedef struct tipovizinho TipoV;
typedef struct tipolistavizinho TipoLV;

typedef struct tipobroker TipoB;
typedef struct tipolistabroker TipoLB;
    
/* Inicializa o sentinela da lista de subscrições
 * inputs: nenhum
 * output: sentinela da lista de subscrições inicializada
 * pre-condicao: nenhuma
 * pos-condicao: sentinela da lista de subscrições de retorno existe e os campos primeiro e ultimo 
 apontam para NULL
 */  
TipoLS* InicializaListaSubscriber();

/* Inicializa a struct do tipo sub e seu conteúdo
 * inputs: id da subscrição, tópico de publicação e nome do cliente
 * output: tipo sub inicializado
 * pre-condicao: nenhum
 * pos-condicao: tipo estruturado de retorno existe e os campos estão incializados e vazios
 */
TipoS* InicializaTipoSubscriber(int id_sub, char* topico, char* cliente);

/* Adiciona uma subscrição em uma determinada lista de subscrições
 * inputs: subscrição nova e lista de subscrições na qual a subscrição será inserida
 * output: nenhum
 * pre-condicao: nenhum
 * pos-condicao: subscrição é inserida no final da lista desejada
 */
void CriaSubscriber(TipoS* subscriber, TipoLS* lista_subscriber);

/* Retira uma subscrição de uma determinada lista de subscrições
 * inputs: lista de subscrições da qual a subscrição será excluída
 * output: nenhum
 * pre-condicao: nenhum
 * pos-condicao: subscrição é retirada da lista desejada
 */
int ExcluiSubscriber(TipoLS* lista_subscriber, int id_sub);

/* Desaloca toda a memória ocupada  pela lista de subscrições desejada e todo seu conteúdo
 * inputs: lista de subscrições que será desalocada
 * output: nenhum
 * pre-condicao: nenhum
 * pos-condicao: lista passada é desalocada, junto com todo seu conteúdo
 */
void LiberaListaSubscriber(TipoLS* lista_subscriber);

/* Imprime todas as subscrições de determinada lista de subscrições
 * inputs: lista de subscrições em questão
 * output: nenhum
 * pre-condicao: nenhum
 * pos-condicao: todos as subscrições da lista serão impressas
 */
void ImprimeSubscriber(TipoLS* lista_subscriber, FILE* ArqSaida);

/* ----- Funções auxiliares ----- */

/* Inicializa a sentinela da lista tipo conteudo
 * inputs: nenhum
 * output: lista de conteúdo inicializada
 * pre-condicao: nenhum
 * pos-condicao: sentinela da lista de retorno existe e os campos Primeiro e Ultimo apontam para NULL
 */
TipoLCT* InicializaListaConteudo();

/* Adiciona uma publicação [conteúdo] em uma determinada lista de conteúdo
 * inputs: variável do tipo conteudo e a lista na qual será inserido
 * output: nenhum
 * pre-condicao: nenhum
 * pos-condicao: conteúdo da publicação é inserido no final da lista desejada
 */
void CriaConteudo(TipoCT* conteudo, TipoLCT* lista_conteudo);

/* Inicializa a struct do tipo conteudo
 * inputs: mensagem da publicação
 * output: tipo conteudo inicializado
 * pre-condicao: nenhum
 * pos-condicao: tipo estruturado de retorno existe e os campos estão incializados e vazios
 */
TipoCT* InicializaTipoConteudo(char* conteudo, int pub);

/* Desaloca memória alocada pela lista de conteúdo desejada
 * inputs: lista de conteúdo que será desalocada
 * output: nenhum
 * pre-condicao: nenhum
 * pos-condicao: lista passada é desalocada, junto com todo seu conteúdo
 */
void LiberaListaConteudo(TipoLCT* lista_subscriber);

/* Função auxiliar para pesquisar e retornar uma subscrição específica
 * inputs: lista de subscrições e id da subscrição a ser pesquisada
 * output: tipo sub a ser pesquisado ou tipo sub NULL caso não exista
 * pre-condicao: nenhuma
 * pos-condicao: tipo sub é retornado caso encontrado ou NULL caso não exista
 */
TipoS* PesquisaSubscricao(int id_sub, TipoLS* lista_subscriber);

/* Percorre a lista de subscrições para verificar a existência de uma subscrição com id específico
 * inputs: lista de subscrições e id da subscrição a ser verificada
 * output: 1 para subscrição já existente e 0 para subscrição não existente
 * pre-condicao: nenhuma
 * pos-condicao: valores 1 ou 0 retornados de acordo com a existência da subscrição
 */
int VerificaExistenciaSubscricao(TipoLS* lista_subscriber, int id_sub);

/* Percorre a lista de conteúdo para verificar a existência de um conteúdo com id pub específico
 * inputs: lista de conteúdo e id da publicação a ser verificada
 * output: 1 para conteúdo já existente e 0 para conteúdo não existente
 * pre-condicao: nenhuma
 * pos-condicao: valores 1 ou 0 retornados de acordo com a existência da conteúdo
 */
int VerificaExistenciaConteudo(TipoLCT* lista_conteudo, int id_pub) ;

/* Função auxiliar que retorna a lista de conteúdo de uma subscrição
 * inputs: tipo conteúdo
 * output: lista de conteúdo da subscrição
 * pre-condicao: nenhuma
 * pos-condicao: lista de conteúdo é retornada
 */
TipoLCT* RtnListaConteudo(TipoS* subscriber);

/* ----- Funções do macthing abaixo ----- */

/* Função auxiliar para a impressão do matching
 * inputs:  lista de subscribers e o arquivo de saída para impressão
 * output: nenhuma
 * pre-condicao: nenhuma
 * pos-condicao: percorre toda lista de conteudo de todo os subscriber, e chama a função
 para imprimer em cada um deles
 */
void VerificaMatchingSubscriber(TipoLS* lista_subscriber, FILE* ArqSaida);

/* Função que imprime os subscriber que possuem matching
 * inputs: subscriber e o conteúdo a serem impressos e o arquivo de saída
 * output: nenhuma
 * pre-condicao: nenhuma
 * pos-condicao: caso a mensagem do subscriber seja diferente nula, é impresso no arquivo
 de saída o id da subscrição, o conteúdo e o tópico
 */
void ImprimeMatching(TipoS* subscriber, TipoCT* conteudo, FILE* ArqSaida);

/* Função auxiliar que dependendo do valor do flag, pesquisa o matching para o subscriber ou
 coloca todo o conteúdo da lista de mensagems como nulo
 * inputs: lista de subscriber, lista de vizinhos, lista de brokers, o broker e a flag
 * output: nenhuma
 * pre-condicao: nenhuma
 * pos-condicao: caso a flag seja igual a 1, funções que realizam o matching são chamadas
 caso a flag seja igual a 0, todas as mensagens da lista de conteúdo são zeradas.
 */
void PesquisaSubscriber(TipoLS* lista_subscriber, TipoLV* lista_vizinhos, TipoLB* lista_broker, TipoB* broker, int flag);

#endif	/* LISTA_SUBSCRIBER_H */
