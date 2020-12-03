#include <iostream>
#include <string>
#include <stdlib.h>
#include <ctime>

								//kolko krzyzyk
								//dawid szulc

using namespace std;

int tablica[3][3];				// plansza globalna
int mv=0;						// zmienna gracza,  0 - X, 1 - O
int xPos,yPos;					// potrzebne do sprawnosci "AI", wartosci 1-3 dla komorek 0-2
int aiLv = 2;						// poziom "zaawansowania" sztucznego gracza


void wyswietl(int cont); 		// pre-definicja funkcji

string gracz(int a){			// definiuje gracza na podstawie liczby, 0 - X, 1 - O
	if (a == 0) {
		return "X";
	} else {
		return "O";
	}

}

int sprawdzremis(){
	int draw = 0;
	for (int i = 0; i<3; i++){
		for (int j = 0; j<3; j++){
			if (tablica[i][j] != 2){
				draw++;
			}
		}
	}
	return draw;
}

int sprawdz(){	 				// 0 - kontynuuj, 1 - koniec
	for (int a = 0; a <2; a++){		// Sprawdzanie wszystkich 8 mozliwosci wygranych i 1 remisu
		if (tablica[0][0] == a && tablica[1][0] == a && tablica[2][0] == a){ // """
			cout << "\n\n\tWygrana! Gracz " << gracz(a) << " wygrywa mecz!\n\n";	return 1;
		}
		if (tablica[0][1] == a && tablica[1][1] == a && tablica[2][1] == a){ // ---
			cout << "\n\n\tWygrana! Gracz " << gracz(a) << " wygrywa mecz!\n\n";	return 1;
		}
		if (tablica[0][2] == a && tablica[1][2] == a && tablica[2][2] == a){ // ___
			cout << "\n\n\tWygrana! Gracz " << gracz(a) << " wygrywa mecz!\n\n";	return 1;
		}
		if (tablica[0][0] == a && tablica[0][1] == a && tablica[0][2] == a){ // |--
			cout << "\n\n\tWygrana! Gracz " << gracz(a) << " wygrywa mecz!\n\n";	return 1;
		}
		if (tablica[1][0] == a && tablica[1][1] == a && tablica[1][2] == a){ // -|-
			cout << "\n\n\tWygrana! Gracz " << gracz(a) << " wygrywa mecz!\n\n";	return 1;
		}
		if (tablica[2][0] == a && tablica[2][1] == a && tablica[2][2] == a){ // --|
			cout << "\n\n\tWygrana! Gracz " << gracz(a) << " wygrywa mecz!\n\n";	return 1;
		}
		if (tablica[0][0] == a && tablica[1][1] == a && tablica[2][2] == a){ // "-_
			cout << "\n\n\tWygrana! Gracz " << gracz(a) << " wygrywa mecz!\n\n";	return 1;
		}
		if (tablica[0][2] == a && tablica[1][1] == a && tablica[2][0] == a){ // _-"
			cout << "\n\n\tWygrana! Gracz " << gracz(a) << " wygrywa mecz!\n\n";	return 1;
		}

	}
	if (sprawdzremis() == 9){
			cout << "\n\n\t\tREMIS! Koniec gry! \n\n";	return 1;
		}
	return 0;
}


string zwroc(int x, int y){		// zwraca zajete komorki tablicy
	string zwr;
	if (tablica[x][y] == 2){
		zwr = "_";
	} else if (tablica[x][y] == 0){
		zwr = "X";
	} else if (tablica[x][y] == 1){
		zwr = "O";
	} else {
		zwr = "!";				// Error inform
		cout << "!!! ERROR IN "<<x<<" " << y <<" !!!";
	}
	return zwr;

}

