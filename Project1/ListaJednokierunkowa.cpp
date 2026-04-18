#include "ListaJednokierunkowa.h"
#include <fstream>
#include <cstdlib>
#include <iostream>

using namespace std;

// Konstruktor: inicjalizacja pustej listy
ListaJednokierunkowa::ListaJednokierunkowa() : head(nullptr), tail(nullptr), rozmiar(0) {}

// Konstruktor kopiujacy: glebokie kopiowanie elementow
ListaJednokierunkowa::ListaJednokierunkowa(const ListaJednokierunkowa& o)
    : head(nullptr), tail(nullptr), rozmiar(0) {
    for (Wezel* w = o.head; w != nullptr; w = w->next) {
        dodajNaKoniec(w->data);
    }
}

// Destruktor: czyszczenie pamieci
ListaJednokierunkowa::~ListaJednokierunkowa() {
    wyczysc();
}

// Dodawanie na poczatek: O(1)
void ListaJednokierunkowa::dodajNaPoczatek(int e) {
    Wezel* n = new Wezel(e);
    if (czyPusta()) {
        head = tail = n;
    }
    else {
        n->next = head;
        head = n;
    }
    rozmiar++;
}

// Dodawanie na koniec: O(1) dzieki wskaznikowi tail (ogon)
void ListaJednokierunkowa::dodajNaKoniec(int e) {
    Wezel* n = new Wezel(e);
    if (czyPusta()) {
        head = tail = n;
    }
    else {
        tail->next = n;
        tail = n;
    }
    rozmiar++;
}

// Dodawanie na dowolna pozycje: O(n)
void ListaJednokierunkowa::dodajNaPozycji(int idx, int e) {
    if (idx <= 0) { dodajNaPoczatek(e); return; }
    if (idx >= rozmiar) { dodajNaKoniec(e); return; }

    Wezel* w = head;
    for (int i = 0; i < idx - 1; i++) {
        w = w->next;
    }

    Wezel* n = new Wezel(e);
    n->next = w->next;
    w->next = n;
    rozmiar++;
}

// Usuwanie z poczatku: O(1)
void ListaJednokierunkowa::usunZPoczatku() {
    if (czyPusta()) return;

    Wezel* temp = head;
    head = head->next;

    if (!head) tail = nullptr; // Jesli lista stala sie pusta

    delete temp;
    rozmiar--;
}

// Usuwanie z konca: O(n) - trzeba znalezc przedostatni element
void ListaJednokierunkowa::usunZKonca() {
    if (czyPusta()) return;
    if (rozmiar == 1) {
        delete head;
        head = tail = nullptr;
        rozmiar--;
        return;
    }

    Wezel* w = head;
    while (w->next != tail) {
        w = w->next;
    }

    delete tail;
    tail = w;
    tail->next = nullptr;
    rozmiar--;
}

// Usuwanie z pozycji: O(n)
void ListaJednokierunkowa::usunZPozycji(int idx) {
    if (czyPusta() || idx < 0 || idx >= rozmiar) return;
    if (idx == 0) { usunZPoczatku(); return; }
    if (idx == rozmiar - 1) { usunZKonca(); return; }

    Wezel* w = head;
    for (int i = 0; i < idx - 1; i++) {
        w = w->next;
    }

    Wezel* toDelete = w->next;
    w->next = toDelete->next;
    delete toDelete;
    rozmiar--;
}

// Poszukiwanie elementu: O(n)
bool ListaJednokierunkowa::zawiera(int e) const {
    for (Wezel* w = head; w != nullptr; w = w->next) {
        if (w->data == e) return true;
    }
    return false;
}

// Wizualizacja struktury (dla debugowania)
void ListaJednokierunkowa::wyswietl() const {
    if (czyPusta()) { cout << "[pusta]\n"; return; }
    cout << "head -> ";
    for (Wezel* w = head; w != nullptr; w = w->next) {
        cout << w->data << (w->next ? " -> " : "");
    }
    cout << " -> NULL (n=" << rozmiar << ")\n";
}

// Zapelnianie losowymi danymi
void ListaJednokierunkowa::wypelnijLosowo(int n, int z) {
    wyczysc();
    srand(z);
    for (int i = 0; i < n; i++) {
        dodajNaKoniec(rand() % 100000);
    }
}

// Praca z plikiem
void ListaJednokierunkowa::wczytajZPliku(const string& nazwa) {
    ifstream f(nazwa);
    if (!f) { cout << "Nie mozna otworzyc pliku!\n"; return; }
    wyczysc();
    int x;
    while (f >> x) {
        dodajNaKoniec(x);
    }
}

// Metody pomocnicze
void ListaJednokierunkowa::wyczysc() {
    while (!czyPusta()) usunZPoczatku();
}

int ListaJednokierunkowa::getRozmiar() const {
    return rozmiar;
}

bool ListaJednokierunkowa::czyPusta() const {
    return rozmiar == 0;
}