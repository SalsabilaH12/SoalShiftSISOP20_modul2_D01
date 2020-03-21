#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <wait.h>
#include <time.h>

void getTimestamp(char *path);
void writeKillerA();
void writeKillerB();

int main(int argc, char **argb){
  if(strcmp(argb[1], "-a") == 0){
    writeKillerA();
  }
  //jika menjalankan program menggunakan argumen dengan parameter a

  if(strcmp(argb[1], "-b") == 0){
    writeKillerB();
  }
  //jika menjalankan program menggunakan argumen dengan parameter b

  char test[100];
  char *work = getcwd(test, 100);

  pid_t pid, sid;

  pid = fork();
  //untuk membuat proses baru

  if (pid < 0) {
    exit(EXIT_FAILURE); }
    //Jika gagal proses akan berhenti

  if (pid > 0) {
    exit(EXIT_SUCCESS); }
    //Jika gagal proses akan berhenti

  umask(0);

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }
  //Jika gagal proses akan berhenti

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }
  //Jika gagal proses akan berhenti

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

//{ soal2a
  while(1){
    chdir(work);
    pid_t cid;
    int stat_1;

    cid = fork();
    //untuk membuat proses baru

    char folder[1000];
    snprintf(folder, 1000, "./");
    getTimestamp(folder);

    if(cid == 0){
      pid_t cid_2;
      int stat_2;

      cid_2 = fork();
      //untuk membuat proses baru

      if(cid_2 == 0){
        char *argv[] = {"mkdir", folder, NULL};
        execv("/bin/mkdir", argv);
//{ soal2b
      } else {
        while((wait(&stat_2)) > 0);
        //untuk menunggu dan memastikan bahwa folder telah terbentuk

        pid_t cid_3;
        int stat_3, i;
        char current[1000]; strcpy(current, folder);
        char file[1000];
        char link[1000];

        for(i=0; i<20; i++){
        //melakukan looping (untuk download gambar) sebanyak 20
          strcpy(file, current); strcat(file, "/");
          getTimestamp(file);
          long int sec = time(NULL)%1000 + 100;
          //merupakan ukuran gambar yang di download
          snprintf(link, 1000, "https://picsum.photos/%ld", sec);
          //menggabungkan link tempat download gambar dengan ukuran gambar ke dalam variabel link
          cid_3 = fork();
          //untuk membuat proses baru
          if(cid_3 == 0){
            char *argv[] = {"wget", "-O", file, link, NULL};
            //menjalankan command wget link download tertera dalam variabel link
            //mengunakan parameter -O untuk merename gambar hasil download sesuai dengan isi variabel file
            execv("/usr/bin/wget", argv);
            //untuk menjalankan command wget
          } else {

          }
          sleep(5);
          //jeda 5 detik sebelum process dijalankan
        }
//soal2b }

        while((wait(&stat_3)) > 0);

//{ soal2c
        pid_t cid_4;
        int stat_4;

        cid_4 = fork();
        //untuk membuat proses baru

        if(cid_4 == 0){
        //jika child process yang bernama cid_4 berjalan maka snprintf(output, 1000, "%s.zip", current);
        //menggabungkan nama folder menjadi namafolder.zip kemudian menyimpannya dalam variabel output
          char output[1000];
          snprintf(output, 1000, "%s.zip", current);
          char *argv[] = {"zip", "-r", output, current, NULL};
          //parameter r (rekursi) agar file dalam folder juga ikut ter-zip dan terhapus setelah di-zip.
          execv("/usr/bin/zip", argv);
        } else {
          while((wait(&stat_4)) > 0);
          char *argv[] = {"rm", "-r", current, NULL};
          //menjalankan command dengan parameter rm menghapus folder yang telah di zip
          execv("/bin/rm", argv);
          //untuk menjalankan command output
          //output merupakan namafolder.zip dan nama folder yang akan di-zip.
        }
//soal2c }
      }
    } else {

    }
    sleep(30);
    //jeda 30 detik sebelum process dijalankan
  }
