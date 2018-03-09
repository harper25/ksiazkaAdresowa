#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <cstdlib>
#include <vector>
using namespace std;



struct Kontakt
{
    int id;
    string imie, nazwisko, adres, numerTelefonu, email;
};

void dopiszZnajomegoDoPilku(vector <Kontakt> &znajomi, int ktoryZnajomy)
{
    fstream daneKsiazkiAdresowej;
    daneKsiazkiAdresowej.open("ksiazkaAdresowaDane.txt", ios::out | ios::app);
    daneKsiazkiAdresowej << znajomi[ktoryZnajomy].id << "|";
    daneKsiazkiAdresowej << znajomi[ktoryZnajomy].imie << "|";
    daneKsiazkiAdresowej << znajomi[ktoryZnajomy].nazwisko << "|";
    daneKsiazkiAdresowej << znajomi[ktoryZnajomy].numerTelefonu << "|";
    daneKsiazkiAdresowej << znajomi[ktoryZnajomy].email << "|";
    daneKsiazkiAdresowej << znajomi[ktoryZnajomy].adres <<  "|" << endl;
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
    cout << "9. Zakoncz program" << endl << endl;
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
    int indeksNowegoZnajomego = znajomi.size() - 1;
    dopiszZnajomegoDoPilku(znajomi, indeksNowegoZnajomego);

    cout << "Pomyslnie dodano do listy kontaktow!";
    Sleep(1000);
}


void wczytajZnajomychZPliku(vector <Kontakt> &znajomi)
{
    fstream daneKsiazkiAdresowej;
    string linia, atrybutZajomego;
    Kontakt nowyZajomy;
    int numerAtrybutuZnajomego = 1;
    int staraPozycjaSeparatora, nowaPozycjaSeparatora;
    string separator = "|";

    daneKsiazkiAdresowej.open("ksiazkaAdresowaDane.txt",ios::in);

    if (daneKsiazkiAdresowej.good() == false)
    {
        cout << "Nie udalo sie wczytac danych kontaktowych!" << endl;
        cout << "Wcisnij dowolny przycisk, aby przejsc do glownego menu...";
        getch();
    }
    else
    {
        cout << "Wczytywanie znajomych. Prosze czekac..." << endl;
        while(getline(daneKsiazkiAdresowej,linia))
        {
            // pobierzDaneJednegoZnajomego();

            staraPozycjaSeparatora = -1;
            nowaPozycjaSeparatora = linia.find(separator, 0);
            numerAtrybutuZnajomego = 0;

            while(nowaPozycjaSeparatora != string::npos)
            {
                numerAtrybutuZnajomego++;
                atrybutZajomego = linia.substr(staraPozycjaSeparatora + 1,nowaPozycjaSeparatora - staraPozycjaSeparatora - 1);

                switch(numerAtrybutuZnajomego)
                {
                case 1:
                    nowyZajomy.id = atoi(atrybutZajomego.c_str());
                    break;
                case 2:
                    nowyZajomy.imie = atrybutZajomego;
                    break;
                case 3:
                    nowyZajomy.nazwisko = atrybutZajomego;
                    break;
                case 4:
                    nowyZajomy.numerTelefonu = atrybutZajomego;
                    break;
                case 5:
                    nowyZajomy.email = atrybutZajomego;
                    break;
                case 6:
                    nowyZajomy.adres = atrybutZajomego;
                    znajomi.push_back(nowyZajomy);
                    break;
                }
                staraPozycjaSeparatora = nowaPozycjaSeparatora;
                nowaPozycjaSeparatora = linia.find(separator,staraPozycjaSeparatora+1);
            }
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

void wypiszWszystkichZnajomych(vector <Kontakt> &znajomi)
{
    system("cls");
    int liczbaZnajomych = znajomi.size();
    if (liczbaZnajomych != 0)
    {
        for (int i = 0; i < liczbaZnajomych; i++)
        {
            cout << i + 1 << ". ";
            wypiszZnajomego(znajomi, i);
        }
    }
    else
    {
        cout << "Nie ma zapisanych znajomych!" << endl;
    }
    cout << "Wcisnij dowolny przycisk, aby wrocic do glownego menu...";
    getch();
}

void wyszukajZnajomegoPoImieniu(vector <Kontakt> &znajomi)
{
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
        }
    }
    cout << "Koniec wyszukiwania. Znaleziono znajomych: " << liczbaPasujacychZnajomych << endl;

    cout << "Wcisnij dowolny przycisk, aby wrocic do glownego menu...";
    getch();
}

void wyszukajZnajomegoPoNazwisku(vector <Kontakt> &znajomi)
{
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
        }
    }
    cout << "Koniec wyszukiwania. Znaleziono znajomych: " << liczbaPasujacychZnajomych << endl;
    cout << "Wcisnij dowolny przycisk, aby wrocic do glownego menu...";
    getch();
}

