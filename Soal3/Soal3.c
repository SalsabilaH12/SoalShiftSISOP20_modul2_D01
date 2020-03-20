#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main (){
    pid_t cid;
    int stat;

    cid=fork();
    //untuk membuat proses baru

    if (cid < 0){
        exit(EXIT_FAILURE); }
        //Jika gagal proses akan berhenti

    if(cid == 0){
        char *var[] = {"mkdir","-p","/home/linuxlite/modul2/indomie",(char *)NULL};
        //child process untuk membuat direktori baru
        //pada path /home/linuxlite/modul2 yang dinamakan folder indomie

        execv("/bin/mkdir",var);}
        //digunakan agar process sebelumnya dapat berjalan

    else{
        while(wait(&stat)>0);
        //process selanjutnya adalah parent process sehingga child process dapat dijalankan terlebih dahulu

    cid=fork();
    //untuk membuat proses baru

    if (cid < 0){
        exit(EXIT_FAILURE); }
        //Jika gagal proses akan berhenti

    if(cid==0){
        sleep(5);
        //jeda 5 detik sebelum process dijalankan
        //
        char *var[] = {"mkdir","-p","/home/linuxlite/modul2/sedaap",(char *)NULL};
        //child process untuk membuat direktori baru
        //pada path /home/linuxlite/modul2 yang dinamakan folder sedaap

        execv("/bin/mkdir",var);}
        //digunakan agar process sebelumnya dapat berjalan

    else{
        while(wait(&stat)>0);
        //process selanjutnya adalah parent process sehingga child process dapat dijalankan terlebih dahulu

    cid=fork();
    //untuk membuat proses baru

    if (cid < 0){
        exit(EXIT_FAILURE); }
        //Jika gagal proses akan berhenti

    if(cid==0){
        char *var[] = {"unzip","/home/linuxlite/modul2/jpg.zip","-d","/home/linuxlite/modul2",(char *)NULL};
        //melakukan unzip file jpg.zip pada path /home/linuxlite/Downloads menuju direktori modul2

        execv("/usr/bin/unzip",var);}
        //path unzip agar process sebelumnya dapat berjalan

    else{
        while(wait(&stat)>0);
        //process selanjutnya adalah parent process sehingga child process dapat dijalankan terlebih dahulu

    cid=fork();
    //untuk membuat proses baru

    if (cid < 0){
        exit(EXIT_FAILURE); }
        //Jika gagal proses akan berhenti

    if(cid==0){
        char *var[] = {"find","/home/linuxlite/modul2/jpg/","-type","f","-exec","/bin/mv","-t","/home/linuxlite/modul2/sedaap","{}",";",(char *)NULL};
        //melakukan pemindahan file pada direktori jpg pada modul2 kedalam direktori sedaap

        execv("/usr/bin/find",var);}
        //path find digunakan untuk process sebelumnya dapat berjalan

    else{
        while(wait(&stat)>0);
        //process selanjutnya adalah parent process sehingga child process dapat dijalankan terlebih dahulu

    cid=fork();
    //untuk membuat proses baru

    if (cid < 0){
        exit(EXIT_FAILURE); }
        //Jika gagal proses akan berhenti

    if(cid == 0){
        char *var[] = {"find","/home/linuxlite/modul2/jpg/","-mindepth","1","-type","d","-exec","/bin/mv","-t","/home/linuxlite/modul2/indomie","{}",";",(char *)NULL};
        execv("/usr/bin/find",var);}

    //perintah untuk memindahkan direktori yang ada pada direktori jpg pada modul2 kedalam direktori indomie

    else{
        while(wait(&stat)>0);
        //process selanjutnya adalah parent process sehingga child process dapat dijalankan terlebih dahulu

    cid=fork();
    //untuk membuat proses baru

    if (cid < 0){
        exit(EXIT_FAILURE); }
        //Jika gagal proses akan berhenti

    if(cid==0){
        char *var[] = {"find","/home/linuxlite/modul2/indomie/","-mindepth","1","-type","d","-exec","touch","{}/coba1.txt","'\'",";",(char *)NULL};
        //untuk membuat file coba1.txt pada direktori indomie

        execv("/usr/bin/find",var);}
        //path find digunakan untuk process sebelumnya dapat berjalan

    else{
        while(wait(&stat)>0);
        //process selanjutnya adalah parent process sehingga child process dapat dijalankan terlebih dahulu

        sleep(3);
        //jeda 3 detik sebelum process dijalankan

        char *var[] = {"find","/home/linuxlite/modul2/indomie/","-mindepth","1","-type","d","-exec","touch","{}/coba2.txt","'\'",";",(char *)NULL};
        //untuk membuat file coba2.txt pada direktori indomie

        execv("/usr/bin/find",var);}
        //path find digunakan untuk process sebelumnya dapat berjalan
        }
        }
      }
    }
  }
}