//soal2a }

  return 0;
}

void getTimestamp(char *path)
{
  char timeStr[10];

  time_t curtime;
  struct tm *loctime;
  curtime = time (NULL);
  //untuk mengambil waktu lagi saat melalukan looping dan menyimpan dalam variabel curtime

  loctime = localtime (&curtime);
  //mengambil localtime lagi saat melalukan looping dan menyimpan dalam variabel loctime

  snprintf(timeStr, 10, "%d-", loctime->tm_year+1900);
  strcat(path, timeStr);

  if ((loctime->tm_mon+1) < 10)
    snprintf(timeStr, 10, "0%d-", loctime->tm_mon+1);
  else
    snprintf(timeStr, 10, "%d-", loctime->tm_mon+1);
  strcat(path, timeStr);

  if (loctime->tm_mday < 10)
    snprintf(timeStr, 10, "0%d_", loctime->tm_mday);
  else
    snprintf(timeStr, 10, "%d_", loctime->tm_mday);
  strcat(path, timeStr);

  if (loctime->tm_hour < 10)
    snprintf(timeStr, 10, "0%d:", loctime->tm_hour);
  else
    snprintf(timeStr, 10, "%d:", loctime->tm_hour);
  strcat(path, timeStr);

  if (loctime->tm_min < 10)
    snprintf(timeStr, 10, "0%d:", loctime->tm_min);
  else
    snprintf(timeStr, 10, "%d:", loctime->tm_min);
  strcat(path, timeStr);

  if (loctime->tm_sec < 10)
    snprintf(timeStr, 10, "0%d", loctime->tm_sec);
  else
    snprintf(timeStr, 10, "%d", loctime->tm_sec);
  strcat(path, timeStr);
}

//{ soal2d&e
void writeKillerA()
{
  FILE *temp;
  //memberi tau bahwa pointer temp merupakan sebuah file

  temp = fopen("killer.sh", "w");
  //membuat script bash dengan nama killer.sh dengan mode w agar file bisa di-write

  fputs("#!/bin/bash\n", temp);
  //menulis #!/bin/bash\n\n karena file tersebut merupakan bash script

  fputs("killOrder=$(echo $(pidof soal2))\n", temp);
  fputs("kill -9 $killOrder\n", temp);
  fputs("rm $0\n", temp);
  fclose(temp);

  pid_t tempCid;
  int tempStat;
  tempCid = fork();
  //untuk membuat proses baru

  if(tempCid == 0){
    char *argv[]={"chmod", "+x", "killer.sh", NULL};
    //menjalankan command chmod untuk mengganti izin akses agar file bash killer.sh bisa langsung di eksekusi +x

    execv("/bin/chmod", argv);
    //untuk menjalankan command chmod

  } else {

  }
}

void writeKillerB()
{
  FILE *temp;
  //memberi tau bahwa pointer temp merupakan sebuah file

  temp = fopen("killer.sh", "w");
  //membuat script bash dengan nama killer.sh dengan mode w agar file bisa di-write

  fputs("#!/bin/bash\n", temp);
  //menulis #!/bin/bash\n\n karena file tersebut merupakan bash script

  fputs("killOrder=$(echo $(pidof soal2))\n", temp);
  fputs("killOrder=${killOrder##* }\n", temp);
  fputs("kill -9 $killOrder\n", temp);
  fputs("rm $0\n", temp);
  fclose(temp);

  pid_t tempCid;
  int tempStat;
  tempCid = fork();
  //untuk membuat proses baru

  if(tempCid == 0){
    char *argv[]={"chmod", "+x", "killer.sh", NULL};
    // /menjalankan command chmod untuk mengganti izin akses agar file bash killer.sh bisa langsung di eksekusi +x

    execv("/bin/chmod", argv);
    //untuk menjalankan command chmod

  } else {

  }
}
//soal2d&e }
