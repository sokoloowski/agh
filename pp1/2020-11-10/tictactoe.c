#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//kolko krzyzyk

int tablica[3][3]; // plansza globalna
int mv = 0;        // zmienna gracza,  0 - X, 1 - O
int xPos, yPos;    // potrzebne do sprawnosci "AI", wartosci 1-3 dla komorek 0-2
int aiLv = 2;      // poziom "zaawansowania" sztucznego gracza

void wyswietl(int cont); // pre-definicja funkcji

char gracz(int a)
{ // definiuje gracza na podstawie liczby, 0 - X, 1 - O
    if (a == 0)
    {
        return 'X';
    }
    else
    {
        return 'O';
    }
}

int sprawdzremis()
{
    int draw = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (tablica[i][j] != 2)
            {
                draw++;
            }
        }
    }
    return draw;
}

int sprawdz()
{ // 0 - kontynuuj, 1 - koniec
    for (int a = 0; a < 2; a++)
    { // Sprawdzanie wszystkich 8 mozliwosci wygranych i 1 remisu
        if (
            (tablica[0][0] == a && tablica[1][0] == a && tablica[2][0] == a) ||
            (tablica[0][1] == a && tablica[1][1] == a && tablica[2][1] == a) ||
            (tablica[0][2] == a && tablica[1][2] == a && tablica[2][2] == a) ||
            (tablica[0][0] == a && tablica[0][1] == a && tablica[0][2] == a) ||
            (tablica[1][0] == a && tablica[1][1] == a && tablica[1][2] == a) ||
            (tablica[2][0] == a && tablica[2][1] == a && tablica[2][2] == a) ||
            (tablica[0][0] == a && tablica[1][1] == a && tablica[2][2] == a) ||
            (tablica[0][2] == a && tablica[1][1] == a && tablica[2][0] == a))
        {
            printf("\n\n\tWygrana! Gracz %c wygrywa mecz!\n\n", gracz(a));
            return 1;
        }
    }
    if (sprawdzremis() == 9)
    {
        printf("\n\n\t\tREMIS! Koniec gry! \n\n");
        return 1;
    }
    return 0;
}

char zwroc(int x, int y)
{ // zwraca zajete komorki tablicy
    char zwr;
    if (tablica[x][y] == 2)
    {
        zwr = '_';
    }
    else if (tablica[x][y] == 0)
    {
        zwr = 'X';
    }
    else if (tablica[x][y] == 1)
    {
        zwr = 'O';
    }
    else
    {
        zwr = '!'; // Error inform
        printf("!!! ERROR IN %d %d !!!\n", x, y);
    }
    return zwr;
}

void aiBlock()
{ // Blokowanie przeciwnika
    short int a = 0;
    short int b = 2;
    if (tablica[0][0] == a && tablica[1][0] == a && tablica[2][0] == b)
    { // ""!
        xPos = 3;
        yPos = 1;
    }
    if (tablica[0][1] == a && tablica[1][1] == a && tablica[2][1] == b)
    { // --!
        xPos = 3;
        yPos = 2;
    }
    if (tablica[0][2] == a && tablica[1][2] == a && tablica[2][2] == b)
    { // __!
        xPos = 3;
        yPos = 3;
    }
    if (tablica[0][0] == a && tablica[0][1] == a && tablica[0][2] == b)
    { // |-- !
        xPos = 1;
        yPos = 3;
    }
    if (tablica[1][0] == a && tablica[1][1] == a && tablica[1][2] == b)
    { // -|- !
        xPos = 2;
        yPos = 3;
    }
    if (tablica[2][0] == a && tablica[2][1] == a && tablica[2][2] == b)
    { // --| !
        xPos = 3;
        yPos = 3;
    }
    if (tablica[0][0] == a && tablica[1][1] == a && tablica[2][2] == b)
    { // "-_ !
        xPos = 3;
        yPos = 3;
    }
    if (tablica[0][2] == a && tablica[1][1] == a && tablica[2][0] == b)
    { // _-" !
        xPos = 3;
        yPos = 1;
    }
    if (tablica[0][0] == a && tablica[1][0] == b && tablica[2][0] == a)
    { // "!"
        xPos = 2;
        yPos = 1;
    }
    if (tablica[0][1] == a && tablica[1][1] == b && tablica[2][1] == a)
    { // -!-
        xPos = 2;
        yPos = 2;
    }
    if (tablica[0][2] == a && tablica[1][2] == b && tablica[2][2] == a)
    { // _!_
        xPos = 2;
        yPos = 3;
    }
    if (tablica[0][0] == a && tablica[0][1] == b && tablica[0][2] == a)
    { // |-- !
        xPos = 1;
        yPos = 2;
    }
    if (tablica[1][0] == a && tablica[1][1] == b && tablica[1][2] == a)
    { // -|- !
        xPos = 2;
        yPos = 2;
    }
    if (tablica[2][0] == a && tablica[2][1] == b && tablica[2][2] == a)
    { // --| !
        xPos = 3;
        yPos = 2;
    }
    if (tablica[0][0] == a && tablica[1][1] == b && tablica[2][2] == a)
    { // "-_ !
        xPos = 2;
        yPos = 2;
    }
    if (tablica[0][2] == a && tablica[1][1] == b && tablica[2][0] == a)
    { // _-" !
        xPos = 2;
        yPos = 2;
    }
    if (tablica[0][0] == b && tablica[1][0] == a && tablica[2][0] == a)
    { // !""
        xPos = 1;
        yPos = 1;
    }
    if (tablica[0][1] == b && tablica[1][1] == a && tablica[2][1] == a)
    { // !--
        xPos = 1;
        yPos = 2;
    }
    if (tablica[0][2] == b && tablica[1][2] == a && tablica[2][2] == a)
    { // !__
        xPos = 1;
        yPos = 3;
    }
    if (tablica[0][0] == b && tablica[0][1] == a && tablica[0][2] == a)
    { // |-- !
        xPos = 1;
        yPos = 1;
    }
    if (tablica[1][0] == b && tablica[1][1] == a && tablica[1][2] == a)
    { // -|- !
        xPos = 2;
        yPos = 1;
    }
    if (tablica[2][0] == b && tablica[2][1] == a && tablica[2][2] == a)
    { // --| !
        xPos = 3;
        yPos = 1;
    }
    if (tablica[0][0] == b && tablica[1][1] == a && tablica[2][2] == a)
    { // "-_ !
        xPos = 1;
        yPos = 1;
    }
    if (tablica[0][2] == b && tablica[1][1] == a && tablica[2][0] == a)
    { // _-" !
        xPos = 1;
        yPos = 3;
    }
    //    cout << " ===DEBUG=== Blocking on X: " << xPos << " Y: " << yPos<< "\n\n";
    //    system("pause");
}

