#include <iostream>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#include <ostream>
#include <string>
#include "kayttoliittyma.h"
#include "Siirto.h"
#include "asema.h"

using namespace std; 

int main()
{
	wcout << "HeippariShakki\n";
	wcout << "Tervetuloa pelaamaan!\n";
	int lopetus = 100;
	Asema asema; 
	Kayttoliittyma::getInstance()->aseta_asema(&asema);
	
	Peli peli(Kayttoliittyma::getInstance()->
		kysyVastustajanVari());
	std::list<Siirto> lista;
	system("cls");
	int koneenVari = peli.getKoneenVari();

	Kuningas* kuningas = new Kuningas(L"\u2654", 0, VK);
	Daami* daami = new Daami(L"\u2655", 0, VD);
	Torni* torni = new Torni(L"\u2656", 0, VT);  //TOIMII
	Lahetti* lahetti = new Lahetti(L"\u2657", 0, VL);
	Ratsu* ratsu = new Ratsu(L"\u2658", 0, VR); //TOIMII
	Sotilas* sotilas = new Sotilas(L"\u2659", 0, VS);

	Ruutu* ruutu = new Ruutu(4, 7);
	
	asema.vs->annaSiirrot(lista, ruutu, &asema, asema.vs->getVari());
	//    cout << asema.listasotilas.size();
	for (Siirto kohta : asema.listasotilas) {

		wcout << kohta.getLoppuruutu().getRivi() << " Rivi " << kohta.getLoppuruutu().getSarake() << " Sarake" << endl;


	}
	//Kayttoliittyma::getInstance()->piirraLauta(lista);
	
	
	Kayttoliittyma::getInstance()->piirraLauta();

	Siirto siirto = Kayttoliittyma::getInstance()->
			annaVastustajanSiirto();
		asema.paivitaAsema(&siirto);

		Kayttoliittyma::getInstance()->piirraLauta();

		siirto = Kayttoliittyma::getInstance()->
			annaVastustajanSiirto();
		asema.paivitaAsema(&siirto);
		Kayttoliittyma::getInstance()->piirraLauta();
		siirto = Kayttoliittyma::getInstance()->
			annaVastustajanSiirto();
		asema.paivitaAsema(&siirto);
		Kayttoliittyma::getInstance()->piirraLauta();
		siirto = Kayttoliittyma::getInstance()->
			annaVastustajanSiirto();
		asema.paivitaAsema(&siirto);
		Kayttoliittyma::getInstance()->piirraLauta();
	
/*	while (lopetus != 0) {
		lista.clear();
		Kayttoliittyma::getInstance()->piirraLauta();
		wcout << "\n";
		// Tarkasta onko peli loppu?
		asema.annaLaillisetSiirrot(lista);
		if (lista.size() == 0) {
			lopetus = 0;
			std::wcout << "Peli loppui";
			continue;
		}
		Siirto siirto;
		if (asema.getSiirtovuoro() == koneenVari) {
			MinMaxPaluu paluu;
			if (koneenVari == 0) {
				paluu = asema.maxi(3);
			}
			else {
				paluu = asema.mini(3);
			}
			siirto = paluu._parasSiirto;
		}
		else {
			siirto = Kayttoliittyma::getInstance()->
				annaVastustajanSiirto();
		}
		asema.paivitaAsema(&siirto);
	}
	*/
	
	return 0;
}
