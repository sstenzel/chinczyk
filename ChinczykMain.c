
#include"ChinczykPrototypy.h"


int main () {
    srand(time(NULL));
    Gracz gracze[4];
    Kolejka kolejka;
    char plansza[23][63];

    inicjalizacjaPlanszy(plansza, gracze, &kolejka);

    printf("\nPodaj swoje imie (do 14 znakow): ");
    char tmp[14];
    scanf("%14s", tmp);
    gracze[0].imie = tmp;

    pokazPlansze(plansza, gracze, &kolejka);
    long int czas = time(NULL);
    do{ }while (czas + 1 > time(NULL));
    printf("Zaraz rozpocznie sie gra");
    czas = time(NULL);
    do{ }while (czas + 5 > time(NULL));

    do {
          kolej(plansza, gracze, &kolejka);
    } while (gracze[kolejka.Gracz].domek != 4);

    pokazPlansze(plansza, gracze, &kolejka);
    printf("\nGratulacje %s ! Wygrales!\n", gracze[kolejka.Gracz].imie);

return 0;
}


void kolej(char plansza[][63], Gracz * gracze, Kolejka * kolejka) {
    gracz += 2;                   // dla dwoch graczy
    if (gracz == 4)  gracz = 0;

    if (gracze[gracz].baza == 4)
        czteryWBazie(plansza, gracze, kolejka);
    else {
        rzutKostka(plansza, gracze, kolejka);
        if (czyMozliwyRuch(gracze, kolejka))
            wyborPionka(plansza, gracze, kolejka);
        else   { printf("Brak mozliwosci ruchu (nacisnij enter)"); getchar(); }
    }
    while (kostka == 6) {
        rzutKostka(plansza, gracze, kolejka);
        if (czyMozliwyRuch(gracze, kolejka))
            wyborPionka(plansza, gracze, kolejka);
    }
    return;
}


void wyborPionka (char plansza[][63], Gracz * gracze, Kolejka * kolejka) {
        long int czas = time(NULL);
        do{ }while (czas + 1 > time(NULL));

        if (gracz == 2) {
                ruchKomputera(gracze, kolejka);
                printf("Ruch Roberta...");
                if (wybrPionek == -1) {
                    printf("Error ruchKomputera");
                    getchar();
                }
                czas = time(NULL);
                do{
                }while (czas + 2 > time(NULL));
        }
        else {
            printf("Podaj numer pionka, ktorym chcesz ruszyc: ");
            scanf("%d", &(wybrPionek));

            while (wybrPionek < 1  ||  wybrPionek > 4) {
                printf("\nPodaj numer pionka, ktorym chcesz ruszyc: (od 1 do 4)");
                scanf("%d", &(wybrPionek));
            }
        }

        wybor = polePionka(gracz, wybrPionek);
        cel = wybor + kostka;

        if (wybor >= 44  &&  wybor <= 47  &&  kostka != 6) {
            wyborPionka(plansza, gracze, kolejka);  return;
        }
        if (wybor >= 44  &&  wybor <= 47  &&  kostka == 6) {
            cel = 0;
            wyjscieZBazy(plansza, gracze, kolejka);  return;
        }
        if (cel > 43) {
            wyborPionka(plansza, gracze, kolejka);
            return;
        }
        if (wybor <= 43 ) {     // wejscie do domkow wewnatrz ruch()
            ruch(plansza, gracze, kolejka);  return;
        }
}


void rzutKostka(char plansza[][63], Gracz * gracze, Kolejka * kolejka) {
    kostka = (int)(rand()%6+1);
    pokazPlansze(plansza, gracze, kolejka);
}


