#pragma once //ovo sprjecava da header bude inkludan vise puta
#include <vector>
#include <string>

using namespace std;

class Filmovi
{
public:
    string FIme();
    string FZanr();
unsigned int FBroj_filmova();
   vector<int> FOcjene();
   float fOcjena();
void unosFIme(string podatak1);
void unosFZanr(string podatak2);
void unosFBroj_filmova(int podatak3);
void unosFOcjene(int podatak4);

private:
    string ImeFilma;
    string ZanrFilma;
unsigned int Broj_filmova;
    vector<int> OcjeneFilma;

 };
