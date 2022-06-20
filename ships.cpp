#include <iostream>
#include <cstdlib>
#include <time.h>
#include <curses.h>
#include <stddef.h>
#include <random>
#include <thread>
#include <chrono>

using namespace std;

int sprawdz_puste_pola_h(int n, int v, int h, char plansza[11][11], int licznik)
{
    licznik = 0;
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<(n+2); j++)
        {
            if(plansza[v-1+i][h-1+j] != 'O')
            {
                licznik++;
            }
        }
    }

    return licznik; //dla n=1 licznik=9, dla n=2 licznik=12, dla n=3 licznik=15, dla n=4 licznik=18
}

int sprawdz_puste_pola_v(int n, int v, int h, char plansza[11][11], int licznik)
{
    licznik = 0;
    for(int i=0; i<(n+2); i++)
    {
        for(int j=0; j<3; j++)
        {
            if(plansza[v-1+i][h-1+j] != 'O')
            {
                licznik++;
            }
        }
    }

    return licznik; //dla n=1 licznik=9, dla n=2 licznik=12, dla n=3 licznik=15, dla n=4 licznik=18
}

int sprawdz_wynik(int v, int h, char plansza[11][11], int licznik)
{
    licznik = 0;
    for (int i=1; i<11; i++)
    {
        for (int j=1; j<11; j++)
        {
            if(plansza[i][j] == 'X')
            {
                licznik++;
            }
        }
    }
    return licznik;//jeżeli licznik=20 przeciwnik wygrywa bitwę
}

void czekaj(int iMilisekundy)
{
    clock_t koniec = clock() + iMilisekundy * CLOCKS_PER_SEC / 1000.0;
    while( clock() < koniec ) continue;
}

void wyczysc_ekran()
{
    system("clear");
}

void rysowanie_komp_n(int n, int v, int h, int wybor, char plansza_2[11][11], int licznik, int a)
{
       
        if(n==2){a=12;}
        else if(n==3){a=15;}
        else if(n==4){a=18;}
      
for (int i=1; i<=(5-n); i++)
{
        punkt_1:
        int const low=0, high=1, m=1;
        random_device rd;
        uniform_int_distribution<int> dist(low,high);
        mt19937 generator(rd());
        wybor = dist(generator);  // 0 - pionowo, 1 - poziomo
    if (wybor == 1)
    {   
        int const lowv=1, highv=10, mv=1;
        random_device rdv;
        uniform_int_distribution<int> distv(lowv,highv);
        mt19937 generatorv(rdv());
        v = distv(generatorv); 
   
        int const lowh=1, highh=(10-n), mh=1;
        random_device rdh;
        uniform_int_distribution<int> disth(lowh,highh);
        mt19937 generatorh(rdh());
        h = disth(generatorh);
    }
    else if (wybor == 0)
    {
        int const lowv=1, highv=(10-n), mv=1;
        random_device rdv;
        uniform_int_distribution<int> distv(lowv,highv);
        mt19937 generatorv(rdv());
        v = distv(generatorv); 
   
        int const lowh=1, highh=10, mh=1;
        random_device rdh;
        uniform_int_distribution<int> disth(lowh,highh);
        mt19937 generatorh(rdh());
        h = disth(generatorh);
    }   

if (wybor == 0) //v - vertical (pionowo)
    {
        if (sprawdz_puste_pola_v(n, v, h, plansza_2, licznik) == a)
        {
            for(int i=0; i<n; i++)
                {        
                 plansza_2[v+i][h] = 'O';
                }    
        }
        else
        {
            goto punkt_1;
        } 
    }   

else if (wybor == 1) //h - horizontal (poziomo)
    {
        if (sprawdz_puste_pola_h(n, v, h, plansza_2, licznik) == a )
        {
            for(int i=0; i<n; i++)
                {        
                 plansza_2[v][h+i] = 'O';
                }   
        }
        else
        {
            goto punkt_1;
        } 
    }
       system("clear"); //nie będzie czyścić ekranu po wstawaniu nowych statków;
}  
       /* for (int i=0; i<11; i++) //rysowanie statków konputera - finalnie ta opcja musi być wyłączona aby gracz nie widział planszy przeciwnika
        {
            for (int j=0; j<11; j++)
            {
                cout << plansza_2[i][j] << " ";
            }
        cout << endl;
        }*/
}

