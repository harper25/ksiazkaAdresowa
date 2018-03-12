#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <cstdlib>
#include <vector>
using namespace std;

struct Uzytkownik
{
    int id;
    string nazwa, haslo;
};

int rejestracja(Uzytkownik uzytkownicy[], int iloscUzytkownikow)
{
    string nazwa, haslo;
    cout << "Podaj nazwe uzytkownika: ";
    cin >> nazwa;
    int i = 0;
    while (i<iloscUzytkownikow)
    {
        if (uzytkownicy[i].nazwa == nazwa)
        {
            cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
            cin >> nazwa;
            i = 0;
        }
        else
        {
            i++;
        }
    }
    cout << "Podaj haslo: ";
    cin >> haslo;
    uzytkownicy[iloscUzytkownikow].nazwa = nazwa;
    uzytkownicy[iloscUzytkownikow].haslo = haslo;
    uzytkownicy[iloscUzytkownikow].id = iloscUzytkownikow+1; // id liczone od 1
    cout << "Konto zalozone" << endl;
    Sleep(1000);
    return iloscUzytkownikow+1;
}

int logowanie(Uzytkownik uzytkownicy[], int iloscUzytkownikow)
{
    string nazwa, haslo;
    cout << "Podaj nazwe uzytkownika: ";
    cin >> nazwa;
    int i = 0;
    while(i<iloscUzytkownikow)
    {
        if (uzytkownicy[i].nazwa == nazwa)
        {
            for (int proby=0; proby<3; proby++)
            {
                cout << "Podaj haslo. Pozostalo prob " << 3-proby << ": ";
                cin >> haslo;
                if (uzytkownicy[i].haslo == haslo)
                {
                    cout << "Zalogowales sie." << endl;
                    Sleep(1000);
                    return uzytkownicy[i].id;
                }
            }
            cout << "Podales 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba" << endl;
            Sleep(1000);
            return 0;
        }
        i++;
    }
    cout << "Nie ma takiego uzytkownika" << endl;
    Sleep(1000);
    return 0;
}

void zmianaHasla(Uzytkownik uzytkownicy[], int iloscUzytkownikow, int idZalogowanegoUzytkownika)
{
    string haslo;
    cout << "Podaj nowe haslo: ";
    cin >> haslo;
    // po co tak to nie wiem...
    for (int i=0; i<iloscUzytkownikow; i++)
    {
        if (uzytkownicy[i].id == idZalogowanegoUzytkownika)
        {
            uzytkownicy[i].haslo = haslo;
            cout << "Haslo zostalo zmienione" << endl;
            Sleep(1500);
        }
    }
}




struct Kontakt
{
    int id;
    string imie, nazwisko, adres, numerTelefonu, email;
};

void zaktualizujPlikZDanymi(vector <Kontakt> &znajomi)
{
    fstream daneKsiazkiAdresowej;
    daneKsiazkiAdresowej.open("ksiazkaAdresowaDane.txt", ios::out);
    int liczbaZnajomych = znajomi.size();

    for (int i = 0; i < liczbaZnajomych; i++)
    {
        daneKsiazkiAdresowej << znajomi[i].id << "|";
        daneKsiazkiAdresowej << znajomi[i].imie << "|";
        daneKsiazkiAdresowej << znajomi[i].nazwisko << "|";
        daneKsiazkiAdresowej << znajomi[i].numerTelefonu << "|";
        daneKsiazkiAdresowej << znajomi[i].email << "|";
        daneKsiazkiAdresowej << znajomi[i].adres <<  "|" << endl;
    }
    daneKsiazkiAdresowej.close();
}


void wyswietlMenuGlowne()
{
    system("cls");
    cout << "1. Dodaj znajomego" << endl;
    cout << "2. Wyszukaj znajomego (wpisz imie)" << endl;
    cout << "3. Wyszukaj znajomego (wpisz nazwisko)" << endl;
    cout << "4. Zmodyfikuj znajomego" << endl;
    cout << "5. Usun znajomego" << endl;
    cout << "6. Wyswietl wszystkich znajomych" << endl;
    cout << "7. Zmiana hasla" << endl;
    cout << "8. Wylogowanie" << endl << endl;
}

