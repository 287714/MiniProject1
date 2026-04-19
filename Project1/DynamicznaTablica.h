#ifndef DYNAMICZNATABLICA_H
#define DYNAMICZNATABLICA_H

#include <iostream>
#include <string>

using namespace std;

/**
 * Klasa DynamicznaTablica (Dynamic Array)
 * Implementacja tablicy, ktora automatycznie zwieksza swoja pojemnosc dwukrotnie,
 * gdy zabraknie miejsca na nowe elementy.
 */
class DynamicznaTablica {
private:
    int* data;          // Wskaznik na tablice elementow 
    int size;           // Aktualna liczba elementow 
    int capacity;       // Calkowita pojemnosc tablicy 

    void zmienRozmiar();

public:
    // Konstruktory i destruktor
    DynamicznaTablica();
    DynamicznaTablica(const DynamicznaTablica& other);
    ~DynamicznaTablica();

    // Operacje modyfikujace
    void dodajNaPoczatek(int element);           // O(n)
    void dodajNaKoniec(int element);             // O(1) amortyzowane
    void dodajNaPozycji(int index, int element); // O(n)

    void usunZPoczatku();                        // O(n)
    void usunZKonca();                           // O(1)
    void usunZPozycji(int index);                // O(n)

    // Operacje wyszukiwania i administracyjne
    bool zawiera(int element) const;             // O(n)
    void wyswietl() const;                       // Wyswietla zawartosc tablicy
    void wypelnijLosowo(int n, int ziarno);      // Generuje n losowych liczb
    void wczytajZPliku(const string& nazwa);     // Wczytuje dane z pliku tekstowego
    void wyczysc();                             // Resetuje tablice i zwalnia pamiec

    // Gettery
    int getRozmiar() const;
};

#endif