void rysowanie_komp_1(int n, int v, int h, int wybor, char plansza_2[11][11], int licznik)
{
    
for (int i=1; i<=(5-n); i++)
   {
    punkt:
        int const lowv=1, highv=10, mv=1;
        random_device rdv;
        uniform_int_distribution<int> distv(lowv,highv);
        mt19937 generatorv(rdv());
        v = distv(generatorv); 
   
        int const lowh=1, highh=(10), mh=1;
        random_device rdh;
        uniform_int_distribution<int> disth(lowh,highh);
        mt19937 generatorh(rdh());
        h = disth(generatorh);
        do
        {
        for(int i=0; i<n; i++)
        {
           
            if (sprawdz_puste_pola_h(n, v, h, plansza_2, licznik) >= 9)
            {
            plansza_2[v+i][h] = 'O';
            }
            else if (sprawdz_puste_pola_h(n, v, h, plansza_2, licznik) < 9)
            {
                goto punkt;
            }
        }
        }while (v>(11-n) and v<0 and h>(11-n) and h<0);     
            
        system("clear"); //nie będzie czyścić ekranu po wstawaniu nowych statków;
    
        /*for (int i=0; i<11; i++) //rysowanie statków konputera - finalnie ta opcja musi być wyłączona aby gracz nie widział planszy przeciwnika
        {
            for (int j=0; j<11; j++)
            {
                cout << plansza_2[i][j] << " ";
            }
        cout << endl;
        }*/
   }

}

void rysowanie_1(int n, int v, int h, char wybor, char plansza_1[11][11], int licznik)
{
    for (int i=1; i<=(5-n); i++)
    {
        wprowadzenie:
        cout << endl << "Ustaw swój " << n << " masztowiec " << "(" << i << " z " << 5-n << ")" << endl;
        cout << "Podaj współrzędne " << n << " masztowca " << endl;
        ponownie_1:
        cout << "Współrzędna pionowa v: ";
        cin >> v;
        cout << "Współrzędna pozioma h: ";
        cin >> h;
        cout << endl;
        {
            if (v < 1 or v > 10 or h < 1 or h > 10)
            {
                cout << endl << "Błąd: podano współrzędne spoza obszaru walk. Spróbuj ponownie." << endl << endl;
                goto ponownie_1;
            }
        }
   
        if (sprawdz_puste_pola_h(n, v, h, plansza_1, licznik) >= 9)
        {
            for(int i=0; i<n; i++)
            {
            plansza_1[v+i][h] = 'O';
            }
        }
        else if (sprawdz_puste_pola_h(n, v, h, plansza_1, licznik) < 9)    
        {
            cout << endl << "Błąd: wykryto kolizję masztowców." << endl << endl;
            goto wprowadzenie;
        }
        system("clear");
    
        for (int i=0; i<11; i++)
            {
            for (int j=0; j<11; j++)
            {
                cout << plansza_1[i][j] << " ";
            }
            cout << endl;
            }

    }
}

