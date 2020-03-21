# SoalShiftSisop20_modul2_D01

## Soal 1
**A. Program menerima 4 argumen berupa:
  i. Detik: 0-59 atau * (any value)
  ii. Menit: 0-59 atau * (any value)
  iii. Jam: 0-23 atau * (any value)
  iv. Path file .sh** 
  
**B. Program akan mengeluarkan pesan error jika argumen yang diberikan tidak sesuai**

**C. Program hanya menerima 1 config cron**

**D. Program berjalan di background (daemon)**

**E. Tidak boleh menggunakan fungsi system()
  Contoh: ./program \* 34 7 /home/somi/test.sh
  Program dengan argumen seperti contoh di atas akan menjalankan script test.sh setiap detik pada jam 07:34.**
  
  Code :
  ```
  
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

```
- Penjelasan penyelesaiannya sebagai berikut:
- Dengan menggunakan template daemon yang ada di modul
```

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

```
- Lalu melakukan pengecekan argument 
```

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

```
- Dengan terdapat ketentuan yaitu argumen harus 5, berupa angka (dicek oleh angka()) atau cekbintang (dicek oleh cekbintang()). Argumen yang dimasukkan harus sesuai dengan timetamp detik(0-59), menit(0-59), dan jam (0-24).
- Lalu, terdapat proses atau loop utama yang menjalankan argumen ke empat :

```

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

```
- Dengan ketentuan program akan mengecek waktu dan membuat child yang akan menjalankan argumen keempat jika argumen - argumen sebelumnya sudah sama dengan waktu sekarang.
- Program menggunakan fungsi dan struct dari time.h untuk proses 
- Dilakukan Pengencekan waktu :
```

    if ((tm_now->tm_sec == arg[1] || arg[1] == -1)){
	if (tm_now->tm_min == arg[2] || arg[2] == -1){
	if (tm_now -> tm_hour == arg[3] || arg[3] == -1)

```
- Dan Child menjalankan bash :
```
char *argexec[] = {"bash", argv[4], NULL}; 
execv("/bin/bash", argexec);

```

## Soal 2 
**A. Pertama-tama, Kiwa membuat sebuah folder khusus, di dalamnya dia membuat sebuah program C yang per 30 detik membuat sebuah folder dengan nama timestamp [YYYY-mm-dd_HH:ii:ss].**

**B. Tiap-tiap folder lalu diisi dengan 20 gambar yang di download dari https://picsum.photos/, dimana tiap gambar di download setiap 5 detik. Tiap gambar berbentuk persegi dengan ukuran (t%1000)+100 piksel dimana t adalahdetik Epoch Unix. Gambar tersebut diberi nama dengan format timestamp [YYYY-mm-dd_HH:ii:ss].**

**C. Agar rapi, setelah sebuah folder telah terisi oleh 20 gambar, folder akan di zip dan folder akan di delete(sehingga hanya menyisakan .zip).**

**D. Karena takut program tersebut lepas kendali, Kiwa ingin program tersebut men- generate sebuah program "killer" yang siap di run(executable) untuk menterminasi semua operasi program tersebut. Setelah di run, program yang menterminasi ini lalu akan mendelete dirinya sendiri.**

**E. Kiwa menambahkan bahwa program utama bisa dirun dalam dua mode, yaitu MODE_A dan MODE_B. untuk mengaktifkan MODE_A, program harus dijalankan dengan argumen -a. Untuk MODE_B, program harus dijalankan dengan argumen b. Ketika dijalankan dalam MODE_A, program utama akan langsung menghentikan semua operasinya ketika program killer dijalankan. Untuk MODE_B, ketika program killer dijalankan, program utama akan berhenti tapi membiarkan proses di setiap folder yang masih berjalan sampai selesai(semua folder terisi gambar, terzip lalu di delete). Kiwa lalu terbangun dan sedih karena menyadari programnya hanya sebuah mimpi. Buatlah program dalam mimpi Kiwa jadi nyata!
  Catatan: - Tidak boleh memakai system().
           - Program utama harus ter-detach dari terminal
  Hint: 
           - Gunakan fitur picsum.photos untuk mendapatkan gambar dengan ukuran tertentu
           - Epoch Unix bisa didapatkan dari time()**