void aiBlock(){                 // Blokowanie przeciwnika
    short int a = 0;
    short int b = 2;
    if (tablica[0][0] == a && tablica[1][0] == a && tablica[2][0] == b){ // ""!
        xPos = 3;
        yPos = 1;
    }
    if (tablica[0][1] == a && tablica[1][1] == a && tablica[2][1] == b){ // --!
        xPos = 3;
        yPos = 2;
	}
    if (tablica[0][2] == a && tablica[1][2] == a && tablica[2][2] == b){ // __!
        xPos = 3;
        yPos = 3;
	}
	if (tablica[0][0] == a && tablica[0][1] == a && tablica[0][2] == b){ // |-- !
        xPos = 1;
        yPos = 3;
	}
	if (tablica[1][0] == a && tablica[1][1] == a && tablica[1][2] == b){ // -|- !
        xPos = 2;
        yPos = 3;
	}
	if (tablica[2][0] == a && tablica[2][1] == a && tablica[2][2] == b){ // --| !
        xPos = 3;
        yPos = 3;
	}
	if (tablica[0][0] == a && tablica[1][1] == a && tablica[2][2] == b){ // "-_ !
        xPos = 3;
        yPos = 3;
	}
	if (tablica[0][2] == a && tablica[1][1] == a && tablica[2][0] == b){ // _-" !
        xPos = 3;
        yPos = 1;
    }
    if (tablica[0][0] == a && tablica[1][0] == b && tablica[2][0] == a){ // "!"
        xPos = 2;
        yPos = 1;
    }
    if (tablica[0][1] == a && tablica[1][1] == b && tablica[2][1] == a){ // -!-
        xPos = 2;
        yPos = 2;
	}
    if (tablica[0][2] == a && tablica[1][2] == b && tablica[2][2] == a){ // _!_
        xPos = 2;
        yPos = 3;
	}
	if (tablica[0][0] == a && tablica[0][1] == b && tablica[0][2] == a){ // |-- !
        xPos = 1;
        yPos = 2;
	}
	if (tablica[1][0] == a && tablica[1][1] == b && tablica[1][2] == a){ // -|- !
        xPos = 2;
        yPos = 2;
	}
	if (tablica[2][0] == a && tablica[2][1] == b && tablica[2][2] == a){ // --| !
        xPos = 3;
        yPos = 2;
	}
	if (tablica[0][0] == a && tablica[1][1] == b && tablica[2][2] == a){ // "-_ !
        xPos = 2;
        yPos = 2;
	}
	if (tablica[0][2] == a && tablica[1][1] == b && tablica[2][0] == a){ // _-" !
        xPos = 2;
        yPos = 2;
    }
    if (tablica[0][0] == b && tablica[1][0] == a && tablica[2][0] == a){ // !""
        xPos = 1;
        yPos = 1;
    }
    if (tablica[0][1] == b && tablica[1][1] == a && tablica[2][1] == a){ // !--
        xPos = 1;
        yPos = 2;
	}
    if (tablica[0][2] == b && tablica[1][2] == a && tablica[2][2] == a){ // !__
        xPos = 1;
        yPos = 3;
	}
	if (tablica[0][0] == b && tablica[0][1] == a && tablica[0][2] == a){ // |-- !
        xPos = 1;
        yPos = 1;
	}
	if (tablica[1][0] == b && tablica[1][1] == a && tablica[1][2] == a){ // -|- !
        xPos = 2;
        yPos = 1;
	}
	if (tablica[2][0] == b && tablica[2][1] == a && tablica[2][2] == a){ // --| !
        xPos = 3;
        yPos = 1;
	}
	if (tablica[0][0] == b && tablica[1][1] == a && tablica[2][2] == a){ // "-_ !
        xPos = 1;
        yPos = 1;
	}
	if (tablica[0][2] == b && tablica[1][1] == a && tablica[2][0] == a){ // _-" !
        xPos = 1;
        yPos = 3;
    }
//    cout << " ===DEBUG=== Blocking on X: " << xPos << " Y: " << yPos<< "\n\n";
//    system("pause");
}