void rysowanie_n(int n, int v, int h, char wybor, char plansza_1[11][11], int licznik, int a)
{
    if(n==2){a=12;}
    else if(n==3){a=15;}
    else if(n==4){a=18;}
   
   for (int i=1; i<=(5-n); i++)
    {
    start:
    cout << endl << "Ustaw swój " << n << " masztowiec " << "(" << i << " z " << 5-n << ")" << endl;
    rysowanie_1:
    cout << endl << "Ustawiasz statek poziomo czy pionowo? (h - poziomo, v - pionowo): ";
    cin >> wybor;
    if (wybor != 'h' and wybor != 'v')
        {
            cout << endl << "Błąd: niezrozumiałe wskazania orientacji masztowca. Proszę o ponownienie rozkazu." << endl;
            goto rysowanie_1;
        }
      
    cout << "Współrzędne " << n << " masztowca ";
       
    if(wybor == 'v')
    {       cout << "pionowo: ";
            wsp_ponownie_v:
            cout << endl;
            cout << "Współrzędna pionowa v: ";
            cin >> v;
            cout << "Współrzędna pozioma h: ";
            cin >> h;
            if(v > (11-n) or v < 1 or h > 10 or h < 1)
            {
                cout << endl << "Błąd: masztowiec wychodzi poza obszar walk. Podaj współrzędne ponownie." << endl;
                goto wsp_ponownie_v;
            }
    }

    else if(wybor == 'h')
    {
        cout << "poziomo: ";
        wsp_ponownie_h:
        cout << endl;
        cout << "Współrzędna pionowa v: ";
        cin >> v;
        cout << "Współrzędna pozioma h: ";
        cin >> h;
        if(h > (11-n) or h < 1 or v > 10 or v < 1)
            {
                cout << endl << "Błąd: masztowiec wychodzi poza obszar walk. Podaj współrzędne ponownie." << endl;
                goto wsp_ponownie_h;
            }
    }

   if (wybor == 'v') //v - vertical (poziomo)
   {
        if (sprawdz_puste_pola_v(n, v, h, plansza_1, licznik) == a)
        {
            for(int i=0; i<n; i++)
                {        
                 plansza_1[v+i][h] = 'O';
                }   
            system("clear");
    
        for (int i=0; i<11; i++)
        {
            for (int j=0; j<11; j++)
            {
                cout << plansza_1[i][j] << " ";
            }
        cout << endl;
        }
        }
        else
        {
            cout << endl << "Błąd: wykryto kolizję masztowców." << endl << endl;
            goto start;
        } 
    }   

else if (wybor == 'h') //h - horizontal (poziomo)
    {
        if (sprawdz_puste_pola_h(n, v, h, plansza_1, licznik) == a)
        {
            for(int i=0; i<n; i++)
                {        
                 plansza_1[v][h+i] = 'O';
                }   
                 system("clear");
    
        for (int i=0; i<11; i++)
        {
            for (int j=0; j<11; j++)
            {
                cout << plansza_1[i][j] << " ";
            }
        cout << endl;
        }
        }
        else
        {
            cout << endl << "Błąd: wykryto kolizję masztowców." << endl << endl;
            goto start;
        } 
    }
    }
       
}

void plansza_gracza(char plansza_1[11][11])
{
    plansza_1[0][0]=' ';
    plansza_1[0][1]='1';
    plansza_1[0][2]='2';
    plansza_1[0][3]='3';
    plansza_1[0][4]='4';
    plansza_1[0][5]='5';
    plansza_1[0][6]='6';
    plansza_1[0][7]='7';
    plansza_1[0][8]='8';
    plansza_1[0][9]='9';
    plansza_1[0][10]='0';
    
    plansza_1[1][0]='1';
    plansza_1[2][0]='2';
    plansza_1[3][0]='3';
    plansza_1[4][0]='4';
    plansza_1[5][0]='5';
    plansza_1[6][0]='6';
    plansza_1[7][0]='7';
    plansza_1[8][0]='8';
    plansza_1[9][0]='9';
    plansza_1[10][0]='0';
    
    for(int i=1; i<11; i++)
    {
        for(int j=1; j<11; j++)
        {
            plansza_1[i][j]='-';
        }
    }
}

void plansza_komputera(char plansza_2[11][11])

{
    plansza_2[0][0]=' ';
    plansza_2[0][1]='1';
    plansza_2[0][2]='2';
    plansza_2[0][3]='3';
    plansza_2[0][4]='4';
    plansza_2[0][5]='5';
    plansza_2[0][6]='6';
    plansza_2[0][7]='7';
    plansza_2[0][8]='8';
    plansza_2[0][9]='9';
    plansza_2[0][10]='0';
    
    plansza_2[1][0]='1';
    plansza_2[2][0]='2';
    plansza_2[3][0]='3';
    plansza_2[4][0]='4';
    plansza_2[5][0]='5';
    plansza_2[6][0]='6';
    plansza_2[7][0]='7';
    plansza_2[8][0]='8';
    plansza_2[9][0]='9';
    plansza_2[10][0]='0';
    
    for(int i=1; i<11; i++)
    {
        for(int j=1; j<11; j++)
        {
            plansza_2[i][j]='-';
        }
    }
}

