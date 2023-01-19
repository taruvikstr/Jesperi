#include <Windows.h>
#include <iostream>
#include <string>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include "kayttoliittyma.h"

using namespace std;


Kayttoliittyma* Kayttoliittyma::instance = 0;


Kayttoliittyma* Kayttoliittyma::getInstance()
{
	if (instance == 0)
		instance = new Kayttoliittyma();
	return instance;
	
}


void Kayttoliittyma::piirraLauta()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	for (int i = 0; i < 8; i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
			BACKGROUND_GREEN | BACKGROUND_BLUE);

		wcout << 8 - i << " ";
		int index = 0;
		for (int j = 0; j < 8; j++)
		{
			if (i % 2 == 0) {

				if(index % 2 != 0) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY |
					BACKGROUND_GREEN);
				else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY |
					BACKGROUND_BLUE);
			}
			else {
				if (index % 2 == 0) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY |
					BACKGROUND_GREEN);
				else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY |
					BACKGROUND_BLUE);
			}



			if (_asema->_lauta[i][j] != NULL) {

				wcout << " " << _asema->_lauta[i][j]->getUnicode() << " ";
			}
			else {
				wcout << "   ";
			}
			index++;
		}
		wcout << endl;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
		BACKGROUND_GREEN | BACKGROUND_BLUE);

	wcout << L"   A  B  C  D  E  F  G  H " << endl;
}


/*
	Aliohjelma tarkistaa ett� k�ytt�j�n antama sy�te siirroksi on 
	muodollisesti korrekti (ei tarkista aseman laillisuutta)
	Ottaa irti myos nappulan kirjaimen (K/D/L/R/T), tarkistaa etta kirjain korrekti
*/
Siirto Kayttoliittyma::annaVastustajanSiirto()
{

	// give opnents move
	string input;
	cout << "Give your move: ";
	cin >> input;
	cout << endl;

	string alku = input.substr(0, 2);
	string loppu = input.substr(2, 2);

	// convert strings to int

	int alkuX = alku[0] - 'A';
	int alkuY = 8 - (alku[1] - '0');
	int loppuX = loppu[0] - 'A';
	int loppuY = 8 - (loppu[1] - '0');

	// create move

	Siirto siirto(Ruutu(alkuX, alkuY), Ruutu(loppuX, loppuY));

	// check if move is valid
	/*if (input.length() != 4) {
		cout << "Invalid move!" << endl;
		return annaVastustajanSiirto();
	}*/


    //Siirto siirto;
	return siirto;

}


int Kayttoliittyma::kysyVastustajanVari()
{
	return 0;
}
