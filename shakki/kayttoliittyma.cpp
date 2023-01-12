#include <Windows.h>
#include <iostream>
#include <string>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include "kayttoliittyma.h"

using namespace std;




// Konstruktori asettaa luokan j�senmuuttujan arvoksi parametrinaan saamansa asema olion osoittimen arvon.
Kayttoliittyma::Kayttoliittyma(Asema* asema) { this->_asema = asema; }




Kayttoliittyma* Kayttoliittyma::instance = 0;







Kayttoliittyma* Kayttoliittyma::getInstance()
{
	if (instance == 0)
		instance = new Kayttoliittyma();
	return instance;
	
}




void Kayttoliittyma::piirraLauta()
{
	
	

	
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
		BACKGROUND_GREEN | BACKGROUND_BLUE);
	_setmode(_fileno(stdout), _O_U16TEXT);

}


/*
	Aliohjelma tarkistaa ett� k�ytt�j�n antama sy�te siirroksi on 
	muodollisesti korrekti (ei tarkista aseman laillisuutta)
	Ottaa irti my�s nappulan kirjaimen (K/D/L/R/T), tarkistaa ett� kirjain korrekti
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