void plansza_3(char plansza_pomoc[11][11])
{
    plansza_pomoc[0][0]=' ';
    plansza_pomoc[0][1]='1';
    plansza_pomoc[0][2]='2';
    plansza_pomoc[0][3]='3';
    plansza_pomoc[0][4]='4';
    plansza_pomoc[0][5]='5';
    plansza_pomoc[0][6]='6';
    plansza_pomoc[0][7]='7';
    plansza_pomoc[0][8]='8';
    plansza_pomoc[0][9]='9';
    plansza_pomoc[0][10]='0';
    
    plansza_pomoc[1][0]='1';
    plansza_pomoc[2][0]='2';
    plansza_pomoc[3][0]='3';
    plansza_pomoc[4][0]='4';
    plansza_pomoc[5][0]='5';
    plansza_pomoc[6][0]='6';
    plansza_pomoc[7][0]='7';
    plansza_pomoc[8][0]='8';
    plansza_pomoc[9][0]='9';
    plansza_pomoc[10][0]='0';
    
    for(int i=1; i<11; i++)
    {
        for(int j=1; j<11; j++)
        {
            plansza_pomoc[i][j]='-';
        }
    }
}

void rysuj_plansze(char plansza[11][11])
{
    for (int i=0; i<11; i++)
    {
        for (int j=0; j<11; j++)
        {
            cout << plansza[i][j] << " ";
        }
        cout << endl;
    }
}

void strzal_gracz(int v, int h, char plansza_2[11][11], char plansza_pomoc[11][11], int licznik, char plansza_1[11][11])
{
    strzal_g:
    cout << endl << "Podaj współrzędne celu, który ma zostać zbombardowany." << endl << "Współrzędna pionowa: ";
    cin >> v;
    cout << "Współrzędna pozioma: ";
    cin >> h;
    cout << endl;
    if(v < 1 or v > 10 or h < 1 or v > 10)
    {
        cout << "Błąd: współrzedne celu poza obszarem walk. Spróbuj ponownie." << endl << endl;
        goto strzal_g;
    }
    if(plansza_2[v][h] == 'O')
    {
        plansza_2[v][h] = 'X';
        plansza_pomoc[v][h] = 'X';
        system("clear");
        rysuj_plansze(plansza_1);
        cout << endl;
        rysuj_plansze(plansza_pomoc);
        cout << endl << "Cel trafiony!" << endl;
        if(sprawdz_wynik(v, h, plansza_2, licznik) == 20)
        {
            cout << "Zwycięstwo!";
            //goto koniec_gry;
        }
        goto strzal_g;
    }
    else if(plansza_2[v][h] == '-')
    {
        plansza_pomoc[v][h] = '+';
        system("clear");
        rysuj_plansze(plansza_1);
        cout << endl;
        rysuj_plansze(plansza_pomoc);
        cout << endl << "Cel chybiony, oczekujemy ruchu przeciwnika." << endl;
    }

}

