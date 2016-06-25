# Makefile do primeiro trabalho de Estrutura de Dados I
# Gustavo Luiz & LABB

# Argumentos do programa
ENTRADA = /home/luiz/diretorio/entrada.txt
SAIDA = saida.txt

# Compilador utilizado
CC = gcc

# Opções de compilação
CFLAGS = -Wall -g

# Ligação com as bibliotecas
LDFLAGS = -lm

FONTES = $(wildcard *.c)

OBJETOS = $(FONTES:.c=.o)

# Nome do arquivo executável
EXECUTAVEL = ted1_1

all: $(EXECUTAVEL)

$(EXECUTAVEL): $(OBJETOS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c $(CFLAGS) $^

clean:
	rm -rf *.o

rmproper: clean
	rm -rf $(EXECUTAVEL)

run: $(EXECUTAVEL)
	./$(EXECUTAVEL) $(ENTRADA) $(SAIDA)

run-val: $(EXECUTAVEL)
	valgrind --track-origins=yes ./$(EXECUTAVEL) $(ENTRADA) $(SAIDA)
