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
void Dobrodosli();
void Pocetna_Stranica(vector<Korisnici>& users);             //Obzirom da pozivam funkciju pravljenja korisnika u ovoj funkciji moram i u nju proslijediti vektor
void PravljenjeKorisnika(vector<Korisnici>& users);          // Na ovu funkciju proslijeđujemo potpunu listu korisnika po referenci jer ce biti editovana ovdje
void Sekvenca_Gasenja();
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

cout<<"\n"<<"\n"<<"                                        PRITISNITE BILO KOJE DUGME DA BISTE NASTAVILI"<<endl;
cin.ignore();

system("CLS");


}
void Pocetna_Stranica(vector<Korisnici>& users)
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
    switch(Login_izbor)
    {
     /* case (1):
     {
            {if(LoginAuth()) TO-DO DODATI FUNKCIJU ZA AUTENTIKACIJU KORISNIKA I LOGIN
                           {
                             system("CLS");
                             cout<<"Dobrodošli nazad"<<endl;
                             cin.ignore();
                             nekadrugafunkcija();    TO-DO FUNKCIJA IZBORNOG MENIA
                           }
                else
                { cout<<"Žao nam je pogriješili ste previše puta :(""<<"\n"<<Kontaktirajte administratora."<<endl;
                   Sekvenca_Gasenja()       TO-DO FUNKCIJA KOJA CISTI OUTPUT I DISPLAYA SEKVENCU GASENJA
                }
            }
     }
     */
      case(2):
          PravljenjeKorisnika(users); //Pozivamo funkciju za pravljenje novog korisnika i proslijedjujemo joj vektor korisnika po referenci
     }



}
void PravljenjeKorisnika(vector<Korisnici>& users)
{
      string nickname;

                         /* TO-DO : završiti ovu funkciju tako sto kreiramo neki Korisnici NoviUser i onda pisemo users.push_back(NoviUser)
                          Vjerujem da postoji bolji nacin ali trenutno neka bude ovako, u vektor cemo unositi indefinite broj objekata "NoviUser"
                          ali ce se medusobro razlikovati po svojim zasebnim elementima username, ime i ostale stvari*/

                          //DOSTA ZA DANAS :3 22:22 26.05.2023

      system("CLS");
      cout<<"Zdravo, za pravljenje novog racuna bit ce potrebno da izaberete username: ";
      cin>>nickname;



               //nekadrugafunkcija();  TO-DO FUNKCIJA IZBORNOG MENIA

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
int main()
{
    vector<Korisnici> Korisnik;
    vector<Filmovi> Film;

     string command_window = "mode con: cols=132 lines=35"; //Odeđuje komandu koju je moguce mogificirati
     system(command_window.c_str());                    //Uzima parametre prethodno modificirane komande i oređuje velicinu terminal prozora


     Dobrodosli();
     Pocetna_Stranica(Korisnik);

}