void wyswietlKomunikatPowrotMenuGlowne()
{
    cout << "Wcisnij dowolny przycisk, aby wrocic do glownego menu...";
    getch();
}

void wyswietlMenuWprowadzaniaZmian()
{
    cout << "1. Wyswietl wszystkie kontakty i wybierz znajomego" << endl;
    cout << "2. Wyszukaj znajomego po imieniu" << endl;
    cout << "3. Wyszukaj znajomego po nazwisku" << endl;
    cout << "4. Powrot do menu glownego" << endl;
    cout << endl << "Wybor: ";
}

int znajdzWolneID(vector <Kontakt> &znajomi)
{
    int sprawdzaneID = 1;
    int liczbaZnajomych = znajomi.size();
    if (liczbaZnajomych != 0)
    {
        int i = 0;
        while(i < liczbaZnajomych)
        {
            if (znajomi[i].id == sprawdzaneID)
            {
                sprawdzaneID++;
                i = 0;
            }
            else
            {
                i++;
            }
        }
    }
    return sprawdzaneID;
}

void dodajZnajomego(vector <Kontakt> &znajomi)
{
    system("cls");
    Kontakt nowyZnajomy;
    nowyZnajomy.id = znajdzWolneID(znajomi);

    cout << "Podaj imie: ";
    cin >> nowyZnajomy.imie;
    cout << "Podaj nazwisko: ";
    cin >> nowyZnajomy.nazwisko;
    cout << "Podaj nr telefonu: ";
    cin.sync();
    getline(cin, nowyZnajomy.numerTelefonu);
    cout << "Podaj e-mail: ";
    cin >> nowyZnajomy.email;
    cout << "Podaj adres: ";
    cin.sync();
    getline(cin, nowyZnajomy.adres);

    znajomi.push_back(nowyZnajomy);

    cout << "Pomyslnie dodano do listy kontaktow!";
    Sleep(1000);
}

void pobierzDaneJednegoZnajomego(string &linia, Kontakt &nowyZajomy)
{
    string separator = "|";
    string atrybutZnajomego;
    int staraPozycjaSeparatora = -1;
    int nowaPozycjaSeparatora = linia.find(separator, 0);
    int numerAtrybutuZnajomego = 0;

    while(nowaPozycjaSeparatora != string::npos)
    {
        numerAtrybutuZnajomego++;
        atrybutZnajomego = linia.substr(staraPozycjaSeparatora + 1,nowaPozycjaSeparatora - staraPozycjaSeparatora - 1);

        switch(numerAtrybutuZnajomego)
        {
        case 1:
            nowyZajomy.id = atoi(atrybutZnajomego.c_str());
            break;
        case 2:
            nowyZajomy.imie = atrybutZnajomego;
            break;
        case 3:
            nowyZajomy.nazwisko = atrybutZnajomego;
            break;
        case 4:
            nowyZajomy.numerTelefonu = atrybutZnajomego;
            break;
        case 5:
            nowyZajomy.email = atrybutZnajomego;
            break;
        case 6:
            nowyZajomy.adres = atrybutZnajomego;
            break;
        }
        staraPozycjaSeparatora = nowaPozycjaSeparatora;
        nowaPozycjaSeparatora = linia.find(separator,staraPozycjaSeparatora+1);
    }
}

void wczytajZnajomychZPliku(vector <Kontakt> &znajomi)
{
    fstream daneKsiazkiAdresowej;
    string linia;
    Kontakt nowyZajomy;

    daneKsiazkiAdresowej.open("ksiazkaAdresowaDane.txt",ios::in);

    if (daneKsiazkiAdresowej.good() == false)
    {
        cout << "Nie udalo sie wczytac danych kontaktowych!" << endl;
        wyswietlKomunikatPowrotMenuGlowne();
    }
    else
    {
        cout << "Wczytywanie znajomych. Prosze czekac..." << endl;
        while(getline(daneKsiazkiAdresowej,linia))
        {
            pobierzDaneJednegoZnajomego(linia, nowyZajomy);
            znajomi.push_back(nowyZajomy);
        }
        daneKsiazkiAdresowej.close();
        cout << "Wczytano dane kontaktowe!" << endl;
        Sleep(1000);
    }
}