void strzal_komp(int v, int h, char plansza_1[11][11], int licznik, char plansza_pomoc[11][11], int b, int c, char plansza_2[11][11], char wybor)
{
    strzal_k:
    int const lowv=1, highv=10, mv=1;
    random_device rdv;
    uniform_int_distribution<int> distv(lowv,highv);
    mt19937 generatorv(rdv());
    v = distv(generatorv); 
   
    int const lowh=1, highh=(10), mh=1;
    random_device rdh;
    uniform_int_distribution<int> disth(lowh,highh);
    mt19937 generatorh(rdh());
    h = disth(generatorh);

    int const lowb=(0), highb=(3), mb=1;
    random_device rdb;
    uniform_int_distribution<int> distb(lowb,highb);
    mt19937 generatorb(rdb());
    b = distb(generatorb);

    int const lowc=(0), highc=(1), mc=1;
    random_device rdc;
    uniform_int_distribution<int> distc(lowc,highc);
    mt19937 generatorc(rdc());
    c = distc(generatorc);
    again:
    

    if(plansza_1[v][h] == 'O')
    {
        plansza_1[v][h] = 'X';
        czekaj(3000);
        system("clear");
        rysuj_plansze(plansza_1);
        cout << endl;
        rysuj_plansze(plansza_pomoc);
        cout << endl << "Nasza jednostka została trafiona (" << v << ", " << h << "). Spodziewany kolejny atak." << endl;
        if(sprawdz_wynik(v, h, plansza_1, licznik) == 20)
        {
            system("clear");
            rysuj_plansze(plansza_1);
            cout << endl << "Przeciwnik zwyciężył" << endl << endl;
            rysuj_plansze(plansza_2);
           // goto koniec_gry;
        }
            //mozna wykorzystać wskaźniki, że co jakiś czas próbujemy trafić w pole obok "X".
            if(b==0 and v>1 and v<10 and h>1 and h<10)
            {   
                up_0:
                v = v-1;
                h = h+0;
                if(plansza_1[v][h] == 'O')
                {
                    czekaj(3000);
                    system("clear");
                    rysuj_plansze(plansza_1);
                    cout << endl;
                    rysuj_plansze(plansza_pomoc);
                    cout << endl << "Nasza jednostka została trafiona (" << v << ", " << h << "). Spodziewany kolejny atak." << endl;
                    if(sprawdz_wynik(v, h, plansza_1, licznik) == 20)
                    {
                        system("clear");
                        rysuj_plansze(plansza_1);
                        cout << endl << "Przeciwnik zwyciężył" << endl << endl;
                        rysuj_plansze(plansza_2);
                        // goto koniec_gry;
                    }
                    goto up_0;
                }
            }
            else if(b==1 and v>1 and v<10 and h>1 and h<10)
            {   
                up_1:
                v = v+1;
                h = h+0;
                if(plansza_1[v][h] == 'O')
                {
                    czekaj(3000);
                    system("clear");
                    rysuj_plansze(plansza_1);
                    cout << endl;
                    rysuj_plansze(plansza_pomoc);
                    cout << endl << "Nasza jednostka została trafiona (" << v << ", " << h << "). Spodziewany kolejny atak." << endl;
                    if(sprawdz_wynik(v, h, plansza_1, licznik) == 20)
                    {
                        system("clear");
                        rysuj_plansze(plansza_1);
                        cout << endl << "Przeciwnik zwyciężył" << endl << endl;
                        rysuj_plansze(plansza_2);
                        // goto koniec_gry;
                    }
                    goto up_1;
                }
            }
            else if(b==2 and v>1 and v<10 and h>1 and h<10)
            {   
                up_2:
                v = v+0;
                h = h-1;
                if(plansza_1[v][h] == 'O')
                {
                    czekaj(3000);
                    system("clear");
                    rysuj_plansze(plansza_1);
                    cout << endl;
                    rysuj_plansze(plansza_pomoc);
                    cout << endl << "Nasza jednostka została trafiona (" << v << ", " << h << "). Spodziewany kolejny atak." << endl;
                    if(sprawdz_wynik(v, h, plansza_1, licznik) == 20)
                    {
                        system("clear");
                        rysuj_plansze(plansza_1);
                        cout << endl << "Przeciwnik zwyciężył" << endl << endl;
                        rysuj_plansze(plansza_2);
                        // goto koniec_gry;
                    }
                    goto up_2;
                }
            }
            else if(b==3 and v>1 and v<10 and h>1 and h<10)
            {   
                up_3:
                v = v+0;
                h = h+1;
                if(plansza_1[v][h] == 'O')
                {
                    czekaj(3000);
                    system("clear");
                    rysuj_plansze(plansza_1);
                    cout << endl;
                    rysuj_plansze(plansza_pomoc);
                    cout << endl << "Nasza jednostka została trafiona (" << v << ", " << h << "). Spodziewany kolejny atak." << endl;
                    if(sprawdz_wynik(v, h, plansza_1, licznik) == 20)
                    {
                        system("clear");
                        rysuj_plansze(plansza_1);
                        cout << endl << "Przeciwnik zwyciężył" << endl << endl;
                        rysuj_plansze(plansza_2);
                        // goto koniec_gry;
                    }
                    goto up_3;
                }
            }
            else if(c==0 and v==1 and h>1 and h<10)
            {
                up_4:
               v = v+0;
                h = h+1;
                if(plansza_1[v][h] == 'O')
                {
                    czekaj(3000);
                    system("clear");
                    rysuj_plansze(plansza_1);
                    cout << endl;
                    rysuj_plansze(plansza_pomoc);
                    cout << endl << "Nasza jednostka została trafiona (" << v << ", " << h << "). Spodziewany kolejny atak." << endl;
                    if(sprawdz_wynik(v, h, plansza_1, licznik) == 20)
                    {
                        system("clear");
                        rysuj_plansze(plansza_1);
                        cout << endl << "Przeciwnik zwyciężył" << endl << endl;
                        rysuj_plansze(plansza_2);
                        // goto koniec_gry;
                    }
                    goto up_4;
                }
            }
            else if(c==1 and v==1 and h>1 and h<10)
            {
                up_5:
                v = v+0;
                h = h-1;
                if(plansza_1[v][h] == 'O')
                {
                    czekaj(3000);
                    system("clear");
                    rysuj_plansze(plansza_1);
                    cout << endl;
                    rysuj_plansze(plansza_pomoc);
                    cout << endl << "Nasza jednostka została trafiona (" << v << ", " << h << "). Spodziewany kolejny atak." << endl;
                    if(sprawdz_wynik(v, h, plansza_1, licznik) == 20)
                    {
                        system("clear");
                        rysuj_plansze(plansza_1);
                        cout << endl << "Przeciwnik zwyciężył" << endl << endl;
                        rysuj_plansze(plansza_2);
                        // goto koniec_gry;
                    }
                    goto up_5;
                }
            }
            
            goto again;
    }
    else if(plansza_1[v][h] == '-')
    {
        plansza_1[v][h] = '+';
        czekaj(3000);
        system("clear");
        rysuj_plansze(plansza_1);
        cout << endl;
        rysuj_plansze(plansza_pomoc);
        cout << endl << "Przeciwnik chybił (" << v << ", " << h << ")." << endl;
    }
    else
    {
        goto strzal_k;
    }
}

