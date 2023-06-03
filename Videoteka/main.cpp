#include <iostream>
#include <cstdlib>
#include <limits>
#include <string>
#include <vector>
#include <stdlib.h>
#include <windows.h>
#include <algorithm>
#include <conio.h>  //Koristit cu ga samo za getch();---> "pritisnite dugme da nastavite"
#include "Korisnik.h"
#include "Film.h"


using namespace std;
void Dobrodosli();   //---------------> Graffiti art screen za pcoetak programa
bool Pocetna_Stranica(); //----------------------->Pocetna stranica za izbog log.in ili pravljenje novog usera
void PravljenjeKorisnika(vector<Korisnici>& users);//--------> Na ovu funkciju proslijeđujemo potpunu listu korisnika po referenci jer ce biti editovana ovdje
bool LoginAuth(Korisnici& User, vector<Korisnici> ListaKorisnika , int& redniBroj); //Trenutni korisnik po ref. jer ce u njega biti ucitane vrijednosti iz Korisnik za kasniju upotrebu
void DobrodosliNazad(Korisnici TrenutniKorisnik); //------------->Screen dobrodoslice nakon uspjesne autentikacije

void GlavniMeni(vector<Filmovi>& ListaFilmova, vector<Korisnici>& ListaKorisnika, Korisnici& TrenKorisnik, int RBRTrenKor);

                                                   /*Eh ovo je do sada najveca funkcija u programu, ovo je funkcija glavnog menija koja ce u biti raditi sve.
                                                    Od ucitavanja liste filmova na display sa ocjenom, izabira filmova, ostavljanja ocjena filmovima, dodavanja novih filmova,
                                                    listanja lsite korisnika od strane administratora.
                                                    MOŽDA DODAM OPCIJU DA ADMIN UPOZORI ILI CAK IZBRISE KORISNIKA 3:) */
void PokaziFilmove(vector<Filmovi> ListaFilmova);//---------> Basic output funkcija za formatiran ispis filmova i njihovog opisa u videoteci
void NarucivanjeFilmova(vector<Filmovi>& ListaFilmova,Korisnici& TrenKorisnik); //------------------> Funkcija narucivanja filma
void VracanjeFilmova(vector<Filmovi>& ListaFilmova,Korisnici& TrenKorisnik); //---------------------> Funkcija vracanja i ocjenjivanja filma
void PreviseGresaka();//------------------------------------>Ukratko-funkcija poziva sekvencu gasenja
void Sekvenca_Gasenja(); //---------------------------------> Funkcija koja gasi program
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
getch();

