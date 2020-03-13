# SoalShiftSisopP20_modul2_D01

## Soal 1
**A. Program menerima 4 argumen berupa:
  i. Detik: 0-59 atau * (any value)
  ii. Menit: 0-59 atau * (any value)
  iii. Jam: 0-23 atau * (any value)
  iv. Path file .sh
  B. Program akan mengeluarkan pesan error jika argumen yang diberikan tidak sesuai
  C. Program hanya menerima 1 config cron
  D. Program berjalan di background (daemon)
  E. Tidak boleh menggunakan fungsi system()
  Contoh: ./program \* 34 7 /home/somi/test.sh
  Program dengan argumen seperti contoh di atas akan menjalankan script test.sh setiap detik pada jam 07:34.**

## Soal 2 
**A. Pertama-tama, Kiwa membuat sebuah folder khusus, di dalamnya dia membuat sebuah program C yang per 30 detik membuat sebuah folder dengan nama timestamp [YYYY-mm-dd_HH:ii:ss].
  B. Tiap-tiap folder lalu diisi dengan 20 gambar yang di download dari https://picsum.photos/, dimana tiap gambar di download setiap 5 detik. Tiap gambar berbentuk persegi dengan ukuran (t%1000)+100 piksel dimana t adalahdetik Epoch Unix. Gambar tersebut diberi nama dengan format timestamp [YYYY-mm-dd_HH:ii:ss].
  C. Agar rapi, setelah sebuah folder telah terisi oleh 20 gambar, folder akan di zip dan folder akan di delete(sehingga hanya menyisakan .zip).
  D. Karena takut program tersebut lepas kendali, Kiwa ingin program tersebut men- generate sebuah program "killer" yang siap di run(executable) untuk menterminasi semua operasi program tersebut. Setelah di run, program yang menterminasi ini lalu akan mendelete dirinya sendiri.
  E. Kiwa menambahkan bahwa program utama bisa dirun dalam dua mode, yaitu MODE_A dan MODE_B. untuk mengaktifkan MODE_A, program harus dijalankan dengan argumen -a. Untuk MODE_B, program harus dijalankan dengan argumen b. Ketika dijalankan dalam MODE_A, program utama akan langsung menghentikan semua operasinya ketika program killer dijalankan. Untuk MODE_B, ketika program killer dijalankan, program utama akan berhenti tapi membiarkan proses di setiap folder yang masih berjalan sampai selesai(semua folder terisi gambar, terzip lalu di delete). Kiwa lalu terbangun dan sedih karena menyadari programnya hanya sebuah mimpi. Buatlah program dalam mimpi Kiwa jadi nyata!
  Catatan: - Tidak boleh memakai system().
           - Program utama harus ter-detach dari terminal
  Hint: 
           - Gunakan fitur picsum.photos untuk mendapatkan gambar dengan ukuran tertentu
           - Epoch Unix bisa didapatkan dari time()**
## Soal 3
**A. Program buatan jaya harus bisa membuat dua direktori di “/home/[USER]/modul2/”. Direktori yang pertama diberi nama “indomie”, lalu
lima detik kemudian membuat direktori yang kedua bernama “sedaap”.
  B. Kemudian program tersebut harus meng-ekstrak file jpg.zip di direktori “/home/[USER]/modul2/”. Setelah tugas sebelumnya selesai, ternyata tidak hanya itu tugasnya.
  C. Diberilah tugas baru yaitu setelah di ekstrak, hasil dari ekstrakan tersebut (di dalam direktori “home/[USER]/modul2/jpg/”) harus dipindahkan sesuai dengan pengelompokan, semua file harus dipindahkan ke “/home/[USER]/modul2/sedaap/” dan semua direktori harus dipindahkan ke “/home/[USER]/modul2/indomie/”.
  D. Untuk setiap direktori yang dipindahkan ke “/home/[USER]/modul2/indomie/” harus membuat dua file kosong. File yang pertama diberi nama “coba1.txt”, lalu 3 detik kemudian membuat file bernama “coba2.txt”. (contoh : “/home/[USER]/modul2/indomie/{nama_folder}/coba1.txt”). Karena Jaya terlalu banyak tugas dia jadi stress, jadi bantulah Jaya agar bisa membuat program tersebut.
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
#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

int status;
int main(){
pid_t cid1;
char path[100];
char indomiepath[100];
sprintf(path, 
              "/home/linuxlite/modul2/");


cid1 = fork();

if (cid1 < 0){
  exit(EXIT_FAILURE);
}

if (cid1 == 0){
sprintf(indomiepath, 
              "%s/indomie", path);

char *var[] = {"mkdir", "-p", indomiepath, NULL};
execv("/bin/mkdir", var);
} else {
while ((wait(&status)) > 0);

pid_t cid2;
cid2 = fork();
if (cid2 <  0){
  exit(EXIT_FAILURE);
}

if (cid2 == 0){
sleep(5);
char sedaappath[100];
sprintf(sedaappath, 
              "%s/sedaap", path);
char *var[] = {"mkdir", "-p", sedaappath, NULL};
execv("/bin/mkdir", var);
}else{
  while ((wait(&status)) > 0);
    pid_t cid6;
    cid6 = fork();
    //soal 3b
    if (cid6 < 0){
      exit(EXIT_FAILURE);
    }
    if (cid6== 0){
      char* var[] = {"unzip", "/home/linuxlite/modul2/jpg.zip", NULL};
      execv("/usr/bin/unzip", var);
    } else{
  while ((wait(&status)) > 0);
  char jpgpath[100];
  sprintf(jpgpath, "%sjpg/",path);
  chdir(jpgpath);
  DIR *direct;
  direct = opendir(".");
  struct dirent *dir;
  if(direct){
    while((dir = readdir(direct)) != NULL){
      pid_t cid3;
      struct stat st;
      stat(dir->d_name, &st);
      cid3 = fork();
      if(cid3 < 0){
        exit(EXIT_FAILURE);
      }
      if(cid3 == 0){
        char filepath[100];
        sprintf(filepath,"%s",jpgpath);
 strcat(filepath,dir->d_name);
        if(S_ISDIR(st.st_mode)){
          if(strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0);
              else{
                pid_t cid4;
                cid4 = fork();
                if(cid4 < 0){
                  exit(EXIT_FAILURE);
                }
                if(cid4 == 0){
                  char* var[] = {"mv", filepath, indomiepath, NULL};
                  execv("/bin/mv", var);
                }else{
                  while((dir = readdir(direct)) != NULL){
                  pid_t cid5;
                  cid5 = fork();
                  if(cid5 < 0){
                    exit(EXIT_FAILURE);
                  }
                  if(cid5 == 0){
                    char cobapath[100];
                    sprintf(cobapath, "%s",indomiepath);
      strcat(cobapath,dir->d_name);
      strcat(cobapath,"/coba1.txt");
                    char *var[] = {"touch", "-p", cobapath, NULL};
        execv("usr/bin/touch", var);
                  }else{
                    char cobapath[100];
                    sprintf(cobapath, "%s",indomiepath);
      strcat(cobapath,dir->d_name);
      strcat(cobapath,"/coba2.txt");
                    char *var[] = {"touch", "-p", cobapath, NULL};
      execv("usr/bin/touch", var);
                  }
                }
              }
        }
      }else{
        char* var[] = {"mv", filepath, "/home/linuxlite/modul2/sedaap/", NULL};
        execv("/bin/mv", var);
      }
  }
} 
closedir(direct);
}
}
}
}
}

```
