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



	Ruutu* ruutu = new Ruutu(2, 1); //VAIHDA TESTI NAPPULAN SIJAINTIA LAUDALLA
	asema.kaksoisaskelSarakkeella = 2;
	//VALKOISEN TESTAUKSEEN	
	//asema.vk->annaSiirrot(lista, ruutu, &asema, asema.vk->getVari()); //testattu
//	asema.vd->annaSiirrot(lista, ruutu, &asema, asema.vd->getVari());  //testattu
//	asema.vt->annaSiirrot(lista, ruutu, &asema, asema.vt->getVari());  //testattu
//	asema.vl->annaSiirrot(lista, ruutu, &asema, asema.vl->getVari()); // testattu
//	asema.vr->annaSiirrot(lista, ruutu, &asema, asema.vr->getVari());  //testattu
//	asema.vs->annaSiirrot(lista, ruutu, &asema, asema.vs->getVari()); 
	
//MUSTAN TESTAUKSEEN
//	asema.mk->annaSiirrot(lista, ruutu, &asema, asema.mk->getVari());  //testattu
//	asema.md->annaSiirrot(lista, ruutu, &asema, asema.md->getVari()); //testattu
//	asema.mt->annaSiirrot(lista, ruutu, &asema, asema.mt->getVari()); //testattu
//	asema.ml->annaSiirrot(lista, ruutu, &asema, asema.ml->getVari()); //testattu
//	asema.mr->annaSiirrot(lista, ruutu, &asema, asema.mr->getVari()); //testattu
	asema.ms->annaSiirrot(lista, ruutu, &asema, asema.ms->getVari());

	Kayttoliittyma::getInstance()->piirraLautaF(asema.listasotilas); //MUUTA T�T� TESTAUKSEEN
	
	
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
