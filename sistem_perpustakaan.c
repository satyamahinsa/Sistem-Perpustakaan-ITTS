#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <string.h>

// struct pengunjung digunakan untuk menampung kumpulan variabel dari berbagai tipe data yang dibutuhkan oleh setiap orang yang berkunjung ke perpustakaan
typedef struct {
  char nama_lengkap[100], waktu_berkunjung[100], pengambilan_data[100];
  int nim, banyak_buku, id_buku_yang_dipinjam[5];
} pengunjung;

// struct buku digunakan untuk menampung kumpulan variabel dari berbagai tipe data yang dibutuhkan oleh setiap buku yang tersedia di perpustakaan
typedef struct {
  char judul[100], pengarang[100], penerbit[100], kategori[100], pengambilan_data[100];
  int id, tahun_terbit, jumlah_halaman, status;
} buku;

int total_pengunjung = 0; // total dari banyaknya orang yang berkunjung ke perpustakaan
int total_buku = 0; // total dari banyaknya buku yang tersedia di perpustakaan
pengunjung data_pengunjung[100]; // database yang digunakan untuk menampung data lengkap dari pengunjung
buku data_buku[100]; // database yang digunakan untuk menampung data lengkap dari buku

// fungsi waktu_saat_ini() digunakan untuk mendapatkan waktu saat ini, nantinya berhubungan dengan data pengunjung
char* waktu_saat_ini() {
  time_t waktu;
  struct tm *info_waktu;
  time(&waktu);
  info_waktu = localtime(&waktu);

  return asctime(info_waktu);
}

// fungsi pengubah_string() digunakan untuk mengubah style penulisan di database dan data yang muncul pada user interface
char* pengubah_string(char ganti, char data[]) {
  for(int i = 0; i < strlen(data); i++) {
    if(ganti == ' ' && data[i] == ganti) {
      data[i] = '_';
    } else if(ganti == '_' && data[i] == ganti) {
      data[i] = ' ';
    }
  }
  return data;
}

// fungsi sortir_pengunjung() digunakan untuk melakukan pengurutan (sortir) berdasarkan nama dan nim dari data pengunjung
void sortir_pengunjung(int pilihan, pengunjung *data_pengunjung) {
  switch (pilihan) {
    case 1:
      for(int i = 0; i < total_pengunjung - 1; i++) {
        pengunjung temp;
        for(int j = 0; j < total_pengunjung - 1 - i; j++) {
          if(data_pengunjung[j].nama_lengkap[0] > data_pengunjung[j + 1].nama_lengkap[0]) {
            temp = data_pengunjung[j];
            data_pengunjung[j] = data_pengunjung[j + 1];
            data_pengunjung[j + 1] = temp;
          }
        }
      }
      break;
    case 2:
      for(int i = 0; i < total_pengunjung - 1; i++) {
        pengunjung temp;
        for(int j = 0; j < total_pengunjung - 1 - i; j++) {
          if(data_pengunjung[j].nim > data_pengunjung[j + 1].nim) {
            temp = data_pengunjung[j];
            data_pengunjung[j] = data_pengunjung[j + 1];
            data_pengunjung[j + 1] = temp;
          }
        }
      }
      break;
    default:
      printf("Salah Input!\n");
  }

  for(int i = 0; i < total_pengunjung; i++) {
    printf("%d. %s (%d)\n", i + 1, pengubah_string('_', data_pengunjung[i].nama_lengkap), data_pengunjung[i].nim);
  }
}

// fungsi sortir_buku() digunakan untuk melakukan pengurutan (sortir) berdasarkan judul dan id dari data buku
void sortir_buku(int pilihan, buku *data_buku) {
  switch (pilihan) {
    case 1:
      for(int i = 0; i < total_buku - 1; i++) {
        buku temp;
        for(int j = 0; j < total_buku - 1 - i; j++) {
          if(data_buku[j].judul[0] > data_buku[j + 1].judul[0]) {
            temp = data_buku[j];
            data_buku[j] = data_buku[j + 1];
            data_buku[j + 1] = temp;
          }
        }
      }
      break;
    case 2:
      for(int i = 0; i < total_buku - 1; i++) {
        buku temp;
        for(int j = 0; j < total_buku - 1 - i; j++) {
          if(data_buku[j].id > data_buku[j + 1].id) {
            temp = data_buku[j];
            data_buku[j] = data_buku[j + 1];
            data_buku[j + 1] = temp;
          }
        }
      }

      break;
    default:
      printf("Salah Input!\n");
  }

  for(int i = 0; i < total_buku; i++) {
    printf("%d. %s (%d)\n", i + 1, pengubah_string('_', data_buku[i].judul), data_buku[i].id);
  }
}

