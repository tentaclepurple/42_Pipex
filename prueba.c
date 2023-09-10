//#include "pipex_bonus.h"

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>



int main()   
{
    int fd1[2],fd2[2];
    int status, pid;
	
    pipe(fd1);                 /* comunica ls y grep */
    pid = fork();     

    if(pid == 0)              /* hijo 1*/
    {      		
        close(fd1[0]);   /* cerrar extremo no necesario */
        dup2(fd1[1], STDOUT_FILENO); 
		close(fd1[1]);
        execlp("/bin/ls", "ls", "-l", NULL);
    }
    
	close(fd1[1]);    /* extremo no necesario ya */	
	pipe(fd2);		  /* comunica grep y wc */
    pid = fork();
        
    if(pid == 0)               /* hijo 2 */
    {
		close(fd2[0]);   /* cerrar extremo no necesario */
		dup2(fd1[0], STDIN_FILENO);
		close(fd1[0]);
		dup2(fd2[1], STDOUT_FILENO);			
	  	close(fd2[1]);
		execlp("/bin/grep","grep", "u",NULL);
	}
	 /* padre */
	
    close(fd1[0]);      /* cerrar extremo no necesario */
    close(fd2[1]);     /* cerrar extremo no necesario */		
    pid = fork();
		
	if(pid == 0) /* hijo 3*/
    {
	    dup2(fd2[0], STDIN_FILENO);
	    close(fd2[0]);	
	    execlp("/usr/bin/wc","wc", "-l",NULL);
	}
     
    close(fd2[0]);  /* cerrar extremo que queda abierto en el padre  */
   /* wait para cada hijo */
    wait(&status);   
    wait(&status);	
    wait(&status);
	
    return 0;
  	
}
