#include "DynamicznaTablica.h"
#include "ListaJednokierunkowa.h"
#include "ListaDwukierunkowa.h"
#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <functional>
#include <ctime>   
#include <cstdlib> 

using namespace std;
using namespace std::chrono;

// --- Sekcja automatycznych badań (bez zmian) ---

const int ROZMIARY[] = { 5000, 10000, 20000, 40000, 60000, 80000, 100000, 150000 };
const int POWTORZENIA = 20;

template<typename T>
long long mierz(int n, int* dane, function<void(T&)> op) {
    vector<T> kopie(POWTORZENIA);
    for (auto& k : kopie) for (int i = 0; i < n; i++) k.dodajNaKoniec(dane[i]);
    auto start = high_resolution_clock::now();
    for (auto& k : kopie) op(k);
    return duration_cast<nanoseconds>(high_resolution_clock::now() - start).count() / POWTORZENIA;
}

template<typename T>
void badajStrukture(ofstream& csv, string nazwa) {
    cout << "\n--- " << nazwa << " [ns] ---\n";
    cout << "Rozm.\tD.Pocz\tD.Los\tD.Kon\tU.Pocz\tU.Los\tU.Kon\tSzukaj\n";

    for (int n : ROZMIARY) {
        int* dane = new int[n];
        for (int i = 0; i < n; i++) dane[i] = rand();
        int r = (n > 0) ? rand() % n : 0;

        long long dp = mierz<T>(n, dane, [](T& s) { s.dodajNaPoczatek(9); });
        long long dl = mierz<T>(n, dane, [r](T& s) { s.dodajNaPozycji(r, 9); });
        long long dk = mierz<T>(n, dane, [](T& s) { s.dodajNaKoniec(9); });
        long long up = mierz<T>(n, dane, [](T& s) { s.usunZPoczatku(); });
        long long ul = mierz<T>(n, dane, [r](T& s) { s.usunZPozycji(r); });
        long long uk = mierz<T>(n, dane, [](T& s) { s.usunZKonca(); });
        long long sz = mierz<T>(n, dane, [dane, n](T& s) { s.zawiera(dane[n / 2]); });

        csv << nazwa << ";" << n << ";" << dp << ";" << dl << ";" << dk << ";"
            << up << ";" << ul << ";" << uk << ";" << sz << "\n";

        cout << n << "\t" << dp << "\t" << dl << "\t" << dk << "\t"
            << up << "\t" << ul << "\t" << uk << "\t" << sz << "\n";

        delete[] dane;
    }
}

void uruchomBadania() {
    ofstream csv("wyniki.csv");
    csv << "Struktura;Rozmiar;DodajPoczatek[ns];DodajLosowo[ns];DodajKoniec[ns];"
        << "UsunPoczatek[ns];UsunLosowo[ns];UsunKoniec[ns];Szukaj[ns]\n";

    badajStrukture<DynamicznaTablica>(csv, "Tablica");
    badajStrukture<ListaJednokierunkowa>(csv, "Lista1K");
    badajStrukture<ListaDwukierunkowa>(csv, "Lista2K");

    csv.close();
    cout << "\nBadania zakonczone. Wyniki zapisano do wyniki.csv\n";
}

// --- Sekcja interaktywnego menu z pomiarem czasu ---

template<typename T>
void menuDlaStruktury(string nazwaStruktury) {
    T struktura;
    int wybor, wartosc, indeks;
    string nazwaPliku;

    do {
        cout << "\n--- " << nazwaStruktury << " ---\n";
        cout << "1. Zbuduj z pliku\n";
        cout << "2. Usun (podaj indeks)\n";
        cout << "3. Dodaj (podaj indeks i wartosc)\n";
        cout << "4. Znajdz element\n";
        cout << "5. Utworz losowo\n";
        cout << "6. Wyswietl\n";
        cout << "0. Powrot\n";
        cout << "Wybor: ";
        cin >> wybor;

        auto start = high_resolution_clock::now(); // Start zegara dla kazdej operacji

        switch (wybor) {
        case 1:
            cout << "Podaj nazwe pliku: ";
            cin >> nazwaPliku;
            struktura.wczytajZPliku(nazwaPliku);
            break;
        case 2:
            cout << "Podaj indeks: ";
            cin >> indeks;
            start = high_resolution_clock::now(); // Reset startu przed sama operacja
            struktura.usunZPozycji(indeks);
            break;
        case 3:
            cout << "Podaj indeks: "; cin >> indeks;
            cout << "Podaj wartosc: "; cin >> wartosc;
            start = high_resolution_clock::now();
            struktura.dodajNaPozycji(indeks, wartosc);
            break;
        case 4:
            cout << "Podaj szukana wartosc: ";
            cin >> wartosc;
            start = high_resolution_clock::now();
            if (struktura.zawiera(wartosc)) cout << "Element znajduje sie w strukturze.\n";
            else cout << "Brak elementu.\n";
            break;
        case 5:
            cout << "Ile elementow wygenerowac? ";
            cin >> indeks;
            start = high_resolution_clock::now();
            struktura.wypelnijLosowo(indeks, time(NULL));
            break;
        case 6:
            struktura.wyswietl();
            break;
        }

        auto end = high_resolution_clock::now();
        if (wybor > 0 && wybor < 6) { // Wyswietl czas tylko dla operacji modyfikujacych/szukajacych
            cout << "Czas wykonania operacji: "
                << duration_cast<nanoseconds>(end - start).count() << " ns\n";
        }

    } while (wybor != 0);
}

int main() {
    srand(static_cast<unsigned int>(time(NULL)));
    int wyborGlowny;

    do {
        cout << "\n=== MENU GLOWNE ===\n";
        cout << "1. Tablica Dynamiczna\n";
        cout << "2. Lista Jednokierunkowa\n";
        cout << "3. Lista Dwukierunkowa\n";
        cout << "4. Automatyczne badania wydajnosci (do CSV)\n";
        cout << "0. Wyjscie\n";
        cout << "Wybor: ";
        cin >> wyborGlowny;

        switch (wyborGlowny) {
        case 1: menuDlaStruktury<DynamicznaTablica>("Tablica Dynamiczna"); break;
        case 2: menuDlaStruktury<ListaJednokierunkowa>("Lista Jednokierunkowa"); break;
        case 3: menuDlaStruktury<ListaDwukierunkowa>("Lista Dwukierunkowa"); break;
        case 4: uruchomBadania(); break;
        }
    } while (wyborGlowny != 0);

    return 0;
}