int main()
{ 
    char plansza_1[11][11];
    char plansza_2[11][11];
    char plansza_pomoc[11][11];
   
    int n, v, h, licznik, a, b, c;
    char wybor;

plansza_gracza(plansza_1);
plansza_komputera(plansza_2);
plansza_3(plansza_pomoc);
    
rysowanie_komp_n(n=4, v, h, wybor, plansza_2, licznik, a);
rysowanie_komp_n(n=3, v, h, wybor, plansza_2, licznik, a);
rysowanie_komp_n(n=2, v, h, wybor, plansza_2, licznik, a);
rysowanie_komp_1(n=1, v, h, wybor, plansza_2, licznik);
//wyczysc_ekran();
/*instrukcja(); funkcja oczekiuje na napisanie*/
rysuj_plansze(plansza_1);

rysowanie_n(n=4, v, h, wybor, plansza_1, licznik, a);
rysowanie_n(n=3, v, h, wybor, plansza_1, licznik, a);
rysowanie_n(n=2, v, h, wybor, plansza_1, licznik, a);
rysowanie_1(n=1, v, h, wybor, plansza_1, licznik);
    cout << endl;
    rysuj_plansze(plansza_pomoc);
for (int i=0; i<100; i++)
{   
    strzal_gracz(v, h,  plansza_2, plansza_pomoc, licznik, plansza_1);
    cout << endl;
    strzal_komp(v, h, plansza_1, licznik, plansza_pomoc, b, c, plansza_2, wybor);
}
return 0;  
}