void aiAttack()
{ // Zakonczenie linii
    short int a = 1;
    short int b = 2;
    if (tablica[0][0] == a && tablica[1][0] == a && tablica[2][0] == b)
    { // ""!
        xPos = 3;
        yPos = 1;
    }
    if (tablica[0][1] == a && tablica[1][1] == a && tablica[2][1] == b)
    { // --!
        xPos = 3;
        yPos = 2;
    }
    if (tablica[0][2] == a && tablica[1][2] == a && tablica[2][2] == b)
    { // __!
        xPos = 3;
        yPos = 3;
    }
    if (tablica[0][0] == a && tablica[0][1] == a && tablica[0][2] == b)
    { // |-- !
        xPos = 1;
        yPos = 3;
    }
    if (tablica[1][0] == a && tablica[1][1] == a && tablica[1][2] == b)
    { // -|- !
        xPos = 2;
        yPos = 3;
    }
    if (tablica[2][0] == a && tablica[2][1] == a && tablica[2][2] == b)
    { // --| !
        xPos = 3;
        yPos = 3;
    }
    if (tablica[0][0] == a && tablica[1][1] == a && tablica[2][2] == b)
    { // "-_ !
        xPos = 3;
        yPos = 3;
    }
    if (tablica[0][2] == a && tablica[1][1] == a && tablica[2][0] == b)
    { // _-" !
        xPos = 3;
        yPos = 1;
    }
    if (tablica[0][0] == a && tablica[1][0] == b && tablica[2][0] == a)
    { // "!"
        xPos = 2;
        yPos = 1;
    }
    if (tablica[0][1] == a && tablica[1][1] == b && tablica[2][1] == a)
    { // -!-
        xPos = 2;
        yPos = 2;
    }
    if (tablica[0][2] == a && tablica[1][2] == b && tablica[2][2] == a)
    { // _!_
        xPos = 2;
        yPos = 3;
    }
    if (tablica[0][0] == a && tablica[0][1] == b && tablica[0][2] == a)
    { // |-- !
        xPos = 1;
        yPos = 2;
    }
    if (tablica[1][0] == a && tablica[1][1] == b && tablica[1][2] == a)
    { // -|- !
        xPos = 2;
        yPos = 2;
    }
    if (tablica[2][0] == a && tablica[2][1] == b && tablica[2][2] == a)
    { // --| !
        xPos = 3;
        yPos = 2;
    }
    if (tablica[0][0] == a && tablica[1][1] == b && tablica[2][2] == a)
    { // "-_ !
        xPos = 2;
        yPos = 2;
    }
    if (tablica[0][2] == a && tablica[1][1] == b && tablica[2][0] == a)
    { // _-" !
        xPos = 2;
        yPos = 2;
    }
    if (tablica[0][0] == b && tablica[1][0] == a && tablica[2][0] == a)
    { // !""
        xPos = 1;
        yPos = 1;
    }
    if (tablica[0][1] == b && tablica[1][1] == a && tablica[2][1] == a)
    { // !--
        xPos = 1;
        yPos = 2;
    }
    if (tablica[0][2] == b && tablica[1][2] == a && tablica[2][2] == a)
    { // !__
        xPos = 1;
        yPos = 3;
    }
    if (tablica[0][0] == b && tablica[0][1] == a && tablica[0][2] == a)
    { // |-- !
        xPos = 1;
        yPos = 1;
    }
    if (tablica[1][0] == b && tablica[1][1] == a && tablica[1][2] == a)
    { // -|- !
        xPos = 2;
        yPos = 1;
    }
    if (tablica[2][0] == b && tablica[2][1] == a && tablica[2][2] == a)
    { // --| !
        xPos = 3;
        yPos = 1;
    }
    if (tablica[0][0] == b && tablica[1][1] == a && tablica[2][2] == a)
    { // "-_ !
        xPos = 1;
        yPos = 1;
    }
    if (tablica[0][2] == b && tablica[1][1] == a && tablica[2][0] == a)
    { // _-" !
        xPos = 1;
        yPos = 3;
    }
    //    cout << " ===DEBUG=== Attacking on X: " << xPos << " Y: " << yPos<< "\n\n";
    //    system("pause");
}