// fungsi peminjaman_buku() digunakan untuk mengubah status buku yang dipinjam menjadi 0 (dipinjam)
// fungsi ini juga sudah terintegrasi dengan data pengunjung yang meminjam buku
void peminjaman_buku(int id_buku_yang_dipinjam) {
  for(int i = 0; i < total_buku; i++) {
    if(id_buku_yang_dipinjam == data_buku[i].id) {
      data_buku[i].status = 0;
    }
  }
}

// fungsi data_pengunjung_lengkap() digunakan untuk menampilkan data pengunjung secara lengkap berdasarkan database pengunjung
void data_pengunjung_lengkap(int i) {
  int data = 0;
  printf("Nama Lengkap: %s\n", pengubah_string('_', data_pengunjung[i].nama_lengkap));
  printf("NIM: %d\n", data_pengunjung[i].nim);
  printf("Waktu Berkunjung: %s\n", data_pengunjung[i].waktu_berkunjung);
  if(total_buku == 0) {
    printf("Buku yang dipinjam: ID Buku tidak ditemukan!\n");
  } else {
    for(int j = 0; j < total_buku; j++) {
      for(int k = 0; k < data_pengunjung[i].banyak_buku; k++) {
        if(data_pengunjung[i].id_buku_yang_dipinjam[k] == data_buku[j].id) {
          printf("Buku yang dipinjam: %s (%d)\n", data_buku[j].judul, data_buku[j].id);
          data = 1;
        }
      }
    }
    
    if(data == 0) {
      printf("Buku yang dipinjam: ID Buku tidak ditemukan!\n");
    }
  }
}

// fungsi data_buku_lengkap() digunakan untuk menampilkan data buku secara lengkap berdasarkan database buku
void data_buku_lengkap(int i) {
  printf("ID Buku: %d\n", data_buku[i].id);
  printf("Judul Buku: %s\n", pengubah_string('_', data_buku[i].judul));
  printf("Pengarang: %s\n", pengubah_string('_', data_buku[i].pengarang));
  printf("Penerbit: %s\n", pengubah_string('_', data_buku[i].penerbit));
  printf("Tahun Terbit: %d\n", data_buku[i].tahun_terbit);
  printf("Kategori: %s\n", pengubah_string('_', data_buku[i].kategori));
  printf("Jumlah Halaman: %d halaman\n", data_buku[i].jumlah_halaman);
  if(data_buku[i].status == 1) {
    printf("Status: Tersedia\n");
  } else if(data_buku[i].status == 0) {
    printf("Status: Dipinjam\n");
  }
}

// fungsi file_pengunjung() termasuk file handling yang digunakan untuk membuat database pengunjung dalam bentuk file data_pengunjung.txt yang akan terus up to date berdasarkan pengunjung yang datang ke perpustakaan 
void file_pengunjung(pengunjung *data_pengunjung) {
  FILE *file_data_pengunjung = fopen("data_pengunjung.txt", "w");
  for(int i = 0; i < total_pengunjung; i++) {
    fprintf(file_data_pengunjung, "%d. ", i + 1);
    fprintf(file_data_pengunjung, "%s ", pengubah_string(' ', data_pengunjung[i].nama_lengkap));
    fprintf(file_data_pengunjung, "%d ", data_pengunjung[i].nim);
    fprintf(file_data_pengunjung, "%s ", data_pengunjung[i].waktu_berkunjung);
    fprintf(file_data_pengunjung, "%d ", data_pengunjung[i].banyak_buku);
    for(int j = 0; j < data_pengunjung[i].banyak_buku; j++) {
      fprintf(file_data_pengunjung, "%d ", data_pengunjung[i].id_buku_yang_dipinjam[j]);
    }
    fprintf(file_data_pengunjung, "\n");
  }
  fclose(file_data_pengunjung);
}

