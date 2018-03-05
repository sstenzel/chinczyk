
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


    // prosze odkomentowac wybrany system i zakomentowac drugi

//#define systemOp 'w'    // windows
#define systemOp 'l'  // linux


#if systemOp == 'w'
    #include <windows.h>
    #define bialy SetConsoleTextAttribute(hConsole, 15)
    #define czerwony SetConsoleTextAttribute(hConsole, 12)
    #define niebieski SetConsoleTextAttribute(hConsole,9)
    #define rozowy SetConsoleTextAttribute(hConsole, 13)
    #define zielony SetConsoleTextAttribute(hConsole, 10)
#elif systemOp == 'l'
    #define bialy printf("%c[%dm",0x1B,0)
    #define czerwony printf("%c[%dm",0x1B,31)
    #define niebieski printf("%c[%dm",0x1B,34)
    #define rozowy printf("%c[%dm",0x1B,35)
    #define zielony printf("%c[%dm",0x1B,32)
#endif

#define wskPola(x,y)    gracze[x].planszaGracza[y].zawartosc
#define zawartPola(x,y) *(gracze[x].planszaGracza[y].zawartosc)
#define polePionka(x,y) gracze[x].pionek[(y)-1]

#define gracz       kolejka->Gracz
#define kostka      kolejka->Kostka
#define wybrPionek  kolejka->WybrPionek
#define wybor       kolejka->Wybor
#define cel         kolejka->Cel


typedef struct {
    int numer;
    char * zawartosc;
} Pole;

typedef struct {
    char * imie;
    unsigned int baza;
    unsigned int domek;
    unsigned int pionek[4];
    Pole planszaGracza[48];
} Gracz;

typedef struct {
    unsigned int Gracz;
    unsigned int Kostka;
    unsigned int WybrPionek;
    unsigned int Wybor;
    unsigned int Cel;
} Kolejka;

typedef struct {
    int Gracz;
    int Pionek;
} NaPolu;


// Main
void kolej(char [][63], Gracz *, Kolejka *);
void wyborPionka (char [][63], Gracz *, Kolejka *);
void rzutKostka(char [][63], Gracz *, Kolejka *);
NaPolu ktoryGracz(Gracz *, Kolejka *, int);
void czteryWBazie(char [][63], Gracz *, Kolejka *);
void wyjscieZBazy(char [][63], Gracz *, Kolejka *);
void zbicie(Gracz *, Kolejka *, NaPolu);
void ruch(char [][63], Gracz *, Kolejka *);
bool czyMozliwyRuch(Gracz *, Kolejka *);

// Plansza
void pokazPlansze(char [][63], Gracz *, Kolejka *);
void inicjalizacjaPlanszy(char [][63], Gracz *, Kolejka *);

// Robert
void ruchKomputera (Gracz *, Kolejka *);
int pionekZPlanszy (Gracz *, Kolejka *);
int pionekZBazy (Gracz *, Kolejka *);
int pionekZDomku (Gracz *, Kolejka *);
bool czyMozliwyRuchPionka (Gracz *, Kolejka *, int);
bool czyPrzeciwnikNaCelu (Gracz *, Kolejka *, int);
bool czyPrzeciwnikPrzedCelem (Gracz *, Kolejka *, int);
bool czyPrzeciwnikZTylu (Gracz *, Kolejka *, int);
