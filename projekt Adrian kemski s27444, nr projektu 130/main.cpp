#include <iostream>
#include <conio.h>
#include "windows.h"

// funkcja przenosz�ca kursor do podanych wsp�rz�dnych (x, y)
void punkt(int x, int y)
{
COORD c;
c.X = x;
c.Y = y;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

// funkcja zwracaj�ca aktualn� wsp�rz�dn� x kursora
int wherex()
{
CONSOLE_SCREEN_BUFFER_INFO csbi;
GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
return csbi.dwCursorPosition.X;
}

// funkcja zwracaj�ca aktualn� wsp�rz�dn� y kursora
int wherey()
{
CONSOLE_SCREEN_BUFFER_INFO csbi;
GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
return csbi.dwCursorPosition.Y;
}

// wy�wietla powitanie
void Wstep();

// pobiera od u�ytkownika dane potrzebne do rysowania figury (rozmiar i znak)
void WczytajDane(float &size, char &znak);

// rysuje figur� o podanych wsp�rz�dnych (x, y), rozmiarze i znaku
void Rysuj(float size, float x, float y, char znak);

// pozwala u�ytkownikowi na przesuwanie figury po ekranie za pomoc� klawiszy strza�ek
void Przesuwanie(float size, float &x, float &y, char znak);

using namespace std;
using std::cin;
using std::cout;
using std::endl;

int rozmiar;
int main()
{
        float x=30,y=12;
        float size;
        char znak;
        system("cls");

        Wstep();
        WczytajDane(size, znak);
        Rysuj(size, x, y, znak);
        getch();
        Przesuwanie(size, x, y, znak);

        return 0;
}

// funkcja wy�wietlaj�ca informacj� o programie
void Wstep()
{
cout << "\t=========================================================== \n"
        "\t========== Program rysowania figury znakiem ASCII ========= \n"
        "\t=========================================================== \n"
        "\t========================  FIGURA  ========================= \n"
        "\t=========================================================== \n"
        "\t=========================  +++++  ========================= \n"
        "\t=========================     +   ========================  \n"
        "\t=========================    +    ========================  \n"
        "\t=========================     +   ========================  \n"
        "\t=========================  +++++  ========================= \n"
        "\t=========================================================== \n"
        "\t==================== Program umozliwia: =================== \n"
        "\t== wybor znaku kodu ASCII ================================= \n"
        "\t== wczytanie poczatkowych rozmiarow figury ================ \n"
        "\t== przesuwanie firury klawiszami strzalek ================= \n"
        "\t== powiekszanie oraz zmianiszanie figury za pomoca + i - == \n"
        "\t== ograniczenie przesuwania figury do rozmiaru ekranu ===== \n"
        "\t=========================================================== \n"
        "\t======== dowolny klawisz rozpocznie prace programu ======== \n"
        "\t=========================================================== ";
        getch();
}

// funkcja wy�wietlaj�ca legend�
void Legenda()
{
punkt(55,0), cout << "\t========== Legenda  =====================================" << endl;
punkt(55,1), cout << "\t= strzalki: przesuwanie                                 =" << endl;
punkt(55,2), cout << "\t= spacja: powrot do rozmiarow poczatkowych,             =" << endl;
punkt(55,3), cout << "\t= aby zobaczyc efekt dodatkowo kliknij '+'              =" << endl;
punkt(55,4), cout << "\t= +: powiekszanie figury                                =" << endl;
punkt(55,5), cout << "\t= -: zmniejszanie figury                                =" << endl;
punkt(55,6), cout << "\t= TAB: znikanie figury,                                 =" << endl;
punkt(55,7), cout << "\t= aby figura pojawila sie ponownie kliknij '+' lub '-'  =" << endl;
punkt(55,8), cout << "\t= ESC: zakonczenie pracy programu                       =" << endl;
punkt(55,9), cout << "\t=========================================================" << endl;
        getch();
}

// funkcja wprowadzaj�ca dane

void WczytajDane (float &size, char &znak)
{
        system("cls");
        int max=10 , min=1;
        do
        {
        cout << "Podaj rozmiar figury z zakresu (1-10): ";
        cin >> rozmiar;
          if(rozmiar < min){
               cout << "Podales liczbe za mala, musisz podac wieksza" << endl;
            }
          else if(rozmiar > max){
              cout << "Podales liczbe za duza, musisz podac mniejsza" << endl;
            }
        }
        while( rozmiar < min || rozmiar > max);


        size = rozmiar;

        cout << "Podaj znak kodu ASCII: ";
        cin >> znak;

}

// funkcja rysuj�ca figur�

void Rysuj(float size, float x, float y, char znak)
{
float i,j;
int k;

        system("cls");

        for(i=x , j=y , k=0 ; k < size ; i--, k++)
        {
        punkt(i,j), cout << znak;
        }

        for(i=x , j=y , k=0 ; k < (size/2) ; i++,j++,k++)
        {
            punkt(i,j), cout << znak;
        }

        for(i=x+(size/2) , j=y+(size/2) , k=0 ; k < (size/2) ; i++,j++,k++)
        {
            punkt(i,j), cout << znak;
        }

        for(i=x-1, j=(y+size)-1 , k=0 ; k < size ; i++ , k++)
        {
            punkt(i,j), cout << znak;
        }
        Legenda();

}

// funkcja odpowiedzialna za przesuwanie, zmiennianie rozmiar�w itp.

void Przesuwanie(float size, float &x, float &y, char znak) // przesuwanie figury klawiszami strza�ek
{
        int zmiana = 0, max=10;
        char przycisk;


        do
        {
        przycisk = getch();

        switch (przycisk)
                {
                case 72: //strza�ka w g�r�
                        {
                        y--; zmiana = 1;
                        if (y < 1)
                        {
                                y++;
                                zmiana = 0;
                        }
                 break;
                 }

                 case 80: //strza�ka w d�
                        {
                        y++; zmiana = 1;
                        if (y > max - (size-18))
                        {
                        y--;
                        zmiana = 0;
                        }
                 break;
                 }
                case 75: //strza�ka w lewo
                    {
                        x--; zmiana = 1;
                        if (x < 12 )
                        {
                            x++;
                            zmiana = 0;
                        }
                break;
                }
                case 77: //strza�ka w prawo
                    {
                        x++; zmiana = 1;
                        if (x > 45 - size)
                        {
                            x--;
                            zmiana = 0;
                        }
                        break;
                        }
                case '+': //zwi�kszanie figury
		        {
                    size++; zmiana=1;
                    if (size < 1 || size > max)
                {
                        size--; y--;
                        zmiana = 0;
                        }
                    break;
                 }

                 case '-': //zmniejszanie figury
                        {
                        size--;
                        zmiana=1;
                        if (size < 1 || size > max)
                        {
                        size++;
                        zmiana = 0;
                  }
                  break;
         }

               case 32: //powr�t do rozmiar�w pocz�tkowych
                        {
                        size = rozmiar;
                        break;
                    }

                case '\t': //znikanie figury
                        {
                        Rysuj(size, x, y, ' ');
                        break;
                    }



}



if (zmiana)
{
Rysuj(size, x, y, znak); zmiana = 0;
}



}
while (przycisk != 27);// ESC ko�cz�cy program

}


//koniec programu
