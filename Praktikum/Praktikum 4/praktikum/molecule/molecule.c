#include "molecule.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Implementasi Fungsi ADT Molekul ---

/**
 * @brief Menginisialisasi sebuah molekul menjadi kosong.
 *
 * @param m Pointer ke Molecule yang akan diinisialisasi.
 * numAtomTypes diatur ke 0.
 */
void createMolecule(Molecule *m){
    m->numAtomTypes = 0;

}


/**
 * @brief Menambahkan sejumlah atom dengan simbol tertentu ke dalam molekul.
 *
 * Jika atom dengan simbol tersebut sudah ada, jumlahnya akan ditambahkan.
 * Jika belum ada dan masih ada ruang (numAtomTypes < MAX_ATOM_TYPES),
 * atom baru akan ditambahkan ke dalam array atoms.
 * Jika sudah penuh, penambahan atom baru akan diabaikan.
 *
 * @param m Pointer ke Molecule yang akan ditambahkan atom.
 * @param symbol Simbol atom yang akan ditambahkan
 * @param count Jumlah atom yang akan ditambahkan.
 */
void addAtom(Molecule *m, const char *symbol, int count) {
    int index = m->numAtomTypes;

    
    for(int i = 0; i<index; i++){
        if (strcmp(m->atoms[i].symbol, symbol) == 0){ //Bandingin string, kalau sama (nilai = 0), maka string sudah ada
            m->atoms[i].count += count;
            return;
        }
    }

    if(index<MAX_ATOM_TYPES){
    strcpy(m->atoms[index].symbol, symbol); //Copy string pake string.h
    m->atoms[index].count = count;
    m->numAtomTypes++;
    }
}

double getAtomicWeight(const char *symbol) {
    if (strcmp(symbol, "H") == 0)
        return 1.008;
    else if (strcmp(symbol, "He") == 0)
        return 4.0026;
    else if (strcmp(symbol, "Li") == 0)
        return 6.94;
    else if (strcmp(symbol, "C") == 0)
        return 12.011;
    else if (strcmp(symbol, "N") == 0)
        return 14.007;
    else if (strcmp(symbol, "O") == 0)
        return 15.999;
    else if (strcmp(symbol, "F") == 0)
        return 18.998;
    else if (strcmp(symbol, "Ne") == 0)
        return 20.180;
    else if (strcmp(symbol, "Na") == 0)
        return 22.990;
    else if (strcmp(symbol, "Mg") == 0)
        return 24.305;
    else if (strcmp(symbol, "Al") == 0)
        return 26.982;
    else if (strcmp(symbol, "Si") == 0)
        return 28.085;
    else if (strcmp(symbol, "P") == 0)
        return 30.974;
    else if (strcmp(symbol, "S") == 0)
        return 32.06;
    else if (strcmp(symbol, "Cl") == 0)
        return 35.45;
    else if (strcmp(symbol, "Ar") == 0)
        return 39.948;
    else if (strcmp(symbol, "K") == 0)
        return 39.098;
    else if (strcmp(symbol, "Ca") == 0)
        return 40.078;
    else if (strcmp(symbol, "Fe") == 0)
        return 55.845;
    else if (strcmp(symbol, "Au") == 0)
        return 196.967;
    else if (strcmp(symbol, "Br") == 0)
        return 79.904;
    else if (strcmp(symbol, "I") == 0)
        return 126.904;
    return 0.0;
}

/**
 * @brief Menghitung perkiraan berat molekul total.
 *
 * Menggunakan fungsi helper getAtomicWeight
 * untuk mendapatkan massa atom relatif setiap jenis atom.
 *
 * @param m Pointer ke Molecule yang akan dihitung beratnya.
 * @return double Berat molekul total. Mengembalikan 0.0 jika molekul
 * kosong.
 */
double calculateMolecularWeight(const Molecule *m) {
    if(m->numAtomTypes == 0 ) return 0.0;

    double berat = 0;

    for(int i = 0; i<m->numAtomTypes ; i++){
        berat += getAtomicWeight(m->atoms[i].symbol) * m->atoms[i].count;
    }

    return berat;
}

/**
 * @brief Mendapatkan jumlah atom dengan simbol tertentu dalam molekul.
 *
 * @param m Pointer ke Molecule yang akan dicari.
 * @param symbol Simbol atom yang jumlahnya ingin diketahui.
 * @return int Jumlah atom dengan simbol tersebut. Mengembalikan 0 jika
 * tidak ditemukan.
 */
int getAtomCount(const Molecule *m, const char *symbol) {
    for(int i = 0; i<m->numAtomTypes; i++){
        if(strcmp(m->atoms[i].symbol, symbol) == 0){
            return m->atoms[i].count;
        }
    }
    return 0;
}

// --- Fungsi Bantuan untuk qsort jika diperlukan ---
int compareAtomInfo(const void *a, const void *b) {
    AtomInfo *atomA = (AtomInfo *)a;
    AtomInfo *atomB = (AtomInfo *)b;
    return strcmp(atomA->symbol, atomB->symbol);
}

void sortMolecule(Molecule *m) {
    if (m->numAtomTypes > 1) {
        qsort(m->atoms, m->numAtomTypes, sizeof(AtomInfo), compareAtomInfo);
    }
}

/**
 * @brief Membandingkan dua molekul untuk kesetaraan komposisi.
 *
 * Dua molekul dianggap sama jika memiliki jenis atom yang sama
 * dengan jumlah yang sama untuk setiap jenis atom, *tidak peduli urutan
 * atom dalam array*.
 *
 * @param m1 Pointer ke Molecule pertama.
 * @param m2 Pointer ke Molecule kedua.
 * @return true Jika kedua molekul memiliki komposisi yang sama, false jika
 * tidak.
 */
