#include"ChinczykPrototypy.h"


void ruchKomputera (Gracz * gracze, Kolejka * kolejka) {
    if(gracze[gracz].baza == 4) {
        wybrPionek = 1; return;
    }
    if (4 - gracze[gracz].baza == gracze[gracz].domek) {
        if (kostka == 6) {
            wybrPionek = pionekZBazy(gracze, kolejka); return;
        }
        wybrPionek = pionekZDomku(gracze, kolejka); return;
    }

   /*

    if (4 - gracze[gracz].baza > gracze[gracz].domek + 1) {
        int tmpPole = -1, tmpNr = -1;
        for(int i=1; i<=4; i++) {
            if (polePionka(gracz,i) <= 39 ) {
                if (czyMozliwyRuchPionka(gracze, kolejka, i))  {
                     if (polePionka(gracz, 1) > tmpPole){
                                tmpPole = polePionka(gracz,1);
                                tmpNr = i;
        }}}}
        pionek = tmpNr;
    }

    else if (4 - gracze[gracz].baza == gracze[gracz].domek + 1) {
        pionek = pionekZPlanszy(gracze, kolejka);
    } */
     int pionek = pionekZPlanszy(gracze, kolejka);
     int pozycja;
        if (pionek == -1) {
            if (kostka == 6) {
               wybrPionek = pionekZBazy(gracze, kolejka); return;
            }
            wybrPionek = pionekZDomku(gracze, kolejka); return;
        }
        pozycja = polePionka(gracz, pionek);

        if (czyPrzeciwnikNaCelu(gracze, kolejka, pozycja)) {
                wybrPionek = pionek; return;
        }
        if (pozycja + kostka > 39) {
                wybrPionek = pionek; return;
        }
        if (czyPrzeciwnikZTylu(gracze, kolejka, pozycja)) {
                wybrPionek = pionek; return;
        }
        if (kostka == 6) {
            if (pozycja > 14 && gracze[gracz].baza != 0) {
               wybrPionek = pionekZBazy(gracze, kolejka);
               if (wybrPionek != -1)
                    return;
            }
            wybrPionek = pionek; return;
        }
        wybrPionek = pionek; return;
}

int pionekZPlanszy (Gracz * gracze, Kolejka * kolejka) {
    for(int i=1; i<=4; i++) {
        if (polePionka(gracz,i) <= 39 ) {
            if (czyMozliwyRuchPionka(gracze, kolejka, i)) {
                return i;
    }}}
    return -1;
}

int pionekZBazy (Gracz * gracze, Kolejka * kolejka){
    for(int i=1; i<=4; i++) {
        if(polePionka(gracz,i) >= 44 ) {
            if (czyMozliwyRuchPionka(gracze, kolejka, i)) {
                return i;
    }}}
    return -1;
}
int pionekZDomku (Gracz * gracze, Kolejka * kolejka){
    for(int i=1; i<=4; i++) {
            if(polePionka(gracz,i) >= 40 && polePionka(gracz,i) < 43) {
                if (czyMozliwyRuchPionka(gracze, kolejka, i)) {
                    return i;
    }}}
    return -1;
}

bool czyMozliwyRuchPionka (Gracz * gracze, Kolejka * kolejka, int pionek) {
    int pozycja = polePionka(gracz, pionek);
    if (pozycja <= 43 && pozycja + kostka > 43)
        return 0;
    if (pozycja > 43) {
        for (int i=1; i<=4; i++) {
            if ( polePionka(gracz, i) == 0 )
                return 0;
    }}
    for (int i=1; i<=4; i++) {
        if (pozycja+kostka == polePionka(gracz, i) )
                return 0;
    }
    return 1;
}

bool czyPrzeciwnikNaCelu (Gracz * gracze, Kolejka * kolejka, int pozycja) {
    if (zawartPola(gracz, pozycja+kostka ) != 0 ) {
        bool przeciwnik = 1;
            for(int x=1; x<=4; x++) {
                if (polePionka(gracz, x) == pozycja + kostka) {
                    przeciwnik = 0; break;
                }
            }
            if (przeciwnik == 1)
                return 1;
    }
    return 0;
}

bool czyPrzeciwnikPrzedCelem (Gracz * gracze, Kolejka * kolejka, int pozycja) {
    for (int i=1; i<kostka; i++) {
        if (zawartPola (gracz, pozycja + i)  !=  0 ) {
            bool przeciwnik = 1;
            for(int x=1; x<=4; x++) {
                if (polePionka(gracz, x) == pozycja + i) {
                    przeciwnik = 0; break;
                }
            }
            if (przeciwnik == 1)
                return 1;
        }
    }
    return 0;
}

bool czyPrzeciwnikZTylu (Gracz * gracze, Kolejka * kolejka, int pozycja) {
    for (int i=0; i<6; i++) {
        if (pozycja == 0)
            pozycja = 39;
        else pozycja--;

        if (zawartPola (gracz, pozycja)  !=  0 ) {
            bool przeciwnik = 1;
            for(int x=1; x<=4; x++) {
                if (polePionka(gracz, x) == pozycja + i) {
                    przeciwnik = 0; break;
                }
            }
            if (przeciwnik == 1)
                return 1;
        }
    }
    return 0;
}
