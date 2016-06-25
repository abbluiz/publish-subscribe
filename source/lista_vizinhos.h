#ifndef LISTA_VIZINHOS_H
#define LISTA_VIZINHOS_H

#include "lista_brokers.h"

typedef struct tiposubscriber TipoS;
typedef struct tipolistasubscriber TipoLS;

typedef struct tipobroker TipoB;
typedef struct tipolistabroker TipoLB;

typedef struct tipovizinho TipoV;
typedef struct tipolistavizinho TipoLV;

/* ----- Funções elementares abaixo ----- */

/* Inicializa o sentinela da lista de vizinhos
 * inputs: nenhum
 * output: sentinela da lista de vizinhos inicializado
 * pre-condicao: nenhuma
 * pos-condicao: sentinela da lista de vizinhos de retorno existe e os campos primeiro e ultimo 
 apontam para NULL
 */    
TipoLV* InicializaListaVizinho();

/* Inicializa o tipo vizinho
 * inputs: nome do vizinho e lista de brokers
 * output: tipo vizinho inicializado
 * pre-condicao: nenhuma
 * pos-condicao: tipo vizinho de retorno existe e os campos são devidamente inicializados
 */
TipoV* InicializaTipoVizinho(char* nome, TipoLB* lista_brokers);
    
/* Insere um vizinho na lista de vizinhos
 * inputs: tipo vizinho a ser inserido e lista na qual será inserido
 * output: nenhum
 * pre-condicao: nenhuma
 * pos-condicao: vizinho é inserido corretamente no final da lista de vizinhos
 */
void CriaVizinho(TipoV* vizinho, TipoLV* lista_vizinhos);

/* Retira um vizinho da lista de vizinhos
 * inputs: lista de vizinhos e nome do vizinho a ser retirado
 * output: nenhum
 * pre-condicao: nenhuma
 * pos-condicao: vizinho com nome especificado é retirado da lista de vizinhos
 */
void ExcluiVizinhos(TipoLV* lista_vizinhos, char * nome);

/* Imprime toda a lista de vizinhos no arquivo de saída
 * inputs: lista de vizinhos e arquivo de saída
 * output: nenhum
 * pre-condicao: arquivo de saída válido
 * pos-condicao: toda a lista de vizinhos é impressa no arquivo de saída
 */
void ImprimeVizinho(TipoLV* lista_vizinho, FILE* ArqSaida);

/* Libera toda memória alocada pela lista de vizinhos
 * inputs: lista de vizinhos
 * output: nenhum
 * pre-condicao: nenhuma
 * pos-condicao: toda memória alocada pela lista de vizinhos é desalocada
 */
void LiberaListaVizinho(TipoLV* lista_vizinhos);

/* ----- Funções auxiliares abaixo ----- */

/* Percorre a lista de vizinhos para verificar a existência de um vizinho de nome específico
 * inputs: lista de vizinhos e nome do vizinho a ser verificado
 * output: 1 para vizinho já existente e 0 para vizinho não existente
 * pre-condicao: nenhuma
 * pos-condicao: valores 1 ou 0 retornados de acordo com a existência do vizinho
 */
int VerificaExistenciaVizinho(TipoLV* lista_vizinhos, char* nome_vizinho);

/* Função auxiliar necessária para o cancelamento de vizinhança caso um broker seja excluído, 
 chamando a função elementar ExcluiVizinho
 * inputs: lista de vizinhos, nome do vizinho
 * output: nenhum
 * pre-condicao: nenhuma
 * pos-condicao: exclui o vizinho com nome especificado caso exista
 */
void ExcluiVizinhoU(TipoLV* lista_vizinhos, char* nome_vizinho);

/* ----- Funções do matching abaixo ----- */

/* A função principal do matching de forma recursiva para que a função funcione ao longo de toda a 
 rede de brokers
 * inputs: lista de vizinhos, tipo subscriber e tópico
 * output: nenhum
 * pre-condicao: nenhuma
 * pos-condicao: as publicações pesquisadas são colocadas corretamente na lista de conteúdo da
 subscrição correspondente ao longo da rede
 */
void PesquisaVizinhos(TipoLV* lista_vizinhos, TipoS* subscriber, char* topico);

#endif	/* LISTA_VIZINHOS_H */