#include "escalona.h"

int main(int argc, char *argv[]){
	/* entrada de dados */
	fr **mat =NULL; int l,c; 
	while(1){
		printf("nº equações: ");
		scanf("%d",&l);
		printf("nº variáveis + resultado: ");
		scanf("%d",&c);
	
		/* criacao da matriz */
		mat = matriz(l);
		entrada(mat,l,c);
		/* exibe o sistema */
		printf("\n----------sistema\n");
		show(mat,l,c);
		printf("\n------------------\n");
		/* escalona o sistema */
		escalonar(mat,l,c);
		show(mat,l,c);
		escalonarR(mat,l,c);
		finaliza(mat,l,c);
		/* exibe o sistema escalonado */
		show(mat,l,c);
	}
	return 0;
}