void wypiszZnajomego(const vector <Kontakt> &znajomi, int ktoryZnajomy)
{
    cout << znajomi.at(ktoryZnajomy).imie << " " << znajomi.at(ktoryZnajomy).nazwisko << endl;
    cout << "Numer telefonu: " << znajomi.at(ktoryZnajomy).numerTelefonu << endl;
    cout << "Adres e-mail: " << znajomi.at(ktoryZnajomy).email << endl;
    cout << "Adres: " << znajomi.at(ktoryZnajomy).adres << endl << endl;
}

void wypiszWszystkichZnajomych(vector <Kontakt> &znajomi, vector <int> &listaID)
{
    if (znajomi.size() == 0)
    {
        cout << "Nie ma zapisanych znajomych!" << endl;
        Sleep(1000);
        return;
    }

    system("cls");
    int liczbaZnajomych = znajomi.size();

    for (int i = 0; i < liczbaZnajomych; i++)
    {
        cout << i + 1 << ". ";
        wypiszZnajomego(znajomi, i);
        listaID.push_back(znajomi[i].id);
    }
}

void wyszukajZnajomegoPoImieniu(vector <Kontakt> &znajomi, vector <int> &listaID)
{
    if (znajomi.size() == 0)
    {
        cout << "Nie ma zapisanych znajomych!" << endl;
        Sleep(1000);
        return;
    }

    system("cls");
    string imie;
    int liczbaZnajomych = znajomi.size();
    int liczbaPasujacychZnajomych = 0;
    cout << "Podaj imie znajomego: ";
    cin >> imie;
    cout << endl;

    for (int i = 0; i < liczbaZnajomych; i++)
    {
        if (znajomi[i].imie == imie)
        {
            liczbaPasujacychZnajomych++;
            cout << liczbaPasujacychZnajomych << ". ";
            wypiszZnajomego(znajomi, i);
            listaID.push_back(znajomi[i].id);
        }
    }
    cout << "Koniec wyszukiwania. Znaleziono znajomych: " << liczbaPasujacychZnajomych << endl;
}

void wyszukajZnajomegoPoNazwisku(vector <Kontakt> &znajomi, vector <int> &listaID)
{
    if (znajomi.size() == 0)
    {
        cout << "Nie ma zapisanych znajomych!" << endl;
        Sleep(1000);
        return;
    }

    system("cls");
    string nazwisko;
    int liczbaZnajomych = znajomi.size();
    int liczbaPasujacychZnajomych = 0;
    cout << "Podaj nazwisko znajomego: ";
    cin >> nazwisko;
    cout << endl;

    for (int i = 0; i < liczbaZnajomych; i++)
    {
        if (znajomi[i].nazwisko == nazwisko)
        {
            liczbaPasujacychZnajomych++;
            cout << liczbaPasujacychZnajomych << ". ";
            wypiszZnajomego(znajomi, i);
            listaID.push_back(znajomi[i].id);
        }
    }
    cout << "Koniec wyszukiwania. Znaleziono znajomych: " << liczbaPasujacychZnajomych << endl;
}

void wpiszNoweDaneZnajomego(vector <Kontakt> &znajomi, int modyfikowaneID)
{
    char czyZmianaAtrybutu;
    int numerZnajomego;

    int liczbaZnajomych = znajomi.size();
    for (int i = 0; i < liczbaZnajomych; i++)
    {
        if (znajomi[i].id == modyfikowaneID)
        {
            numerZnajomego = i;
            break;
        }
    }


    cout << "Zmien imie (1 - tak, 0 - nie): ";
    cin >> czyZmianaAtrybutu;
    if (czyZmianaAtrybutu == '1')
    {
        cout << "Podaj nowe imie: ";
        cin >> znajomi[numerZnajomego].imie;
    }
    cout << "Zmien nazwisko (1 - tak, 0 - nie): ";
    cin >> czyZmianaAtrybutu;
    if (czyZmianaAtrybutu == '1')
    {
        cout << "Podaj nowe nazwisko: ";
        cin >> znajomi[numerZnajomego].nazwisko;
    }
    cout << "Zmien numer telefonu (1 - tak, 0 - nie): ";
    cin >> czyZmianaAtrybutu;
    if (czyZmianaAtrybutu == '1')
    {
        cout << "Podaj nowy numer telefonu: ";
        cin.sync();
        getline(cin,znajomi[numerZnajomego].numerTelefonu);
    }
    cout << "Zmien adres email (1 - tak, 0 - nie): ";
    cin >> czyZmianaAtrybutu;
    if (czyZmianaAtrybutu == '1')
    {
        cout << "Podaj nowy adres email: ";
        cin >> znajomi[numerZnajomego].email;
    }
    cout << "Zmien adres (1 - tak, 0 - nie): ";
    cin >> czyZmianaAtrybutu;
    if (czyZmianaAtrybutu == '1')
    {
        cout << "Podaj nowy adres: ";
        cin.sync();
        getline(cin,znajomi[numerZnajomego].adres);
    }
}

