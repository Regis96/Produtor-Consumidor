#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <signal.h>

#define TAM 4
//vou usar letra A
void *produtor(void *args);

void *consumidor(void *args);

int vetorVazio(char  string[TAM]);

int vetorCheio(char  string[TAM]);



char buffer[TAM]={'b','b','b','b'};
int consumidorDormindo=0,produtorDormindo=0;
int contador=0;
pthread_t thread1,thread2;

void *produtor(void *args){
	while(1){
		if(vetorCheio(buffer) == -1){
			produtorDormindo=1;
			while(produtorDormindo){
				printf("\nProdutor dormindo por 3 segundos\n");
				sleep(100);
				
			}
			
		}
		
		if(vetorVazio(buffer) == 1 ){
			buffer[contador] = 'A';
			signal(SIGCONT);//acorda o consumidor se o buffer estiver vazio
			printf("\nProdutor acordou o consumidor\n");
		}else{
			buffer[contador] = 'A';
			
		}
		
		printf("\nProdutor escreveu A no buffer na posicao %d\n",contador);
		printf("%c|%c|%c|%c",buffer[0],buffer[1],buffer[2],buffer[3]);
		
		if(contador == 3){
			contador = 0;
		}
		else{
			contador+=1;
		}

		

		
	}

}

void *consumidor(void *args){
	while(1){
		if(vetorVazio(buffer) == 1){
			consumidorDormindo=1;
			while(consumidorDormindo){
				printf("\nConsumidor dormindo por 3 segundos\n");
				sleep(100);
				
			}

		}
		if(vetorCheio(buffer) == -1){
			buffer[contador]='B';
			signal(SIGCONT);//acorda o produtor se o buffer ja estiver cheio
			printf("\nConsumidor acordou o produtor\n");
		}else{
			buffer[contador]='B';
			
		}
		
		printf("\nConsumidor apagou o A do buffer na posicao %d\n",contador);
		printf("%c|%c|%c|%c",buffer[0],buffer[1],buffer[2],buffer[3]);
		if(contador == 0){
			contador = 3;
		}
		else{
			contador-=1;
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
	
	pthread_create(&thread1,NULL,produtor,NULL);
	pthread_create(&thread2,NULL,consumidor,NULL);
	while(1){

	}


}


