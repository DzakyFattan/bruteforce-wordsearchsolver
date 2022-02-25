/* PROGRAM WORD SEARCH PUZZLE DENGAN BRUTE FORCE
Nama    : Dzaky Fattan Rizqullah
NIM     : 13520003
Kelas   : K3
*/

#include <stdio.h>
#include <string.h>
#include <time.h>

#include "WordSearchBF.h"

int bacaPuzzle();       // membaca dan membentuk matriks wordsearch
void bacaKata();        // membaca kata kunci yang akan dicari pada wordsearch
void tulisPuzzle();     // menulis matriks dan kata kunci wordsearch
void solve();           // selesaikan wordsearch
void cetakmarkmtx();    // mencetak matriks

int cekKedua(int a, int b, int wctr);   // cek huruf kedua
int cekSisa(int a, int b, int dir, int len, char kata[]); // cek huruf ketiga dan seterusnya



// auxiliary untuk menampilkan jawaban
void markmtx(int y, int x, int dir, int len);



int main()
{
    // Fungsi Utama, termasuk perhitungan waktu real-time eksekusi
    printf("\x1b[0m"
           "PEMECAHAN WORD SEARCH PUZZLE MENGGUNAKAN ALGORITMA BRUTEFORCE (IMPLEMENTASI DENGAN BAHASA C)\n");
    printf("Nama\t: Dzaky Fattan Rizqullah\nNIM\t: 13520003\nKelas\t: K3\n");
    int opcode = bacaPuzzle();
    if (opcode)
    {
        tulisPuzzle();
        printf("\nSelesaikan? Tekan Enter untuk menyelesaikan puzzle.\n");
        getchar();
        getchar();
        struct timespec begin, end;
        clock_gettime(CLOCK_REALTIME, &begin);
        solve();
        clock_gettime(CLOCK_REALTIME, &end);
        double ttaken = ((double)(end.tv_nsec - begin.tv_nsec)) / ((double)100000);
        printf("\n");
        cetakmarkmtx();
        printf("Waktu eksekusi program = %.2f nanodetik.\n", ttaken);
        printf("Total perbandingan huruf = %d kali.\n\n", total);
        printf("Tekan ENTER untuk keluar\n");
        getchar();
    }
    return 0;
}

int bacaPuzzle()
{
    // Fungsi membaca file .txt eksternal, HANYA SUPPORT EOL CRLF
    FILE *fP;
    char filename[50];
    char basepath[60] = "../test/";
    int lgth;
    printf("\nMasukkan nama file tanpa menulis ekstensi (format harus .txt)\n");
    scanf("%s", filename);
    strcat(basepath, filename);
    strcat(basepath, ".txt");
    fP = fopen(basepath, "r");
    if (fP == NULL)
    {
        printf("File error/tidak ada!\n");
        return 0;
    }
    else
    {
        char line[100];
        int i;
        puzzleH = 0;
        fgets(line, sizeof(line), fP);
        while (line[1] != '\n')
        {
            puzzleW = 0;
            for (i = 0; i < strlen(line) - 2; i++)
            {
                if (line[i] != ' ')
                {
                    puzzle[puzzleH][puzzleW] = line[i];
                    puzzleW++;
                }
            }
            fgets(line, sizeof(line), fP);
            puzzleH++;
        }
        banyakKata = 0;
        while (fgets(line, sizeof(line), fP) != NULL)
        {
            if (line[strlen(line) - 1] == '\n')
            {
                for (i = 0; i < (strlen(line) - 2); i++)
                {
                    words[banyakKata][i] = line[i];
                }
                banyakKata++;
            }
            else
            {
                for (i = 0; i < (strlen(line)); i++)
                {
                    words[banyakKata][i] = line[i];
                }
                banyakKata++;
            }
        }
        printf("\nBaris: %d\nKolom: %d\nBanyak Kata: %d\n", puzzleH, puzzleW, banyakKata);

        fclose(fP);
        return 1;
    }
}

void tulisPuzzle()
{
    // Prosedur menampilkan matriks puzzle dan daftar kata kunci yang akan dicari
    printf("\nPuzzle: \n");
    for (int i = 0; i < puzzleH; i++)
    {
        for (int j = 0; j < puzzleW; j++)
            printf("%c ", puzzle[i][j]);
        printf("\n");
    }
    printf("\nDaftar kata: \n");
    for (int i = 0; i < banyakKata; i++)
    {
        printf("%d. ", i + 1);
        int j = 0;
        while (words[i][j] != '\0')
        {
            printf("%c", words[i][j]);
            j++;
        }
        printf("\n");
    }
}

int cekKedua(int a, int b, int wctr)
{
    // Prosedur mengecek huruf kedua untuk kata kunci yang sedang dicari
    compcount++;
    if (puzzle[a][b] == words[wctr][1])
        return 1;
    else
        return 0;
}

