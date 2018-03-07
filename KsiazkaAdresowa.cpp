#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <cstdlib>
using namespace std;

struct Kontakt
{
    int id;
    string imie, nazwisko, adres, numerTelefonu, email;
};

void dopiszZnajomegoDoPilku(Kontakt znajomi[], int ktoryZnajomy)
{
    fstream daneKsiazkiAdresowej;
    daneKsiazkiAdresowej.open("ksiazkaAdresowaDane.txt", ios::out | ios::app);
    daneKsiazkiAdresowej << znajomi[ktoryZnajomy].id << endl;
    daneKsiazkiAdresowej << znajomi[ktoryZnajomy].imie << endl;
    daneKsiazkiAdresowej << znajomi[ktoryZnajomy].nazwisko << endl;
    daneKsiazkiAdresowej << znajomi[ktoryZnajomy].numerTelefonu << endl;
    daneKsiazkiAdresowej << znajomi[ktoryZnajomy].email << endl;
    daneKsiazkiAdresowej << znajomi[ktoryZnajomy].adres << endl;
    daneKsiazkiAdresowej.close();
}

void wyswietlMenuGlowne()
{
    system("cls");
    cout << "1. Dodaj znajomego" << endl;
    cout << "2. Wyszukaj znajomego (wpisz imie)" << endl;
    cout << "3. Wyszukaj znajomego (wpisz nazwisko)" << endl;
    cout << "4. Wyswietl wszystkich znajomych" << endl;
    cout << "9. Zakoncz program" << endl << endl;
}

int znajdzWolneID(Kontakt znajomi[], int liczbaZnajomych)
{
    // funkcja z myślą o rozbudowie programu o kasowanie znajomych
    // czyli zwalnianie kluczy ID // można też przechowywać osobną
    // zmienną int ID i inkrementować zawsze o 1 przy dodawaniu znajomych
    int sprawdzaneID = 1;
    if (liczbaZnajomych != 0)
    {
        int i = 0;
        while(i<liczbaZnajomych)
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

void dodajZnajomego(Kontakt znajomi[], int &liczbaZnajomych)
{
    znajomi[liczbaZnajomych].id = znajdzWolneID(znajomi, liczbaZnajomych);

    system("cls");
    cout << "Podaj imie: ";
    cin >> znajomi[liczbaZnajomych].imie;
    cout << "Podaj nazwisko: ";
    cin >> znajomi[liczbaZnajomych].nazwisko;
    cout << "Podaj nr telefonu: ";
    cin.sync();
    getline(cin, znajomi[liczbaZnajomych].numerTelefonu);
    cout << "Podaj e-mail: ";
    cin >> znajomi[liczbaZnajomych].email;
    cout << "Podaj adres: ";
    cin.sync();
    getline(cin, znajomi[liczbaZnajomych].adres);

    dopiszZnajomegoDoPilku(znajomi, liczbaZnajomych);

    liczbaZnajomych += 1;
    cout << "Pomyslnie dodano do listy kontaktow!";
    Sleep(1000);
}

void wypiszZnajomego(Kontakt znajomi[], int ktoryZnajomy)
{
    cout << znajomi[ktoryZnajomy].imie << " " << znajomi[ktoryZnajomy].nazwisko << endl;
    cout << "Numer telefonu: " << znajomi[ktoryZnajomy].numerTelefonu << endl;
    cout << "Adres e-mail: " << znajomi[ktoryZnajomy].email << endl;
    cout << "Adres: " << znajomi[ktoryZnajomy].adres << endl << endl;
}

void wypiszWszystkichZnajomych(Kontakt znajomi[], int liczbaZnajomych)
{
    system("cls");
    if (liczbaZnajomych!=0)
    {
        for (int i=0; i<liczbaZnajomych; i++)
        {
            cout << i+1 << ". ";
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

void wyszukajZnajomegoPoImieniu(Kontakt znajomi[], int liczbaZnajomych)
{
    system("cls");
    string imie;
    int liczbaPasujacychZnajomych = 0;
    cout << "Podaj imie znajomego: ";
    cin >> imie;
    cout << endl;

    for (int i=0; i<liczbaZnajomych; i++)
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

void wyszukajZnajomegoPoNazwisku(Kontakt znajomi[], int liczbaZnajomych)
{
    system("cls");
    string nazwisko;
    int liczbaPasujacychZnajomych = 0;
    cout << "Podaj nazwisko znajomego: ";
    cin >> nazwisko;
    cout << endl;

    for (int i=0; i<liczbaZnajomych; i++)
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

int wczytajZnajomychZPliku(Kontakt znajomi[])
{
    fstream daneKsiazkiAdresowej;
    string linia;
    int numerLinii = 1;
    int liczbaZnajomych = 0;

    daneKsiazkiAdresowej.open("ksiazkaAdresowaDane.txt",ios::in);

    if (daneKsiazkiAdresowej.good()==false)
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
            switch(numerLinii)
            {
            case 1:
                znajomi[liczbaZnajomych].id = atoi(linia.c_str());
                break;
            case 2:
                znajomi[liczbaZnajomych].imie = linia;
                break;
            case 3:
                znajomi[liczbaZnajomych].nazwisko = linia;
                break;
            case 4:
                znajomi[liczbaZnajomych].numerTelefonu = linia;
                break;
            case 5:
                znajomi[liczbaZnajomych].email = linia;
                break;
            case 6:
                znajomi[liczbaZnajomych].adres = linia;
                numerLinii = 0;
                liczbaZnajomych++;
                break;
            }
            numerLinii++;
        }
        daneKsiazkiAdresowej.close();
        cout << "Wczytano dane kontaktowe!" << endl;
        Sleep(1000);
    }
    return liczbaZnajomych;
}

int main()
{
    const int MAX_LICZBA_ZNAJOMYCH = 1000;
    Kontakt znajomi [MAX_LICZBA_ZNAJOMYCH];
    char wyborUzytkownika;
    int liczbaZnajomych = wczytajZnajomychZPliku(znajomi);

    while(1)
    {
        wyswietlMenuGlowne();
        cin >> wyborUzytkownika;

        switch (wyborUzytkownika)
        {
        case '1':
            dodajZnajomego(znajomi, liczbaZnajomych);
            break;
        case '2':
            wyszukajZnajomegoPoImieniu(znajomi, liczbaZnajomych);
            break;
        case '3':
            wyszukajZnajomegoPoNazwisku(znajomi, liczbaZnajomych);
            break;
        case '4':
            wypiszWszystkichZnajomych(znajomi, liczbaZnajomych);
            break;
        case '9':
            exit(0);
        default:
            continue;
        }
    }
    return 0;
}
