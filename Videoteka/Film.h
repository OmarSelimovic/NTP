#ifndef FILMOVI_H //ovo sprjecava da header bude inkludan vise puta
#define FILMOVI_H

#include <vector>
#include <string>

using namespace std;

struct Filmovi
{
    string FIme();
    string FZanr();
    vector<int> FOcjene();
    float fOcjena();
    unsigned int FBroj_filmova();   //Funkcije strukture Filmovi
void smanjBroj_filmova();
void povecajBroj_filmova();
void unosFIme(string podatak1);
void unosFZanr(string podatak2);
void unosFBroj_filmova(unsigned int podatak3);
void unosFOcjene(int podatak4);

    string ImeFilma;
    string ZanrFilma;
unsigned int Broj_filmova;
    vector<int> OcjeneFilma;

 };
#endif // FILMOVI_H
