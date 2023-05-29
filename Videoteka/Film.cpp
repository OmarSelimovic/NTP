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

unsigned int Filmovi::FBroj_filmova(){
     return Broj_filmova;
}

vector<int> Filmovi::FOcjene(){
    return OcjeneFilma;
}

float Filmovi::fOcjena(){
    if(OcjeneFilma.size()<1)
     {
       return 0;
     }
    else
    {
       float b=0;
       unsigned int q;
       for(int i=0;i<OcjeneFilma.size();i++)
        {
          b=b+OcjeneFilma[i];
          q=i;
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

void Filmovi::unosFBroj_filmova(int podatak3){
 Broj_filmova=podatak3;
}

void Filmovi::unosFOcjene(int podatak4){
   OcjeneFilma.push_back(podatak4);
}










