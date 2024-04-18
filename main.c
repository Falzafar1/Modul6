/**EL2008 Praktikum Pemecahan Masalah dengan C 2023/2024
 * Modul            : 6 - Linked List
 *Hari dan Tanggal  : Rabu, 17 April 2024
 *Nama (NIM)        : Naufal Afiq Muzaffar (13222025)
 *Asisten (NIM)     : Maheswara Apta (18320005)
 * Nama File        : main.c
 * Deskripsi        : Program untuk menyeleksi pegawai yang akan mendapatkan
 *                    promosi di suatu cabang perusahaan
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Pegawai {
    char Nama[50];
    int Jumlah;
    int Cabang;
    struct Pegawai* next; 
} Pegawai;

// Menghapus data dengan jumlah pemilih terbesar
void HapusData(Pegawai** NodeList, int xJumlah) { 
    
    if ((*NodeList)->Jumlah == xJumlah) { 
        *NodeList = (*NodeList)->next;
    }
    else {
        if ((*NodeList)->next != NULL) { 
            HapusData(&(*NodeList)->next, xJumlah);
        }
    }   
}

// Melakukan perulangan untuk mendapatkan kadndidat dengan pemilih terbanyak
void printLinkedList(struct Pegawai* head, int jumlahData) {
    int max=0;
    int hasil=0;
    Pegawai* coba = (Pegawai*) malloc(sizeof(Pegawai));
    int i,j;
    int n=jumlahData;

    // Print 3 Pegawai yang akan dipromosikan
    for (j = 0; j < 3; j++){
        coba = head;
        for (i = 0; i < n; i++){
          hasil = coba->Jumlah;
          coba = coba->next;
          if (hasil>max){
            max = hasil;
          }

          else if (hasil == max){
            HapusData(&head, max);
            n = n-1;
          }
        }

        coba = head;
        while (coba->Jumlah != max){
            coba = coba->next;
        }
        printf("%d. %s dengan %d suara dari Cabang A%d\n", j+1,coba->Nama, coba->Jumlah, coba->Cabang);
        HapusData(&head, max);
        n = n-1;
        max = 0;
    }
}

void insertSorted(struct Pegawai* head, struct Pegawai* newNode) {
    // Memasukkan node ke list sesuai urutan menurun
    if (head->next == NULL) {
        Pegawai* temp = (Pegawai*) malloc(sizeof(Pegawai)); 
        strcpy(temp->Nama, newNode->Nama); 
        temp->Cabang = newNode->Cabang;
        temp->Jumlah = newNode->Jumlah;
        temp->next = newNode->next;
        head->next = temp;
    }
    else{
        insertSorted(head->next, newNode);
    } 
}

int main() {
    int n;
    int jumlahDATA =1;
    char filename[20];

    Pegawai* head = (Pegawai*) malloc(sizeof(Pegawai));
    Pegawai* Temp = (Pegawai*) malloc(sizeof(Pegawai));

    strcpy(head->Nama, "Dummy"); 
    head->Jumlah = 0;
    head->Cabang = 0;
    head->next = NULL;

    printf("Masukkan Cabang dari data: ");
    scanf("%d", &n);

    // Cek nilai n apakah valid 0<n<=10
    sprintf(filename, "%d.txt", n);
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Gagal membuka file %s. Pastikan file tersebut ada.\n", filename);
        return 0;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        char nama[50];
        int jumlah, cabang;

        char* token = strtok(line, ",");
        strcpy(nama, token);

        token = strtok(NULL, ",");
        jumlah = atoi(token);

        //Membuat node baru
        strcpy(Temp->Nama, nama); 
        Temp->Jumlah = jumlah;
        Temp->Cabang = n;
        Temp->next = NULL;

        //Insert Node kedalam linked list & Sort
        insertSorted(head,Temp);
        jumlahDATA = jumlahDATA +1;  

    }
    fclose(file);

    //Membuka File kedua
    FILE* stream = fopen("Insert.txt", "r");
    while (fgets(line, sizeof(line), stream)) {
        char nama[50];
        int jumlah, cabang;

        char* token = strtok(line, ",");
        strcpy(nama, token);

        token = strtok(NULL, "");
        jumlah = atoi(token);

        //Membuat node baru
        strcpy(Temp->Nama, nama); 
        Temp->Jumlah = jumlah;
        Temp->Cabang = n;
        Temp->next = NULL;

        //Insert Node kedua kedalam linked list & Sort
        insertSorted(head,Temp);
        jumlahDATA = jumlahDATA +1;   

    }
    fclose(stream);

    // Mencetak isi linked list setelah pengurutan
    printf("\nPegawai Yang Mendapat Promosi :\n");
    printLinkedList(head, jumlahDATA);

    return 0;
}