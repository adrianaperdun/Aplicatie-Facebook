#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

ifstream users("users.txt");

ifstream facebook("facebook.txt");

int n,a[101][101],m,nr;

char pers[101][20],pass[101][20];

void wrongoption();

int same()
{
    string x;
    string y;
    if(x == y)
        return 0;

}

void citire()
{
    int i,x,y;
    users >> n;
    for(i = 1; i <= n; i++)
        users >> pers[i] >> pass[i];
    facebook >> n;
    facebook >> m;
    for(i = 1; i <= m; i++)
        {
            facebook >> x >> y;
            a[x][y] = a[y][x] = 1;
        }
}

void cauta(char nume[],bool &gasit,bool &validat)
{
    int i;
    char parola[20];
    bool ok = false, okpass = false;
    for(i = 1; i <= n; i++)
        if(strcmp(pers[i],nume) == 0)
          {
              nr = i;
              ok = true;
              cout << "Introduceti parola?" << endl;
              cin >> parola;
              if(strcmp(pass[i],parola) == 0)
                okpass = true;
              else
                okpass = false;
          }
    if(ok == false)
    {
        cout << "Va rugam alegeti o parola: " << endl;
        cin >> pass[n+1];
        strcpy(pers[n+1],nume);
        n++;
        nr = n;
        if(same() == 0)
        {
            cout << "Parola trebuie sa fie diferita fata de nume. Alegeti alta parola. \n" << endl;
            cauta(nume, gasit, validat);
        }

    }
    gasit = ok;
    validat = okpass;
}

void persoane()
{
    int i;
    cout << "Urmatoarele persoane folosesc aplicatia: \n \n";
    for(i = 1; i <= n; i++)
      cout << pers[i] << " ";
      cout << '\n' << '\n';
}

void adauga(int nr)
{
    int i,j;
    char prieten[15];
    cout << "Ce prieteni vrei sa adaugi? \n";
    cin >> prieten;
    for(i = 1;i <= n; i++)
      if(strcmp(pers[i],prieten) == 0)
      {
          a[nr][i] = 1;
          a[i][nr] = 1;
      }
}

void sugestii(int nr)
{
   int i,j,z, r;
   bool ok = false;
   for(i = 1; i <= n; i++)
      if(a[i][nr] == 0 && i != nr)
      {
          r = 0;
          z = 0;
          for(j = 1; j <= n; j++)
            if(a[i][j] == 1 && a[nr][j] == 1)
                z++;
        if(z != 0)
              {cout << pers[i] << " ";
                ok = true;}
      }
      if(ok == false)
    while( a != 0)
        {cout << "Nu sunt sugestii disponibile." << endl;
        cout << "Pentru a putea vedea sugestiile trebuie sa aveti adaugat cel putin un prieten. \n" << endl;
        r--;
        }
     cout <<"\n \n \n";
}

void prieteni(int nr)
{

   int i, x = 1, y = 1;
   for(i = 1; i <= n; i++)
     if(a[i][nr] == 1 && i != nr)
      {
          while( y != 0)
          {
              cout << "Lista prietenilor este : \n" << endl;
              y--;
          }
          cout << pers[i] << " ";
          x = 0;
      }
      else
        while(x != 0)
        {
            cout << "Inca nu ati adaugat niciun prieten!" << endl;
            x--;
            y = 0;
        }
    cout <<"\n \n";
    x = 1;


}

void logout()
{
   int i,j, x = 1;
   ofstream f("users.txt");
   ofstream g("facebook.txt");
   f << n << endl;
   for(i = 1; i <= n; i++)
     f << pers[i] << " " << pass[i] << endl;
   g << n << " ";
   m = 0;
   for(i = 1; i <= n; i++)
     for(j = i; j <= n; j++)
        m = m + a[i][j];
   g << m << " ";
   for(i = 1; i <= n; i++)
     for(j = i; j <= n; j++)
       if(a[i][j] == 1)
         g << i << " " << j << endl;

}



void mesajeinceput()
{
    cout << "Pentru a va conecta, va rog sa introduceti urmatoarele date: " << endl;
    cout << "User?" << endl;
}

void mesajesfarsit()
{
    int x = 1;
    while(x != 0)
    {
        cout << "Va multumim ca ati folosit aplicatia noastra.";
        x--;
        break;
    }
    x = 0;


}

void meniu()
{
    int optiune;
    do
        {
        cout << "1.Lista persoanelor din aplicatie: \n";
        cout << "2.Lista sugestiilor de prietenie: \n";
        cout << "3.Lista prietenilor actuali: \n";
        cout << "4.Adaugarea unui prieten: \n";
        cout << "0.Logout: \n";
        cin >> optiune;
        switch(optiune)
        {
            case 1:
            {
                persoane();
                break;
            }
            case 2:
            {
                sugestii(nr);
                break;
            }
            case 3:
            {
                prieteni(nr);
                break;
            }

            case 4:
            {
                adauga(nr);
                break;
            }
            case 0:
            {
                logout();
                mesajesfarsit();
                break;
            }
            default :
              {wrongoption();
               break;
              }
        }
        }while(optiune != 0);

}


int main()
{
    char nume[100];
    bool gasit,validat;
    int optiune, k = 2;
    citire();
    mesajeinceput();
    cin >> nume;
    cauta(nume,gasit,validat);
    if(gasit && !validat)
    {
        cout << "Parola gresita,reincercati!";
        while(gasit && !validat && k!=0)
        {
            {
                cauta(nume, gasit, validat);
                k--;
            }
            if(k==0)
              cout<<"Ne pare rau, insa numarul de incercari a fost consumat. Va rugam incercati mai tarziu!"<<endl;}
    }
    else
    {
        meniu();
    }
    return 0;
}

void wrongoption()
{
    cout << "Nu exista aceasta optiune" << endl;
    meniu();
}

