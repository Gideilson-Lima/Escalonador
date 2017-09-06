#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define TAM 2

typedef struct {
	int num;
	int den;
}fr;

fr new(int num, int den){
	fr frac;
	if(den==0)
		frac.den = 1;
	else
		frac.den = den;
		
	frac.num = num;	
	return frac;
}

int meuMMC(int num1, int num2){
	int x=1;
	while(1){
		if(x%num1==0 && x%num2==0)
			break;
		x++;
	}
	return x;
}

void mostra(int qtd,...){
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


fr simplifica(fr f){
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

fr soma(fr fr1, fr fr2){
	int Mmc = meuMMC(fr1.den, fr2.den);
	fr r;
	r.den = Mmc;
	r.num = ((Mmc/fr1.den)*fr1.num) + ((Mmc/fr2.den)*fr2.num);
	
	return r;
}

fr subt(fr fr1, fr fr2){
	int Mmc = meuMMC(fr1.den, fr2.den);
	fr r;
	r.den = Mmc;
	r.num = ((Mmc/fr1.den)*fr1.num) - ((Mmc/fr2.den)*fr2.num);
	
	return r;
}
fr mult(fr fr1, fr fr2){
	fr r;
	r.num = fr1.num*fr2.num;
	r.den = fr1.den*fr2.den;

	r = simplifica(r);
	return r;
}
fr divi(fr fr1, fr fr2){
	fr r;
	r.num = fr1.num*fr2.den;
	r.den = fr1.den*fr2.num;
	if(r.num!=0&&r.den!=0)
		r = simplifica(r);
	return r;
}
void entraDados(int esc){
	fr f1,f2;
	scanf("%d %d",&f1.num,&f1.den);
	scanf("%d %d",&f2.num,&f2.den);
	if(esc==1)
		mostra(1,simplifica(soma(f1,f2)));
	else if(esc==2)
		mostra(1,simplifica(subt(f1,f2)));
	else if(esc==3)
		mostra(1,simplifica(mult(f1,f2)));
	else if(esc==4)
		mostra(1,simplifica(divi(f1,f2)));
}

void menu(){
	int esc;
	printf("Escolha uma opcao:\n1-somar\n2-subtrair\n3-multiplicar\n4-dividir\n\n::");
		
	scanf("%d",&esc);
	entraDados(esc);
}
