#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>  
#include <errno.h>	
#include <signal.h>

#define MAX 30
typedef struct {
    char comando[MAX];
    char argumentos[5][MAX];
	int qtdArg;
} Tcomandos;

/*
void newsh_bash()
{
	int i, parametros, exit_status = 0;
	while(1)
	{
		char *bufferIn = (char *)malloc(sizeof(char)*100);
		printf("newsh%% ");
		fflush(stdin);
		scanf("\n%[^\n]s", bufferIn);
		char **entrada = split(bufferIn,&parametros);
		command_map(entrada, parametros, &exit_status, bufferIn);        
		free(bufferIn);
		for(i=0;i<100;i++)free(*(entrada+i));
		free(entrada); 
		if(exit_status)break;
	}
}
*/
void command_map(char **comandos, int qtParametros, int *exit_status, char *nome){
	int i;
	if(!strcmp(comandos[0],"waitz")){
	}
	else if(!strcmp(comandos[0],"exit")){
	}
	else{}
}
/*
void command_map(char **comandos, int qtParametros, int *exit_status, char *nome)
{
	int i;
	if(!strcmp(comandos[0],"cd"))
	{
	    cd(comandos[1]); //cd(caminho)
	}
	else
	if(!strcmp(comandos[0],"pwd"))
	{
	    pwd(); //pwd
	}
	else
	if(!strcmp(comandos[0],"echo"))
	{
	    //echo <STRING>
	    for(i=1;i<=qtParametros;i++)printf("%s ", comandos[i]);
	    printf("\n");
	}
	else
	if(!strcmp(comandos[0],"wait"))
	{
	    mywait();
	}
	else
	if(!strcmp(comandos[0],"exit"))
	{
	    int i;
	    for(i=0;i<c_back;i++)
		{
			kill(processos_back[i].pid,SIGKILL);
		}
	    for(i=0;i<c_fore;i++)
		{
			kill(processos_fore[i].pid,SIGKILL);
		}
	    *exit_status = 1;
	}
	else
	if(!strcmp(comandos[0],"clean"))
	{
	    int i = 0, status;
	    for(i=0;i<c_back;i++)
	    {
	    	waitpid(processos_back[i].pid,&status,WNOHANG);
		printf("PID: %d RETORNOU: %d\n", processos_back[i].pid, status);
		
	    }
	}
	else
	{
	    //Background
		if(!strcmp(comandos[qtParametros],"&"))
		{
			comandos[qtParametros] = NULL;
			int c = fork();
			if(c<0)
			{
				printf("Erro ao realizar o fork :-/\n");
				exit(0);
			}      
			else if(c==0)
			{
				int exec_status;
				setpgid(getpid(), getpid());
				exec_status = execvp(comandos[0], comandos);
				if(exec_status==-1)
				{
					printf("Erro ao executar exec!\n");
					exit(0);
				}
			}
			else if(c>0)
			{
				printf("[%d] %d\n", c_back+1, c);
				processos_back[c_back].pid = c;
				strcpy(processos_back[c_back].nome,nome);
				processos_back[c_back].nome[strlen(processos_back[c_back].nome)-1] = '\0';
				c_back++;
			}      
		}
		else
		{      
		    //Foreground
			comandos[qtParametros+1] = NULL;
			int c = fork();
			if(c<0)
			{
				printf("Erro ao realizar o fork :-/\n");
				exit(0);
			}
			else
			{
				if(c==0)
				{	
					int exec_status;
					exec_status = execvp(comandos[0], comandos);
					if(exec_status==-1)
					{
						printf("Falha ao executar exec!\n");
						exit(0);
					}
				}
				else if(c>0)
				{
					processos_fore[c_fore].pid = c;
					strcpy(processos_fore[c_fore].nome,nome);
					c_fore++;
					waitpid(c, NULL, WUNTRACED);
				}
			}
		}
	}
}
*/
void printacomandos(int qtdComandos, Tcomandos *comandos) {
	int i;
	printf("QTD COMANDOS %d",qtdComandos);
	for (i=0; i<qtdComandos; i++) {
		printf("\n         %s\n",comandos[i].comando);
	}
	printf("ACABOU");
}

void limpa_comandos(Tcomandos *comandos) {
	for (int i = 0; i < 5; i++) {
		strcpy(comandos[i].comando,"");
		comandos[i].qtdArg = 0;
	}
}

void separa_comandos(int *qtdComandos,  Tcomandos *comandos, char* str) {

	int i = 0;
	int qtdArg = 0, comando = 1;
	//Tcomandos comandos[5];

	const char s[2] = " ";
	char *token;

	token = strtok(str, s);
	
	while( 1 ) {

		while (strcmp(token,"@")) {
			if (comando == 1) {
				strcpy(comandos[i].comando,token);
				//printf("comando %d: %s\n",i, token);
				comando = 0;
				(*qtdComandos)++;
			} else {
				strcpy(comandos[i].argumentos[qtdArg],token);
				qtdArg++;
				//printf("arg %d do comando %d: %s\n",qtdArg,i,comandos[i].argumentos[qtdArg-1]);
			}
			token = strtok(NULL, s);
			if (token == NULL) break;
		}
		comandos[i].qtdArg = qtdArg;
		if (token == NULL) break;
		if (!strcmp(token,"@")) {
			qtdArg = 0;
			i++;
			comando = 1;
			token = strtok(NULL, s);
		}
	}
	//printf ("quantidade de comandos %d          ",*qtdComandos);
	//printacomandos((*qtdComandos),comandos);
}

void novo_bash(){
	int i, parametros = 5, exit_status = 0;
	while(1){
		char *bufferIn = (char *)malloc(sizeof(char)*100);
		Tcomandos comandos[5];
		int qtdComandos = 0;
		printf("fsh> ");
		scanf("\n%[^\n]s", bufferIn);

		separa_comandos(&qtdComandos, comandos, bufferIn);
		printf("PID_P1 executará comando %s com %d argumentos\n",comandos[0].comando,comandos[0].qtdArg);
		printf("PID_P2 executará comando %s com %d argumentos\n",comandos[1].comando ,comandos[1].qtdArg);
		printf("PID_P3 executará comando %s com %d argumentos\n",comandos[2].comando ,comandos[2].qtdArg);

	}
}

int main(int argc, char **argv){
//	signal(SIGTSTP, trata_SIGTSTP);
//	signal(SIGINT, trata_SIGINT);
		novo_bash();
		
	return 0;
}
































