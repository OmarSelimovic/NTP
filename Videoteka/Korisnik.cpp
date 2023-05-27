#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "Korisnik.h"
#include "Film.h"

using namespace std;


 string Korisnici::getNadimak()
 {
   return Nadimak;
 }

string Korisnici::getIme() //funkcija koja vraća Ime korisnika
{
    return Ime;
}
string Korisnici::getLoginSifra() //funkcija koja vraća LoginSifru korisnika
{
    return LoginSifra;
}
vector<string> Korisnici::getUzeti_filmovi() //funkcija koja vraća Vektor uzetih filmova korisnika
{
    return Uzeti_filmovi;
}

bool Korisnici::getAdmin() //funkcija koja vraća Da ili Ne vrijednost Ili jesi ili nisi admin
{
    return Admin;
}

void Korisnici::UzmiFilm(string Film) //funkcija koja ubacuje novouzeti film u inventory osobe
{
    Uzeti_filmovi.push_back(Film);
}

bool Korisnici::VratiFilm(string Film)
{
  for(int i=0; i<Uzeti_filmovi.size();i++)                   //Uzima proslijeđeni argument i skida ga sa liste iznajmljenih
       if(Uzeti_filmovi[i]==Film)
          {  Uzeti_filmovi.erase(Uzeti_filmovi.begin() + i);
             cout<<"Hvala Vam na saradnji"<<endl;
             return(true);
          }
       else
        {  cout<<"Korisnik nema taj film"<<endl;
           return(false);
        }
}

void Korisnici::skrivenaFunkcija(){
   Admin=true;

}

void Korisnici::unosNadimak(string inf1){
   Nadimak=inf1;
}

void Korisnici::unosIme(string inf2){
   Ime=inf2;
}

void Korisnici::unosLoginSifra(string inf3){
     LoginSifra=inf3;
}

void Korisnici::unosUzeti_filmovi(vector <string> inf4){
    Uzeti_filmovi=inf4;
}




