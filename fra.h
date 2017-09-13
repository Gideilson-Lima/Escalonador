#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

//#define TAM 2

typedef struct { //--------definição do tipo fração
	int num;
	int den;
}fr;

fr new(int num, int den){ //-- cria uma nova fração
	fr frac;
	if(den==0)
		frac.den = 1;
	else
		frac.den = den;
		
	frac.num = num;	
	return frac;
}

int meuMMC(int num1, int num2){ //-descobre o MMC de dois números
	int x=1;
	while(1){
		if(x%num1==0 && x%num2==0)
			break;
		x++;
	}
	return x;
}

void mostra(int qtd,...){ //---exibe uma quantidade qualquer de frações na tela
	int i;
	va_list ap;
	va_start(ap, qtd);
	
	for(i=0;i<qtd;i++){
		fr frac = va_arg(ap,fr);
		if(frac.den==1)
			printf("%d ",frac.num);
		else 
			printf("%d/%d ",frac.num,frac.den);
			
	}
	va_end(ap);
}


fr simplifica(fr f){//------- simplifica uma fração
	if(f.num!=0&&f.den!=0){
		if(f.num%f.den==0){
			f.num/=f.den;
			f.den = 1;
			return f;
		}
		int i=1,maior = f.num;
		if(f.den>maior)
			maior = f.den;
		while(i<=maior){
			if(f.num%i==0 && f.den%i==0){
				f.num/=i;
				f.den/=i;
			}
			i++;
		}
	}
	return f;
}

fr soma(fr fr1, fr fr2){ //--------soma duas frações
	int Mmc = meuMMC(fr1.den, fr2.den);
	fr r;
	r.den = Mmc;
	r.num = ((Mmc/fr1.den)*fr1.num) + ((Mmc/fr2.den)*fr2.num);
	
	return r;
}

fr subt(fr fr1, fr fr2){ //-------subtrai duas frações
	int Mmc = meuMMC(fr1.den, fr2.den);
	fr r;
	r.den = Mmc;
	r.num = ((Mmc/fr1.den)*fr1.num) - ((Mmc/fr2.den)*fr2.num);
	
	return r;
}
fr mult(fr fr1, fr fr2){//-------multiplica duas frações
	fr r;
	r.num = fr1.num*fr2.num;
	r.den = fr1.den*fr2.den;

	r = simplifica(r);
	return r;
}
fr divi(fr fr1, fr fr2){//------divite uma fração por outra
	fr r;
	r.num = fr1.num*fr2.den;
	r.den = fr1.den*fr2.num;
	if(r.num!=0&&r.den!=0)
		r = simplifica(r);
	return r;
}
void entraDados(int esc){
	fr f1,f2;
	if(esc>0&&esc<5){
		scanf("%d %d",&f1.num,&f1.den);
		scanf("%d %d",&f2.num,&f2.den);
	}
	switch (esc){
		case 1:
			mostra(1,simplifica(soma(f1,f2)));
			printf("\n");
			break;
		case 2:
			mostra(1,simplifica(subt(f1,f2)));
			printf("\n");
			break;
		case 3:
			mostra(1,simplifica(mult(f1,f2)));
			printf("\n");
			break;
		case 4:
			mostra(1,simplifica(divi(f1,f2)));
			printf("\n");
			break;
		default:
			printf("-----------\nnão existe %dª opção\n-----\n",esc);
			break;
	}
}

void menu(){//---------menu
	int esc;
	printf("Escolha uma opcao:\n1-somar\n2-subtrair\n3-multiplicar\n4-dividir\n\n:::");
		
	scanf("%d",&esc);
	entraDados(esc);
}
