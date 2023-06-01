#ifndef KORISNIK_H //ovo sprjecava da header bude inkludan vise puta
#define KORISNIK_H
#include <vector>
#include <string>

using namespace std;

struct Korisnici
{
    string getNadimak();
    string getIme();
    string getLoginSifra();
    vector <string> getUzeti_filmovi();
    bool getAdmin();
unsigned int getBrUzFilmova();
void skrivenaFunkcija();
void unosNadimak(string inf1);        //ovo su sve deklaracije funkcija u Korisnik.cpp koje ce imati pristup privatnim clanovima klase Korisnici
void unosIme(string inf2);
void unosLoginSifra(string inf3);
void povecaj_brUzFilmova();
void smanji_brUzFilmova();
bool VratiFilm(string Film);
void UzmiFilm(string Film);

    string Nadimak;
    string Ime;
    string LoginSifra;              //private memberi klase Korisnik
    vector <string> Uzeti_filmovi;
unsigned int brojUzetihFilmova=0;
    bool Admin=false;


};
#endif // KORISNIK_H
