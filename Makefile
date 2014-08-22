#Compilador
CC = gcc

#Variaveis de diretorios
LIB = ./lib
INCLUDE = ./include
SRC = ./src
OBJ = ./obj

#Opcões de compilação
FLAGS = -Wall -Wextra -pedantic

limpa: principal
	@rm *.o

#Cria um biblioteca dinamica com as bibliotecas
principal: biblioteca
	@$(CC) $(SRC)/main.c $(FLAGS) -o Lexico

#Compila as bibliotecas	
biblioteca:
	@$(CC) -c $(SRC)/*.c $(FLAGS) -I$(INCLUDE)


