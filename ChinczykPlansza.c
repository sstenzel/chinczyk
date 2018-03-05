
#include "ChinczykPrototypy.h"

/*   numeracja na plansza gracza
                               19
                      18[  ]==[  ]==[  ]20
                         ||    ||    ||
         {  }{  }     17[  ]  {  }  [  ]21       {  }{  }
         {  }{  }        ||    ||    ||          {  }{  }
                      16[  ]  {  }  [  ]22
                         ||    ||    ||
                      15[  ]  {  }  [  ]23
     10   11   12   13   ||    ||    ||   25   26   27   28
    [  ]=[  ]=[  ]=[  ]=[  ]  {  }  [  ]=[  ]=[  ]=[  ]=[  ]
     ||                                                  ||
   9[  ]={  }={  }={  }={  }        {  }={  }={  }={  }=[  ]29
     ||                                                  ||
    [  ]=[  ]=[  ]=[  ]=[  ]43{  }  [  ]=[  ]=[  ]=[  ]=[  ]
     8    7    6    5    ||    ||    ||   33   32   31   30
                       3[  ]42{  }  [  ]35
                         ||    ||    ||
        45  46         2[  ]41{  }  [  ]36
       {  }{  }          ||    ||    ||          {  }{  }
       {  }{  }        1[  ]40{  }  [  ]37       {  }{  }
        44  47           ||    ||    ||
                       0[  ]==[  ]==[  ]38
                               39
*/

/*  tablica (numeracja na planszy glownej)
                               19
                      18[  ]==[  ]==[  ]20
          61  62         ||    ||    ||           65  66
         {  }{  }     17[  ]48{  }  [  ]21       {  }{  }
         {  }{  }        ||    ||    ||          {  }{  }
          60  63      16[  ]49{  }  [  ]22        64  67
                         ||    ||    ||
                      15[  ]50{  }  [  ]23
     10   11   12   13   ||    ||    ||   25   26   27   28
    [  ]=[  ]=[  ]=[  ]=[  ]51{  }  [  ]=[  ]=[  ]=[  ]=[  ]
     ||   44   45   46   47          55   54   53   52   ||
   9[  ]={  }={  }={  }={  }        {  }={  }={  }={  }=[  ]29
     ||                                                  ||
    [  ]=[  ]=[  ]=[  ]=[  ]43{  }  [  ]=[  ]=[  ]=[  ]=[  ]
     8    7    6    5    ||    ||    ||   33   32   31   30
                       3[  ]42{  }  [  ]35
                         ||    ||    ||
        57  58         2[  ]41{  }  [  ]36        69  70
       {  }{  }          ||    ||    ||          {  }{  }
       {  }{  }        1[  ]40{  }  [  ]37       {  }{  }
        56  59           ||    ||    ||           68  71
                       0[  ]==[  ]==[  ]38
                               39
*/





