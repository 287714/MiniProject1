#include "ListaDwukierunkowa.h"
#include <fstream>
#include <cstdlib>
#include <iostream>

using namespace std;

// Konstruktor: inicjalizacja pustej listy
ListaDwukierunkowa::ListaDwukierunkowa() : head(nullptr), tail(nullptr), rozmiar(0) {}

// Konstruktor kopiujacy: gleboka kopia elementow
ListaDwukierunkowa::ListaDwukierunkowa(const ListaDwukierunkowa& o)
    : head(nullptr), tail(nullptr), rozmiar(0) {
    for (Wezel* w = o.head; w != nullptr; w = w->next) {
        dodajNaKoniec(w->data);
    }
}

// Destruktor: zwolnienie pamieci
ListaDwukierunkowa::~ListaDwukierunkowa() {
    wyczysc();
}

// Dodawanie na poczatek: O(1)
void ListaDwukierunkowa::dodajNaPoczatek(int e) {
    Wezel* n = new Wezel(e);
    if (czyPusta()) {
        head = tail = n;
    }
    else {
        n->next = head;
        head->prev = n;
        head = n;
    }
    rozmiar++;
}

// Dodawanie na koniec: O(1)
void ListaDwukierunkowa::dodajNaKoniec(int e) {
    Wezel* n = new Wezel(e);
    if (czyPusta()) {
        head = tail = n;
    }
    else {
        n->prev = tail;
        tail->next = n;
        tail = n;
    }
    rozmiar++;
}

// Dodawanie na dowolna pozycje: O(n)
void ListaDwukierunkowa::dodajNaPozycji(int idx, int e) {
    if (idx <= 0) { dodajNaPoczatek(e); return; }
    if (idx >= rozmiar) { dodajNaKoniec(e); return; }

    Wezel* w = head;
    for (int i = 0; i < idx - 1; i++) {
        w = w->next;
    }

    Wezel* n = new Wezel(e);
    n->next = w->next;
    n->prev = w;

    if (w->next) w->next->prev = n;
    w->next = n;

    rozmiar++;
}

// Usuwanie z poczatku: O(1)
void ListaDwukierunkowa::usunZPoczatku() {
    if (czyPusta()) return;

    Wezel* temp = head;
    head = head->next;

    if (head) {
        head->prev = nullptr;
    }
    else {
        tail = nullptr; // Lista stala sie pusta
    }

    delete temp;
    rozmiar--;
}

// Usuwanie z konca: O(1) - to jest przewaga nad lista jednokierunkowa!
void ListaDwukierunkowa::usunZKonca() {
    if (czyPusta()) return;

    Wezel* temp = tail;
    tail = tail->prev;

    if (tail) {
        tail->next = nullptr;
    }
    else {
        head = nullptr; // Lista stala sie pusta
    }

    delete temp;
    rozmiar--;
}

// Usuwanie z dowolnej pozycji: O(n)
void ListaDwukierunkowa::usunZPozycji(int idx) {
    if (czyPusta() || idx < 0 || idx >= rozmiar) return;
    if (idx == 0) { usunZPoczatku(); return; }
    if (idx == rozmiar - 1) { usunZKonca(); return; }

    Wezel* w = head;
    for (int i = 0; i < idx; i++) {
        w = w->next;
    }

    w->prev->next = w->next;
    w->next->prev = w->prev;

    delete w;
    rozmiar--;
}

// Wyszukiwanie elementu: O(n)
bool ListaDwukierunkowa::zawiera(int e) const {
    for (Wezel* w = head; w != nullptr; w = w->next) {
        if (w->data == e) return true;
    }
    return false;
}

// Wyswietlanie struktury
void ListaDwukierunkowa::wyswietl() const {
    if (czyPusta()) { cout << "[pusta]\n"; return; }
    cout << "NULL <-> ";
    for (Wezel* w = head; w != nullptr; w = w->next) {
        cout << w->data << (w->next ? " <-> " : "");
    }
    cout << " <-> NULL (n=" << rozmiar << ")\n";
}

// Wypelnianie losowymi danymi
void ListaDwukierunkowa::wypelnijLosowo(int n, int z) {
    wyczysc();
    srand(z);
    for (int i = 0; i < n; i++) {
        dodajNaKoniec(rand() % 100000);
    }
}

// Wczytywanie z pliku
void ListaDwukierunkowa::wczytajZPliku(const string& nazwa) {
    ifstream f(nazwa);
    if (!f) { cout << "Nie mozna otworzyc pliku!\n"; return; }
    wyczysc();
    int x;
    while (f >> x) {
        dodajNaKoniec(x);
    }
}

// Metody pomocnicze
void ListaDwukierunkowa::wyczysc() {
    while (!czyPusta()) usunZPoczatku();
}

int ListaDwukierunkowa::getRozmiar() const {
    return rozmiar;
}

bool ListaDwukierunkowa::czyPusta() const {
    return rozmiar == 0;
}