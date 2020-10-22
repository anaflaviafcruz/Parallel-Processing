#include <stdio.h>

int function_div(int n){
	int qt_divisores=0, aux=1, i;
	if(n < 24)
		return 1;
	else{
		while(n>24){
			for (i = 1; i <=n; i++){
                if (qt_divisores > 8) break;
                if (n%i==0) qt_divisores++;
			}	
			if(qt_divisores == 8) aux++;
			qt_divisores = 0;		
			n--;
		}
	}
	return aux;
}

int main(){
	printf("%d\n",function_div(1000000));
	return 0;
}

//f(1000000) = 224427
//Tempo gasto (em seg.): 1020