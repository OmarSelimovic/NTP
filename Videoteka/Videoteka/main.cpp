#include <iostream>
#include <cstdlib>
#include <limits>
#include <string>
#include <vector>
#include <stdlib.h>
#include <windows.h>
#include <algorithm>
#include "Korisnik.h"
#include "Film.h"


using namespace std;
void Dobrodosli();   //---------------> Graffiti art screen za pcoetak programa
bool Pocetna_Stranica(); //----------------------->Pocetna stranica za izbog log.in ili pravljenje novog usera
void PravljenjeKorisnika(vector<Korisnici>& users);//--------> Na ovu funkciju proslijeđujemo potpunu listu korisnika po referenci jer ce biti editovana ovdje
void Sekvenca_Gasenja(); //---------------------------------> Funkcija koja gasi program
bool LoginAuth(Korisnici& User, vector<Korisnici> ListaKorisnika , int& redniBroj); //Trenutni korisnik po ref. jer ce u njega biti ucitane vrijednosti iz Korisnik za kasniju upotrebu
void DobrodosliNazad(Korisnici TrenutniKorisnik); //------------->Screen dobrodoslice nakon uspjesne autentikacije
void PreviseGresaka();//--------------------------------------->Ukratko-funkcija poziva sekvencu gasenja
// Ovo je samo da razdvojim deklaracije funkcija od samij funkcija pošto je već postano previše zagušeno
void Dobrodosli()
{
    cout<< R"(

 $$$$$$\  $$$$$$\ $$$$$$$$\ $$$$$$$$\.......$$\    $$\ $$$$$$\ $$$$$$$\  $$$$$$$$\  $$$$$$\ $$$$$$$$\ $$$$$$$$\ $$\   $$\  $$$$$$\
$$  __$$\ \_$$  _|\____$$  |$$  _____|......$$ |   $$ |\_$$  _|$$  __$$\ $$  _____|$$  __$$\\__$$  __|$$  _____|$$ | $$  |$$  __$$\
$$ /  \__|  $$ |      $$  / $$ |............$$ |   $$ |  $$ |  $$ |  $$ |$$ |      $$ /  $$ |  $$ |   $$ |      $$ |$$  / $$ /  $$ |
\$$$$$$\    $$ |     $$  /  $$$$$\..........\$$\  $$  |  $$ |  $$ |  $$ |$$$$$\    $$ |  $$ |  $$ |   $$$$$\    $$$$$  /  $$$$$$$$ |
 \____$$\   $$ |    $$  /   $$  __|..........\$$\$$  /   $$ |  $$ |  $$ |$$  __|   $$ |  $$ |  $$ |   $$  __|   $$  $$<   $$  __$$ |
$$\   $$ |  $$ |   $$  /    $$ |..............\$$$  /    $$ |  $$ |  $$ |$$ |      $$ |  $$ |  $$ |   $$ |      $$ |\$$\  $$ |  $$ |
\$$$$$$  |$$$$$$\ $$$$$$$$\ $$$$$$$$\..........\$  /   $$$$$$\ $$$$$$$  |$$$$$$$$\  $$$$$$  |  $$ |   $$$$$$$$\ $$ | \$$\ $$ |  $$ |
 \______/ \______|\________|\________|..........\_/    \______|\_______/ \________| \______/   \__|   \________|\__|  \__|\__|  \__| )";

cout<<"\n \n"<<"                                        PRITISNITE BILO KOJE DUGME DA BISTE NASTAVILI"<<endl;
cin.ignore();