int cekSisa(int a, int b, int dir, int len, char kata[])
{
    // Prosedur untuk mengecek sisa huruf untuk kata kunci yang sedang dicari
    char temp[len];
    int i = 0;
    int chk = 1;
    if (len > 2)
    {
        while (i < len - 2 && chk == 1)
        {
            if (kata[i + 2] != puzzle[a][b])
            {
                chk = 0;
            }
            a += yr[dir];
            b += xr[dir];
            i++;
        }
    }
    compcount += i;
    return chk;
}

void solve()
{
    // Prosedur utama untuk penyelesaian puzzle
    total = 0;
    int wctr, dir, len;
    for (wctr = 0; wctr < banyakKata; wctr++)
    {
        compcount = 0;
        int chked = 0;
        int found = 0;
        len = strlen(words[wctr]);
        int i = 0;
        while (i < puzzleH && chked == 0)
        {
            int j = 0;
            while (j < puzzleW && chked == 0)
            {
                if (words[wctr][0] == puzzle[i][j] && chked == 0)
                {
                    compcount++;
                    if (cekKedua(i, j + 1, wctr) == 1)
                    {
                        if (cekSisa(i, j + 2, 0, len, words[wctr]) == 1)
                        {

                            markmtx(i, j, 0, len);
                            chked = 1;
                            found = 1;
                            printf("Ditemukan kata ke-%d (panjang %d huruf) pada posisi (%d,%d) ke kanan.\n", wctr + 1, len, j, i);
                        }
                    }
                    if (cekKedua(i + 1, j + 1, wctr) == 1 && found == 0)
                    {
                        if (cekSisa(i + 2, j + 2, 1, len, words[wctr]) == 1)
                        {
                            markmtx(i, j, 1, len);
                            chked = 1;
                            found = 1;
                            printf("Ditemukan kata ke-%d (panjang %d huruf) pada posisi (%d,%d) ke kanan bawah.\n", wctr + 1, len, j, i);
                        }
                    }
                    if (cekKedua(i + 1, j, wctr) == 1 && found == 0)
                    {
                        if (cekSisa(i + 2, j, 2, len, words[wctr]) == 1)
                        {
                            markmtx(i, j, 2, len);
                            chked = 1;
                            found = 1;
                            printf("Ditemukan kata ke-%d (panjang %d huruf) pada posisi (%d,%d) ke bawah.\n", wctr + 1, len, j, i);
                        }
                    }
                    if (cekKedua(i + 1, j - 1, wctr) == 1 && found == 0)
                    {
                        if (cekSisa(i + 2, j - 2, 3, len, words[wctr]) == 1)
                        {
                            markmtx(i, j, 3, len);
                            chked = 1;
                            found = 1;
                            printf("Ditemukan kata ke-%d (panjang %d huruf) pada posisi (%d,%d) ke kiri bawah.\n", wctr + 1, len, j, i);
                        }
                    }
                    if (cekKedua(i, j - 1, wctr) == 1 && found == 0)
                    {
                        if (cekSisa(i, j - 2, 4, len, words[wctr]) == 1)
                        {
                            markmtx(i, j, 4, len);
                            chked = 1;
                            found = 1;
                            printf("Ditemukan kata ke-%d (panjang %d huruf) pada posisi (%d,%d) ke kiri.\n", wctr + 1, len, j, i);
                        }
                    }
                    if (cekKedua(i - 1, j - 1, wctr) == 1 && found == 0)
                    {
                        if (cekSisa(i - 2, j - 2, 5, len, words[wctr]) == 1)
                        {
                            markmtx(i, j, 5, len);
                            chked = 1;
                            found = 1;
                            printf("Ditemukan kata ke-%d (panjang %d huruf) pada posisi (%d,%d) ke kiri atas.\n", wctr + 1, len, j, i);
                        }
                    }
                    if (cekKedua(i - 1, j, wctr) == 1 && found == 0)
                    {
                        if (cekSisa(i - 2, j, 6, len, words[wctr]) == 1)
                        {
                            markmtx(i, j, 6, len);
                            chked = 1;
                            found = 1;
                            printf("Ditemukan kata ke-%d (panjang %d huruf) pada posisi (%d,%d) ke atas.\n", wctr + 1, len, j, i);
                        }
                    }
                    if (cekKedua(i - 1, j + 1, wctr) == 1 && found == 0)
                    {
                        if (cekSisa(i - 2, j + 2, 7, len, words[wctr]) == 1)
                        {
                            markmtx(i, j, 7, len);
                            chked = 1;
                            found = 1;
                            printf("Ditemukan kata ke-%d (panjang %d huruf) pada posisi (%d,%d) ke kanan atas.\n", wctr + 1, len, j, i);
                        }
                    }
                }
                else
                {
                    compcount++;
                }
                j++;
            }
            i++;
        }
        total += compcount;
        printf("Jumlah perbandingan huruf: %d kali\n", compcount);
    }
}