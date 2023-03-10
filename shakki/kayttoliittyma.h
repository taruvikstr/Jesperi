#pragma once
#include "asema.h"
#include "nappula.h"
#include "peli.h"
#include "siirto.h"


// Shakkiohjelman k�ytt�liittym�, joka osaa visualisoida nykyisen aseman
// ja lukea k�ytt�j�n sy�tt�m�t siirrot. Singleton.
class Kayttoliittyma
{
public:

	void aseta_asema(Asema* asema) { this->_asema = asema;  }
	void piirraLautaF(std::list<Siirto> lista);
	void piirraLauta();
	Siirto annaVastustajanSiirto();
	int kysyVastustajanVari();
	int _vari = 0;
	static Kayttoliittyma* getInstance();

private:

	Asema* _asema;
	static Kayttoliittyma* instance; // osoitin luokan ainoaan olioon (Singleton).

	Kayttoliittyma() { _asema = 0; }
	Kayttoliittyma(Asema* asema) { this->_asema = asema; }
};