Code :
```
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
  if(strcmp(argb[1], "-b") == 0){
    writeKillerB();
  }
  char test[100];
  char *work = getcwd(test, 100);

  pid_t pid, sid;

  pid = fork();
  if (pid < 0) {
    exit(EXIT_FAILURE); }
  if (pid > 0) {
    exit(EXIT_SUCCESS); }
  umask(0);

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }
  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1){
    chdir(work);
    pid_t cid;
    int stat_1;

    cid = fork();

    char folder[1000];
    snprintf(folder, 1000, "./");
    getTimestamp(folder);

    if(cid == 0){
      pid_t cid_2;
      int stat_2;

      cid_2 = fork();

      if(cid_2 == 0){
        char *argv[] = {"mkdir", folder, NULL};
        execv("/bin/mkdir", argv);
      } else {
        while((wait(&stat_2)) > 0);soal2b
        pid_t cid_3;
        int stat_3, i;
        char current[1000]; strcpy(current, folder);
        char file[1000];
        char link[1000];

        for(i=0; i<20; i++){
          strcpy(file, current); strcat(file, "/");
          getTimestamp(file);
          long int sec = time(NULL)%1000 + 100;
          snprintf(link, 1000, "https://picsum.photos/%ld", sec);
          cid_3 = fork();
          if(cid_3 == 0){
            char *argv[] = {"wget", "-O", file, link, NULL};
            execv("/usr/bin/wget", argv);
          } else {

          }
          sleep(5);
        
        }
        while((wait(&stat_3)) > 0);
        pid_t cid_4;
        int stat_4;

        cid_4 = fork();
         if(cid_4 == 0){
          char output[1000];
          snprintf(output, 1000, "%s.zip", current);
          char *argv[] = {"zip", "-r", output, current, NULL};
          execv("/usr/bin/zip", argv);
        } else {
          while((wait(&stat_4)) > 0);
          char *argv[] = {"rm", "-r", current, NULL};
          execv("/bin/rm", argv);
   	    }
      }
    } else {

    }
    sleep(30);
  }

  return 0;
}

void getTimestamp(char *path)
{
  char timeStr[10];

  time_t curtime;
  struct tm *loctime;
  curtime = time (NULL);
  loctime = localtime (&curtime);
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

void writeKillerA()
{
  FILE *temp;
  temp = fopen("killer.sh", "w");
  fputs("#!/bin/bash\n", temp);
  fputs("killOrder=$(echo $(pidof soal2))\n", temp);
  fputs("kill -9 $killOrder\n", temp);
  fputs("rm $0\n", temp);
  fclose(temp);

  pid_t tempCid;
  int tempStat;
  tempCid = fork();
  
  if(tempCid == 0){
    char *argv[]={"chmod", "+x", "killer.sh", NULL};
    execv("/bin/chmod", argv);
  } else {

  }
}

void writeKillerB()
{
  FILE *temp;
  temp = fopen("killer.sh", "w");
  fputs("#!/bin/bash\n", temp);
  fputs("killOrder=$(echo $(pidof soal2))\n", temp);
  fputs("killOrder=${killOrder##* }\n", temp);
  fputs("kill -9 $killOrder\n", temp);
  fputs("rm $0\n", temp);
  fclose(temp);

  pid_t tempCid;
  int tempStat;
  tempCid = fork();
  if(tempCid == 0){
    char *argv[]={"chmod", "+x", "killer.sh", NULL};
    execv("/bin/chmod", argv);

  } else {

  }
}
```
- `int main(int argc, char **argb){ if(strcmp(argb[1], "-a") == 0){writeKillerA();}` jika menjalankan program menggunakan argumen dengan parameter a
- `if(strcmp(argb[1], "-b") == 0){writeKillerB();}` jika menjalankan program menggunakan argumen dengan parameter b
- `pid = fork();` untuk membuat proses baru
-  `exit(EXIT_FAILURE); }` Jika gagal proses akan berhenti
- Soal 2a :
```
  while(1){
    chdir(work);
    pid_t cid;
    int stat_1;

    cid = fork();

    char folder[1000];
    snprintf(folder, 1000, "./");
    getTimestamp(folder);

    if(cid == 0){
      pid_t cid_2;
      int stat_2;

      cid_2 = fork();

      if(cid_2 == 0){
        char *argv[] = {"mkdir", folder, NULL};
        execv("/bin/mkdir", argv);
```
- soal 2b :
- `else {while((wait(&stat_2)) > 0);` untuk menunggu dan memastikan bahwa folder telah terbentuk
- `for(i=0; i<20; i++)` melakukan looping (untuk download gambar) sebanyak 20
- `strcpy(file, current); strcat(file, "/"); getTimestamp(file); long int sec = time(NULL)%1000 + 100;` merupakan ukuran gambar yang di download
-  `snprintf(link, 1000, "https://picsum.photos/%ld", sec);` menggabungkan link tempat download gambar dengan ukuran gambar ke dalam variabel link
- `if(cid_3 == 0){char *argv[] = {"wget", "-O", file, link, NULL};` menjalankan command wget link download tertera dalam variabel link mengunakan parameter -O untuk merename gambar hasil download sesuai dengan isi variabel file
- `execv("/usr/bin/wget", argv);` untuk menjalankan command wget
- `sleep(5);` jeda 5 detik sebelum process dijalankan      
- Soal 2c :
- `if(cid_4 == 0)` jika child process yang bernama cid_4 berjalan maka snprintf(output, 1000, "%s.zip", current); menggabungkan nama folder menjadi namafolder.zip kemudian menyimpannya dalam variabel output
- `char output[1000]; snprintf(output, 1000, "%s.zip", current); char *argv[] = {"zip", "-r", output, current, NULL};` parameter r (rekursi) agar file dalam folder juga ikut ter-zip dan terhapus setelah di-zip.
- `while((wait(&stat_4)) > 0);char *argv[] = {"rm", "-r", current, NULL};` menjalankan command dengan parameter rm menghapus folder yang telah di zip
- `execv("/bin/rm", argv);` untuk menjalankan command output. output merupakan namafolder.zip dan nama folder yang akan di-zip.
-  `sleep(30);` jeda 30 detik sebelum process dijalankan
-  `curtime = time (NULL);` untuk mengambil waktu lagi saat melalukan looping dan menyimpan dalam variabel curtime
- `loctime = localtime (&curtime);` mengambil localtime lagi saat melalukan looping dan menyimpan dalam variabel loctime
- Soal 2 d & e :
-  `FILE *temp;` memberi tau bahwa pointer temp merupakan sebuah file
-  `temp = fopen("killer.sh", "w");` membuat script bash dengan nama killer.sh dengan mode w agar file bisa di-write
- `fputs("#!/bin/bash\n", temp);` menulis #!/bin/bash\n\n karena file tersebut merupakan bash script
- `if(tempCid == 0){char *argv[]={"chmod", "+x", "killer.sh", NULL};` menjalankan command chmod untuk mengganti izin akses agar file bash killer.sh bisa langsung di eksekusi +x
- `execv("/bin/chmod", argv);` untuk menjalankan command chmod
           
