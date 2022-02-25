# Word Search Solver
## Using Brute Force Algorithm
### By: Dzaky Fattan Rizqullah
#### Tugas Kecil Mata Kuliah IF2211 Strategi Algoritma
===

A. Deskripsi singkat program

Program ini berfungsi untuk menyelesaikan Word Search Puzzle dengan pendekatan bruteforce. Bahasa yang digunakan adalah Bahasa C. Ukuran petak puzzle maksimal ialah 50x50 huruf dan jumlah keyword sebanyak 100 kata dengan panjang kata masing-masing 50 huruf.

===

B. Requirement program
- Executable yang diberikan di dalam folder "bin" ialah ".exe" yang sudah diujicoba dan dapat dijalankan pada sistem operasi Windows (Windows 11).
- Karena jawaban puzzle diberikan dalam bentuk pewarnaan teks yang memanfaatkan ANSI processing, maka terminal yang digunakan untuk menjalankan program harus support ANSI. Pada Windows, pengguna dapat mengakses registry editor, navigasi ke "HKEY_CURRENT_USER\Console\VirtualTerminalLevel", kemudian membuat kunci DWORD dan memberikan nilai 1 untuk mengaktivasi ANSI processing.

===

C. Cara menggunakan program
	1. Cukup jalankan executable "WordSearchSolver.exe" di dalam folder "bin", atau compile file "WordSearchBF.c" dan jalankan hasil kompilasi.
	2. Pengguna akan diminta untuk memasukkan nama file data uji tanpa ekstensinya (format .txt). Pastikan pula .txt menggunakan format EOL yaitu CRLF dan memakai UTF-8.
	3. Program akan menampilkan Petak Puzzle dan kumpulan kata kunci yang akan ditemukan. Pengguna dapat menekan tombol Enter untuk melanjutkan program.
	4. Program akan menyelesaikan puzzle tersebut, menampilkan informasi berupa: Posisi dan arah kata yang ditemukan beserta jumlah perbandingan huruf per-kata; Petak puzzle yang sudah ditandai jawabannya, waktu eksekusi program, dan total perbandingan huruf yang dilakukan.

===

D. Author
Nama    : Dzaky Fattan Rizqullah
NIM     : 13520003
Kelas   : K3