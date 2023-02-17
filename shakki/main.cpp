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
	
	while (lopetus != 0) {
		wcout << "kierros" << endl;
		lista.clear();
	
	//	Kayttoliittyma::getInstance()->piirraLauta();
		
		wcout << "\n";
		// Tarkasta onko peli loppu?
		asema.annaLaillisetSiirrot(lista);
		Kayttoliittyma::getInstance()->piirraLauta();

		if (lista.size() == 0) {
			lopetus = 0;
			string a = "1";
			int b = stoi(a);

			std::wcout << b << endl;
			std::wcout << a[0];
			continue;
		}
		Siirto siirto;
		if (asema.getSiirtovuoro() == koneenVari) {
			wcout << "koneen vuoro" << endl;
			MinMaxPaluu paluu;

			if (koneenVari == 0) {
				paluu = asema.maxi(3, -10000000, 10000000);
			}
			else {
				paluu = asema.mini(3, -10000000, 10000000);
			}

			siirto = paluu._parasSiirto;
		}
		else {
			wcout << "pelaajan vuoro" << endl;
			siirto = Kayttoliittyma::getInstance()->
				annaVastustajanSiirto();
		}
		asema.paivitaAsema(&siirto);
		
	}

	return 0;
}