// fungsi baca_file_pengunjung() termasuk file handling yang digunakan untuk membaca database pengunjung yang ada di dalam file data_pengunjung.txt 
void baca_file_pengunjung(pengunjung *data_pengunjung) {
  FILE *file_data_pengunjung = fopen("data_pengunjung.txt", "r");
  while(fgets(data_pengunjung->pengambilan_data, sizeof(data_pengunjung), file_data_pengunjung)) {
    fscanf(file_data_pengunjung, " %s %d %s %d ", &data_pengunjung[total_pengunjung].nama_lengkap, &data_pengunjung[total_pengunjung].nim, &data_pengunjung[total_pengunjung].waktu_berkunjung, &data_pengunjung[total_pengunjung].banyak_buku);
    for(int i = 0; i < data_pengunjung[total_pengunjung].banyak_buku; i++) {
      fscanf(file_data_pengunjung, "%d ", &data_pengunjung[total_pengunjung].id_buku_yang_dipinjam[i]);
    }
    total_pengunjung++;
  }
  fclose(file_data_pengunjung);
}

// fungsi file_buku() termasuk file handling yang digunakan untuk membuat database buku dalam bentuk file data_buku.txt yang akan terus up to date berdasarkan buku yang ada di perpustakaan 
void file_buku(buku *data_buku) {
  FILE *file_data_buku = fopen("data_buku.txt", "w");
  for(int i = 0; i < total_buku; i++) {
    fprintf(file_data_buku, "\n");
    fprintf(file_data_buku, "%d ", data_buku[i].id);
    fprintf(file_data_buku, "%s ", pengubah_string(' ', data_buku[i].judul));
    fprintf(file_data_buku, "%s ", pengubah_string(' ', data_buku[i].pengarang));
    fprintf(file_data_buku, "%s ", pengubah_string(' ', data_buku[i].penerbit));
    fprintf(file_data_buku, "%d ", data_buku[i].tahun_terbit);
    fprintf(file_data_buku, "%s ", pengubah_string(' ', data_buku[i].kategori));
    fprintf(file_data_buku, "%d ", data_buku[i].jumlah_halaman);
    fprintf(file_data_buku, "%d", data_buku[i].status);
  }
  fclose(file_data_buku);
}

// fungsi baca_file_buku() termasuk file handling yang digunakan untuk membaca database buku yang ada di dalam file data_buku.txt 
void baca_file_buku(buku *data_buku) {
  FILE *file_data_buku = fopen("data_buku.txt", "r");
  while(fgets(data_buku->pengambilan_data, sizeof(data_buku), file_data_buku)) {
    fscanf(file_data_buku, "%d %s %s %s %d %s %d %d", &data_buku[total_buku].id, &data_buku[total_buku].judul, &data_buku[total_buku].pengarang, &data_buku[total_buku].penerbit, &data_buku[total_buku].tahun_terbit, &data_buku[total_buku].kategori, &data_buku[total_buku].jumlah_halaman, &data_buku[total_buku].status);
    total_buku++;
  }
  fclose(file_data_buku);
}