void aiAttack(){                 // Zakonczenie linii
    short int a = 1;
    short int b = 2;
    if (tablica[0][0] == a && tablica[1][0] == a && tablica[2][0] == b){ // ""!
        xPos = 3;
        yPos = 1;
    }
    if (tablica[0][1] == a && tablica[1][1] == a && tablica[2][1] == b){ // --!
        xPos = 3;
        yPos = 2;
	}
    if (tablica[0][2] == a && tablica[1][2] == a && tablica[2][2] == b){ // __!
        xPos = 3;
        yPos = 3;
	}
	if (tablica[0][0] == a && tablica[0][1] == a && tablica[0][2] == b){ // |-- !
        xPos = 1;
        yPos = 3;
	}
	if (tablica[1][0] == a && tablica[1][1] == a && tablica[1][2] == b){ // -|- !
        xPos = 2;
        yPos = 3;
	}
	if (tablica[2][0] == a && tablica[2][1] == a && tablica[2][2] == b){ // --| !
        xPos = 3;
        yPos = 3;
	}
	if (tablica[0][0] == a && tablica[1][1] == a && tablica[2][2] == b){ // "-_ !
        xPos = 3;
        yPos = 3;
	}
	if (tablica[0][2] == a && tablica[1][1] == a && tablica[2][0] == b){ // _-" !
        xPos = 3;
        yPos = 1;
    }
    if (tablica[0][0] == a && tablica[1][0] == b && tablica[2][0] == a){ // "!"
        xPos = 2;
        yPos = 1;
    }
    if (tablica[0][1] == a && tablica[1][1] == b && tablica[2][1] == a){ // -!-
        xPos = 2;
        yPos = 2;
	}
    if (tablica[0][2] == a && tablica[1][2] == b && tablica[2][2] == a){ // _!_
        xPos = 2;
        yPos = 3;
	}
	if (tablica[0][0] == a && tablica[0][1] == b && tablica[0][2] == a){ // |-- !
        xPos = 1;
        yPos = 2;
	}
	if (tablica[1][0] == a && tablica[1][1] == b && tablica[1][2] == a){ // -|- !
        xPos = 2;
        yPos = 2;
	}
	if (tablica[2][0] == a && tablica[2][1] == b && tablica[2][2] == a){ // --| !
        xPos = 3;
        yPos = 2;
	}
	if (tablica[0][0] == a && tablica[1][1] == b && tablica[2][2] == a){ // "-_ !
        xPos = 2;
        yPos = 2;
	}
	if (tablica[0][2] == a && tablica[1][1] == b && tablica[2][0] == a){ // _-" !
        xPos = 2;
        yPos = 2;
    }
    if (tablica[0][0] == b && tablica[1][0] == a && tablica[2][0] == a){ // !""
        xPos = 1;
        yPos = 1;
    }
    if (tablica[0][1] == b && tablica[1][1] == a && tablica[2][1] == a){ // !--
        xPos = 1;
        yPos = 2;
	}
    if (tablica[0][2] == b && tablica[1][2] == a && tablica[2][2] == a){ // !__
        xPos = 1;
        yPos = 3;
	}
	if (tablica[0][0] == b && tablica[0][1] == a && tablica[0][2] == a){ // |-- !
        xPos = 1;
        yPos = 1;
	}
	if (tablica[1][0] == b && tablica[1][1] == a && tablica[1][2] == a){ // -|- !
        xPos = 2;
        yPos = 1;
	}
	if (tablica[2][0] == b && tablica[2][1] == a && tablica[2][2] == a){ // --| !
        xPos = 3;
        yPos = 1;
	}
	if (tablica[0][0] == b && tablica[1][1] == a && tablica[2][2] == a){ // "-_ !
        xPos = 1;
        yPos = 1;
	}
	if (tablica[0][2] == b && tablica[1][1] == a && tablica[2][0] == a){ // _-" !
        xPos = 1;
        yPos = 3;
    }
//    cout << " ===DEBUG=== Attacking on X: " << xPos << " Y: " << yPos<< "\n\n";
//    system("pause");
}