## Soal 3
**A. Program buatan jaya harus bisa membuat dua direktori di “/home/[USER]/modul2/”. Direktori yang pertama diberi nama “indomie”, lalu
lima detik kemudian membuat direktori yang kedua bernama “sedaap”.**

**B. Kemudian program tersebut harus meng-ekstrak file jpg.zip di direktori “/home/[USER]/modul2/”. Setelah tugas sebelumnya selesai, ternyata tidak hanya itu tugasnya.**

**C. Diberilah tugas baru yaitu setelah di ekstrak, hasil dari ekstrakan tersebut (di dalam direktori “home/[USER]/modul2/jpg/”) harus dipindahkan sesuai dengan pengelompokan, semua file harus dipindahkan ke “/home/[USER]/modul2/sedaap/” dan semua direktori harus dipindahkan ke “/home/[USER]/modul2/indomie/”.**

**D. Untuk setiap direktori yang dipindahkan ke “/home/[USER]/modul2/indomie/” harus membuat dua file kosong. File yang pertama diberi nama “coba1.txt”, lalu 3 detik kemudian membuat file bernama “coba2.txt”. (contoh : “/home/[USER]/modul2/indomie/{nama_folder}/coba1.txt”). Karena Jaya terlalu banyak tugas dia jadi stress, jadi bantulah Jaya agar bisa membuat program tersebut.
Catatan :- Tidak boleh memakai system().
         - Tidak boleh memakai function C mkdir() ataupun rename().
         - Gunakan exec dan fork
         - Direktori “.” dan “..” tidak termasuk**
         