bool areEqual(const Molecule *m1, const Molecule *m2) {
    if(m1->numAtomTypes != m2->numAtomTypes){
        return false;
    }

    Molecule copy1 = *m1;
    Molecule copy2 = *m2;

    sortMolecule(&copy1);
    sortMolecule(&copy2);

    for(int i = 0; i<copy1.numAtomTypes ; i++){
        if(strcmp(copy1.atoms[i].symbol, copy2.atoms[i].symbol) != 0){ //Banding simbol
            return false;
        }
        if(copy1.atoms[i].count != copy2.atoms[i].count){ // Banding jumlah
            return false;
        }
    }
    
    return true;
}


/**
 * @brief Menggabungkan dua molekul menjadi satu molekul baru.
 *
 * Membuat molekul baru yang berisi semua atom dari m1 dan m2.
 * Jumlah atom dengan simbol yang sama akan dijumlahkan.
 * Jika hasil penggabungan melebihi MAX_ATOM_TYPES, atom tambahan
 * dari m2 yang tidak muat akan diabaikan (sesuai perilaku addAtom).
 *
 * @param m1 Pointer ke Molecule pertama.
 * @param m2 Pointer ke Molecule kedua.
 * @return Molecule Molekul baru hasil penggabungan.
 */
Molecule combineMolecules(const Molecule *m1, const Molecule *m2) {
    Molecule result;
    createMolecule(&result);
    int biggest = (m1->numAtomTypes < m2->numAtomTypes) ? m2->numAtomTypes : m1->numAtomTypes;

    for(int i = 0; i<biggest; i++){
        if(i < m1->numAtomTypes){
            addAtom(&result, m1->atoms[i].symbol, m1->atoms[i].count);
        }
        if(i < m2->numAtomTypes){
            addAtom(&result, m2->atoms[i].symbol, m2->atoms[i].count);
        }
    }
    return result;
}

/**
 * @brief Memeriksa apakah molekul m_sub dapat dikurangkan dari m_total.
 *
 * Pengecekan berhasil jika untuk setiap jenis atom dalam m_sub,
 * jumlah atom tersebut dalam m_total lebih besar atau sama.
 *
 * @param m_total Pointer ke Molecule total.
 * @param m_sub Pointer ke Molecule yang akan dikurangkan.
 * @return true Jika m_sub dapat dikurangkan dari m_total, false jika tidak.
 */
bool canSubtract(const Molecule *m_total, const Molecule *m_sub) {
    Molecule total = *m_total;
    Molecule sub = *m_sub;

    sortMolecule(&total);
    sortMolecule(&sub);

    for(int i = 0; i < total.numAtomTypes; i++){
        if(total.atoms[i].count < sub.atoms[i].count){
            return false;
        }
    }
    return true;
}

/**
 * @brief Mengurangkan molekul m_sub dari m_total dan mengembalikan hasilnya.
 *
 * Fungsi ini pertama-tama akan memanggil canSubtract.
 * Jika canSubtract mengembalikan false, fungsi ini akan mengembalikan
 * molekul kosong.
 * Jika canSubtract mengembalikan true, fungsi ini akan membuat molekul baru
 * yang merupakan salinan m_total, kemudian mengurangi jumlah setiap atom
 * yang ada di m_sub dari molekul baru tersebut. Atom dengan jumlah 0
 * setelah pengurangan sebaiknya diabaikan dalam perhitungan/pencetakan
 * selanjutnya.
 *
 * @param m_total Pointer ke Molecule total.
 * @param m_sub Pointer ke Molecule yang akan dikurangkan.
 * @return Molecule Molekul baru hasil pengurangan, atau molekul kosong jika
 * pengurangan tidak memungkinkan (canSubtract == false).
 */
Molecule subtractMolecule(const Molecule *m_total, const Molecule *m_sub) {
    Molecule result;
    createMolecule(&result);

    if (!canSubtract(m_total, m_sub)) {
        return result;  // return empty molecule
    }

    // Copy m_total into result
    result = *m_total;

    // Sort both result and sub to match atom order
    sortMolecule(&result);
    Molecule sortedSub = *m_sub;
    sortMolecule(&sortedSub);

    for (int i = 0; i < result.numAtomTypes; i++) {
        for (int j = 0; j < sortedSub.numAtomTypes; j++) {
            if (strcmp(result.atoms[i].symbol, sortedSub.atoms[j].symbol) == 0) {
                result.atoms[i].count -= sortedSub.atoms[j].count;
                break;
            }
        }
    }

    // Remove atoms with count <= 0
    int k = 0;
    for (int i = 0; i < result.numAtomTypes; i++) {
        if (result.atoms[i].count > 0) {
            result.atoms[k++] = result.atoms[i];
        }
    }
    result.numAtomTypes = k;

    return result;
}

void printMoleculeFormula(const Molecule *m) {
    // TODO: Implementasikan fungsi ini
    // 1. Jika m->numAtomTypes == 0, cetak "(Kosong)".
    // 2. Urutkan atom berdasarkan simbol untuk output (gunakan fungsi sorting
    // yang sudah diberikan)
    // 3. Cetak formula molekul
    // Contoh output: C6H12O6, H2O, NaCl

    if (m->numAtomTypes == 0) {
        printf("(Kosong)\n");
        return;
    }

    Molecule copy1 = *m;
    sortMolecule(&copy1);
    for(int i = 0;i<m->numAtomTypes;i++){
        printf("%s", m->atoms[i].symbol);
        if(m->atoms[i].count > 1){
            printf("%d",copy1.atoms[i].count);
        }
    }
    printf("\n");
}