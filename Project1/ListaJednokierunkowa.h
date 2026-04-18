#ifndef LISTAJEDNOKIERUNKOWA_H
#define LISTAJEDNOKIERUNKOWA_H

#include <iostream>
using namespace std;

class ListaJednokierunkowa {
private:
    struct Wezel {
        int data;
        Wezel* next;
        Wezel(int d) : data(d), next(nullptr) {}
    };

    Wezel* head; // head - pierwszy element
    Wezel* tail;  // tail - ostatni element (szybkie dodawanie na koniec)
    int rozmiar;

public:
    ListaJednokierunkowa();
    ListaJednokierunkowa(const ListaJednokierunkowa& other);
    ~ListaJednokierunkowa();

    void dodajNaPoczatek(int element);           // O(1)
    void dodajNaKoniec(int element);             // O(1) 
    void dodajNaPozycji(int index, int element); // O(n)

    void usunZPoczatku();                        // O(1)
    void usunZKonca();                           // O(n) - trzeba dojsc do przedostatniego
    void usunZPozycji(int index);                // O(n)

    bool zawiera(int element) const;             // O(n)

    void wyswietl() const;
    void wypelnijLosowo(int n, int ziarno);
    void wczytajZPliku(const string& nazwa);
    void wyczysc();
    int getRozmiar() const;
    bool czyPusta() const;
};

#endif