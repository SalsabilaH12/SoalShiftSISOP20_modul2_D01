#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
 
int cekbintang (char bintang[]) {
	if (bintang[0]=='*') 
	return 1;
    return 0;
}

int angka (char cek[]){
  int x = 0;
  for (; cek[x] != '\0'; x++){
    if(!isdigit(cek[x]))
      return 0;
  }
     return 1;
}

void error(){
     printf("Tidak valid\n");
}

static void daemonsize()
{
  pid_t pid, sid;
  pid = fork();
  if (pid < 0)
    exit(EXIT_FAILURE);

  if (pid > 0)
    exit(EXIT_SUCCESS);

  umask(0);

  sid = setsid();
  if (sid < 0)
  exit(EXIT_FAILURE);
  
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
}

 
int main(int arg1, char **argv1) {
if (arg1 != 5){
	error();
	exit (EXIT_FAILURE);
}

if (arg1 == 5) {
  int arg[4];
  int x;
  for (x = 1; x < 4; x++)
  {
    if (angka(argv1[x]))
    {
      arg[x] = atoi(argv1[x]);
      if(arg[x]<0)
        error();
    }
    else if (cekbintang(argv1[x]))
      arg[x] = -1;
    else 
    {
      error();
      exit (EXIT_FAILURE);
    }

  int cek = atoi(argv1[x]);
  if ((x == 0 || x ==1) && (cek > 59 || cek < 0))
 {
error();
return 0;
 }

if (x == 2 && (cek > 23 || cek < 0 )){
error();
return 0;
  }
 }

daemonsize();

  while (1)
  {
    time_t waktu;
    struct tm * tm_now;
    time(&waktu);
    tm_now = localtime(&waktu);
    if ((tm_now->tm_sec == arg[1] || arg[1] == -1)){
	if (tm_now->tm_min == arg[2] || arg[2] == -1){
	if (tm_now -> tm_hour == arg[3] || arg[3] == -1)
    {
      int stts;
      pid_t child = fork();
      if (child == 0){
        char *argv2[] = {"bash", argv1[4], NULL};
        execv("/bin/bash", argv2);
      }
    }
}
 }
    sleep (1);
  }
}
else
{
  error();
  exit (EXIT_FAILURE);
  }
}
