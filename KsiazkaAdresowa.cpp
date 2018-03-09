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

int znajdzWolneID(vector <Kontakt> &znajomi)
{
    int sprawdzaneID = 1;
    int liczbaZnajomych = znajomi.size();
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

void wypiszZnajomego(const vector <Kontakt> &znajomi, int ktoryZnajomy)
{
//    cout << znajomi[ktoryZnajomy].imie << " " << znajomi[ktoryZnajomy].nazwisko << endl;
//    cout << "Numer telefonu: " << znajomi[ktoryZnajomy].numerTelefonu << endl;
//    cout << "Adres e-mail: " << znajomi[ktoryZnajomy].email << endl;
//    cout << "Adres: " << znajomi[ktoryZnajomy].adres << endl << endl;
    cout << znajomi.at(ktoryZnajomy).imie << " " << znajomi.at(ktoryZnajomy).nazwisko << endl;
    cout << "Numer telefonu: " << znajomi.at(ktoryZnajomy).numerTelefonu << endl;
    cout << "Adres e-mail: " << znajomi.at(ktoryZnajomy).email << endl;
    cout << "Adres: " << znajomi.at(ktoryZnajomy).adres << endl << endl;


}

void wypiszWszystkichZnajomych(vector <Kontakt> &znajomi)
{
    system("cls");
    int liczbaZnajomych = znajomi.size();
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

void wyszukajZnajomegoPoImieniu(vector <Kontakt> &znajomi)
{
    system("cls");
    string imie;
    int liczbaZnajomych = znajomi.size();
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

void wyszukajZnajomegoPoNazwisku(vector <Kontakt> &znajomi)
{
    system("cls");
    string nazwisko;
    int liczbaZnajomych = znajomi.size();
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

void wczytajZnajomychZPliku(vector <Kontakt> &znajomi)
{
    fstream daneKsiazkiAdresowej;
    string linia;
    Kontakt nowyZajomy;
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
                nowyZajomy.id = atoi(linia.c_str());
                break;
            case 2:
                nowyZajomy.imie = linia;
                break;
            case 3:
                nowyZajomy.nazwisko = linia;
                break;
            case 4:
                nowyZajomy.numerTelefonu = linia;
                break;
            case 5:
                nowyZajomy.email = linia;
                break;
            case 6:
                nowyZajomy.adres = linia;
                znajomi.push_back(nowyZajomy);
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
}

int main()
{
    vector <Kontakt> znajomi;
    char wyborUzytkownika;
    wczytajZnajomychZPliku(znajomi);

    while(1)
    {
        wyswietlMenuGlowne();
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