CODE :
```
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main (){
    pid_t cid;
    int stat;

    cid=fork();
    if (cid < 0){
        exit(EXIT_FAILURE); }
    if(cid == 0){
        char *var[] = {"mkdir","-p","/home/linuxlite/modul2/indomie",(char *)NULL};
        execv("/bin/mkdir",var);}
    else{
        while(wait(&stat)>0);
    cid=fork();
    if (cid < 0){
        exit(EXIT_FAILURE); }
    if(cid==0){
        sleep(5);
        char *var[] = {"mkdir","-p","/home/linuxlite/modul2/sedaap",(char *)NULL};
        execv("/bin/mkdir",var);}
    else{
        while(wait(&stat)>0);
    cid=fork();
    if (cid < 0){
        exit(EXIT_FAILURE); }
    if(cid==0){
        char *var[] = {"unzip","/home/linuxlite/modul2/jpg.zip","-d","/home/linuxlite/modul2",(char *)NULL};
        execv("/usr/bin/unzip",var);}
    else{
        while(wait(&stat)>0);
    cid=fork();
    if (cid < 0){
        exit(EXIT_FAILURE); }
    if(cid==0){
        char *var[] = {"find","/home/linuxlite/modul2/jpg/","-type","f","-exec","/bin/mv","-t","/home/linuxlite/modul2/sedaap","{}",";",(char *)NULL};
        execv("/usr/bin/find",var);}
    else{
        while(wait(&stat)>0);
    cid=fork();
    if (cid < 0){
        exit(EXIT_FAILURE); }
    if(cid == 0){
        char *var[] = {"find","/home/linuxlite/modul2/jpg/","-mindepth","1","-type","d","-exec","/bin/mv","-t","/home/linuxlite/modul2/indomie","{}",";",(char *)NULL};
        execv("/usr/bin/find",var);}
    else{
        while(wait(&stat)>0);
    cid=fork();
    if (cid < 0){
        exit(EXIT_FAILURE); }
    if(cid==0){
        char *var[] = {"find","/home/linuxlite/modul2/indomie/","-mindepth","1","-type","d","-exec","touch","{}/coba1.txt","'\'",";",(char *)NULL};
        execv("/usr/bin/find",var);}
    else{
        while(wait(&stat)>0);
        sleep(3);
        char *var[] = {"find","/home/linuxlite/modul2/indomie/","-mindepth","1","-type","d","-exec","touch","{}/coba2.txt","'\'",";",(char *)NULL};
        execv("/usr/bin/find",var);}
        }
        }
      }
    }
  }
}

```
- `cid=fork();` 
untuk membuat proses baru
- `exit(EXIT_FAILURE);` 
Jika gagal proses akan berhenti
- `  if(cid == 0){ char *var[] = {"mkdir","-p","/home/linuxlite/modul2/indomie",(char *)NULL};` child process untuk membuat direktori baru pada path /home/linuxlite/modul2 yang dinamakan folder indomie
- `execv("/bin/mkdir",var);` digunakan agar process sebelumnya dapat berjalan
-  `else{while(wait(&stat)>0);}`process selanjutnya adalah parent process sehingga child process dapat dijalankan terlebih dahulu
- `if(cid==0){sleep(5); char *var[] = {"mkdir","-p","/home/linuxlite/modul2/sedaap",(char *)NULL};` jeda 5 detik sebelum process dijalankan, child process untuk membuat direktori baru pada path /home/linuxlite/modul2 yang dinamakan folder sedaap
- `else{ while(wait(&stat)>0);` process selanjutnya adalah parent process sehingga child process dapat dijalankan terlebih dahulu
- `if(cid==0){char *var[] = {"unzip","/home/linuxlite/modul2/jpg.zip","-d","/home/linuxlite/modul2",(char *)NULL};` melakukan unzip file jpg.zip pada path /home/linuxlite/Downloads menuju direktori modul2
- `execv("/usr/bin/unzip",var);}` path unzip agar process sebelumnya dapat berjalan
- `if(cid==0){char *var[] = {"find","/home/linuxlite/modul2/jpg/","-type","f","-exec","/bin/mv","-t","/home/linuxlite/modul2/sedaap","{}",";",(char *)NULL};` melakukan pemindahan file pada direktori jpg pada modul2 kedalam direktori sedaap
- `if(cid == 0){char *var[] = {"find","/home/linuxlite/modul2/jpg/","-mindepth","1","-type","d","-exec","/bin/mv","-t","/home/linuxlite/modul2/indomie","{}",";",(char *)NULL};execv("/usr/bin/find",var);}` perintah untuk memindahkan direktori yang ada pada direktori jpg pada modul2 kedalam direktori indomie
-  `if(cid==0){char *var[] = {"find","/home/linuxlite/modul2/indomie/","-mindepth","1","-type","d","-exec","touch","{}/coba1.txt","'\'",";",(char *)NULL};` untuk membuat file coba1.txt pada direktori indomie
-  `sleep(3);` jeda 3 detik sebelum process dijalankan
-  `char *var[] = {"find","/home/linuxlite/modul2/indomie/","-mindepth","1","-type","d","-exec","touch","{}/coba2.txt","'\'",";",(char *)NULL};` untuk membuat file coba2.txt pada direktori indomie

  


        