void inicjalizacjaPlanszy(char plansza[][63], Gracz * gracze, Kolejka * kolejka) {
    int i, x;

    FILE *f;
    f=fopen("planszaCzysta.txt","rt");
    if (f == NULL) {
        printf("Problem z wczytaniem planszy. \nSprawdz czy plik z plansza jest w folderze.\n");
        getchar();
        return;
    }
    for (i=0; i<23; i++) {
        for (x=0; x<63; x++)
            plansza[i][x] = fgetc(f);
    }
    fclose(f);

#if systemOp == 'w'
    Pole * tablica = malloc(72*sizeof(Pole));
#elif systemOp == 'l'
    Pole * tablica;     // nie wiemy dlaczego, ale malloc nie chce dzialac na linuksie
#endif

    for (i=0,x=0; i<5; i++, x+=2) {
    tablica[i].zawartosc = (plansza[21-x]+25);
    tablica[14+i].zawartosc = (plansza[9-x]+25);
    tablica[39+i].zawartosc = (plansza[21-x]+32);
    tablica[51-i].zawartosc = (plansza[9-x]+32);
    tablica[24-i].zawartosc = (plansza[9-x]+38);
    tablica[38-i].zawartosc = (plansza[21-x]+38);
    }
    tablica[19].zawartosc = (plansza[1]+32);
    tablica[9].zawartosc = (plansza[11]+6);
    tablica[29].zawartosc = (plansza[11]+58);
    for (i=0, x=0; i<4; x+=5, i++ ) {
    tablica[10+i].zawartosc = (plansza[9]+(6+x));
    tablica[8-i].zawartosc = (plansza[13]+(6+x));
    tablica[25+i].zawartosc = (plansza[9]+(43+x));
    tablica[33-i].zawartosc = (plansza[13]+(43+x));
    tablica[44+i].zawartosc = (plansza[11]+(11+x));
    tablica[55-i].zawartosc = (plansza[11]+(38+x));
    }
    for (i=0; i<2; i++) {
    tablica[60+i].zawartosc = (plansza[4-i]+8);
    tablica[63-i].zawartosc = (plansza[4-i]+12);
    tablica[64+i].zawartosc = (plansza[4-i]+50);
    tablica[67-i].zawartosc = (plansza[4-i]+54);
    tablica[56+i].zawartosc = (plansza[19-i]+8);
    tablica[59-i].zawartosc = (plansza[19-i]+12);
    tablica[68+i].zawartosc = (plansza[19-i]+50);
    tablica[71-i].zawartosc = (plansza[19-i]+54);
    }

    for (i=0; i<72; i++)
       *(tablica[i].zawartosc) = 0;


    for (i=0; i<=39; i++) {
                gracze[0].planszaGracza[i].zawartosc = (tablica+i)->zawartosc;
      if (i<10) gracze[1].planszaGracza[i].zawartosc = (tablica+(i+10))->zawartosc;
      else      gracze[1].planszaGracza[i].zawartosc = (tablica+(i-30))->zawartosc;
      if (i<20) gracze[2].planszaGracza[i].zawartosc = (tablica+(i+20))->zawartosc;
      else      gracze[2].planszaGracza[i].zawartosc = (tablica+(i-20))->zawartosc;
      if (i<30) gracze[3].planszaGracza[i].zawartosc = (tablica+(i+30))->zawartosc;
      else      gracze[3].planszaGracza[i].zawartosc = (tablica+(i-10))->zawartosc;
    }
    for (i=0; i<4; i++) {
        gracze[0].planszaGracza[40+i].zawartosc = (tablica+(40+i))->zawartosc;
        gracze[1].planszaGracza[40+i].zawartosc = (tablica+(44+i))->zawartosc;
        gracze[2].planszaGracza[40+i].zawartosc = (tablica+(48+i))->zawartosc;
        gracze[3].planszaGracza[40+i].zawartosc = (tablica+(52+i))->zawartosc;
        gracze[0].planszaGracza[44+i].zawartosc = (tablica+(56+i))->zawartosc;
        gracze[1].planszaGracza[44+i].zawartosc = (tablica+(60+i))->zawartosc;
        gracze[2].planszaGracza[44+i].zawartosc = (tablica+(64+i))->zawartosc;
        gracze[3].planszaGracza[44+i].zawartosc = (tablica+(68+i))->zawartosc;
    }

#if systemOp == 'w'
    free(tablica);
#endif

    for(x=0; x<4; x++) {
        gracze[x].baza = 4;
        gracze[x].domek = 0;
        for (i=0; i<=47; i++)
           gracze[x].planszaGracza[x].numer = i;
        for (i=0; i<4; i++) {
            polePionka(x,i+1) = 44+i;
            zawartPola(x,44+i) = 'A'+ 4*x + i;
        }
    }

    gracze[1].imie = "[brak gracza]";
    gracze[2].imie = "Robert";
    gracze[3].imie = "[brak gracza]";

    gracz = 2;
    kostka = 0;
    wybrPionek = 0;
    wybor = 0;
    cel = 0;

}


void pokazPlansze(char plansza[][63], Gracz * gracze, Kolejka * kolejka) {

#if systemOp == 'w'
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");
#elif systemOp == 'l'
   system("clear");
   //printf("\033[H\033[J");
#else
    printf("Blad: wybierz w kodzie programu system operacyjny");
#endif

    rozowy;      printf("\n%15s", gracze[1].imie);
    niebieski;   printf("\t\t\t\t\t%-15s", gracze[2].imie);
    bialy;
    for (int i=0; i<23; i++) {
        for (int j=0; j<63; j++) {
            switch (plansza[i][j]) {
                case 0: printf(" "); break;
                case 'A': czerwony; printf("1"); bialy; break;       // pionki gracza 0
                case 'B': czerwony; printf("2"); bialy; break;
                case 'C': czerwony; printf("3"); bialy; break;
                case 'D': czerwony; printf("4"); bialy; break;
                case 'E': rozowy; printf("1"); bialy; break;         // pionki gracza 1
                case 'F': rozowy; printf("2"); bialy; break;
                case 'G': rozowy; printf("3"); bialy; break;
                case 'H': rozowy; printf("4"); bialy; break;
                case 'I': niebieski; printf("1"); bialy; break;      // pionki gracza 2
                case 'J': niebieski; printf("2"); bialy; break;
                case 'K': niebieski; printf("3"); bialy; break;
                case 'L': niebieski; printf("4"); bialy; break;
                case 'M': zielony; printf("1"); bialy; break;        // pionki gracza 3
                case 'N': zielony; printf("2"); bialy; break;
                case 'O': zielony; printf("3"); bialy; break;
                case 'P': zielony; printf("4"); bialy; break;
                default: printf ("%c", plansza[i][j]); break;
            }
        }
    }
    czerwony;    printf("%15s", gracze[0].imie);
    zielony;     printf("\t\t\t\t\t%-15s\n", gracze[3].imie);
    bialy;
    printf ("\n-------------------------------------------------------------\n");
    printf("\nKolejka gracza: ");
    switch (gracz) {
        case 0: czerwony; break;
        case 1: rozowy; break;
        case 2: niebieski; break;
        case 3: zielony; break;
    }

    printf("%-14s", gracze[gracz].imie);
    bialy;   printf("\tKostka: %d\n\n", kostka);
    printf ("-------------------------------------------------------------\n\n");
}
