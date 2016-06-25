#ifndef COMANDOS_H
#define	COMANDOS_H

#include "lista_brokers.h"

/* Função que manipula os arquivos de entrada e saída do programa
 * inputs: caminho do arquivo de entrada e caminho do arquivo de saída
 * output: nenhum
 * pre-condicao: nenhum
 * pos-condicao: manipulação correta dos arquivos de entrada e saída
 */
void Manipulador(int parametros, char* entrada, char* saida);

/* Função que trata os comando do arquivo de entrada e seus parâmetros
 * inputs: lista de brokers, nome do comando, arquivos de entrada e saída
 * output: nenhum
 * pre-condicao: nenhum
 * pos-condicao: os comandos referentes ao problema foram corretamente interpretados e passados para a função correta
 */
void VerificaComando(TipoLB* lista_brokers, char* comando, FILE* ArqEntrada, FILE* ArqSaida);

/* ----- Funções referentes aos comandos dos arquivos de entrada ----- */

/* Chama todas as funções necessárias para a criação de um broker
 * inputs: lista de brokers e nome do broker a ser criado
 * output: nenhum
 * pre-condicao: nenhum
 * pos-condicao: broker é criado, caso não haja outro broker com o mesmo nome
 */
void CRIABROKER(TipoLB* lista_brokers, char* nome_broker);

/* Chama todas as funções necessárias para a especificação da vizinhança de um broker com outro
 * inputs: lista de brokers, nome do broker de destino e nome do broker de origem
 * output: nenhum
 * pre-condicao: nenhum
 * pos-condicao: nome do broker de origem foi inserido na lista de vizinhos do broker de destino e vice-versa (caso os brokers existam e não tem o mesmo nome)
 */
void INSEREVIZINHO(TipoLB* lista_brokers, char* broker_destino, char* broker_origem);

/* Chama todas as funções necessárias para a criação de um cliente tipo Publisher ou Subscriber
 * inputs: lista de brokers, nome do cliente, id de identificação Publisher/Subscriber e nome do broker no qual será inserido
 * output: nenhum
 * pre-condicao: nenhum
 * pos-condicao: cliente é criado no broker especificado, caso haja broker e não haja nenhum cliente com mesmo nome
 */
void CRIACLIENTE(TipoLB* lista_brokers, char* nome_cliente, char pubsub, char* nome_broker);

/* Chama todas as funções necessárias para imprimir a rede de brokers no arquivo de saída do programa
 * inputs: lista de brokers e arquivo de saída
 * output: nenhum
 * pre-condicao: arquivo de saída válido
 * pos-condicao: rede de brokers será corretamente impressa no arquivo de saída
 */
void IMPRIMEREDE(TipoLB* lista_broker, FILE* ArqSaida);

/* Chama todas as funções necessárias para adicionar uma publicação de um cliente tipo Publisher
 * inputs: lista de brokers, id da publicação, nome do cliente, tópico e mensagem do conteúdo
 * output: nenhum
 * pre-condicao: nenhum
 * pos-condicao: publicação é inserida caso não exista outra publicação com mesmo id e caso o cliente especificado exista
 */
void PUBLICA(TipoLB* lista_brokers, int id_pub, char* nome_cliente, char* topico, char* mensagem);

/* Chama todas as funções necessárias para adicionar uma subscrição de um cliente tipo Subscriber
 * inputs: lista de brokers, id da subscrição, nome do cliente e tópico do conteúdo
 * output: nenhum
 * pre-condicao: nenhum
 * pos-condicao: susbcrição é inserida caso não exista outra subscrição com mesmo id e caso o cliente especificado exista
 */
void SUBSCREVE(TipoLB* lista_brokers, int id_sub, char* nome_cliente, char* topico);

/* Chama todas as funções necessárias para excluir um broker e seus clientes
 * inputs: lista de brokers e nome do broker
 * output: nenhum
 * pre-condicao: nenhum
 * pos-condicao: broker é apagado, sua memória é desalocada, bem como todos os itens abaixo dele e seu nome é apagado de todos seus vizinhos
 */
void EXCLUIBROKER(TipoLB* lista_brokers, char* nome_broker);

/* Chama todas as funções necessárias para cancelar a vizinhança de dois brokers
 * inputs: lista de brokers, nome do broker de origem e nome do broker de destino
 * output: nenhum
 * pre-condicao: nenhum
 * pos-condicao: caso a vizinhança exista, o nome do broker de origem será apagado da lista de vizinhos do broker de destino e vice-versa
 */
void CANCELAVIZINHO(TipoLB* lista_brokers, char* broker_origem, char* broker_destino);

/* Chama todas as funções necessárias para excluir um cliente e suas publicações/subscrições
 * inputs: lista de brokers e nome do cliente
 * output: nenhum
 * pre-condicao: nenhum
 * pos-condicao: caso o cliente exista, ele será apagado da lista de clientes onde estava, bem como suas publicações ou subscrições
 */
void EXCLUICLIENTE(TipoLB* lista_brokers, char* nome_cliente);

/* Chama todas as funções necessárias para excluir uma subscrição de um Subscriber
 * inputs: lista de brokers e id da subscrição
 * output: nenhum
 * pre-condicao: nenhum
 * pos-condicao: subscrição é apagada e sua memória desalocada corretamente
 */
void EXCLUISUBSCRICAO(TipoLB* lista_brokers, int id_sub);

/* Chama todas as funções necessárias para verificar o matching entre publicação e subscrição
 * inputs: lista de brokers e arquivo de saída
 * output: nenhum
 * pre-condicao: arquivo de saída é válido
 * pos-condicao: faz uma série de verificações percorrendo a rede de brokers e imprimindo o matching entre subscrição e publicação
 */
void VERIFICAMATCHING(TipoLB* lista_brokers, FILE* ArqSaida);

/* Chama todas as funções necessárias para apagar toda lista de brokers e desalocar toda a memória do programa
 * inputs: lista de brokers
 * output: nenhum
 * pre-condicao: nenhum
 * pos-condicao: todos a memória utilizada na lista de brokers é desalocada corretamente
 */
void FIM(TipoLB* lista_brokers);

#endif	/* COMANDOS_H */