int wskazZnajomego()
{
    int numerWybranegoUzytkownika;
    cout << "Podaj numer znajomego (0 - powrot do menu): ";
    cin >> numerWybranegoUzytkownika;
    return numerWybranegoUzytkownika;
}

bool okreslCzyWskazanyNumerZnajomegoJestPoprawny(vector <int> &listaID, int numerUzytkownikaDoZmodyfikowania)
{
    if ((numerUzytkownikaDoZmodyfikowania > listaID.size()) || (numerUzytkownikaDoZmodyfikowania < 0))
    {
        return false;
    }
    else
    {
        return true;
    }
}

void zmodyfikujZnajomego(vector <Kontakt> &znajomi, vector <int> &listaID)
{
    listaID.clear();
    char wyborUzytkownika;
    int modyfikowaneID, numerUzytkownikaDoZmodyfikowania;
    bool czyPoprawnyNumer;

    if (znajomi.size() == 0)
    {
        cout << "Nie ma zapisanych znajomych!" << endl;
        Sleep(1000);
        return;
    }

    system("cls");
    cout << "Wybierz metode wyszukiwania znajomego do modyfikacji:" << endl;
    wyswietlMenuWprowadzaniaZmian();
    cin >> wyborUzytkownika;

    switch (wyborUzytkownika)
    {
    case '1':
        wypiszWszystkichZnajomych(znajomi, listaID);
        break;
    case '2':
        wyszukajZnajomegoPoImieniu(znajomi, listaID);
        break;
    case '3':
        wyszukajZnajomegoPoNazwisku(znajomi, listaID);
        break;
    case '4':
        return;
    default:
        cout << "Nieprawidlowy wybor!" << endl;
        wyswietlKomunikatPowrotMenuGlowne();
        return;
    }

    if (listaID.empty())
    {
        cout << "Nie znaleziono zadnego znajomego!" << endl;
        wyswietlKomunikatPowrotMenuGlowne();
        return;
    }

    numerUzytkownikaDoZmodyfikowania = wskazZnajomego();
    czyPoprawnyNumer = okreslCzyWskazanyNumerZnajomegoJestPoprawny(listaID, numerUzytkownikaDoZmodyfikowania);

    if (czyPoprawnyNumer ==  true)
    {
        if (numerUzytkownikaDoZmodyfikowania == 0)
        {
            return;
        }
        else
        {
            modyfikowaneID = listaID[numerUzytkownikaDoZmodyfikowania - 1];
            wpiszNoweDaneZnajomego(znajomi, modyfikowaneID);
            cout << "Zakonczono modyfikacje!" << endl << endl;
        }
    }
    else
    {
        cout << "Nieprawidlowy wybor!" << endl << endl;
    }
    wyswietlKomunikatPowrotMenuGlowne();
}

void usunZnajomegoPoID(vector <Kontakt> &znajomi, int usuwaneID)
{
    int liczbaZnajomych = znajomi.size();
    for (int i = 0; i < liczbaZnajomych; i++)
    {
        if (znajomi[i].id == usuwaneID)
        {
            znajomi.erase(znajomi.begin() + i);
            break;
        }
    }
}