// fungsi tambah_pengunjung() digunakan untuk menambah data pengunjung yang datang ke perpustakaan ke dalam database pengunjung dengan data yang diinput, yaitu nama lengkap, nim, waktu berkunjung, banyak buku yang dipinjam, dan id buku yang dipinjam
void tambah_pengunjung(pengunjung *data_pengunjung, buku *data_buku) {
  char input;
  do {
    printf("=============================\n");
    printf("      TAMBAH PENGUNJUNG      \n");
    printf("=============================\n");
    printf("Nama Lengkap: ");
    fflush(stdin);
    scanf("%[^\n]%*c", &data_pengunjung[total_pengunjung].nama_lengkap);
    printf("NIM: ");
    scanf("%d", &data_pengunjung[total_pengunjung].nim);
    strcpy(data_pengunjung[total_pengunjung].waktu_berkunjung, waktu_saat_ini());
    for(int i = 0; i < strlen(data_pengunjung[total_pengunjung].waktu_berkunjung); i++) {
      if(data_pengunjung[total_pengunjung].waktu_berkunjung[i] == ' ') {
        data_pengunjung[total_pengunjung].waktu_berkunjung[i] = '/';
      } else if(data_pengunjung[total_pengunjung].waktu_berkunjung[i] == '\n') {
        data_pengunjung[total_pengunjung].waktu_berkunjung[i] = '\0';
      }
    }
    printf("Banyak buku yang dipinjam (max: 5): ");
    scanf("%d", &data_pengunjung[total_pengunjung].banyak_buku);
    if(data_pengunjung[total_pengunjung].banyak_buku > 5) {
      break;
    } else {
      for(int i = 0; i < data_pengunjung[total_pengunjung].banyak_buku; i++) {
        printf("ID Buku yang dipinjam: ");
        scanf("%d", &data_pengunjung[total_pengunjung].id_buku_yang_dipinjam[i]);
        peminjaman_buku(data_pengunjung[total_pengunjung].id_buku_yang_dipinjam[i]);
      }
    }
    total_pengunjung++;
    file_pengunjung(data_pengunjung);
    file_buku(data_buku);
    printf("Apakah ingin input data lagi? (y/n): ");
    scanf("%s", &input);
  } while(input != 'n');
  printf("\n");
}

// fungsi detail_pengunjung() digunakan untuk menampilkan data pengunjung secara lengkap
void detail_pengunjung(pengunjung *data_pengunjung) {
  printf("=============================\n");
  printf("      DETAIL PENGUNJUNG      \n");
  printf("=============================\n");

  if(total_pengunjung == 0) {
    printf("Data Pengunjung tidak ada\n");
  } else {
    char input;
    do {
      int nim, data = 0;
      printf("Masukkan NIM: ");
      scanf("%d", &nim);
      for(int i = 0; i < total_pengunjung; i++) {
        if(data_pengunjung[i].nim == nim) {
          data_pengunjung_lengkap(i);
          data = 1;
          break;
        }
      }

      if(data == 0) {
        printf("NIM tidak ditemukan!\n");
        printf("Ingin mencari lagi? (y/n): ");
        fflush(stdin);
        scanf("%c", &input);
      } else {
        break;
      }
    } while(input != 'n');
  }

  getch();
  printf("\n");
}

// fungsi edit_pengunjung() digunakan untuk melakukan edit data pengunjung sesuai dengan data yang ingin diedit
void edit_pengunjung(pengunjung *data_pengunjung) {
  printf("=============================\n");
  printf("       EDIT PENGUNJUNG       \n");
  printf("=============================\n");

  if(total_pengunjung == 0) {
    printf("Data Pengunjung tidak ada\n");
  } else {
    char input;
    do {
      int nim, data = 0;
      printf("Masukkan NIM: ");
      scanf("%d", &nim);
      for(int i = 0; i < total_pengunjung; i++) {
        if(data_pengunjung[i].nim == nim) {
          printf("1. Nama Lengkap\n");
          printf("2. NIM\n");
          printf("3. ID Buku yang dipinjam\n");
          printf("Pilih bagian yang mau diedit (1-3): ");
          int edit;
          scanf("%d", &edit);
          switch (edit) {
            case 1:
              printf("Nama Lengkap (%s): ", pengubah_string('_', data_pengunjung[i].nama_lengkap));
              fflush(stdin);
              scanf("%[^\n]%*c", &data_pengunjung[i].nama_lengkap);
              printf("Edit data pengunjung berhasil!");
              break;
            case 2:
              printf("NIM (%d): ", data_pengunjung[i].nim);
              scanf("%d", &data_pengunjung[i].nim);
              printf("Edit data pengunjung berhasil!");
              break;
            case 3:
              for(int j = 0; j < data_pengunjung[i].banyak_buku; j++) {
                printf("ID Buku yang Dipinjam (%d): ", data_pengunjung[i].id_buku_yang_dipinjam[j]);
                scanf("%d", &data_pengunjung[i].id_buku_yang_dipinjam[j]);
              }
              printf("Edit data pengunjung berhasil!");
              break;
            default:
              printf("Salah Input!\n");
          }
          data = 1;
          file_pengunjung(data_pengunjung);
          printf("\n");
          break;
        }
      }

      if(data == 0) {
        printf("NIM tidak ditemukan!\n");
        printf("Ingin mencari lagi? (y/n): ");
        fflush(stdin);
        scanf("%c", &input);
      } else {
        break;
      }
    } while(input != 'n');
  }

  getch();
  printf("\n");
}

