#ifndef LISTADWUKIERUNKOWA_H
#define LISTADWUKIERUNKOWA_H

#include <iostream>
#include <string>

using namespace std;

/**
 * Klasa ListaDwukierunkowa (Doubly Linked List)
 * Kazdy wezel przechowuje wskaznik na nastepnik oraz poprzednik.
 * Pozwala to na optymalizacje operacji usuwania z konca do O(1).
 */
class ListaDwukierunkowa {
private:
    struct Wezel {
        int data;           // Wartosc przechowywana w wezle
        Wezel* prev;        // Wskaznik na poprzedni element
        Wezel* next;        // Wskaznik na nastepny element

        Wezel(int d) : data(d), prev(nullptr), next(nullptr) {}
    };

    Wezel* head;            // Wskaznik na poczatek listy
    Wezel* tail;            // Wskaznik na koniec listy
    int rozmiar;            // Aktualna liczba elementow

public:
    // Konstruktory i destruktor
    ListaDwukierunkowa();
    ListaDwukierunkowa(const ListaDwukierunkowa& other);
    ~ListaDwukierunkowa();

    // Operacje modyfikujace strukture
    void dodajNaPoczatek(int element);           // O(1)
    void dodajNaKoniec(int element);             // O(1)
    void dodajNaPozycji(int index, int element); // O(n)

    void usunZPoczatku();                        // O(1)
    void usunZKonca();                           // O(1) - przewaga nad lista 1-kierunkowa
    void usunZPozycji(int index);                // O(n)

    // Operacje wyszukiwania i administracyjne
    bool zawiera(int element) const;             // O(n)
    void wyswietl() const;                       // Wyswietla zawartosc w konsoli
    void wypelnijLosowo(int n, int ziarno);      // Generuje n losowych elementow
    void wczytajZPliku(const string& nazwa);     // Odczytuje dane z pliku tekstowego
    void wyczysc();                             // Usuwa wszystkie elementy (zwalnia pamiec)

    // Gettery
    int getRozmiar() const;
    bool czyPusta() const;
};

#endif