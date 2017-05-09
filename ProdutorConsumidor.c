#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>


#define TAM 4
//vou usar letra A
void *produtor(void *args);

void *consumidor(void *args);

int vetorVazio(char  string[TAM]);

int vetorCheio(char  string[TAM]);



char buffer[TAM]={'b','b','b','b'};
int contador=0,contadorGeral=0;
pthread_t thread1,thread2;


pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;	
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t buffer_cheio = PTHREAD_COND_INITIALIZER;
pthread_cond_t buffer_vazio = PTHREAD_COND_INITIALIZER;


void *produtor(void *args){
	while(1){
		if(contador == 4 ){

				
				printf("\nProdutor dormindo \n");
				pthread_cond_wait(&buffer_cheio, &mutex1);
				
			
			
		}
		
		pthread_mutex_lock(&mutex2);
		printf("\nProdutor escreveu pela %d vez\nContador: %d \n",contadorGeral,contador+1);
		
		contador+=1;
		

		contadorGeral++;
		if(contador == 1){
			buffer[contador] = 'A';
				
					pthread_cond_signal(&buffer_vazio);//acorda o consumidor se o buffer estiver vazio
					printf("\nProdutor acordou o consumidor\n");

			
		}else{
			buffer[contador] = 'A';
			
		}
		
		
		
		
				pthread_mutex_unlock(&mutex2);

		

		
	}

}

void *consumidor(void *args){
	while(1){
		if(contador == 0){
			
				printf("\nConsumidor dormindo \n");
				pthread_cond_wait(&buffer_vazio,&mutex1);
		}
		pthread_mutex_lock(&mutex2);
		printf("\nConsumidor apagou pela %d vez\nContador: %d",contadorGeral,contador-1);
		
		
		contador-=1;
		
		contadorGeral++;
		if(contador == 3){
			
			pthread_cond_signal(&buffer_cheio);//acorda o produtor se o buffer ja estiver cheio
			printf("\nConsumidor acordou o produtor\n");
		}
		buffer[contador]='B';
		
		pthread_mutex_unlock(&mutex2);
		

	}
	
}



int  main(){
	
	pthread_create(&thread1,NULL,produtor,NULL);
	pthread_create(&thread2,NULL,consumidor,NULL);
	while(1){

	}


}