// fungsi hapus_pengunjung() digunakan untuk menghapus data pengunjung yang ingin dihapus
void hapus_pengunjung(pengunjung *data_pengunjung, buku *data_buku) {
  printf("=============================\n");
  printf("       HAPUS PENGUNJUNG      \n");
  printf("=============================\n");

  if(total_pengunjung == 0) {
    printf("Data Pengunjung tidak ada\n");
  } else {
    char input, hapus;
    do {
      int nim, data = 0;
      printf("Masukkan NIM: ");
      scanf("%d", &nim);
      for(int i = 0; i < total_pengunjung; i++) {
        if(data_pengunjung[i].nim == nim) {
          data_pengunjung_lengkap(i);
          printf("Yakin untuk menghapus data pengunjung ini? (y/n): ");
          fflush(stdin);
          scanf("%c", &hapus);
          if(hapus == 'y') {
            for(int j = 0; j < total_buku; j++) {
              for(int k = 0; k < data_pengunjung[i].banyak_buku; k++) {
                if(data_pengunjung[i].id_buku_yang_dipinjam[k] == data_buku[j].id) {
                  data_buku[j].status = 1;
                }
              }
            }
            for(int j = i; j < total_pengunjung; j++) {
              data_pengunjung[j] = data_pengunjung[j + 1];
            }
            total_pengunjung--;
            file_pengunjung(data_pengunjung);
            file_buku(data_buku);
            printf("Hapus data pengunjung berhasil!");
          } else if(hapus == 'n') {
            printf("Hapus data pengunjung gagal!");
          }
          data = 1;
          printf("\n");
          break;
        }
      }

      if(data == 0) {
        printf("NIM tidak ditemukan!\n");
        printf("Ingin mencari lagi? (y/n): ");
        fflush(stdin);
        scanf("%c", &input);
      } else {
        break;
      }
    } while(input != 'n');
  }

  getch();
  printf("\n");
}

// fungsi list_pengunjung() digunakan untuk melihat data pengunjung secara keseluruhan yang di dalamnya terdapat fitur pengurutan (sorting) berdasarkan nama dan nim
void list_pengunjung(pengunjung *data_pengunjung) {
  printf("=============================\n");
  printf("       LIST PENGUNJUNG       \n");
  printf("=============================\n");
  printf("1. Nama\n");
  printf("2. NIM\n");
  printf("Sortir berdasarkan (1-2): ");
  int pilihan;
  scanf("%d", &pilihan);
  
  if(total_pengunjung == 0) {
    printf("Data Pengunjung tidak ada\n");
  } else {
    sortir_pengunjung(pilihan, data_pengunjung);
  }

  getch();
  printf("\n");
}

// fungsi menu_pengunjung() digunakan untuk menampilkan menu utama yang berisi beberapa pilihan dalam pengolahan data pengunjung
void menu_pengunjung() {
  int input;
  do {
    printf("=============================\n");
    printf("       DATA PENGUNJUNG       \n");
    printf("=============================\n");
    printf("1. Tambah Pengunjung\n");
    printf("2. Detail Pengunjung\n");
    printf("3. Edit Pengunjung\n");
    printf("4. Hapus Pengunjung\n");
    printf("5. List Data Pengunjung\n");
    printf("6. Kembali\n");
    printf("Masukkan pilihan: ");
    scanf("%d", &input);
    printf("\n");
    switch (input) {
      case 1:
        tambah_pengunjung(data_pengunjung, data_buku);
        break;
      case 2:
        detail_pengunjung(data_pengunjung);
        break;
      case 3:
        edit_pengunjung(data_pengunjung);
        break;
      case 4:
        hapus_pengunjung(data_pengunjung, data_buku);
        break;
      case 5:
        list_pengunjung(data_pengunjung);
        break;
      case 6:
        break;
      default:
        printf("Salah Input!\n\n");
    }
  } while(input != 6);
}

