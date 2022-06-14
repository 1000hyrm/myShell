#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char *argv[]) {
	int fd, i, status, pid;
	char *pathPtr[20], allPath[1024], exStr[128], ch, line1[256];

	if ((fd = open (".myshell", O_RDONLY)) <= 0) {
		perror ("open error.");
		exit (-1);
	}

	memset (allPath, 0, 1024);
	while (1) {		// discard "PATH="
		read(fd, &ch, 1);
		if (ch=='=')
			break;
	}

	read (fd, allPath, 1024);
	pathPtr[0] = strtok(allPath, ":\n");

	i = 0;
	while (pathPtr[i]!=NULL) {
		printf("pathPtr[%d]=[%s]\n", i, pathPtr[i]);  
		i++;
		pathPtr[i] = strtok(NULL, ":\n");
	}
/*
	strcpy (exStr, pathPtr[1]);
	strcat (exStr, "/");
	printf ("-->[%s]\n", exStr);
	
	strcpy (exStr, pathPtr[0]);
	strcat (exStr, "/");
	printf ("-->[%s]\n", exStr);*/
	
	while(1){
		printf("%% ");
		
		fgets(line1, 255, stdin);
		
		printf("str = %s\n", line1); //\n exist
		line1[strlen(line1)-1]='\0';
		strtok(line1, " ");
		printf("new str = %s\n", line1);
		
		strcpy (exStr, pathPtr[0]);
		strcat (exStr, "/");
		printf ("-->[%s]\n", exStr);
		strcat(exStr, line1);
		
		if(access(exStr, F_OK) == 0){
			printf("%s\n", exStr);
			printf("Existed in pathPtr[0]\n");
			
			if(fork() == 0){
				execl(exStr, "exe", (char *)0);
				perror("fork error\n");
				exit(-1);
			}
			pid = wait(&status);
			printf("Parent: child exit. pid = [%d], status = [%x]\n", pid, status);
		}
		else{
			strcpy(exStr, pathPtr[1]);
			strcat(exStr, "/");
			printf ("try-->[%s]\n", exStr);
			strcat(exStr, line1);
			
			if(access(exStr, F_OK) == 0){
				printf("%s\n", exStr);
				printf("Existed in pathPtr[1]\n");
				
				if(fork() == 0){
					execl(exStr, "exe", (char *)0);
					perror("fork error\n");
					exit(-1);
				}
				pid = wait(&status);
				printf("Parent: child exit. pid = [%d], status = [%x]\n", pid, status);
			}
			else{
				strcpy(exStr, pathPtr[2]);
				strcat(exStr, "/");
				printf ("try2-->[%s]\n", exStr);
				strcat(exStr, line1);
				
				if(access(exStr, F_OK) == 0){
					printf("%s\n", exStr);
					printf("Finally, Existed in pathPtr[2]\n");
					
					if(fork() == 0){
						execl(exStr, "exe", (char *)0);
						perror("fork error\n");
						exit(-1);
					}
					pid = wait(&status);
					printf("Parent: child exit. pid = [%d], status = [%x]\n", pid, status);
				}
				else{
					printf("command not found\n");
				}
			}
			
		}
	}
}