NaPolu ktoryGracz(Gracz * gracze, Kolejka * kolejka, int pole) {
     NaPolu tmp = {-1, -1};
     int zawartTmp = zawartPola(gracz, pole);

     for (int i=0; i<4; i++){
        if ('A'+i == zawartTmp) { tmp.Gracz = 0; tmp.Pionek = i+1; return tmp;}
        else if ('E'+i == zawartTmp) { tmp.Gracz = 1; tmp.Pionek = i+1; return tmp;}
        else if ('I'+i == zawartTmp) { tmp.Gracz = 2; tmp.Pionek = i+1; return tmp;}
        else if ('M'+i == zawartTmp) { tmp.Gracz = 3; tmp.Pionek = i+1; return tmp;}
     }
     return tmp;
}


void czteryWBazie(char plansza[][63], Gracz * gracze, Kolejka * kolejka) {
    kostka = 0;
    pokazPlansze(plansza, gracze, kolejka);
    long int czas;
    for (int i=0; i<3 && kostka!=6 ; i++) {
        czas = time(NULL);
        do{ }while (czas + 1 > time(NULL));

        if (gracz==2)
            printf("Robert rzuca kostka...");
        else
            printf("Musisz wylosowac szostke. Rzuca kostka...");

        czas = time(NULL);
        do{ }while (czas + 3 > time(NULL));

        rzutKostka(plansza, gracze, kolejka);

        if (kostka == 6) {
                //printf ("\n-------------------------------------------------------------\n\n");
                return wyborPionka(plansza, gracze, kolejka);
        }
    }
        if (gracz ==2)
            printf("Robert nie moze wyjsc z bazy");
        else
            printf("Nie mozesz wyjsc z bazy");
        czas = time(NULL);
        do{ }while (czas + 3 > time(NULL));
}


void wyjscieZBazy(char plansza[][63], Gracz * gracze, Kolejka * kolejka) {
    NaPolu naPolu = ktoryGracz(gracze, kolejka, 0);

    if (naPolu.Gracz == gracz)
        return wyborPionka(plansza, gracze, kolejka);
    if (naPolu.Gracz != -1)
        zbicie(gracze, kolejka, naPolu);

    zawartPola(gracz, 0) = zawartPola(gracz, wybor);
    zawartPola(gracz, wybor) = 0;
    polePionka(gracz, wybrPionek) = 0;
    gracze[gracz].baza--;
    return;
}


void zbicie(Gracz * gracze, Kolejka * kolejka, NaPolu naPolu) {
    zawartPola(naPolu.Gracz, 44 + naPolu.Pionek - 1) = zawartPola(gracz, cel);
    polePionka(naPolu.Gracz, naPolu.Pionek) = 44 + naPolu.Pionek - 1;
    gracze[naPolu.Gracz].baza++;
    getchar();
}


void ruch(char plansza[][63], Gracz * gracze, Kolejka * kolejka) {
    NaPolu naPolu = ktoryGracz(gracze, kolejka, cel);
    if (naPolu.Gracz == gracz) {
        wyborPionka(plansza, gracze, kolejka);
        return;
    }
    if (naPolu.Gracz != -1)
        zbicie(gracze, kolejka, naPolu);

    if (wybor <= 39  &&  cel >=40)
        gracze[gracz].domek++;

    zawartPola(gracz, cel) = zawartPola(gracz, wybor);
    zawartPola(gracz, wybor) = 0;
    polePionka(gracz, wybrPionek) = cel;
    return;
}

bool czyMozliwyRuch(Gracz * gracze, Kolejka * kolejka) {
    if (gracze[gracz].baza > 0 && kostka == 6) {
        bool ruch = 1;
        for (int i=1; i<=4; i++) {
            if (polePionka(gracz, i) == 0 )
                ruch = 0;
        }
        if (ruch == 1)
            return 1;
    }
    for (int i=1; i<=4; i++) {
        if (polePionka(gracz, i) < 43  &&  polePionka(gracz, i)+kostka < 44) {
            bool ruch = 1;
            for (int x=1; x<=4; x++) {
                    if (polePionka(gracz, i)+kostka == polePionka(gracz, x) )
                        ruch = 0;
            }
            if (ruch == 1) return 1;
        }
    }
    return 0;
}
