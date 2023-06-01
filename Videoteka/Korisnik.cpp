#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "Korisnik.h"
#include "Film.h"

using namespace std;


string Korisnici::getNadimak(){ //fuknkcija koja vraca Nadimak korisnika
   return Nadimak;
 }
string Korisnici::getIme(){ //funkcija koja vraća Ime korisnika
    return Ime;
}
string Korisnici::getLoginSifra(){ //funkcija koja vraća LoginSifru korisnika
    return LoginSifra;
}
vector<string> Korisnici::getUzeti_filmovi(){ //funkcija koja vraća Vektor uzetih filmova korisnika
    return Uzeti_filmovi;
}
bool Korisnici::getAdmin(){ //funkcija koja vraća Da ili Ne vrijednost Ili jesi ili nisi admin
    return Admin;
}
unsigned int Korisnici::getBrUzFilmova(){ //funkcija koja vraca broj uzetih filmova
    return brojUzetihFilmova;
}
void Korisnici::UzmiFilm(string Film){ //funkcija koja ubacuje novouzeti film u inventory osobe
      Uzeti_filmovi.push_back(Film);
      cout<<"\n \n Uzivajte u gledanju ^_^"<<endl;
      povecaj_brUzFilmova();
}
bool Korisnici::VratiFilm(string Film){ //funkcija koja vadi film sa liste uzetih filmova
  for(int i=0; i<Uzeti_filmovi.size();i++)                   //Uzima proslijeđeni argument i skida ga sa liste iznajmljenih
       if(Uzeti_filmovi[i]==Film)
          {  Uzeti_filmovi.erase(Uzeti_filmovi.begin() + i);
             cout<<"Hvala Vam na saradnji"<<endl;
             smanji_brUzFilmova();
             return(true);
          }
       else
        {  cout<<"Korisnik nema taj film"<<endl;
           return(false);
        }
}
void Korisnici::povecaj_brUzFilmova(){ //funkcija koja povecava broj uzetih filmova
  brojUzetihFilmova++;
}
void Korisnici::smanji_brUzFilmova(){ //funkcija koja smanjuje broj uzetih filmova
     if(brojUzetihFilmova==0)
         cout<<"Korisnik nema filmova"<<endl;
     else
         brojUzetihFilmova--;
}
void Korisnici::skrivenaFunkcija(){ //funkcija koja usera cini administratorom
   Admin=true;
}
void Korisnici::unosNadimak(string inf1){ //funkcija koja unosi nadimak novom useru
   Nadimak=inf1;
}
void Korisnici::unosIme(string inf2){ // funkcija koja unosi ime novom useru
   Ime=inf2;
}
void Korisnici::unosLoginSifra(string inf3){ //funkcija koja unosi password novom useru
     LoginSifra=inf3;
}