void wypiszWszystkichZnajomych(vector <Kontakt> &znajomi, vector <int> &listaID)
{
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
        cout << endl << "Podaj nowe nazwisko: ";
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

void zmodyfikujZnajomego(vector <Kontakt> &znajomi)
{
    vector <int> listaID;
    char wyborUzytkownika;
    int modyfikowaneID, numerUzytkownikaDoZmodyfikowania;

    if (znajomi.size() == 0)
    {
        cout << "Nie ma zapisanych znajomych!" << endl;
        Sleep(1000);
    }
    else
    {
        system("cls");
        cout << "1. Wyswietl wszystkich znajomych i wybierz znajomego do modyfikacji" << endl;
        cout << "2. Wyszukaj znajomego do modyfikacji po imieniu" << endl;
        cout << "3. Wyszukaj znajomego do modyfikacji po nazwisku" << endl;
        cout << "4. Powrot do menu glownego" << endl;
        cout << endl << "Wybor: ";
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
            Sleep(1000);
            return;
        }

        if (!listaID.empty())
        {
            numerUzytkownikaDoZmodyfikowania = wskazZnajomego();

            if ((numerUzytkownikaDoZmodyfikowania <= listaID.size()) && (numerUzytkownikaDoZmodyfikowania > 0))
            {
                modyfikowaneID = listaID[numerUzytkownikaDoZmodyfikowania - 1];
                wpiszNoweDaneZnajomego(znajomi, modyfikowaneID);
                cout << "Zmodyfikowano dane znajomego!" << endl;
                Sleep(1000);
            }
            else if (numerUzytkownikaDoZmodyfikowania == 0)
            {
                cout << "Wybrano powrot do menu glownego." << endl;
                Sleep(1000);
            }
            else
            {
                cout << "Nieprawidlowy wybor!" << endl;
                Sleep(1000);
            }
        }
        else
        {
            cout << "Wcisnij dowolny przycisk, aby wrocic do glownego menu...";
            getch();
        }
    }
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

void usunZnajomego(vector <Kontakt> &znajomi)
{
    vector <int> listaID;
    char wyborUzytkownika;
    int usuwaneID, numerUzytkownikaDoUsuniecia;

    if (znajomi.size() == 0)
    {
        cout << "Nie ma zapisanych znajomych!" << endl;
        Sleep(1000);
    }
    else
    {
        system("cls");
        cout << "1. Wyswietl wszystkich znajomych i wybierz znajomego do usuniecia" << endl;
        cout << "2. Wyszukaj znajomego do usuniecia po imieniu" << endl;
        cout << "3. Wyszukaj znajomego do usuniecia po nazwisku" << endl;
        cout << "4. Powrot do menu glownego" << endl;
        cout << endl << "Wybor: ";
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
            Sleep(1000);
            return;
        }

        if (!listaID.empty())
        {
            numerUzytkownikaDoUsuniecia = wskazZnajomego();

            if ((numerUzytkownikaDoUsuniecia <= listaID.size()) && (numerUzytkownikaDoUsuniecia > 0))
            {
                usuwaneID = listaID[numerUzytkownikaDoUsuniecia - 1];
                usunZnajomegoPoID(znajomi, usuwaneID);
                cout << "Usunieto znajomego!" << endl;
                Sleep(1000);
            }
            else if (numerUzytkownikaDoUsuniecia == 0)
            {
                cout << "Wybrano powrot do menu glownego." << endl;
                Sleep(1000);
            }
            else
            {
                cout << "Nieprawidlowy wybor!" << endl;
                Sleep(1000);
            }
        }
        else
        {
            cout << "Wcisnij dowolny przycisk, aby wrocic do glownego menu...";
            getch();
        }
    }
}

int main()
{
    vector <Kontakt> znajomi;
    char wyborUzytkownika;
    wczytajZnajomychZPliku(znajomi);

    while(1)
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
            wyszukajZnajomegoPoImieniu(znajomi);
            break;
        case '3':
            wyszukajZnajomegoPoNazwisku(znajomi);
            break;
        case '4':
            zmodyfikujZnajomego(znajomi);
            break;
        case '5':
            usunZnajomego(znajomi);
            break;
        case '6':
            wypiszWszystkichZnajomych(znajomi);
            break;
        case '9':
            cout << "Wyjscie z programu!" << endl;
            exit(0);
        default:
            continue;
        }
    }
    return 0;
}
