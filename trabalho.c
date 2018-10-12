#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>  
#include <errno.h>	
#include <signal.h>
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


char** separa_comandos(char *comando){
	int i = 0, j = 0, k = 0;
	char **comandos = (char **)malloc(sizeof(char *)*100);
	
	for(i=0;i<100;i++){
		*(comandos+i) = (char *)malloc(sizeof(char)*4096);
    	memset(*(comandos+i), '\0', sizeof(char)*4096);
	}
  	for(i=0;j<5;i++){
		if(comando[i] != '@'){
			if(comando[i] != ' '){
				comandos[j][k] = comando[i];
				k++;
			}
		}
		else{
			comandos[j][k] = '\0';
			j++;
			k = 0;
		}
	}
	comandos[j][k] = '\0';
	//*qtdParametros = j;
	return comandos;
}
void novo_bash(){
	int i, parametros = 5, exit_status = 0;
	while(1){
		char *bufferIn = (char *)malloc(sizeof(char)*100);
		printf("fsh> ");
//		getchar();
		scanf("\n%[^\n]s", bufferIn);

		char **entrada = separa_comandos(bufferIn);
		printf("PID_P1 executará comando %s\n",entrada[0]);
		printf("PID_P2 executará comando %s\n",entrada[1]);
		printf("PID_P3 executará comando %s\n",entrada[2]);
		printf("PID_P4 executará comando %s\n",entrada[3]);
		printf("PID_P5 executará comando %s\n",entrada[4]);


	}
}
int main(int argc, char **argv){
//	signal(SIGTSTP, trata_SIGTSTP);
//	signal(SIGINT, trata_SIGINT);
		novo_bash();
	return 0;
}
