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
		if (i % 2 == 0) {

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY |
				BACKGROUND_GREEN);
		}
		else {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY |
				BACKGROUND_RED);
		}
		wcout << 8 - i << " ";
		for (int j = 0; j < 8; j++)
		{
			if (_asema->_lauta[i][j] != NULL) {
				wcout << _asema->_lauta[i][j]->getUnicode() << " ";
			}
			else {
				wcout << " ";
			}
		}
		wcout << endl;
	}

	wcout << L"  a b c d e f g h" << endl;
}


/*
	Aliohjelma tarkistaa että käyttäjän antama syöte siirroksi on 
	muodollisesti korrekti (ei tarkista aseman laillisuutta)
	Ottaa irti myös nappulan kirjaimen (K/D/L/R/T), tarkistaa että kirjain korrekti
*/
Siirto Kayttoliittyma::annaVastustajanSiirto()
{
	Siirto siirto;
	return siirto;
	
}


int Kayttoliittyma::kysyVastustajanVari()
{
	return 0;
}