system("CLS");


}
void DobrodosliNazad(Korisnici TrenutniKorisnik)
{
    system("CLS");
    cout<<"_____Dobrodosli nazad "<<TrenutniKorisnik.getIme()<<"_____"<<"\n"<<endl;
    if (TrenutniKorisnik.getBrUzFilmova()==0)
        cout<<"Nemate iznajmljenih filmova, vrijeme je da to promjenite ;) "<<endl;
    else
        {
          cout<<"Tenutno imate "<<TrenutniKorisnik.getBrUzFilmova()<<" uzetih filmova."<<endl;
          cout<<"A ti filmovi su:"<<endl;
          for(int i=0; i<TrenutniKorisnik.getBrUzFilmova();i++) //koristeci funkciju getBrUzFilmova i dodavanjem broja uzetih filmova u strukturu Korisnik
             {                                                  //sprecujem potrebu da dvaki put brojim koliko filmova ima korisnik
              int j=i++;
              cout<<"["<<j<<".]-"<<TrenutniKorisnik.Uzeti_filmovi[i]<<endl;
             }

        }
}
bool Pocetna_Stranica()
{
    int Login_izbor = 0;

    cout << "Izaberite jednu od opcija:" << endl;
    cout << "[1]-Login" << endl;
    cout << "[2]-Novi korisnik" << endl;
    cout << "____________________________" << endl;

    while (!(cin >> Login_izbor) || (Login_izbor != 1 && Login_izbor != 2))  //unos Login_izbora i provjera da li je jedna od valjanih vrijednosti
        {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Dozvoljava samo unos borjeva
        cout << "Molimo unesite valjan izbor (1 ili 2):" << endl;
        }
    if(Login_izbor==1) return(true);
      else return(false);

}
bool LoginAuth(Korisnici& User , vector<Korisnici> ListaKorisnika , int& redniBroj)
{
    string Username, Password;
    int brPokusaja=3;                     //broji koliko puta smo se pokusali ulogovati
    while (brPokusaja>0)
        {
         system("CLS");
         cout<<"Unesite vas username:"<<endl;
         cin>>Username;
         cout<<endl<<endl;
         cout<<"Unesite vas password:"<<endl;
         cin>>Password;

          for (int i=0;i<ListaKorisnika.size();i++)
             {
                  if(ListaKorisnika[i].getNadimak()==Username && ListaKorisnika[i].getLoginSifra()==Password)
                    /*Ova petlja djeluje komplikovano ali ona lista vektor strukture Korisnik od prvog do zadnje varijable u vektoru i poredi da li objekt iz vektora
                      ima isti username i password kao osoba koja se pokusava ulogovati, drugim rijecima trazi tog korisnika u bazi*/
                  {
                     User=ListaKorisnika[i]; //---->pravimo klon usera sa glavne liste korisnika na priveremni buffer

                     redniBroj=i; /*Ovaj redni broj ce mi biti koristan da kasnije kada budem vracao nove informacije o korisniku da znam gdje ih vratiti bez potrebe
                                    da listam cijelu bazu podataka da bih ga nasao*/
                     return(true);
                  }
             }
         system("CLS");
         cout<<"Pogresan username/password!\n \n ";
         brPokusaja-=1;
         cout<<"Imate jos "<<brPokusaja<<" pokusaja.";
         Sleep(2000);
         }
  return(false);
}
void PravljenjeKorisnika(vector<Korisnici>& users)
{
      string noviNadimak, novoIme, novaLoginSifra; /* -------> Ovo su varijable koje ce biti upisane u zasebne membere objekta strukture Korisnici koji se zove "UserVideoteke"
                                                              Pojedini memberi objekta nece biti inicialitirani odmah te ce biti ostavljeni na njihovim default vrijednostima
                                                              Default vrijednost membera "vector <string> Uzeti_filmovi" ce biti prazan vektor
                                                              Default vrijednost membera "bool Admin;" će biti False*/
     Korisnici UserVideoteke;


      system("CLS");
      cout<<"Zdravo, za pravljenje novog naloga bit ce potrebno da unesete par informacija."<<endl;
      cout<<"-------------------------------------------------------------------------------"<<endl;
      cout<<"        >>>Sve stavke osim Imena i Prezimena se pisu bez razmaka<<<\n\n"<<endl;
      cout<<"Za nastavak pritisnite bilo koje dugme.";
      cin.ignore();cin.ignore();
      system("CLS");
      cout<<"Izaberete vas login username: ";
             cin>>noviNadimak;
             for(int i=0;i<users.size();i++)
             {
               while(noviNadimak==users[i].getNadimak())
                 {
                   cout<<"Zao nam je ali taj username je vec zauzet"<<endl;
                   cout<<"Izaberite neki drugi username:"<<endl;
                   cin>>noviNadimak;
                 }
             }

      cout<<"\n Spremljeno :) "<<endl;
      cout<<"\n Sada unosite vase puno Ime i Prezime: ";
            cin.ignore();
            getline(cin, novoIme);

      cout<<"\n Spremljeno :O \n "<<endl;
      cout<<"Sada je jos samo ostalo da unesete vasu sifru: ";
            cin>>novaLoginSifra;
      cout<<"\n Spremljeno ^_^ "<<endl;
      cout<<"\n \n";
      Sleep(1000);
      system("CLS");
      cout<<"Kreiranje novog korisnickog naloga"<<endl;
      cout<<"[IIII______] 40%"<<endl;
      Sleep(2000);
      system("CLS");
      cout<<"Priprema naloga"<<endl;
      cout<<"[IIII______] 40%"<<endl;
      Sleep(2000);
      system("CLS");
      cout<<"Priprema naloga"<<endl;
      cout<<"[IIIIIIII__] 80%"<<endl;
      Sleep(2000);
      system("CLS");
      cout<<"Pravljenje novog naloga je gotovo!"<<endl;
      cout<<"[IIIIIIIIII] 100%"<<endl;
      Sleep(2000);
      system("CLS");
      UserVideoteke.unosNadimak(noviNadimak);  //funkcija .unosNadimak je void funkcija iz Korisnik.cpp koja upisuje informacije u objekt strukture Korisnik
      UserVideoteke.unosIme(novoIme);
      UserVideoteke.unosLoginSifra(novaLoginSifra);
      cout<<"Informacije o Vasem novom nalogu su:"<<endl;
      cout<<"____________________________________"<<endl;
      cout<<"Username: "<<UserVideoteke.getNadimak()<<endl;
      cout<<"Ime i prezime: "<<UserVideoteke.getIme()<<endl;
      cout<<"Login Password: "<<UserVideoteke.getLoginSifra()<<endl;
      Sleep(5000);

      users.push_back(UserVideoteke);                     //Ucitava novg korisnika u glavni vektor

      system("CLS");
      cout<<"_______________Sada cete biti proslijedeni na log-in screen_______________"<<endl;
      Sleep(2000);
      system("CLS");

}
void Sekvenca_Gasenja()
{
     system("CLS");
     cout<<"Gasenje pozadinskih proceca"<<endl;
     cout<<"[I_________] 10%"<<endl;
     Sleep(2000);
      system("CLS");
      cout<<"Zatvaranje prozora"<<endl;
     cout<<"[II________] 20%"<<endl;
     Sleep(2000);
     system("CLS");
     cout<<"Slanje patuljaka iz vaseg kompjutera na spavanje"<<endl;
     cout<<"[IIIIIIII__] 80%"<<endl;
     Sleep(3000);
     system("CLS");
     cout<<"Gotovo"<<endl;
     cout<<"[IIIIIIIIII] 100%"<<endl;
     Sleep(2000);
     exit(0);
}
void PreviseGresaka()
{
  system("CLS");
      cout<<"Zao nam je, ali pogrijesili ste previse puta"<<"\n"<<"Kontaktirajte administratora."<<endl;
      Sleep(5000);
  Sekvenca_Gasenja();
}
int main()
{
    vector<Korisnici> Korisnik;//----------------------->Glavni vektor o korisnicima u koji ce se ucitavati podaci i sa kojeg ce se pisati pdoaci za pohranu.
    vector<Filmovi> Film;//----------------------------->Glavni vektor o filmovima u koji ce se ucitavati podaci i sa kojeg ce se pisati pdoaci za pohranu.
    Korisnici TrenutniKorisnik;//----------------------->Ovo je privremena varijabla koja cuva informacije o trenutnom korisniku.
    int RBrTrenutniKorisnik;/*-------------------------->Redni broj trenutnog korisnika (Ovo ce olaksati da kasnije kada ga budemo
                                                        unosili nazad u sistem da ga ne moramo traziti na kojem je mjestu u vektoru).*/


     string command_window = "mode con: cols=132 lines=35"; //Odeđuje komandu koju je moguce mogificirati
     system(command_window.c_str());                        //Uzima parametre prethodno modificirane komande i oređuje velicinu terminal prozora


     Dobrodosli();
     if (!Pocetna_Stranica()) /*-------------------------->Ako je odabir usera da pravi novi racun(FALSE) prvo se poziva funkcija pravljenja
                                                           a potom se poziva funkcija za log-in screen*/
     {
        PravljenjeKorisnika(Korisnik);//------------------>Pozivamo funkciju za pravljenje novog korisnika i proslijedjujemo joj vektor korisnika

        if(LoginAuth(TrenutniKorisnik,Korisnik,RBrTrenutniKorisnik)) //Pozivamo funkciju autentikacije i saljemo joj buffer usera, njegov redni broj i potpunu listu
            { DobrodosliNazad(TrenutniKorisnik);

              //nekadrugafunkcija(Film, Korisnik, TrenutniKorisnik, RBrTrenutniKorisnik);    TO-DO FUNKCIJA IZBORNOG MENIA

                           /*---U ovoj funkciji "nekadrugafunkcija" se displaya lsita izbora sta sve korisnik ili administrator zeli da uradi
                                  u njoj ce doci do editovanja lista filmova i editovanja liste korisnika i vrijednosti.
                             ---Po kraju ili izvršenju ove funkcije se vracamo nazad gdje cemo uraditi spremanje promjenjenih podataka u glavne vektore.
                             ---Potom pozivamo funkciju koja ce spremiti sadrzaje vektora u zasebne fajlove  u txt file
                                 CSV(comma-seeparated values) formata ili nekog sličnog*/
            }
         else
            PreviseGresaka(); //-------------------------->Neka lijepa rijec prije nego terminiramo program zbog pogresnih pokusaja logovanja
      }

    else//------------------------------------------------->Ukoliko user izabere da se odmah loguje preskace se funkcija pravljenja korisnika.
    {
      if(LoginAuth(TrenutniKorisnik,Korisnik,RBrTrenutniKorisnik))
        { DobrodosliNazad(TrenutniKorisnik);
            //nekadrugafunkcija(Film, Korisnik, TrenutniKorisnik, RBrTrenutniKorisnik);    TO-DO FUNKCIJA IZBORNOG MENIA

                           /*---U ovoj funkciji "nekadrugafunkcija" se displaya lsita izbora sta sve korisnik ili administrator zeli da uradi
                                  u njoj ce doci do editovanja lista filmova i editovanja liste korisnika i vrijednosti.
                             ---Po kraju ili izvršenju ove funkcije se vracamo nazad gdje cemo uraditi spremanje promjenjenih podataka u glavne vektore.
                             ---Potom pozivamo funkciju koja ce spremiti sadrzaje vektora u zasebne fajlove  u txt file
                                 CSV(comma-seeparated values) formata ili nekog sličnog*/
        }
       else
         PreviseGresaka();

    }


}