// fungsi tambah_buku() digunakan untuk menambah data buku yang ada di perpustakaan ke dalam database buku dengan data yang diinput, yaitu id, judul, pengarang, penerbit, tahun terbit, kategori, jumlah halaman, dan status
void tambah_buku(buku *data_buku, pengunjung *data_pengunjung) {
  char input;
  do {
    printf("=============================\n");
    printf("          TAMBAH BUKU        \n");
    printf("=============================\n");
    printf("ID Buku: ");
    scanf("%d", &data_buku[total_buku].id);
    printf("Judul Buku: ");
    fflush(stdin);
    scanf("%[^\n]%*c", &data_buku[total_buku].judul);
    printf("Pengarang: ");
    fflush(stdin);
    scanf("%[^\n]%*c", &data_buku[total_buku].pengarang);
    printf("Penerbit: ");
    fflush(stdin);
    scanf("%[^\n]%*c", &data_buku[total_buku].penerbit);
    printf("Tahun Terbit: ");
    scanf("%d", &data_buku[total_buku].tahun_terbit);
    printf("Kategori: ");
    fflush(stdin);
    scanf("%[^\n]%*c", &data_buku[total_buku].kategori);
    printf("Jumlah Halaman: ");
    scanf("%d", &data_buku[total_buku].jumlah_halaman);
    if(total_pengunjung == 0) {
      data_buku[total_buku].status = 1;
    } else {
      for(int i = 0; i < total_pengunjung; i++) {
        for(int j = 0; j < data_pengunjung[i].banyak_buku; j++) {
          if(data_buku[total_buku].id == data_pengunjung[i].id_buku_yang_dipinjam[j]) {
            data_buku[total_buku].status = 0;
          } else {
            data_buku[total_buku].status = 1;
          }
        }
      }
    } 
    total_buku++;
    file_buku(data_buku);
    printf("Apakah ingin input data lagi? (y/n): ");
    scanf("%s", &input);
  } while(input != 'n');
  printf("\n");
}

// fungsi detail_buku() digunakan untuk menampilkan data buku secara lengkap
void detail_buku(buku *data_buku) {
  printf("=============================\n");
  printf("         DETAIL BUKU         \n");
  printf("=============================\n");

  if(total_buku == 0) {
    printf("Data Buku tidak ada\n");
  } else {
    char input;
    do {
      int id, data = 0;
      printf("Masukkan ID Buku: ");
      scanf("%d", &id);
      for(int i = 0; i < total_buku; i++) {
        if(data_buku[i].id == id) {
          data_buku_lengkap(i);
          data = 1;
          break;
        }
      }

      if(data == 0) {
        printf("ID Buku tidak ditemukan!\n");
        printf("Ingin mencari lagi? (y/n): ");
        fflush(stdin);
        scanf("%c", &input);
      } else {
        break;
      }
    } while(input != 'n');
  }

  getch();
  printf("\n");
}

