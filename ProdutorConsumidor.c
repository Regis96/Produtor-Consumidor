#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define TAM 4
//vou usar letra A
void *produtor(void *args);

void *consumidor(void *args);

int vetorVazio(char  string[TAM]);

int vetorCheio(char  string[TAM]);



char buffer[TAM];
int consumidorDormindo=0,produtorDormindo=0;
int contador=0;

void *produtor(void *args){
	while(1){
		if(vetorCheio(buffer) == -1){
			produtorDormindo=1;
			while(produtorDormindo){
				sleep(3);
				printf("\nProdutor dormindo por 3 segundos\n");
			}
			
		}
		
		buffer[contador] == 'A';
		
		printf("\nProdutor escreveu A no buffer na posicao %d\n",contador);
		if(contador == 3){
			contador = 0;
		}
		else{
			contador+=1;
		}

		

		if(vetorVazio(buffer) == 1 ){
			consumidorDormindo = 0;//acorda o consumidor se o buffer estiver vazio
			printf("\nProdutor acordou o consumidor\n");
		}
	}

}

void *consumidor(void *args){
	while(1){
		if(vetorVazio(buffer) == 1){
			consumidorDormindo=1;
			while(consumidorDormindo){
				sleep(3);
				printf("\nConsumidor dormindo por 3 segundos\n");
			}

		}
		
		buffer[contador]=='B';
		printf("Consumidor apagou o A do buffer na posicao %d\n",contador);
		if(contador == 0){
			contador = 3;
		}
		else{
			contador-=1;
		}
		

		if(vetorCheio(buffer) == -1){
			produtorDormindo=0;//acorda o produtor se o buffer ja estiver cheio
			printf("\nConsumidor acordou o produtor\n");
		}
	}
	
}




int vetorVazio(char  string[TAM]){
	for(int i=0;i<TAM;i++){
		if (string[i] == 'A')
			return 0;//nao esta vazio
	}
	return 1;//esta vazio
}

int vetorCheio(char  string[TAM]){
	for(int i=0;i<TAM;i++){
		if (string[i] != 'A')
			return i;//nao esta cheio,volta a posicao vazia
	}
	return -1;//esta cheio
}



int  main(){
	pthread_t thread1,thread2;
	pthread_create(&thread1,NULL,produtor,NULL);
	pthread_create(&thread2,NULL,consumidor,NULL);
	while(1){

	}

}


