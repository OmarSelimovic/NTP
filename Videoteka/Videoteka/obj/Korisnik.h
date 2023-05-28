#pragma once //ovo sprjecava da header bude inkludan vise puta
#include <vector>
#include <string>

using namespace std;

class Korisnici
{
public:
    string getNadimak();
    string getIme();
    string getLoginSifra();
    vector <string> getUzeti_filmovi();
    bool getAdmin();
void skrivenaFunkcija();
void unosNadimak(string inf1);        //ovo su sve deklaracije funkcija u Korisnik.cpp koje ce imati pristup privatnim clanovima klase Korisnici
void unosIme(string inf2);
void unosLoginSifra(string inf3);
void unosUzeti_filmovi(vector <string> inf4);
bool VratiFilm(string Film);
void UzmiFilm(string Film);

private:
    string Nadimak;
    string Ime;
    string LoginSifra;              //private memberi klase Korisnik
    vector <string> Uzeti_filmovi;
    bool Admin;


};
