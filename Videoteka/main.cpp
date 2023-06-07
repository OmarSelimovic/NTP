#include <iostream> //Ova biblioteka omogućava unos i ispis podataka
#include <cstdlib> //Ova biblioteka sadrži nekoliko funkcija za manipulaciju s podacima.Npr. funkcija stoi pretvara string u cjelobrojni broj.
#include <limits> //Koristit cemo je za ogranicavanje određenih variajbli
#include <string> //Upotreba stringova i svih popratnih funkcija
#include <vector> //Upotreva vektora i svih popratnih funkcija
#include <stdlib.h>
#include <windows.h> //Ova biblioteka je specifična za Windows i koristimo ih za manipulacija prozorima
#include <algorithm> //Sadrži različite funkcije za obavljanje općih algoritama, kao što su sortiranje, pretraživanje, i manipulacija
#include <conio.h>  // Specificno za Windows, Koristit cu ga samo za getch();---> "pritisnite dugme da nastavite"
#include <fstream> // Ova biblioteka omogućava rad s datotekama. Sadrži klase i funkcije za unos i izlaz podataka iz datoteka.
#include <sstream> //Ova biblioteka sadrži klase i funkcije za rad s tekstualnim tokovima. Manipulacija s stringovima, konverzija između različitih tipova podataka i slično.
#include "Korisnik.h" //Lokalni header fajl za klasu/strukturu Korisnici
#include "Film.h" //Lokalni header fajl za klasu/strukturu Filmovi


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
void PokaziKorisnike(vector<Korisnici> ListaKorisnika); //------------------>Funkcija za listanje korisnika
void EditujKorisnike(vector<Korisnici>& ListaKorisnika); //------------->Funkcija za editovanje/brisanje i upozoravanje korisnika
void BrisanjeKorisnika(vector<Korisnici>& ListaKorisnika); //------------>Funkcija za pronalazenje i brisanje korisnika
void EditujFilmove(vector<Filmovi>& ListaFilmova); //------------------------>Funkcija za editovanje liste filmova
void BrisanjeFilma(vector<Filmovi>& ListaFilmova); //------------------------>Funkcija brisanja filma
void DodavanjeFilma(vector<Filmovi>& ListaFilmova); //-----------------------> Funkcija za dodavanje filmova
void SpremanjeKorisnika(vector<Korisnici>& ListaKorisnika, Korisnici TrenKorisnik, int RBrTrenKorisnik);//--->Samo ucitava trenutnog korisnika u vektor
void SpremanjeListeKorisnika(const vector<Korisnici>& ListaKorisnika, const string& imefajla);
void SpremanjeListeFilmova(const vector<Filmovi>& ListaFilmova, const string& imefajla);
vector<Korisnici> UcitavanjeKorisnika(const string& imefajla);
vector<Filmovi> UcitavanjeFilmova(const string& imefajla);
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
               cout<<"Nemate iznajmljenih filmova, vrijeme je da to promjenite ;)"<<endl;
                if(TrenutniKorisnik.brojUpozorenja!=0)
                   {
                    cout<<"\n\n\n-----_____Administrator vas je upozorio_____-----"<<endl;
                    cout<<"Poruka: '"<<TrenutniKorisnik.porukaUpoz<<"'."<<endl;
                    getch();
                    TrenutniKorisnik.brisanjePorukeUpoz();
                   }
               getch();
               return;
              }
           else
              {
               cout<<"Tenutno imate "<<TrenutniKorisnik.getBrUzFilmova()<<" uzetih filmova."<<endl;
               cout<<"A ti filmovi su:"<<endl;
               for(unsigned int i=0; i<TrenutniKorisnik.getBrUzFilmova();i++)//koristeci funkciju getBrUzFilmova i dodavanjem broja uzetih filmova u strukturu Korisnik sprejcujem potrebu(nastavlja se ispod)
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
    if(TrenKorisnik.Admin==false)
    {
         int Uizbor=0;
      while(Uizbor!=4)
      {
         system("CLS");
         cout << "   Izaberite jednu od opcija:" << endl;
         cout << "|-------------------------------|" << endl;
         cout << "|[1]-Zelim vidjeti izbor filmova|" << endl;
         cout << "|[2]-Zelim naruciti film        |" << endl;
         cout << "|[3]-Zelim vratiti film/ove     |" << endl;
         cout << "|[4]-EXIT                       |" << endl;
         cout << "|-------------------------------|" << endl;

         while (!(cin >> Uizbor) || (Uizbor <1) || (Uizbor>4))  //unos Login_izbora i provjera da li je jedna od valjanih vrijednosti
             {
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Dozvoljava samo unos borjeva
              cout << "Molimo unesite valjan izbor :" << endl;
             }
             if(Uizbor==1) PokaziFilmove(ListaFilmova);

        else if(Uizbor==2) NarucivanjeFilmova(ListaFilmova, TrenKorisnik);

        else if(Uizbor==3) VracanjeFilmova(ListaFilmova, TrenKorisnik);

        else if(Uizbor==4){
                           cout<<"Zelite li spremiti promjene? (y/n)"<<endl;
                           char ch;
                           cin>>ch;
                                 if(ch== 'y' || ch=='Y')
                                   {
                                    SpremanjeKorisnika(ListaKorisnika,TrenKorisnik,RBRTrenKor);
                                    string Fajl1, Fajl2;
                                    Fajl1="Korisnici.csv";
                                    Fajl2="Filmovi.csv";
                                    SpremanjeListeKorisnika(ListaKorisnika,Fajl1);
                                    SpremanjeListeFilmova(ListaFilmova,Fajl2);
                                   }
                            else if(ch== 'n' || ch =='N')
                                   {
                                    cout<<"Promjene nece biti spremljene"<<endl;
                                   }
                            Sekvenca_Gasenja();
                          }
      }
    }
    else
    {
        int Aizbor=0;
        while(Aizbor!=5)
      {
         system("CLS");
         cout << "    Administratorske opcije:" << endl;
         cout << "|-------------------------------|" << endl;
         cout << "|[1]-Lista filmova              |" << endl;
         cout << "|[2]-Izmjena liste filmova      |" << endl;
         cout << "|[3]-Lista korisnika            |" << endl;
         cout << "|[4]-Izmjena liste korisnika    |" << endl;
         cout << "|[5]-EXIT                       |" << endl;
         cout << "|-------------------------------|" << endl;

         while (!(cin >> Aizbor) || (Aizbor <1) || (Aizbor>5))  //unos Login_izbora i provjera da li je jedna od valjanih vrijednosti
             {
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Dozvoljava samo unos borjeva
              cout << "Molimo unesite valjan izbor :" << endl;
             }
             if(Aizbor==1) PokaziFilmove(ListaFilmova);

        else if(Aizbor==2) EditujFilmove(ListaFilmova);

        else if(Aizbor==3) PokaziKorisnike(ListaKorisnika);

        else if(Aizbor==4) EditujKorisnike(ListaKorisnika);

        else if(Aizbor==5){
                           cout<<"Zelite li spremiti promjene? (y/n)"<<endl;
                           char ch;
                           cin>>ch;
                                 if(ch== 'y' || ch=='Y')
                                   {
                                    SpremanjeKorisnika(ListaKorisnika,TrenKorisnik,RBRTrenKor);
                                    string Fajl1, Fajl2;
                                    Fajl1="Korisnici.csv";
                                    Fajl2="Filmovi.csv";
                                    SpremanjeListeKorisnika(ListaKorisnika,Fajl1);
                                    SpremanjeListeFilmova(ListaFilmova,Fajl2);
                                   }
                            else if(ch== 'n' || ch =='N')
                                   {
                                    cout<<"Promjene nece biti spremljene"<<endl;
                                   }
                            Sekvenca_Gasenja();
                          }
      }
    }
}
vector<Korisnici> UcitavanjeKorisnika(const string& imefajla)
{
 vector<Korisnici> korisnici;
    ifstream file(imefajla);
    if (file.is_open())
        {
        string linija;
        while (getline(file, linija))
              {
               stringstream ss(linija);
               string predmet;
               Korisnici korisnik;

               getline(ss, predmet, '$');
               korisnik.Nadimak=predmet;

               getline(ss, predmet, '$');
               korisnik.Ime=predmet;

               getline(ss, predmet, '$');
               korisnik.LoginSifra=predmet;

               getline(ss, predmet, '$');
               korisnik.brojUzetihFilmova=stoi(predmet);

               getline(ss, predmet, '$');
               korisnik.upozorenje=(predmet=="1");

               getline(ss, predmet, '$');
               korisnik.porukaUpoz=predmet;

               getline(ss, predmet, '$');
               korisnik.brojUpozorenja=stoi(predmet); //stoi----> funkcija iz include <string> koja pretvara string u integer

               getline(ss, predmet, '$');
               korisnik.Admin=(predmet=="1");

               getline(ss, predmet, '$');
               unsigned int numUzetiFilmovi=stoi(predmet);

            for (unsigned int i=0;i<numUzetiFilmovi;++i)
                {
                getline(ss, predmet, '$');
                korisnik.Uzeti_filmovi.push_back(predmet);
                }
            korisnici.push_back(korisnik);
        }
        file.close();
    }
else
    {
     cerr<<"Greska pri otvaranju "<<imefajla<< endl;
    }
    return korisnici;
}
vector<Filmovi> UcitavanjeFilmova(const string& imefajla)
{
  vector<Filmovi> filmovi;
  ifstream file(imefajla);
    if (file.is_open())
        {
          string linija;
          while (getline(file, linija))
          {
          stringstream ss(linija);
          string predmet;
          Filmovi film;

          getline(ss, predmet, '$');
          film.ImeFilma=predmet;

          getline(ss, predmet, '$');
          film.ZanrFilma=predmet;

          getline(ss, predmet, '$');
          film.Broj_filmova=stoi(predmet);

          getline(ss, predmet, '$');
          unsigned int numOcjeneFIlma=stoi(predmet);

          for (unsigned int i=0;i<numOcjeneFIlma;++i)
              {
              getline(ss, predmet, '$');
              film.OcjeneFilma.push_back(stoi(predmet));
              }

            filmovi.push_back(film);
          }
        file.close();
    } else {
        cerr<<"Greska pri otvaranju " <<imefajla<< endl;
    }
    return filmovi;
}
void SpremanjeListeFilmova(const vector<Filmovi>& ListaFilmova, const string& imefajla)
{
  system("CLS");
  ofstream file(imefajla);
    if (file.is_open())
       {
        for (const auto& film : ListaFilmova) //--------> ovo "auto" znaci da compiler automatski oređuje tip varijable
            {
             file << film.ImeFilma << "$"     //--------> kao denominator sam izabrao znak $ (Dollar separated values :3)
                  << film.ZanrFilma << "$"
                  << film.Broj_filmova << "$"
                  << film.OcjeneFilma.size();
              for (const auto& ocjena : film.OcjeneFilma)
                  {
                   file << "$" << ocjena;
                  }
             file << endl;
            }
        file.close();
     }
   else
     {
      cerr<<"Greska pri otvaranju " <<imefajla<<endl;
     }
}
void SpremanjeListeKorisnika(const vector<Korisnici>& ListaKorisnika, const string& imefajla)
{
 system("CLS");
 ofstream file(imefajla);
 if (file.is_open())
    {
     for (const Korisnici& korisnik : ListaKorisnika)
         {
          file<<korisnik.Nadimak<<"$"
              <<korisnik.Ime<<"$"
              <<korisnik.LoginSifra<<"$"
              <<korisnik.brojUzetihFilmova<<"$"
              <<(korisnik.upozorenje ? "1":"0")<<"$"
              <<korisnik.porukaUpoz<<"$"
              <<korisnik.brojUpozorenja<<"$"
              <<(korisnik.Admin ? "1" : "0")<<"$"
              <<korisnik.Uzeti_filmovi.size();
           for(const string& film : korisnik.Uzeti_filmovi)
              {
               file<<"$"<<film;
              }
           file<<endl;
         }
     file.close();
    }
 else
    {
      cerr<<"Greska pri otvaranju "<<imefajla<<endl;
    }

}
void SpremanjeKorisnika(vector<Korisnici>& ListaKorisnika,const Korisnici TrenKorisnik, int RBrTrenKorisnik)
{
  ListaKorisnika[RBrTrenKorisnik]=TrenKorisnik;
}
void EditujKorisnike(vector<Korisnici>& ListaKorisnika)
{

  int Aizbor4=0;
  while(Aizbor4!=5)
      {  system("CLS");
         PokaziKorisnike(ListaKorisnika);
         cout << "      Editovanje Korisnika:      " << endl;
         cout << "|-------------------------------|" << endl;
         cout << "|[1]-Upozori korisnika          |" << endl;
         cout << "|[2]-Resetuj upozorenja         |" << endl;
         cout << "|[3]-Obrisi korisnika           |" << endl;
         cout << "|[4]-Napravi admin-korisnika    |" << endl;
         cout << "|[5]-<----NAZAD<----            |" << endl;
         cout << "|-------------------------------|" << endl;

         while (!(cin >> Aizbor4) || (Aizbor4 <1) || (Aizbor4>5))  //unos Login_izbora i provjera da li je jedna od valjanih vrijednosti
             {
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Dozvoljava samo unos borjeva
              cout << "Molimo unesite valjan izbor :" << endl;
             }
             if(Aizbor4==1) {
                              cout<<"\n\nUnesite redni broj korisnika kojeg zelite upozoriti:";
                              int rednibroj=0;
                              cin>>rednibroj;
                                 while(rednibroj>ListaKorisnika.size() || rednibroj<1)
                                      {
                                       cout<<"\nDoslo je do greske, unesite valjan redni broj korisnika:";
                                       cin>>rednibroj;
                                      }
                              rednibroj--;
                              if (ListaKorisnika[rednibroj].brojUpozorenja==3)
                                 {
                                  cout<<"\nKorisnik vec ima 3 upozorenja."<<endl;
                                 }
                              else
                                 {
                                  cout<<"\nJeste li sigurni da zelite upozoriti korinsika -"<<ListaKorisnika[rednibroj].Ime<<"- (y/n)?"<<endl;
                                  char ch;
                                  cin>>ch;
                                       if (ch== 'n' || ch== 'N')
                                          {
                                           cout<<"Upozoravanje korisnika ponisteno"<<endl;
                                           getch();
                                           system("CLS");
                                          }
                                       if (ch== 'y' || ch== 'Y')
                                          {
                                           string porUpoz;
                                           cout<<"Unesite poruku upozorenja:"<<endl;
                                           cin.ignore();
                                           getline(cin,porUpoz);
                                           ListaKorisnika[rednibroj].povecaj_brUpozorenja();
                                           ListaKorisnika[rednibroj].unosPorukeUpoz(porUpoz);
                                           cout<<"Upozorenje zabiljezeno"<<endl;
                                           getch();
                                           system("CLS");
                                          }
                                 }
                            }
        else if(Aizbor4==2) {
                             cout<<"\n\nUnesite redni broj korisnika cija upozorenja brisete"<<endl;
                              int rednibroj=0;
                              cin>>rednibroj;
                                 while(rednibroj>ListaKorisnika.size() || rednibroj<1)
                                      {
                                       cout<<"Doslo je do greske, unesite valjan redni broj korisnika"<<endl;
                                       cin>>rednibroj;
                                      }
                              rednibroj--;
                              ListaKorisnika[rednibroj].ocistiUpozorenja();
                              ListaKorisnika[rednibroj].brisanjePorukeUpoz();
                              cout<<"\n\nUpozorenja obrisana."<<endl;
                              getch();
                              system("CLS");
                            }
        else if(Aizbor4==3) BrisanjeKorisnika(ListaKorisnika);
        else if(Aizbor4==4) {
                              cout<<"\n\nUnesite redni broj korisnika kojeg zelite uciniti administratorom."<<endl;
                              int rednibroj=0;
                              cin>>rednibroj;
                                 while(rednibroj>ListaKorisnika.size() || rednibroj<1)
                                      {
                                       cout<<"Doslo je do greske, unesite valjan redni broj korisnika"<<endl;
                                       cin>>rednibroj;
                                      }
                              rednibroj--;
                              if(ListaKorisnika[rednibroj].Admin==true)
                                {
                                 cout<<"Korisnik je vec administrator."<<endl;
                                }
                            else
                                {
                                 ListaKorisnika[rednibroj].Admin=true;         //--------> ovo pretstavlja sigurnosnu prijetnju jer ko pristupi admin racunu moze svoj racun uciniti
                                                                               //da bude admin racun i eventualno cak obrisati ostale administratorske racune ali za ovu upotrebu se
                                                                               // moze "progledati kroz prste". Neka od solucija je trazenje 2FA za svaku akciju brisanja usera i pravljenja
                                                                               // administratora.
                                 cout<<"Korisnik je sada Administrator"<<endl;
                                }
                            }
        else if(Aizbor4==5) return;

      }
}
void BrisanjeKorisnika(vector<Korisnici>& ListaKorisnika)
{
 cout<<"!!UPOZORENJE!! Brisanje korisnika ce obrisati sve informacije o njima"<<endl;
 cout<<"Ova promjena je stalna i prije upotrebe je potrebno utvrditi da je korisnik vratio sve filmove\n\n\n"<<endl;
 cout<<"Jeste li sigurni da zelite nastaviti?(y/n)"<<endl;
     char ch;
     cin>>ch;
     if (ch== 'n' || ch== 'N')
        {
        cout<<"Brisanje ponisteno."<<endl;
        getch();
        return;
        }
else if (ch== 'y' || ch== 'Y')
        {
         cout<<"Unesite redni broj korisnika kojeg brisete."<<endl;
         int rednibroj=0;
         cin>>rednibroj;
         while(rednibroj>ListaKorisnika.size() || rednibroj<1)
              {
               cout<<"Doslo je do greske, unesite valjan redni broj korisnika"<<endl;
               cin>>rednibroj;
              }
         rednibroj--;
         ListaKorisnika.erase(ListaKorisnika.begin()+ rednibroj);
         cout<<"Korisnik uspjesno obrisan."<<endl;
         getch();
         return;
        }

}
void EditujFilmove(vector<Filmovi>& ListaFilmova)
{
 system("CLS");
  int Aizbor2=0;
  while(Aizbor2!=5)
      {  PokaziFilmove(ListaFilmova);
         cout << "       Editovanje Filmova:       " << endl;
         cout << "|-------------------------------|" << endl;
         cout << "|[1]-Izbrisi film               |" << endl;
         cout << "|[2]-Dodaj novi film            |" << endl;
         cout << "|[3]-Povecaj broj filmova       |" << endl;
         cout << "|[4]-Smanji broj filmova        |" << endl;
         cout << "|[5]-<----NAZAD<----            |" << endl;
         cout << "|-------------------------------|" << endl;

         while (!(cin >> Aizbor2) || (Aizbor2 <1) || (Aizbor2>5))  //unos Login_izbora i provjera da li je jedna od valjanih vrijednosti
             {
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Dozvoljava samo unos borjeva
              cout << "Molimo unesite valjan izbor :" << endl;
             }
            if(Aizbor2==1) BrisanjeFilma(ListaFilmova);

       else if(Aizbor2==2) DodavanjeFilma(ListaFilmova);

       else if(Aizbor2==3) {
                            cout<<"Redni broj filma kojeg zelite dodati u skladiste: ";
                            int broj ;
                            cin>>broj;
                           while(broj>ListaFilmova.size() || broj<1)
                                   {
                                    cout<<"\nTog rednog broja nema na listi, pogledajte listu iznad i pokusajte ponovo."<<endl;
                                    cin>>broj;
                                   }
                            broj--;
                            cout<<"Koliko kopija filma "<<ListaFilmova[broj].ImeFilma<<" zelite dodati? :";
                            int cifra;
                            cin>>cifra;
                             for(int i=0;i<cifra;i++)
                                {
                                 ListaFilmova[broj].povecajBroj_filmova();
                                }
                           }

       else if(Aizbor2==4) {
                            cout<<"Redni broj filma kojem zelite smanjiti kolicine u skladistu: ";
                            int broj ;
                            cin>>broj;
                           while(broj>ListaFilmova.size() || broj<1)
                                   {
                                    cout<<"\nTog rednog broja nema na listi, pogledajte listu iznad i pokusajte ponovo: ";
                                    cin>>broj;
                                   }
                            broj--;
                            cout<<"\nKoliko kopija filma "<<ListaFilmova[broj].ImeFilma<<" zelite oduzeti? :";
                            int cifra;
                            cin>>cifra;
                             while(cifra>ListaFilmova[broj].Broj_filmova || cifra<1)
                                   {
                                    cout<<"\nDoslo je do greske, unesite validnu cifru."<<endl;
                                    cin>>cifra;
                                   }
                             for(int i=0;i<cifra;i++)
                                {
                                 ListaFilmova[broj].smanjBroj_filmova();
                                }
                           }

       else if(Aizbor2==5) return;

      }
}
void DodavanjeFilma(vector<Filmovi>& ListaFilmova)
{
   system("CLS");
   string imeNfilm, zanrNfilm;
   unsigned int brojNfilma;
   Filmovi NoviFilm;
   cout<<"Skladistar: 'Uredu, za dodavanje novog filma trebat ce mi njegovo ime, zenr i kolicina.'"<<endl;
   cout<<"Skladistar: 'Molim Vas pazljivo unosite informacije zbog papirologije :D '"<<endl;
   cout<<"\nIme:";
   cin.ignore();
   getline(cin,imeNfilm);
   cout<<"\nZanr filma(npr.'Akcija/Komedija':";
   cin>>zanrNfilm;
   cout<<"\nKoliko ih ima:";
   cin>>brojNfilma;
   NoviFilm.unosFIme(imeNfilm);
   NoviFilm.unosFZanr(zanrNfilm);
   NoviFilm.Broj_filmova=brojNfilma;
   ListaFilmova.push_back(NoviFilm);
   Sleep(800);
   system("CLS");
   cout<<"Film spremljen!"<<endl;
   getch();
   return;
}
void BrisanjeFilma(vector<Filmovi>& ListaFilmova)
{
 cout<<"_________---------______------_________!!PAZNJA!!_________---------______------_________"<<endl;
 cout<<"Prije brisanja filma, provjerite da li neki od korisnika trenutno ima taj film kod sebe."<<endl;
 cout<<"\n\n\n Jeste li sigurni da zelite nastaviti? (y/n)"<<endl;
 char ch;
 cin>>ch;
 if(ch== 'y' || ch=='Y')
    {
     cout<<"Unesite redni broj filma kojeg zelite obrisati"<<endl;
     int redniBroj=0;
     cin>>redniBroj;
     redniBroj--;
     cout<<"Jeste li sigurni da zelite obrisati film '"<<ListaFilmova[redniBroj].ImeFilma<<"' ?(y/n)"<<endl;
     char potvrda;
     cin>>potvrda;
     if(potvrda== 'y' || potvrda=='Y')
        {
         ListaFilmova.erase(ListaFilmova.begin() + redniBroj);
         cout<<"Film obrisan uspjesno"<<endl;
         getch();
        }
     else if(potvrda== 'n' || potvrda=='N')
        {
         cout<<"Brisanje filma ponisteno"<<endl;
         getch();
        }
     }
else if(ch== 'n' || ch=='N')
     {
      cout<<"Brisanje filma ponisteno"<<endl;
      getch();
     }
 return;
}
void PokaziFilmove(vector<Filmovi> ListaFilmova)//-------> Ispisuje potpunu listu filmova korisniku na prozor
{
    system("CLS");
    Filmovi buffer; //------------> Nisam siguran ali mislim da ako ovo uvedem, da cu olaksati programu da ne mora svaki put listati sav vektor
    cout<<"Lista filmova:"<<endl;
    for(int i=0;i<ListaFilmova.size();i++)
        {
            buffer=ListaFilmova[i];
            cout<<"---------------------------------------------------------"<<endl;
            cout<<"["<<i+1<<"] Ime - "<<buffer.ImeFilma<<endl;
            cout<<"Zanr filma - "<<buffer.ZanrFilma<<endl;
            if(buffer.fOcjena()==0)
            cout<<"Film jos nije ocijenjen."<<endl;
            else
            cout<<"Ocjena filma - "<<buffer.fOcjena()<<endl;
            if(buffer.Broj_filmova==0)
            cout<<"Nazalost, ovog filma nemamo na stanju."<<endl;
            else
            cout<<"Ovih filmova na stanju imamo: "<<buffer.FBroj_filmova()<<endl;
            cout<<"---------------------------------------------------------\n"<<endl;
            Sleep(200);

        }
    cout<<"|KRAJ LISTE____________________________________KRAJ LISTE|"<<endl;
     getch();
}
void PokaziKorisnike(vector<Korisnici> ListaKorisnika) //-----> Ispisuje potpunu listu korisnika
{
  system("CLS");
  Korisnici buffer;
    cout<<"Lista korisnika:"<<endl;
    for(int i=0;i<ListaKorisnika.size();i++)
        {   buffer=ListaKorisnika[i];
            cout<<"---------------------------------------------------------"<<endl;
            cout<<"["<<i+1<<"]-"<<buffer.Nadimak<<endl;
            cout<<"Ime i Prezime: "<<buffer.Ime<<endl;
            if(buffer.Admin==true)
                cout<<"Korisnik ima Administratorske ovlasti."<<endl;
       else
         {     cout<<"Broj upozorenja:"<<buffer.brojUpozorenja<<endl;
            if(buffer.brojUzetihFilmova==0)
               cout<<"Korisnik nema uzetih filmova."<<endl;
            else{
                 cout<<"Broj uzetih filmova:"<<buffer.brojUzetihFilmova<<endl;
                 cout<<"Lista uzetih filmova:"<<endl;
                 for(unsigned int b=0;b<buffer.brojUzetihFilmova;b++)
                     {
                      cout<<"["<<b+1<<".]-"<<buffer.Uzeti_filmovi[b]<<endl;
                     }
                }
         }
            cout<<"---------------------------------------------------------"<<endl;
            Sleep(200);

        }
    cout<<"|KRAJ LISTE____________________________________KRAJ LISTE|"<<endl;
     getch();
}
void NarucivanjeFilmova(vector<Filmovi>& ListaFilmova,Korisnici& TrenKorisnik)
{
  system("CLS");
  if(TrenKorisnik.brojUzetihFilmova>5)
     {
      cout<<"Zao nam je ali vec imate 6 filmova kod sebe, sto je dozvoljeni maksimum."<<endl;
      cout<<"Da biste uzeli nove filmove, morat cete prvo vratiti neke od prethodno uzetih filmova."<<endl;
      getch();
      cout<<"\n \n Bit cete vraceni na glavni meni"<<endl;
      Sleep(1000);
      return;
      }
         int KolFilmova=0, RBrFilma=0;
         PokaziFilmove(ListaFilmova);
                        cout<<"Koliko filmova zelite iznajmiti? (Od 1 do 3)"<<endl;
                        cin>>KolFilmova;
                        while(KolFilmova>3 || KolFilmova<1 || KolFilmova==0)
                                            {
                                             if(KolFilmova==0)
                                                             {
                                                               cout<<"\nDa li vi uopste zelite iznajmiti film (y/n)?"<<endl;
                                                               char g;
                                                               cin>>g;
                                                               if (g== 'n' || g== 'N')
                                                                            {
                                                                              cout<<"\nZao nam je sto ste se predomislili"<<endl;
                                                                              cout<<"Bit cete vraceni na glavni meni"<<endl;
                                                                              getch();
                                                                              return;
                                                                            }
                                                               if (g== 'y' || g== 'Y')
                                                                            {
                                                                             cout<<"\nKoliko filmova zelite iznajmiti? (Od 1 do 3)"<<endl;
                                                                             cin>>KolFilmova;
                                                                            }
                                                             }
                                             if (KolFilmova<1)
                                                             {
                                                                  cout<<"\nNe mozete iznajmiti manje od jednog filma"<<endl;
                                                                  cout<<"Koliko filmova zelite iznajmiti? (Od 1 do 3)"<<endl;
                                                                  cin>>KolFilmova;
                                                             }

                                             if(KolFilmova>3)
                                                             {
                                                              cout<<"\nNe mozete iznajmiti vise od 3 filma odjendom"<<endl;
                                                              cout<<"Koliko filmova zelite iznajmiti? (Od 1 do 3)"<<endl;
                                                              cin>>KolFilmova;
                                                             }
                                              }
                 for(int i=0;i<KolFilmova;i++)
                    {
                      if(ListaFilmova.size()==0)
                        {
                         cout<<"Izvinjavamo se ali nema vise filova koje mozete iznajmiti"<<endl;
                         cout<<"Bit cete vraceni na glavni meni"<<endl;
                         getch();
                         return;
                        }
                      cout<<"Unesite redni broj filma koji zelite"<<endl;
                      cin>>RBrFilma;
                      while (RBrFilma>ListaFilmova.size() || RBrFilma<1)
                            {
                             cout<<"Film tog rednog broja nije na listi :)"<<endl;
                             cout<<"Izaberite valjan film"<<endl;
                             cin>>RBrFilma;
                            }
                      while (ListaFilmova[RBrFilma-1].Broj_filmova==0) //-------> provjeravanje inteligencije korisnika jer zeli film za koji pise da ga nema na stanju
                            {                                        /*-------> Ovja mali test biranja filma utvrđuje da redni broj koji korisnik unosi ne moze
                                                                                oznacavati neki film kojeg nema na stanju. Taj broj ne moze biti veci od maksimalnog
                                                                                broja sa liste niti manji od najmanjeg broja sa liste*/

                              cout<<"Vec smo naglasili da tog filma nemamo na stanju"<<endl;
                              cout<<"Da li zelite neki drugi film? (y/n)"<<endl;
                                   char drfilm='y';
                                   cin>> drfilm;
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

                                  while (RBrFilma>ListaFilmova.size() || RBrFilma<0)
                                         {
                                          cout<<"Film tog rednog broja nije na listi :)"<<endl;
                                          cout<<"Izaberite valjan film"<<endl;
                                          cin>>RBrFilma;
                                         }
                            }
                        RBrFilma--;
                       TrenKorisnik.UzmiFilm(ListaFilmova[RBrFilma].ImeFilma);     //------>U vektor filmova koji su kod korisnika push_backa ime filma koji je korisnik uzeo
                                                                              //------> Tek sada shvatam da je bilo bolje da struktura Korisnici umjesto vector<string> ListaFilmova
                                                                                       // ima vector<Filmovi> ListaFilmova, međutim previse je kasno mijenjati kod a benefiti su mali
                       ListaFilmova[RBrFilma].smanjBroj_filmova(); //-------------------->Smanjuje broj filmova u inventoriju za film koji je uzeo korisnik
                       cout<<"Uzivajte u gledanju filma ^_^ "<<endl;
                       getch();
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
             cout<<"["<<i+1<<"]-"<<TrenKorisnik.Uzeti_filmovi[i]<<endl; //-------------> ovdje stoji i+1 da ne bi lista pocinjala za 0.
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
                 while(RbFilma<1 || RbFilma>TrenKorisnik.brojUzetihFilmova)
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
                 for(int b=0; b<ListaFilmova.size();b++)
                    {
                     if(ListaFilmova[b].ImeFilma==nazivFilma) //-------> vadim redni broj filma na galvnoj listi i povecavam broj tog filma za 1 na glavnoj listi inventara
                       {                                               // pogeldati funkciju "povecajBroj_filmova(); u Film.cpp
                         ListaFilmova[b].povecajBroj_filmova();
                         redniBrFilma=b;
                       }
                    }



                 cout<<"\nDa li biste zeljeli ocjeniti film? (y/n)"<<endl; //---->Dajem korisniku izbor da li zeli oicjeniti film
                  char ch;
                   cin>>ch;
                   if (ch== 'n' || ch== 'N')
                                                    {
                                                     cout<<"Naravno, cijenimo Vasu iskrenost"<<endl;
                                                     getch();
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
                                                        cout<<"Hvala Vam za doprinos"<<endl;              //funkcija "unosFOsjene" i prosliujedjuje se int OcjFilma
                                                        getch();                                          //Pogledati "unosFOcjene();funkciju u Film.cpp
                                                    }
              }
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
    Korisnici InicijalniAdmin, InicijalniUser;//------------------------>Inicijalni admin/user
    int RBrTrenutniKorisnik;/*-------------------------->Redni broj trenutnog korisnika (Ovo ce olaksati da kasnije kada ga budemo
                                                        unosili nazad u sistem da ga ne moramo traziti na kojem je mjestu u vektoru).*/
    Korisnik = UcitavanjeKorisnika("Korisnici.csv");
    Film = UcitavanjeFilmova("Filmovi.csv");
    if(Korisnik.size()==0)
      {
       InicijalniAdmin.Admin=true;
       InicijalniAdmin.Ime="Inicijalni Administrator";
       InicijalniAdmin.Nadimak="Admin";
       InicijalniAdmin.LoginSifra="Admin";
       Korisnik.push_back(InicijalniAdmin);
       InicijalniUser.Admin=false;                //-------> Populiranje liste korisnika sa inicijalnim vrijednostima za pocetak koristenja programa i testiranje
       InicijalniUser.Ime="Inicijalni Korisnik";
       InicijalniUser.Nadimak="User";
       InicijalniUser.LoginSifra="User";
       Korisnik.push_back(InicijalniUser);
      }



     string command_window = "mode con: cols=132 lines=380"; //Odeđuje komandu koju je moguce mogificirati
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
