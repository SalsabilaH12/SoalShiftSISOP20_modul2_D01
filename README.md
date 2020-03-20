# SoalShiftSisopP20_modul2_D01

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
- `cid=fork();` untuk membuat proses baru
