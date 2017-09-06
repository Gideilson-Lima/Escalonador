#include "fra.h"

fr fator(fr piv, fr pret){
	fr f;
	f = divi(pret,piv);
		
	if(mult(f,piv).num == pret.num){
		f = mult(f,new(-1,1));
	}
	
		
	return f;	
}

fr *vetor(){
	fr *v;
	v = malloc(sizeof(int));
	
	return v;
}

fr **matriz(int l){
	fr **m;
	m = malloc(sizeof(fr *));
	
	for(int i=0;i<l;i++)
		*(m+i) = vetor();
	return m;
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


void escalonar(fr **m, int l, int c){
	for(int i=0;i<(l-1);i++){
			for(int v=i;v<(l-1);v++){
				fr f1 = fator(m[i][i],m[v+1][i]);
				mostra(1,f1);
				printf("E: %d,%d",i+1,v+2);
				printf("\n");				
				for(int j=0;j<c;j++){
					m[v+1][j] = soma(m[v+1][j], mult(f1,m[i][j]));
				}
			}
		}
}

void escalonarR(fr **m, int l, int c){
	for(int i=1;i<l;i++){
			for(int v=i;v>0;v--){
				fr f1 = fator(m[i][i],m[v-1][i]);
				mostra(1,f1);
				printf("E: %d,%d",i,v-1);
				printf("\n");				
				for(int j=v;j<c;j++){
					m[v-1][j] = soma(m[v-1][j], mult(f1,m[i][j]));
				}
			}
		}
}

void finaliza(fr **m, int l, int c){
	fr um = new(1,1);
	for(int i=0;i<l;i++){
		for(int j=0;j<c;j++){
			fr fator1 = divi(um,m[i][i]);
			m[i][i]= mult(m[i][i],fator1);
			m[i][c-1] = mult(m[i][c-1],fator1);
			break;
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
					printf(". %c",var);
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