// fungsi edit_buku() digunakan untuk melakukan edit data buku sesuai dengan data yang ingin diedit
void edit_buku(buku *data_buku) {
  printf("=============================\n");
  printf("          EDIT BUKU          \n");
  printf("=============================\n");

  if(total_buku == 0) {
    printf("Data Buku tidak ada\n");
  } else {
    char input;
    do {
      int id, data = 0;
      printf("Masukkan ID Buku: ");
      scanf("%d", &id);
      for(int i = 0; i < total_buku; i++) {
        if(data_buku[i].id == id) {
          printf("1. ID Buku\n");
          printf("2. Judul Buku\n");
          printf("3. Pengarang\n");
          printf("4. Penerbit\n");
          printf("5. Tahun Terbit\n");
          printf("6. Kategori\n");
          printf("7. Jumlah Halaman\n");
          printf("Pilih bagian yang mau diedit (1-7): ");
          int edit;
          scanf("%d", &edit);
          switch (edit) {
            case 1:
              printf("ID Buku (%d): ", data_buku[i].id);
              scanf("%d", &data_buku[i].id);
              printf("Edit data buku berhasil!");
              break;
            case 2:
              printf("Judul Buku (%s): ", data_buku[i].judul);
              fflush(stdin);
              scanf("%[^\n]%*c", &data_buku[i].judul);
              printf("Edit data buku berhasil!");
              break;
            case 3:
              printf("Pengarang (%s): ", pengubah_string('_', data_buku[i].pengarang));
              fflush(stdin);
              scanf("%[^\n]%*c", &data_buku[i].pengarang);
              printf("Edit data buku berhasil!");
              break;
            case 4:
              printf("Penerbit (%s): ", pengubah_string('_', data_buku[i].penerbit));
              fflush(stdin);
              scanf("%[^\n]%*c", &data_buku[i].penerbit);
              printf("Edit data buku berhasil!");
              break;
            case 5:
              printf("Tahun Terbit (%d): ", data_buku[i].tahun_terbit);
              scanf("%d", &data_buku[i].tahun_terbit);
              printf("Edit data buku berhasil!");
              break;
            case 6:
              printf("Kategori (%s): ", pengubah_string('_', data_buku[i].kategori));
              fflush(stdin);
              scanf("%[^\n]%*c", &data_buku[i].kategori);
              printf("Edit data buku berhasil!");
              break;
            case 7:
              printf("Jumlah Halaman (%d halaman): ", data_buku[i].jumlah_halaman);
              scanf("%d", &data_buku[i].jumlah_halaman);
              printf("Edit data buku berhasil!");
              break;
            default:
              printf("Salah Input!\n");
          }
          file_buku(data_buku);
          data = 1;
          printf("\n");
          break;
        }
      }

      if(data == 0) {
        printf("ID Buku tidak ditemukan!\n");
        printf("Ingin mencari lagi? (y/n): ");
        fflush(stdin);
        scanf("%c", &input);
      } else {
        break;
      }
    } while(input != 'n');
  }

  getch();
  printf("\n");
}

// fungsi hapus_buku() digunakan untuk menghapus data buku yang ingin dihapus
void hapus_buku(buku *data_buku) {
  printf("=============================\n");
  printf("          HAPUS BUKU         \n");
  printf("=============================\n");

  if(total_buku == 0) {
    printf("Data Buku tidak ada\n");
  } else {
    char input, hapus;
    do {
      int id, data;
      printf("Masukkan ID Buku: ");
      scanf("%d", &id);
      for(int i = 0; i < total_buku; i++) {
        if(data_buku[i].id == id) {
          data_buku_lengkap(i);
          printf("Yakin untuk menghapus data buku ini? (y/n): ");
          fflush(stdin);
          scanf("%c", &hapus);
          if(hapus == 'y') {
            for(int j = i; j < total_buku; j++) {
              data_buku[j] = data_buku[j + 1];
            }
            total_buku--;
            file_buku(data_buku);
            printf("Hapus data buku berhasil!");
          } else if(hapus == 'n') {
            printf("Hapus data buku gagal!");
          }
          data = 1;
          printf("\n");
          break;
        }
      }

      if(data == 0) {
        printf("ID Buku tidak ditemukan!\n");
        printf("Ingin mencari lagi? (y/n): ");
        fflush(stdin);
        scanf("%c", &input);
      } else {
        break;
      }
    } while(input != 'n');
  }

  getch();
  printf("\n");
}

// fungsi list_buku() digunakan untuk melihat data buku secara keseluruhan yang di dalamnya terdapat fitur pengurutan (sorting) berdasarkan judul dan id
void list_buku(buku *data_buku) {
  printf("=============================\n");
  printf("          LIST BUKU          \n");
  printf("=============================\n");
  printf("1. Judul\n");
  printf("2. ID\n");
  printf("Sortir berdasarkan (1-2): ");
  int pilihan;
  scanf("%d", &pilihan);

  if(total_buku == 0) {
    printf("Data Buku tidak ada\n");
  } else {
    sortir_buku(pilihan, data_buku);
  }

  getch();
  printf("\n");
}

