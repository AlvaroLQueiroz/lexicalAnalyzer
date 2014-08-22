#include <stdio.h>
#include <stdlib.h>

/*Imprime a ultima string lida, char a char.
Entradas: 
carina = String a ser impressa.
carinaSize = Tamanho da string.
end = Caracter especial a ser impresso após a string

Retorno: Nenhum.
*/
void printCarina(char carina[5120], int carinaSize, char end[3]){
	int counter;
	
	for(counter = 0; counter <= carinaSize; counter++){
		printf("%c", carina[counter]);
	}
	printf("%s", end);
}


int main(int argc, char *argv[]){

	FILE *myFile;/*Arquivo a ser lido.*/
	char actualChar;/*Caracter atual do arquivo.*/
	char comment;/*Quando encontrado um '/' esta variavel e usada para verificar se é um inicio de um comentario.*/
	char carina[5120];/*Contera uma unica sub-string do arquivo por vez.*/
	int carinaSize;/*Tamanho da sub-string.*/
	unsigned short ischar, iscomment;/*Usadas para controlar se é uma string, um numero ou um comentario.*/
	
	myFile = NULL;
	ischar= 0;/*Toda sub-string é considerada inicialmente como uma string numerica.*/
	carinaSize = -1;

	/*Verifica se a passagem de parametros esta correta.*/
	if(argc != 2){
		printf("Por favor informe o caminho do arquivo.\n");
		exit(0);
	}

	myFile = fopen(argv[1], "r");

	/*Verifica se o arquivo foi aberto com sucesso.*/
	if(!myFile){
		printf("O arquivo nao existe.\n");
		exit(0);
	}
	
	/*Loop que percorrera o arquivo.*/
	do{
		actualChar = fgetc(myFile);
		
		/*Se o caracter atual for um '/', verifica-se se o proximo caracter é um '*'.
		Caso seja um inicio de comentario,
		um loop que le e descarta os caracteres sera executado até que
		encontre o final do comentario ou chegue ao fim do arquivo.*/
		if(actualChar == (char)47){
			comment = fgetc(myFile);
			
			if(comment == (char)42){
				
				/*Se o comentario começar imediatamente após uma sub-string, a mesma é impressa e zerada,
				para que o tratamento do comentario comece.*/
				if(carinaSize != -1){
					if(ischar){
						printf("Identificador: ");
					}
					else{
						printf("Numero: ");
						printCarina(carina, carinaSize, "\t");
						printf("Valor: ");	
					}
					printCarina(carina, carinaSize, "\n");
				}
				iscomment = 1;
				carinaSize = -1;
				ischar = 0;
				
				while(iscomment && actualChar != EOF){
					actualChar = fgetc(myFile);
					
					if(actualChar == (char)42){
						comment = fgetc(myFile);
		
						if(comment == (char)47){
							iscomment = 0;
						}
						else{
							fseek(myFile, -1, SEEK_CUR);
						}
					}
				}
				/*Caracter atual é setado como um espaço para nao ser considerado uma substring.*/
				actualChar = (char)32;
			}
			/*Se o caracter após o '/' não for um '*'
			o ponteiro volta uma posição, pois ele foi movimentado com a leitura do comment.
			*/
			else{
				fseek(myFile, -1, SEEK_CUR);
			}
		}
		
		/*Se o caracter nao for nenhum caracter especial
			e não for um digito, a sub-string é setada como uma string de texto.
			(Obs: como a sub-string é setada como numerica por padrao,
			ela continuara sendo numerica caso nenhum caracter diferente de um digito, '+', '-' ou de um '.' for encontrado.
		*/
		if(actualChar > (char)32 && actualChar != (char)127){
			if(!((actualChar >= (char)48 && actualChar <= (char)57) || actualChar == (char)43 || actualChar == (char)45 || actualChar == (char)46)){
				ischar = 1;
			}

			++carinaSize;
			carina[carinaSize] = actualChar;
		}
		/*Se um caracter especial for encontrado considera-se que o fim da sub-string foi encontrado,
		entao verifica-se se é numerica ou de textual e é feita a impressao da mesma.*/
		else if(carinaSize != -1){
			if(ischar){
				printf("Identificador: ");
			}
			else{
				printf("Numero: ");
				printCarina(carina, carinaSize, "\t");
				printf("Valor: ");	
			}
			printCarina(carina, carinaSize, "\n");
			
			ischar = 0;
			carinaSize = -1;
		}
	}while(actualChar != EOF);
	
	return 0;
}
