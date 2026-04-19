#include "DynamicznaTablica.h"
#include <fstream>
#include <cstdlib>
#include <iostream>

using namespace std;

// Konstruktor: inicjalizacja pustej tablicy
DynamicznaTablica::DynamicznaTablica() : data(nullptr), size(0), capacity(0) {}

// Konstruktor kopiujacy: gleboka kopia tablicy
DynamicznaTablica::DynamicznaTablica(const DynamicznaTablica& o) {
    size = o.size;
    capacity = o.capacity;
    data = new int[capacity];
    for (int i = 0; i < size; i++) {
        data[i] = o.data[i];
    }
}

// Destruktor: zwolnienie pamieci dynamicznej
DynamicznaTablica::~DynamicznaTablica() {
    delete[] data;
}

// Realokacja: podwajanie pojemnosci tablicy (O(n) przy zmianie rozmiaru)
void DynamicznaTablica::zmienRozmiar() {
    capacity = (capacity == 0) ? 1 : capacity * 2;
    int* newData = new int[capacity];
    for (int i = 0; i < size; i++) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
}

// Dodawanie na koniec: O(1) amortyzowane
void DynamicznaTablica::dodajNaKoniec(int e) {
    if (size == capacity) zmienRozmiar();
    data[size++] = e;
}

// Dodawanie na poczatek: O(n) - wymaga przesuniecia wszystkich elementow
void DynamicznaTablica::dodajNaPoczatek(int e) {
    if (size == capacity) zmienRozmiar();
    for (int i = size; i > 0; i--) {
        data[i] = data[i - 1];
    }
    data[0] = e;
    size++;
}

// Dodawanie na dowolna pozycje: O(n)
void DynamicznaTablica::dodajNaPozycji(int idx, int e) {
    if (idx <= 0) { dodajNaPoczatek(e); return; }
    if (idx >= size) { dodajNaKoniec(e); return; }

    if (size == capacity) zmienRozmiar();
    for (int i = size; i > idx; i--) {
        data[i] = data[i - 1];
    }
    data[idx] = e;
    size++;
}

// Usuwanie z konca: O(1)
void DynamicznaTablica::usunZKonca() {
    if (size > 0) size--;
}

// Usuwanie z poczatku: O(n)
void DynamicznaTablica::usunZPoczatku() {
    usunZPozycji(0);
}

// Usuwanie z dowolnej pozycji: O(n)
void DynamicznaTablica::usunZPozycji(int idx) {
    if (size == 0 || idx < 0 || idx >= size) return;
    for (int i = idx; i < size - 1; i++) {
        data[i] = data[i + 1];
    }
    size--;
}

// Wyszukiwanie elementu: O(n)
bool DynamicznaTablica::zawiera(int e) const {
    for (int i = 0; i < size; i++) {
        if (data[i] == e) return true;
    }
    return false;
}

// Wyswietlanie tablicy
void DynamicznaTablica::wyswietl() const {
    if (size == 0) { cout << "[pusta]\n"; return; }
    cout << "[";
    for (int i = 0; i < size; i++) {
        cout << data[i] << (i < size - 1 ? ", " : "");
    }
    cout << "] (n=" << size << ", cap=" << capacity << ")\n";
}

// Wypelnianie losowymi danymi
void DynamicznaTablica::wypelnijLosowo(int n, int z) {
    wyczysc();
    srand(z);
    for (int i = 0; i < n; i++) {
        dodajNaKoniec(rand() % 100000);
    }
}

// Wczytywanie z pliku tekstowego
void DynamicznaTablica::wczytajZPliku(const string& nazwa) {
    ifstream f(nazwa);
    if (!f) { cout << "Nie mozna otworzyc pliku!\n"; return; }
    wyczysc();
    int x;
    while (f >> x) {
        dodajNaKoniec(x);
    }
    cout << "Wczytano " << size << " elementow.\n";
}

// Resetowanie tablicy
void DynamicznaTablica::wyczysc() {
    delete[] data;
    data = nullptr;
    size = 0;
    capacity = 0;
}

// Pobieranie aktualnego rozmiaru
int DynamicznaTablica::getRozmiar() const {
    return size;
}