void usunZnajomego(vector <Kontakt> &znajomi, vector <int> &listaID)
{
    listaID.clear();
    int usuwaneID, numerUzytkownikaDoUsuniecia;
    char wyborUzytkownika;
    bool czyPoprawnyNumer;

    if (znajomi.size() == 0)
    {
        cout << "Nie ma zapisanych znajomych!" << endl;
        Sleep(1000);
        return;
    }

    system("cls");
    cout << "Wybierz metode wyszukiwania znajomego do usuniecia:" << endl;
    wyswietlMenuWprowadzaniaZmian();
    cin >> wyborUzytkownika;

    switch (wyborUzytkownika)
    {
    case '1':
        wypiszWszystkichZnajomych(znajomi, listaID);
        break;
    case '2':
        wyszukajZnajomegoPoImieniu(znajomi, listaID);
        break;
    case '3':
        wyszukajZnajomegoPoNazwisku(znajomi, listaID);
        break;
    case '4':
        return;
    default:
        cout << "Nieprawidlowy wybor!" << endl;
        wyswietlKomunikatPowrotMenuGlowne();
        return;
    }

    if (listaID.empty())
    {
        cout << "Nie znaleziono zadnego znajomego!" << endl;
        wyswietlKomunikatPowrotMenuGlowne();
        return;
    }

    numerUzytkownikaDoUsuniecia = wskazZnajomego();
    czyPoprawnyNumer = okreslCzyWskazanyNumerZnajomegoJestPoprawny(listaID, numerUzytkownikaDoUsuniecia);

    if (czyPoprawnyNumer ==  true)
    {
        if (numerUzytkownikaDoUsuniecia == 0)
        {
            return;
        }
        else
        {
            usuwaneID = listaID[numerUzytkownikaDoUsuniecia - 1];
            usunZnajomegoPoID(znajomi, usuwaneID);
            cout << "Usunieto znajomego!" << endl << endl;;
        }
    }
    else
    {
        cout << "Nieprawidlowy wybor!" << endl << endl;;
    }
    wyswietlKomunikatPowrotMenuGlowne();
}

int main()
{
    Uzytkownik uzytkownicy[100];
//    vector <Uzytkownik> uzytkownicy;
    int idZalogowanegoUzytkownika = 0;
    int iloscUzytkownikow = 0;
    vector <Kontakt> znajomi;
    vector <int> listaID;
    char wyborUzytkownika;

    while(1)
    {
        if (idZalogowanegoUzytkownika == 0)
        {
            system("cls");
            cout << "Ksiazka adresowa" << endl;
            cout << "1. Rejestracja" << endl;
            cout << "2. Logowanie" << endl;
            cout << "9. Zakoncz program" << endl;
            cin >> wyborUzytkownika;

            switch (wyborUzytkownika)
            {
            case '1':
                iloscUzytkownikow = rejestracja(uzytkownicy, iloscUzytkownikow);
                // zaktualizujPlikZUzytkownikami(uzytkownicy);
                break;
            case '2':
                idZalogowanegoUzytkownika = logowanie(uzytkownicy, iloscUzytkownikow);
                // zaktualizujPlikZUzytkownikami(uzytkownicy);
                wczytajZnajomychZPliku(znajomi);
                break;
            case '9':
                cout << "Wyjscie z programu!" << endl;
                exit(0);
            default:
                cout << "Nieprawidlowy wybor!" << endl;
            }
        }
        else
        {
            wyswietlMenuGlowne();
            cout << "Wybor: ";
            cin >> wyborUzytkownika;

            switch (wyborUzytkownika)
            {
            case '1':
                dodajZnajomego(znajomi);
                break;
            case '2':
                wyszukajZnajomegoPoImieniu(znajomi, listaID);
                wyswietlKomunikatPowrotMenuGlowne();
                break;
            case '3':
                wyszukajZnajomegoPoNazwisku(znajomi, listaID);
                wyswietlKomunikatPowrotMenuGlowne();
                break;
            case '4':
                zmodyfikujZnajomego(znajomi, listaID);
                zaktualizujPlikZDanymi(znajomi);
                break;
            case '5':
                usunZnajomego(znajomi, listaID);
                zaktualizujPlikZDanymi(znajomi);
                break;
            case '6':
                wypiszWszystkichZnajomych(znajomi, listaID);
                wyswietlKomunikatPowrotMenuGlowne();
                break;
            case '7':
                zmianaHasla(uzytkownicy, iloscUzytkownikow, idZalogowanegoUzytkownika);
                break;
            case '8':
                idZalogowanegoUzytkownika = 0;
                znajomi.clear();
                break;
            default:
                continue;
            }
        }
    }
}