// fungsi pengembalian_buku() digunakan untuk mengubah status buku yang dikembalikan menjadi 1 (tersedia) dan juga menghapus data pengunjung yang mengembalikan buku di database pengunjung
void pengembalian_buku(buku *data_buku, pengunjung *data_pengunjung) {
  printf("=============================\n");
  printf("      PENGEMBALIAN BUKU      \n");
  printf("=============================\n");

  if(total_buku == 0) {
    printf("Data Buku tidak ada\n");
  } else {
    char input;
    do {
      int id, data = 0;
      printf("Masukkan ID Buku: ");
      scanf("%d", &id);
      for(int i = 0; i < total_buku; i++) {
        if(data_buku[i].id == id) {
          data = 1;
          for(int j = 0; j < total_pengunjung; j++) {
            for(int k = 0; k < data_pengunjung[j].banyak_buku; k++) {
              if(data_pengunjung[j].id_buku_yang_dipinjam[k] == data_buku[i].id) {
                data_pengunjung_lengkap(j);
                data = 2;
                printf("Apakah data pengunjung sudah benar? (y/n): ");
                fflush(stdin);
                scanf("%c", &input);
                if(input == 'y') {
                  printf("Pengembalian buku berhasil dilakukan!\n");
                  data_buku[i].status = 1;
                  file_buku(data_buku);
                  for(int l = j; l < total_pengunjung; l++) {
                    data_pengunjung[l] = data_pengunjung[l + 1];
                  }
                  total_pengunjung--;
                  file_pengunjung(data_pengunjung);
                } else if(input == 'n') {
                  printf("Pengembalian buku gagal dilakukan!\n");
                  break;
                }
                break;
              }
            }
          }
        }
      }

      if(data == 1) {
        printf("Buku tersedia di perpustakaan\n");
        printf("Ingin mencari lagi? (y/n): ");
        fflush(stdin);
        scanf("%c", &input);
      } else if(data == 0) {
        printf("ID Buku tidak ditemukan!\n");
        printf("Ingin mencari lagi? (y/n): ");
        fflush(stdin);
        scanf("%c", &input);
      } else {
        break;
      }
    } while(input != 'n');
  }

  getch();
  printf("\n");
}

// fungsi menu_buku() digunakan untuk menampilkan menu utama yang berisi beberapa pilihan dalam pengolahan data buku
void menu_buku() {
  int input;
  do {
    printf("=============================\n");
    printf("          DATA BUKU          \n");
    printf("=============================\n");
    printf("1. Tambah Buku\n");
    printf("2. Detail Buku\n");
    printf("3. Edit Buku\n");
    printf("4. Hapus Buku\n");
    printf("5. List Data Buku\n");
    printf("6. Pengembalian Buku\n");
    printf("7. Kembali\n");
    printf("Masukkan pilihan: ");
    scanf("%d", &input);
    printf("\n");
    switch (input) {
      case 1:
        tambah_buku(data_buku, data_pengunjung);
        break;
      case 2:
        detail_buku(data_buku);
        break;
      case 3:
        edit_buku(data_buku);
        break;
      case 4:
        hapus_buku(data_buku);
        break;
      case 5:
        list_buku(data_buku);
        break;
      case 6:
        pengembalian_buku(data_buku, data_pengunjung);
        break;
      case 7:
        break;
      default:
        printf("Salah Input!\n\n");
    }
  } while(input != 7);
}

int main() {
  int input;
  baca_file_pengunjung(data_pengunjung);
  baca_file_buku(data_buku);
  do {
    printf("=============================\n");
    printf("      PERPUSTAKAAN ITTS      \n");
    printf("=============================\n");
    printf("1. Data Pengunjung\n");
    printf("2. Data Buku\n");
    printf("3. Keluar\n");
    printf("Masukkan pilihan: ");
    scanf("%d", &input);
    printf("\n");
    switch(input) {
      case 1:
        menu_pengunjung();
        break;
      case 2:
        menu_buku();
        break;
      default:
        printf("Salah Input!\n\n");
    }
  } while(input != 3);

  return 0;
} 