void ruchAi()
{ // kontrola ruchu AI
    srand(time(NULL));
    xPos = 1 + rand() % 3;
    yPos = 1 + rand() % 3;
    int goOn = 0;
    //	system("pause");
    while (goOn == 0)
    {
        if (tablica[xPos - 1][yPos - 1] == 2)
        {
            goOn = 1;
            //			cout << " ===DEBUG=== Goes on" << xPos << yPos << endl;
        }
        else
        {
            xPos = 1 + rand() % 3;
            yPos = 1 + rand() % 3;
            //		cout << " ===DEBUG=== Reassign X Y " << xPos << yPos << endl;
        }
    }
    //	system("pause");
    if (aiLv >= 1)
    {
        aiBlock();
    }
    if (aiLv >= 2)
    {
        aiAttack();
    }
}

void ruch()
{ // obsluga ruchu gracza
    if (mv == 0)
    {
        printf("\n\n\tX\nRuch gracza X.\n\tX\n\n");

        printf("Wybierz pozycje X: \n");
        scanf("%c", xPos);
        printf("Wybierz pozycje Y: \n");
        scanf("%c", yPos);
    }
    else
    {
        printf("\n\n\tO\nRuch gracza O.\n\tO\n\n");
        ruchAi();
    }

    if (tablica[xPos - 1][yPos - 1] == 2)
    {
        tablica[xPos - 1][yPos - 1] = mv;
        mv = 1 - mv;
        if (sprawdz() == 1)
        {
            wyswietl(0);
        }
        else
        {
            wyswietl(1);
        }
    }
    else if (xPos < 1 || xPos > 3 || yPos < 1 || xPos > 3)
    {
        printf("\n\n\nWprowadziles bledna pozycje! Pozycja od 1 do 3!\n");
        wyswietl(2);
    }
    else if (tablica[xPos - 1][yPos - 1] != 2)
    {
        printf("\n\n\nTa pozycja jest zajeta przez %c . Wybierz inna!\n", zwroc(xPos - 1, yPos - 1));
        wyswietl(2);
    }
    else
    {
        printf("\n\n\nCos poszlo nie tak... Jeszcze raz. \n");

        wyswietl(2);
    }
}

void wyswietl(int cont)
{ // wyswietl tablice
    if (cont != 0 && cont != 2)
    {
        // system("clear"); // czyszczenie ekranu
    }
    printf("\t     1   2   3  \n");
    printf("\t   _____________\n");
    printf("\t1  |_%c_|_%c_|_%c_|\n", zwroc(0,0), zwroc(1,0), zwroc(2,0));
    printf("\t2  |_%c_|_%c_|_%c_|\n", zwroc(0,1), zwroc(1,1), zwroc(2,1));
    printf("\t3  |_%c_|_%c_|_%c_|\n", zwroc(0,2), zwroc(1,2), zwroc(2,2));
    printf("\t   \"\"\"\"\"\"\"\"\"\"\"\"\"\n");
    printf("   ^\n   |Y \n     X-->\n");

    if (cont == 0)
    {
        return;
    }
    else
    {
        ruch();
    }
}
void start()
{ // ustaw cala tablice na pusta (2)
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            tablica[i][j] = 2;
        }
    }
    srand(time(NULL));
    mv = rand() % 2;

    wyswietl(1);
}

int main()
{
    int opt;
    printf("Kolko krzyzyk.\n 1 - Start\n 2 - Wyjscie.\n");
    scanf("%d", opt);

    if (opt == 1)
    {
        printf("\n Poziom Bota (0-2): \n");
        scanf("%d", aiLv);
        start();
    }
    else if (opt == 2)
    {
        return 0;
    }
    else
    {
        main();
    }

    printf("\n\tJeszcze raz? (1/0): \n");
    scanf("%d", opt);
    if (opt == 1)
    {
        // system("clear");
        main();
    }
    else
    {
        return 0;
    }
    return 0;
}