system("CLS");


}
void DobrodosliNazad(Korisnici TrenutniKorisnik)
{
    system("CLS");
    if(TrenutniKorisnik.Admin==true)
    {
        cout<<"...Administratorske ovlasti ucitane..."<<endl;
        cout<<"-----------Dobrodosli nazad-----------"<<endl;
        getch();
        return;
    }
    else
    {
        cout<<"__________Dobrodosli nazad "<<TrenutniKorisnik.getIme()<<"__________"<<"\n"<<endl;
           if (TrenutniKorisnik.getBrUzFilmova()==0)
              {
               cout<<"Nemate iznajmljenih filmova, vrijeme je da to promjenite ;)";
               getch();
               return;
              }
           else
              {
               cout<<"Tenutno imate "<<TrenutniKorisnik.getBrUzFilmova()<<" uzetih filmova."<<endl;
               cout<<"A ti filmovi su:"<<endl;
               for(int i=0; i<TrenutniKorisnik.getBrUzFilmova();i++)//koristeci funkciju getBrUzFilmova i dodavanjem broja uzetih filmova u strukturu Korisnik sprejcujem potrebu(nastavlja se ispod)
               cout<<"["<<i+1<<".]-"<<TrenutniKorisnik.Uzeti_filmovi[i]<<endl; //da svaki put brojim koliko filmova ima kod korisnika
               getch();
               return;
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

    while(!(cin>>Login_izbor)||(Login_izbor != 1 && Login_izbor != 2))  //unos Login_izbora i provjera da li je jedna od valjanih vrijednosti
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
         cout<<"Preostali broj pokusaja: "<<brPokusaja<<endl;
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
      cin.get();cin.get();
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
void GlavniMeni(vector<Filmovi>& ListaFilmova, vector<Korisnici>& ListaKorisnika, Korisnici& TrenKorisnik, int RBRTrenKor)
{
    bool kraj=false;
    if(TrenKorisnik.Admin==false)
    {
         int izbor = 0;
      while(izbor!=4)
      {
         system("CLS");
         cout << "   Izaberite jednu od opcija:" << endl;
         cout << "|-------------------------------|" << endl;
         cout << "|[1]-Zelim vidjeti izbor filmova|"<<endl;
         cout << "|[2]-Zelim naruciti film        |" << endl;
         cout << "|[3]-Zelim vratiti film/ove     |" << endl;
         cout << "|[4]-EXIT                       |" << endl;
         cout << "|-------------------------------|" << endl;

         while (!(cin >> izbor) || (izbor <1) || (izbor>4))  //unos Login_izbora i provjera da li je jedna od valjanih vrijednosti
             {
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Dozvoljava samo unos borjeva
              cout << "Molimo unesite valjan izbor :" << endl;
             }
             if(izbor==1) PokaziFilmove(ListaFilmova);

        else if(izbor==2) NarucivanjeFilmova(ListaFilmova, TrenKorisnik);

        else if(izbor==3) VracanjeFilmova(ListaFilmova, TrenKorisnik);

        else if(izbor==4){
                          cout<<"test"<<endl; // TO-DO dodati funkciju za spremanje svih promjena prije gasenja
                          Sekvenca_Gasenja();
                         }


      }
    }
    else
    {

     //Ovdje ide nesto slično ovom iznad samo što će biti druge, administratorske opcije
    }
}
void PokaziFilmove(vector<Filmovi> ListaFilmova)//-------> Ispisuje potpunu listu filmova korisniku na prozor
{
    system("CLS");
    Filmovi buffer; //------------> Nisam siguran ali mislim da ako ovo uvedem, da cu olaksati programu da ne mora svaki put listati sav vektor
    for(int i=0;i<ListaFilmova.size();i++)
        {
            buffer=ListaFilmova[i];
            cout<<"---------------------------------------------------------"<<endl;
            cout<<"["<<i+1<<"]-"<<buffer.ImeFilma<<endl;
            cout<<"Zanr filma: "<<buffer.ZanrFilma<<endl;
            if(buffer.fOcjena()==0)
            cout<<"Film jos nije ocijenjen."<<endl;
            else
            cout<<"Ocjena filma : "<<buffer.fOcjena()<<endl;
            if(buffer.Broj_filmova==0)
            cout<<"Nazalost, ovog filma nemamo na stanju."<<endl;
            else
            cout<<"Ovih filmova na stanju imamo: "<<buffer.fOcjena()<<endl;
            cout<<"---------------------------------------------------------\n \n"<<endl;
            Sleep(800);

        }
    cout<<"|KRAJ LISTE____________________________________KRAJ LISTE|"<<endl;
     cout<<"Pritisnite bilo koje dugme da se vratite nazad"<<endl;
     getch();
}
void NarucivanjeFilmova(vector<Filmovi>& ListaFilmova,Korisnici& TrenKorisnik)
{
  system("CLS");
  if(TrenKorisnik.brojUzetihFilmova>4)
     {
      cout<<"Zao nam je ali vec imate 5 filmova kod sebe, sto je dozvoljeni maksimum."<<endl;
      cout<<"Da biste uzeli nove filmove, morat ćete prvo vratiti neke od prethodno uzetih filmova."<<endl;
      getch();
      cout<<"\n \n Bit cete vraceni na glavni meni"<<endl;
      Sleep(1000);
      return;
      }

        cout<<"Lista filmova na raspolaganju:"<<endl;

           Filmovi buffer; //------------> isto kao i iznad
           int RBrFilma=0,PRbrFilma=0, KolFilmova=0;
             for(int i=0;i<ListaFilmova.size();i++)
                 {
                  if (ListaFilmova[i].Broj_filmova==0)     //---------------> provjerava da li filma na ListaFilmova[i] ima na stanju
                     {
                        cout<<"["<<i+1<<"]-"<<ListaFilmova[i].FIme()<<endl;
                        cout<<"__Ovog filma nemamo na stanju__"<<endl;      //------> na ovaj nacin lista ostaje cjelokupna ali filmovi kojih nema bivaju oznaceni ovako
                        i++;
                     }
                     buffer=ListaFilmova[i];
                     cout<<"---------------------------------------------------------"<<endl;
                     cout<<"["<<i+1<<"]-"<<buffer.ImeFilma<<endl;
                     cout<<"Zanr filma: "<<buffer.ZanrFilma<<endl;
                     if(buffer.fOcjena()==0)
                     cout<<"Film jos nije ocijenjen."<<endl;
                     else
                     cout<<"Ocjena filma : "<<buffer.fOcjena()<<endl;
                     cout<<"Ovih filmova na stanju imamo: "<<buffer.fOcjena()<<endl;
                     cout<<"---------------------------------------------------------\n"<<endl;
                 }
                     cout<<"|KRAJ LISTE____________________________________KRAJ LISTE|"<<endl;

                        cout<<"Koliko filmova zelite iznajmiti? (Od 1 do 3)"<<endl;
                        cin>>KolFilmova;
                        while(KolFilmova>3 || KolFilmova<1 || KolFilmova==0)
                                            {
                                             if(KolFilmova==0)
                                                             {
                                                               cout<<"Da li vi uopste zelite iznajmiti film (y/n)?"<<endl;
                                                               char g;
                                                               cin>>g;
                                                               if (g== 'n' || g== 'N')
                                                                            {
                                                                              system("CLS");
                                                                              cout<<"Zao nam je sto se te predomislili"<<endl;
                                                                              cout<<"Bit cete vraceni na glavni meni"<<endl;
                                                                              getch();
                                                                              return;
                                                                            }
                                                               if (g== 'y' || g== 'Y')
                                                                            {
                                                                             cout<<"Koliko filmova zelite iznajmiti? (Od 1 do 3)"<<endl;
                                                                             cin>>KolFilmova;
                                                                            }
                                                             }
                                             if (KolFilmova<1)
                                                             {
                                                                  cout<<"Ne mozete iznajmiti manje od jednog filma"<<endl;
                                                                  cout<<"Koliko filmova zelite iznajmiti? (Od 1 do 3)"<<endl;
                                                                  cin>>KolFilmova;
                                                             }

                                             if(KolFilmova>3)
                                                             {
                                                              cout<<"Ne mozete iznajmiti vise od 3 filmoa odjendom"<<endl;
                                                              cout<<"Koliko filmova zelite iznajmiti? (Od 1 do 3)"<<endl;
                                                              cin>>KolFilmova;
                                                             }
                                              }
                 for(int i=0;i<KolFilmova;i++)
                    {
                      cout<<"Unesite redni broj filma koji zelite"<<endl;
                      cin>>RBrFilma;
                      while(RBrFilma==PRbrFilma)
                                   {
                                     cout<<"Ne mozete dva ista filma za redom iznajmiti"<<endl;
                                     cout<<"Izaberite neki drugi film"<<endl;
                                     cin>>RBrFilma;
                                   }
                      while (ListaFilmova[RBrFilma].Broj_filmova==0) //-------> provjeravanje inteligencije korisnika jer zeli film za koji pise da ga nema na stanju
                            {                                        /*-------> Ovja mali test biranja filma utvrđuje da redni broj koji korisnik unosi ne moze
                                                                                oznacavati neki film kojeg nema na stanju. Taj broj ne moze biti veci od maksimalnog
                                                                                broja sa liste niti manji od najmanjeg broja sa liste*/

                              cout<<"Vec smo naglasili da tog filma nemamo na stanju"<<endl;
                              cout<<"Da li zelite neki drugi film? (y/n)"<<endl;
                                   char drfilm;
                                   if (drfilm== 'n' || drfilm== 'N')
                                                                 {
                                                                  system("CLS");
                                                                  cout<<"Zao nam je jer nismo imali filma kojeg ste zeljeli"<<endl;
                                                                  cout<<"Bit cete vraceni na glavni meni"<<endl;
                                                                  Sleep(800);
                                                                  return;
                                                                 }
                                  if (drfilm== 'y' || drfilm== 'Y')
                                                                 {
                                                                   cout<<"\n Unesite valjan broj filma"<<endl;
                                                                   cin>>RBrFilma;
                                                                 }

                                  while (RBrFilma>ListaFilmova.size() || RBrFilma<1)
                                         {
                                          cout<<"Film tog rednog broja nije na listi :)"<<endl;
                                          cout<<"Izaberite valjan film"<<endl;
                                          cin>>RBrFilma;
                                         }
                            }
                       TrenKorisnik.UzmiFilm(ListaFilmova[RBrFilma].ImeFilma);     //------>U vektor filmova koji su kod korisnika push_backa ime filma koji je korisnik uzeo
                                                                              //------> Tek sada shvatam da je bilo bolje da struktura Korisnici umjesto vector<string> ListaFilmova
                                                                                       // ima vector<Filmovi> ListaFilmova, međutim previse je kasno mijenjati kod a benefiti su mali
                       ListaFilmova[RBrFilma].smanjBroj_filmova(); //-------------------->Smanjuje broj filmova u inventoriju za film koji je uzeo korisnik
                       PRbrFilma=RBrFilma; //------> RedniBrojFIlma koji je sada uzet postaje "Prethodni broj Filma"
                    }
}
void VracanjeFilmova(vector<Filmovi>& ListaFilmova,Korisnici& TrenKorisnik) //---------------Vracanje filmova i ocenjivanje
{
  system("CLS");
  if (TrenKorisnik.brojUzetihFilmova==0)                //-----------------> kako vratiti filmove koje nemate? :D
     {
       cout<<"Trenutno nemate filmova koje mozete vratiti"<<endl;
       cout<<"Bit cete vraceni na glavni meni"<<endl;
       getch();
       return;
     }
  else
    {int RbFilma=0, KolFilmova=0;
     string nazivFilma;

       cout<<"Lista filmova koje trenutno imate:"<<endl; //-----------------> Listanje filmova koje imamo
       cout<<"---------------------------------------------------------"<<endl;
         for(int i=0;i<TrenKorisnik.brojUzetihFilmova;i++)
            {
             cout<<"["<<i+1<<".]-"<<TrenKorisnik.Uzeti_filmovi[i]<<endl; //-------------> ovdje stoji i+1 da ne bi lista pocinjala za 0.
             cout<<"---------------------------------------------------------"<<endl;
            }
       cout<<"|KRAJ LISTE____________________________________KRAJ LISTE|\n"<<endl;

       cout<<"Koliko filmova zelite vratiti?(MAX:"<<TrenKorisnik.brojUzetihFilmova<<")"<<endl;
       cin>>KolFilmova;
         while(KolFilmova>TrenKorisnik.brojUzetihFilmova || KolFilmova<1) //------------> basic limitiranje broja. po mogucnosti uvesti zabranu upisa znakova i slova
              {
               cout<<"Unesena vrijednost nije valjana"<<endl;
               cout<<"Koliko filmova zelite vratiti?"<<endl;
               cin>>KolFilmova;
              }
          for (int i=0; i<KolFilmova; i++)                     //----------------> for petlja koja ce se ponoviti onoliko puta koliko filmova treba vratiti
              {
                cout<<"Unesite redni broj filma koji zelite vratiti"<<endl;
                cin>>RbFilma;
                 while(RbFilma<1 || (RbFilma-1)>TrenKorisnik.brojUzetihFilmova)
                      {
                       cout<<"Unesite valjan redni broj filma sa liste iznad."<<endl; //--------> isto kao i gore basic ogranicenja i treba uvesti zabranu unosa znakova i slova kasnije
                       cin>>RbFilma;
                      }
                 RbFilma--; //--------------------------------------->Smanjujem za jedan jer je u ispisu gore bilo povecano za 1 zbog estetike i sada ce korisnik unositi
                                                                    // te vrijednosti, medutim nama treba broj manje da bismo pristupili tom imenu sa liste filmova koje posjeduje
                                                                    // korisnik.
                 nazivFilma=TrenKorisnik.Uzeti_filmovi[RbFilma];    //-----> Vadimo ime filma iz liste preko indeksa koji nam je korisnik dao
                 TrenKorisnik.VratiFilm(nazivFilma); //-------------> brise film sa liste sa tim imenom i smanjuje broj uzetih filmova(pogeldaj funkciju "VratiFilm();" u Korisnik.cpp
                int redniBrFilma=0;                  //-------------> ovaj broj ce trebati kasnije kada budemo ocjenjivali film, da ne moramo opet pokretati for loop
                 for(int b=0; b<ListaFilmova.size();i++)
                    {
                     if(ListaFilmova[i].ImeFilma==nazivFilma) //-------> vadim redni broj filma na galvnoj listi i povecavam broj tog filma za 1 na glavnoj listi inventara
                       {                                               // pogeldati funkciju "povecajBroj_filmova(); u Film.cpp
                         ListaFilmova[i].povecajBroj_filmova();
                         redniBrFilma=i;
                       }
                    }



                 cout<<"\n Da li biste zeljeli ocjeniti film? (y/n)"<<endl; //---->Dajem korisniku izbor da li zeli oicjeniti film
                  char ch;
                   cin>>ch;
                   if (ch== 'n' || ch== 'N')
                                                    {
                                                     cout<<"Naravno, cijenimo Vasu iskrenost"<<endl;
                                                    }
                  if (ch== 'y' || ch== 'Y')
                                                     {
                                                     cout<<"Unesite ocjenu koju zelite dati ovom filmu(1-10)"<<endl;
                                                       int OcjFilma;
                                                       cin>>OcjFilma;
                                                       while(OcjFilma<1 || OcjFilma>10) //------>sve dok ocjena nije u redu korisnik je ovdje zaroblljen :D...zabraniti unos znakova i slova
                                                            {
                                                              cout<<"Zao nam je, ali ocjena filma moze biti izmedu 1(grozan film) i 10(Odlican film)"<<endl;
                                                              cin>>OcjFilma;
                                                            }
                                                        ListaFilmova[redniBrFilma].unosFOcjene(OcjFilma); //Na varijablu iz vektora "ListaFIlmova" na rednom broju [redniBrFilma] se pokrece
                                                     }                                                    //funkcija "unosFOsjene" i prosliujedjuje se int OcjFilma
              }                                                                                           //Pogledati "unosFOcjene();funkciju u Film.cpp
     }

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
              GlavniMeni(Film,Korisnik,TrenutniKorisnik,RBrTrenutniKorisnik);
            }
         else
            PreviseGresaka(); //-------------------------->Neka lijepa rijec prije nego terminiramo program zbog pogresnih pokusaja logovanja
      }

    else//------------------------------------------------->Ukoliko user izabere da se odmah loguje preskace se funkcija pravljenja korisnika.
    {
      if(LoginAuth(TrenutniKorisnik,Korisnik,RBrTrenutniKorisnik))
        {   DobrodosliNazad(TrenutniKorisnik);
            GlavniMeni(Film,Korisnik,TrenutniKorisnik,RBrTrenutniKorisnik);
        }
       else
         PreviseGresaka();
    }


}
