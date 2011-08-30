#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
	
	 ///char *const parmList[] = {"/bin/ls", "-al", "/home/prajakta/Desktop/praj_multi2sim_RandD", NULL};
	//system("clear");
	char buffer[80];
	printf("\n\n\n********************************hello***************************\n\n");
	//printf("\n**********ARGC = %d******************", argc);
	//FILE *in = fopen("/home/prajakta/praj_multi2sim_RandD/guestos_multi2sim/mytest/hello.c","r");
	//fread(buffer,1,79,in);
	//fclose(in);
//	guestos1();
//	guest1();
  //      strcpy(buffer,"Hi Prajakta");
	syscall(400);
//	syscall(401,buffer);
	syscall(401,"foolish Prajakta");
	//syscall(401,"IT IS WORKING!!!!!!");
	syscall(402);
	syscall(403,"/home/abhay");
	//printf("\n%s\n\n",buffer);
	///execv("/bin/ls",parmList);
        syscall(405);
	return(0);
}
