#include "fra.h"

fr fator(fr piv, fr pret){
	fr f;
	f = divi(pret,piv);
		
	if(f.den<0&&f.num>0){
		f = mult(f,new(-1,-1));
	}
	
	if(mult(f,piv).num == pret.num){
		f = mult(f,new(-1,1));
	}
	
	return f;	
}

fr verificado(fr t){
	if(t.den<0&&t.num>0){
		t = mult(t,new(-1,-1));
	}
	
	return t;
}
void entrada(fr **m, int l, int c){
	int num,den;
		
	for(int i=0;i<l;i++){
		for(int j=0;j<c;j++){
			printf("mat[%d][%d]: ", i+1,j+1);
			scanf("%d %d",&num,&den);
			m[i][j] = new(num,den);
		}
	}
}

fr **matriz(fr **m, int l ,int c){
	m = (fr **)malloc(l*sizeof(fr *));//---aloca um vetor de "l" posições (linhas da matriz)
	
	for(int i=0;i<l;i++)
		*(m+i) = (fr *)malloc(c*sizeof(fr));/*vetor(c);*/ //------ aloca um um vetor de "c" posições em 
														  //------ cada posição do vetor de ponteiros
	
	entrada(m,l,c);		   //------ preenche a matriz com frações
	return m;
}

void liberta(fr **m, int l){
	for(int i=0;i<l;i++)
		free(*(m+i)); //------libera da memóra as colunas
	free(m);// ------------- libera da memória as linhas
}

void escalonar(fr **m, int l, int c){
	for(int i=0;i<(l-1);i++){			//---percorre a matriz até a penúltima linha
		for(int v=i;v<(l-1);v++){		//--- percorre a matriz até a penúltima linha a partir da linha atual
			if(m[v+1][i].num!=0){		//--- o numerador do elemento a ser eliminado precisa ser diferente de zero				
				fr f1 = fator(m[i][i],m[v+1][i]); // geração do fator que multiplicado pelo pivô da linha elimina o elemento abaixo
				mostra(1,f1);			//-----------exibe o fator
				printf("E: %d,%d",i+1,v+2);//--------exibe a operação elementar atual
				printf("\n");				
				for(int j=0;j<c;j++){   //-----------percorre todos os elementos da linha
					m[v+1][j] = soma(m[v+1][j], simplifica(mult(f1,m[i][j])));//--- multiplicação da linha do pivô pelo "fator" e 
					m[v+1][j] = verificado(m[v+1][j]);					//--------- soma na linha do elemento a ser eliminado
				}
			}
		}
	}
}

void escalonarR(fr **m, int l, int c){

	for(int i=1;i<l;i++){//---------------------- percorre até a segunda linha da matriz começando pelo final
		for(int v=i;v>0;v--){//------------------ percorre até a segunda linha da matriz começando pela linha atual
			if(m[v-1][i].num!=0&&m[i][i].num!=0){//condição: continua se o elemento acima do pivô e o prórpio pivô forem diferentes de zero 
				fr f1 = fator(m[i][i],m[v-1][i]);// geração do fator que multiplicado pelo pivô da linha elimina o elemento acima
				if(f1.den!=0){					 // condição: continua se o denominador do "fator " for diferente de 0
					mostra(1,f1);		//--------- exibe o fator
					printf("E: %d,%d",i+1,v);//---- exibe a operação elementar atual
					printf("\n");				
					for(int j=v;j<c;j++){//---------percorre todos os elementos da linha
						m[v-1][j] = soma(m[v-1][j], simplifica(mult(f1,m[i][j])));// multiplicação da linha do pivô pelo "fator" e 
						//m[v-1][j] = verificado(m[v-1][j]);				//---- soma na linha do elemento a ser eliminado
					}
				}
			}
		}
	}
}

void finaliza(fr **m, int l, int c){
	fr um = new(1,1); //------------define o numerador do fator
	for(int i=0;i<l;i++){//---------percorre todas as linhas da matriz	
		fr fator1 = divi(um,m[i][i]);// determina que o "fator" será 1 dividido pelo pivô da linha
		mostra(1,fator1);//------------ exibe o fator
		printf("E: %d\n",i+1);//------- exibe a operação elementar atual
		for(int j=0;j<c;j++){//-----percorre todas as colunas da matriz
			
			if(m[i][j].num!=0)
				m[i][j]= mult(m[i][j],fator1);//multiplica a linha do pivô da linha pelo fator
		}
			
	}
}
void show(fr **m, int l, int c){
	char var = 97;
	for(int i=0;i<l;i++){//---------mostra matrix
		for(int j=0;j<c;j++){
			if(m[i][j].num!=0){
				mostra(1,m[i][j]);
			}else
				printf("  ");

			if(j<c-1&&m[i][j].num!=0)
				printf(".%c",var);
			else
				printf("   ");

			if(j<c-2&&m[i][j+1].num>0)
				printf(" + ");
			else if(j==c-2)
				printf(" = ");
			else
				printf("  ");
			var++;
		}
		var =97;
		printf("\n");		
	}
}
