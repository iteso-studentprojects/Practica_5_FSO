#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/msg.h>


#define CICLOS 10

char *pais[3]={"--Peru","**Bolvia","  Colombia"};
//int *g;

// Definir una estructura que se va a usar para mandar los mensajes
typedef struct
{
	long msg_type;		// Tipo de mensaje, debe ser long
	char mensaje[100];	// Contenido
} MSGTYPE; 

int msgqid;	// Identificador de la cola de mensajes
MSGTYPE msg;

void proceso(int i);

int main(int argc, char const *argv[])
{
	int pid;
	int status;
	int args[3];
	int i;

	srand(getpid());

	//Se crea el buzón
	msgqid = msgget (0x1234,0666|IPC_CREAT);

	//Se inicializa el mensaje
	msg.msg_type = 1.0;
	//sprintf(msg.mensaje,"MSJ generico");
	msgsnd(msgqid, &msg, sizeof(MSGTYPE)-sizeof(long) , 0.0);
	

	for( i = 0 ; i < 3 ; i++)
	{
		//Crea un nuevo proceso hijo que ejecuta la función proceso()
		pid = fork();
		if( pid == 0 )
			proceso(i);
	}

	for( i = 0 ; i < 3 ; i++ )
		pid = wait(&status);

	//Elmina cola de mensajes
	msgctl(msgqid, IPC_RMID, NULL);

	return 0;
}

void proceso(int i)
{
	int k;
	int l;

	for(k=0;k<CICLOS;k++)
	{
		//Wait
		msgrcv(msgqid ,&msg , sizeof(MSGTYPE)-sizeof(long), 1.0, 0);

		// Entrada a la sección crítica
		printf("%s Entra\n",pais[i]);
		fflush(stdout);
		sleep(rand()%3);
		printf("%s Sale\n",pais[i]);
		// Salida de la sección crítica

		//Signal
		msgsnd(msgqid, &msg, sizeof(MSGTYPE)-sizeof(long), 0.0);

		// Espera aleatoria fuera de la sección crítica
		sleep(rand()%3);
	}
	exit(0);
	// Termina el proceso
}