void ruchAi(){                  // kontrola ruchu AI
	srand(time(NULL));
	xPos = 1 + rand()%3;
	yPos = 1 + rand()%3;
	int goOn = 0;
//	system("pause");
	while (goOn == 0){
		if (tablica[xPos-1][yPos-1] == 2){
			goOn = 1;
//			cout << " ===DEBUG=== Goes on" << xPos << yPos << endl;
		} else {
			xPos = 1 + rand()%3;
			yPos = 1 + rand()%3;
//		cout << " ===DEBUG=== Reassign X Y " << xPos << yPos << endl;
		}
	}
//	system("pause");
	if (aiLv >= 1){
		aiBlock();
	}
	if (aiLv >= 2){
        aiAttack();
	}

}


void ruch(){					// obsluga ruchu gracza
	if (mv == 0) {
		cout << "\n\n\tX\nRuch gracza X.\n\tX\n\n";

		cout << "Wybierz pozycje X: ";
		cin >> xPos;
		cout << "Wybierz pozycje Y: ";
		cin >> yPos;

	} else {
		cout << "\n\n\tO\nRuch gracza O.\n\tO\n\n";
		ruchAi();
	}

	if (tablica[xPos-1][yPos-1] == 2){
	tablica[xPos-1][yPos-1] = mv;
	mv = 1-mv;
		if ( sprawdz() == 1) {
			wyswietl(0);
		} else {
			wyswietl(1);
		}
	} else if (xPos < 1 || xPos > 3 || yPos < 1 || xPos > 3){
		cout << "\n\n\nWprowadziles bledna pozycje! Pozycja od 1 do 3!\n";
		wyswietl(2);
	} else if (tablica[xPos-1][yPos-1] != 2){
		cout << "\n\n\nTa pozycja jest zajeta przez " << zwroc(xPos-1,yPos-1) << " . Wybierz inna!\n";
		wyswietl(2);
	} else {
		cout << "\n\n\nCos poszlo nie tak... Jeszcze raz. \n";

		wyswietl(2);
	}
}


void wyswietl(int cont){		// wyswietl tablice
	if (cont != 0 && cont != 2){
		system("cls");			// czyszczenie ekranu
	}
	cout << "\t     1   2   3  " << endl;
	cout << "\t   _____________" << endl;
	cout << "\t1  |_" << zwroc(0,0) << "_|_" << zwroc(1,0) << "_|_" << zwroc(2,0) << "_|"<<endl;
	cout << "\t2  |_" << zwroc(0,1) << "_|_" << zwroc(1,1) << "_|_" << zwroc(2,1) << "_|"<<endl;
	cout << "\t3  |_" << zwroc(0,2) << "_|_" << zwroc(1,2) << "_|_" << zwroc(2,2) << "_|"<<endl;
	cout << "\t   \"\"\"\"\"\"\"\"\"\"\"\"\""<<endl;
	cout << "   ^\n   |Y \n     X-->\n";

	if (cont == 0){
		return;
	} else {
		ruch();
	}

}
void start(){					// ustaw cala tablice na pusta (2)
	for (int i =0; i<3;i++){
		for (int j=0; j<3; j++){
			tablica[i][j] = 2;
		}
	}
	srand(time(NULL));
	mv = rand()%2;

	wyswietl(1);

}

int main() {
	int opt;
	cout << "Kolko krzyzyk.\n 1 - Start\n 2 - Wyjscie.\n";
	cin >> opt;

	if (opt == 1) {
        cout << "\n Poziom Bota (0-2): ";
        cin >> aiLv;
		start();
	} else if (opt == 2) {
		return 0;
	} else {
		main();
	}


    cout << "\n\tJeszcze raz? (1/0): ";
    cin >>opt;
    if (opt == 1){
        system("cls");
        main();
    } else {
        return 0;
    }
	return 0;

}