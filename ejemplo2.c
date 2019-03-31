#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "semaphores.h"

							
#define CICLOS 10

char *pais[5]={"Peru","Bolvia","Colombia"};

SEM_ID exmut_sem;

void *hilo1(void *arg)
{
	int *mynum=(int *) arg;
	int i=*mynum;

	int k;

	for(k=0;k<CICLOS;k++)
	{
		semwait(exmut_sem);	
		// Inicia sección Crítica
		printf("Entra %s\n",pais[i]);
		fflush(stdout);
		sleep(rand()%3);
		printf("- %s Sale\n",pais[i]);
		// Termina sección Crítica
		semsignal(exmut_sem);
		
		// Espera aleatoria fuera de la sección crítica
		sleep(rand()%3);
	}
}

int main()
{
	pthread_t tid[3];
	int res;
	int args[3];
	int i;
	void *thread_result;

	exmut_sem=seminit(0x1234,1);
	
	srand(getpid());

	// Crea los hilos
	for(i=0;i<3;i++)
	{
		args[i]=i;
		res = pthread_create(&tid[i], NULL, hilo1, (void *) &args[i]);
	}

	// Espera que terminen los hilos
	for(i=0;i<3;i++)
		res = pthread_join(tid[i], &thread_result);

	erasesem(exmut_sem);
}
