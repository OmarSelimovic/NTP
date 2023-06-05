#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "Korisnik.h"
#include "Film.h"

using namespace std;


string Filmovi::FIme(){
    return ImeFilma;
}

string Filmovi::FZanr(){
    return ZanrFilma;
}

unsigned int Filmovi::FBroj_filmova(){   //Vraca broj filmova
     return Broj_filmova;
}

vector<int> Filmovi::FOcjene(){
    return OcjeneFilma;
}

void Filmovi::smanjBroj_filmova(){
  Broj_filmova--;
}

void Filmovi::povecajBroj_filmova(){
  Broj_filmova++;
}

float Filmovi::fOcjena(){
 if(OcjeneFilma.size()<1)
     {
       return 0;
     }
 else
    {
       float b=0.0;
       unsigned int q=0;
       for(int k=0;k<OcjeneFilma.size();k++)
        {
          b=b+OcjeneFilma[k];
          q++;
        }
      b=b/q;
     return b;
    }
}

void Filmovi::unosFIme(string podatak1){
 ImeFilma=podatak1;
}

void Filmovi::unosFZanr(string podatak2){
 ZanrFilma=podatak2;
}

void Filmovi::unosFBroj_filmova(unsigned int podatak3){
 Broj_filmova=podatak3;
}

void Filmovi::unosFOcjene(int podatak4){
   OcjeneFilma.push_back(podatak4);
}










