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



			if (_asema->_lauta[7-i][j] != NULL) {

				wcout << " " << _asema->_lauta[7-i][j]->getUnicode() << " ";
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
	int alkuX;
	int alkuY;
	int loppuX;
	int loppuY;

	// give opnents move
	string inputString;
	do {
		wcout << "Give your move: ";
		cin >> inputString;
		//cout << endl;

		if (inputString == "L0-0" || inputString == "L0-0-0") {
			if (inputString == "L0-0") {
				return Siirto(true, false);
			}
			else {
				return Siirto(false, true);
			}
		}
		else if (inputString.length() == 6) {

			//nappulastring=siirtostring[0];
			inputString.erase(0, 1);
		}
		else {
			//
		}
		alkuX = inputString[0] - 'a';
		alkuY = inputString[1] - '1';
		loppuX = inputString[3] - 'a';
		loppuY = inputString[4] - '1';

		
		if (((alkuX < 0) || (alkuX > 7) || (alkuY < 0) || (alkuY > 7) || (loppuX < 0) || (loppuX > 7) || (loppuY < 0) || (loppuY > 7)))
			wcout << "Siirron täytyy olla muotoa esim. Tf0-f4, \n aakkoset väliltä a-h \n numerot väliltä 1-8. \n Nappula on (K,k),(D,d),(T,t),(L,l),(R,r),(S,s)";
	} while (((alkuX < 0) || (alkuX > 7) || (alkuY < 0) || (alkuY > 7) || (loppuX < 0) || (loppuX > 7) || (loppuY < 0) || (loppuY > 7)));

	Ruutu alkuRuutu(alkuX, alkuY);
	Ruutu loppuRuutu(loppuX, loppuY);
	Siirto siirto(alkuRuutu,loppuRuutu);

	return siirto;

}


int Kayttoliittyma::kysyVastustajanVari()
{
	int vari;
	cout << "Anna väri 0=valkoinen, 1=musta" << endl;
	cin >> vari;
	return vari;
}
