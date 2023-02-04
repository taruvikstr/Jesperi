#include <iostream>
#include "asema.h"
#include "minMaxPaluu.h"
#include "nappula.h"
#include "ruutu.h"
using namespace std;

Nappula* Asema::vk = new Kuningas(L"\u2654", 0, VK);
Nappula* Asema::vd = new Daami(L"\u2655", 0, VD);
Nappula* Asema::vt = new Torni(L"\u2656", 0, VT);
Nappula* Asema::vl = new Lahetti(L"\u2657", 0, VL);
Nappula* Asema::vr = new Ratsu(L"\u2658", 0, VR);
Nappula* Asema::vs = new Sotilas(L"\u2659", 0, VS);

Nappula* Asema::mk = new Kuningas(L"\u265A", 1, MK);
Nappula* Asema::md = new Daami(L"\u265B", 1, MD);
Nappula* Asema::mt = new Torni(L"\u265C", 1, MT);
Nappula* Asema::ml = new Lahetti(L"\u265D", 1, ML);
Nappula* Asema::mr = new Ratsu(L"\u265E", 1, MR);
Nappula* Asema::ms = new Sotilas(L"\u265F", 1, MS);


Asema::Asema()
{
	// Ensin alustetaan kaikki laudan ruudut nappulla "NULL", koska muuten ruuduissa satunnaista tauhkaa
	
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			_lauta[i][j] = NULL;
		}
	}
	
	// Asetetaan alkuaseman mukaisesti nappulat ruuduille
	

	_lauta[0][0] = vt;
	_lauta[0][1] = vr;
	_lauta[0][2] = vl;
	_lauta[0][3] = vd;
	_lauta[0][4] = vk;
	_lauta[0][5] = vl;
	_lauta[0][6] = vr;
	_lauta[0][7] = vt;

	_lauta[7][0] = mt;
	//_lauta[7][1] = mr;
	//_lauta[7][2] = ml;
	//_lauta[7][3] = md;
	_lauta[7][4] = mk; 
	//_lauta[7][5] = ml;
	//_lauta[7][6] = mr;
	_lauta[7][7] = mt;

	for (int i = 0; i < 8; i++) {
		//_lauta[1][i] = vs;
		//_lauta[6][i] = ms;
	}

	_siirtovuoro = 0;
	_onkoValkeaKuningasLiikkunut = false;
	_onkoMustaKuningasLiikkunut = false;
	_onkoValkeaDTliikkunut = false;
	_onkoValkeaKTliikkunut = false;
	_onkoMustaDTliikkunut = false;
	_onkoMustaKTliikkunut = false;
}


void Asema::paivitaAsema(Siirto *siirto)
{
	//Tarkastetaan on siirto lyhyt linna
	if (siirto->onkoLyhytLinna())
	{
		if (_siirtovuoro == 0) {
			// Asetetaan kuningas ja torni oikeisiin ruutuihin
			_lauta[0][6] = vk;
			_lauta[0][5] = vt;
			// Tyhjennet‰‰n vanhat ruudut
			_lauta[0][4] = NULL;
			_lauta[0][7] = NULL;
		}
		if (_siirtovuoro == 1) {
			// Asetetaan kuningas ja torni oikeisiin ruutuihin
			_lauta[7][6] = mk;
			_lauta[7][5] = mt;
			// Tyhjennet‰‰n vanhat ruudut
			_lauta[7][4] = NULL;
			_lauta[7][7] = NULL;
		}
	}
	
	// onko pitk‰ linna //pitk‰lle linnalle sama  ku lyhyelle
	if (siirto->onkoPitkalinna())
	{
		if (_siirtovuoro == 0) {
			// Asetetaan kuningas ja torni oikeisiin ruutuihin
			_lauta[0][2] = vk;
			_lauta[0][3] = vt;
			// Tyhjennet‰‰n vanhat ruudut
			_lauta[0][0] = NULL;
			_lauta[0][4] = NULL;
		}
		if (_siirtovuoro == 1) {
			// Asetetaan kuningas ja torni oikeisiin ruutuihin
			_lauta[7][2] = mk;
			_lauta[7][3] = mt;
			// Tyhjennet‰‰n vanhat ruudut
			_lauta[7][0] = NULL;
			_lauta[7][4] = NULL;
		}
	}

	// Kaikki muut siirrot

	//Ottaa siirron alkuruudussa olleen nappulan talteen

	//ota siirron int arvo esim. lauta00 ja kato mik‰ nappula 
	//on siin‰ kohtaa, siirr‰ lauta00 nulliksi ja siirr‰ kohdassa 
	//ollut nappula loppuruutuun esim lauta55 ja aseta nappula laudalle
	int rivi_alku = siirto->getAlkuruutu().getRivi();

	int sarake_alku = siirto->getAlkuruutu().getSarake();

	int rivi_loppu = siirto->getLoppuruutu().getRivi();
	int sarake_loppu = siirto->getLoppuruutu().getSarake();

	// Katsotaan jos nappula on sotilas ja rivi on p‰‰tyrivi niin korotetaan nappula kysym‰ll‰ mihin korotetaan	
	if (_lauta[rivi_alku][sarake_alku] == vs && rivi_loppu == 7 || _lauta[rivi_alku][sarake_alku] == ms && rivi_loppu == 0) {
		wcout << "miksik‰ korotetaan?\n";
	}
	//muissa tapauksissa alkuruutuun null ja loppuruutuun sama alkuruudusta l‰htenyt nappula
	else {
		//Laittaa talteen otetun nappulan uuteen ruutuun
		_lauta[rivi_loppu][sarake_loppu] = _lauta[rivi_alku][sarake_alku];
		_lauta[rivi_alku][sarake_alku] = NULL;

	}

	// katsotaan jos liikkunut nappula on kuningas niin muutetaan onkoKuningasLiikkunut arvo (molemmille v‰reille)
	if (_lauta[0][4] == NULL) {
		_onkoValkeaKuningasLiikkunut = true;
	}
	if (_lauta[7][7] == NULL) {
		_onkoMustaKuningasLiikkunut = true;
	}

	// katsotaan jos liikkunut nappula on torni niin muutetaan onkoTorniLiikkunut arvo (molemmille v‰reille ja molemmille torneille)
	if (_lauta[0][0] == NULL) {
		_onkoValkeaDTliikkunut = true;
	}
	if (_lauta[0][7] == NULL) {
		_onkoValkeaKTliikkunut = true;
	}
	if (_lauta[7][0] == NULL) {
		_onkoMustaDTliikkunut = true;
	}
	if (_lauta[7][7] == NULL) {
		_onkoMustaKTliikkunut = true;
	}



	//p‰ivitet‰‰n _siirtovuoro
	if (_siirtovuoro == 0) {
		setSiirtovuoro(1);
	}
	else {
		setSiirtovuoro(0);
	}

}



int Asema::getSiirtovuoro() 
{
	return _siirtovuoro;
}


void Asema::setSiirtovuoro(int vuoro) 
{
	this->_siirtovuoro = vuoro;

}


bool Asema::getOnkoValkeaKuningasLiikkunut() 
{
	return _onkoValkeaKuningasLiikkunut;
}


bool Asema::getOnkoMustaKuningasLiikkunut() 
{
	return _onkoMustaKuningasLiikkunut;
}


bool Asema::getOnkoValkeaDTliikkunut() 
{
	return _onkoValkeaDTliikkunut;
}


bool Asema::getOnkoValkeaKTliikkunut() 
{
	return _onkoValkeaKTliikkunut;
}


bool Asema::getOnkoMustaDTliikkunut()
{
	return _onkoMustaDTliikkunut;
}


bool Asema::getOnkoMustaKTliikkunut() 
{
	return _onkoMustaKTliikkunut;
}


/* 1. Laske nappuloiden arvo
Daami = 9
Torni = 5
L‰hetti = 3,25
Ratsu = 3
Sotilas = 1

2. Kuninkaan hyvyys
Jos avaus tai keskipeli, niin hyv‰ ett‰ kunigas g1 tai b1/c1
Loppupeliss‰ vaikea sanoa halutaanko olla auttamassa omaa sotilasta korottumaan
vai olla est‰m‰ss‰ vastustajan korotusta siksi ei oteta kantaa
3. Arvosta keskustaa sotilailla ja ratsuilla
4. Arvosta pitki‰ linjoja daami, torni ja l‰hetti
*/
double Asema::evaluoi() 
{
	return 0;

	//kertoimet asetettu sen takia ett‰ niiden avulla asioiden painoarvoa voidaan s‰‰t‰‰ helposti yhdest‰ paikasta
	
	//1. Nappuloiden arvo
	
	//2. Kuningas turvassa
	
	//3. Arvosta keskustaa
	
	// 4. Arvosta linjoja
	
}


double Asema::laskeNappuloidenArvo(int vari) 
{
	return 0;
	
}


bool Asema::onkoAvausTaiKeskipeli(int vari) 
{
	return 0;
	// Jos upseereita 3 tai v‰hemm‰n on loppupeli
	// mutta jos daami laudalla on loppueli vasta kun kuin vain daami j‰ljell‰
	
	//Jos vari on 0 eli valkoiset
	//niin on keskipeli jos mustalla upseereita yli 2 tai jos daami+1
	

}


double Asema::nappuloitaKeskella(int vari) 
{
	return 0;

	//sotilaat ydinkeskustassa + 0.25/napa
	//ratsut ydinkeskustassa + 0.25/napa
	//sotilaat laitakeskustassa + 0.11/napa
	//ratsut laitakeskustassa + 0.11/napa
	
	//valkeille ydinkeskusta

	
	
	//valkeille laitakeskusta
	


	//mustille ydinkeskusta
	
	//mustille laitakeskusta
	
}


double Asema::linjat(int vari) 
{
	return 0;
	
	//valkoiset
	
	//mustat
	
}


// https://chessprogramming.wikispaces.com/Minimax MinMax-algoritmin pseudokoodi (lis‰sin parametrina aseman)
//int maxi(int depth, asema a) 
//	if (depth == 0) return evaluate();
//	int max = -oo;
//	for (all moves ) {
//		score = mini(depth - 1, seuraaja);
//		if (score > max)
//			max = score;
//	}
//	return max;
//}

//int mini(int depth, asema a) {
//	if (depth == 0) return -evaluate();
//	int min = +oo;
//	for (all moves) {
//		score = maxi(depth - 1);
//		if (score < min)
//			min = score;
//	}
//	return min;
//}
MinMaxPaluu Asema::minimax(int syvyys)
{
	MinMaxPaluu paluuarvo;

	// Generoidaan aseman lailliset siirrot.

	// Rekursion kantatapaus 1: peli on loppu

	// Rekursion kantatapaus 2: katkaisusyvyydess‰

	// Rekursioaskel: kokeillaan jokaista laillista siirtoa s
	// (alustetaan paluuarvo huonoimmaksi mahdolliseksi).

	srand(time(NULL)); // seed the random number generator
	int randomNumber = (rand() % 6) + 1;

	if (randomNumber == 1) {
		int randomNumber2 = (rand() % listadaami.size());
		auto it = listadaami.begin();
		std::advance(it, randomNumber2);
		paluuarvo._parasSiirto = *it;
	}
	else if (randomNumber == 2) {
		int randomNumber2 = (rand() % listakunkku.size());
		auto it = listakunkku.begin();
		std::advance(it, randomNumber2);
		paluuarvo._parasSiirto = *it;
	}
	else if (randomNumber == 3) {
		int randomNumber2 = (rand() % listatorni.size());
		auto it = listatorni.begin();
		std::advance(it, randomNumber2);
		paluuarvo._parasSiirto = *it;
	}
	else if (randomNumber == 4) {
		int randomNumber2 = (rand() % listalahetti.size());
		auto it = listalahetti.begin();
		std::advance(it, randomNumber2);
		paluuarvo._parasSiirto = *it;
	}
	else if (randomNumber == 5) {
		int randomNumber2 = (rand() % listasotilas.size());
		auto it = listasotilas.begin();
		std::advance(it, randomNumber2);
		paluuarvo._parasSiirto = *it;
	}
	else if (randomNumber == 6) {
		int randomNumber2 = (rand() % listatorni.size());
		auto it = listatorni.begin();
		std::advance(it, randomNumber2);
		paluuarvo._parasSiirto = *it;
	}

	return paluuarvo;
}


MinMaxPaluu Asema::maxi(int syvyys, std::list<Siirto>& lista)
{
	MinMaxPaluu paluuarvo;
//	srand(time(NULL)); // seed the random number generator
//	int randomNumber = (rand() % lista.size());
//
//	
//	auto it = lista.begin();
//	std::advance(it, randomNumber);
//paluuarvo._parasSiirto = *it;

return paluuarvo;
}


MinMaxPaluu Asema::mini(int syvyys, std::list<Siirto>& lista)
{
	MinMaxPaluu paluuarvo;
	srand(time(NULL)); // seed the random number generator
	int randomNumber = (rand() % lista.size());


	auto it = lista.begin();
	std::advance(it, randomNumber);

	paluuarvo._parasSiirto = *it;

	for (it = lista.begin(); it != lista.end(); it++)
	{
		wcout << it->onkoLyhytLinna() << endl;
		wcout << it->onkoPitkalinna() << endl;
		if (it->onkoLyhytLinna()) {
			paluuarvo._parasSiirto = *it;
		}
		if (it->onkoPitkalinna()) {
			    paluuarvo._parasSiirto = *it;
		}

	}
	return paluuarvo;
}


bool Asema::onkoRuutuUhattu(Ruutu* ruutu, int vastustajanVari)
{
	std::list<Siirto> vastustajanSiirtolista;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (this->_lauta[i][j] == NULL) {
				continue;
			}
			if (this->_lauta[i][j]->getVari() == vastustajanVari) {
				this->_lauta[i][j]->annaSiirrot(vastustajanSiirtolista, &Ruutu(i, j), this, vastustajanVari);
			}
		}
	}
	bool ruutuOk = true;
	for (auto s : vastustajanSiirtolista) {
		if (ruutu->getSarake() == s.getLoppuruutu().getSarake() && ruutu->getRivi() == s.getLoppuruutu().getRivi()) {
			ruutuOk = false;
			break;
		}
	}
	return ruutuOk;

}


void Asema::huolehdiKuninkaanShakeista(std::list<Siirto>& lista, int vari)
{
	
	int kuninkaanRivi = 0;
	int kuninkaanSarake = 0;
	if (vari == 0) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (this->_lauta[i][j] == NULL) {
					continue;
				}
				if (this->_lauta[i][j]->getKoodi() == VK) {
					kuninkaanRivi = i;
					kuninkaanSarake = j;
					break;
				}
			}
		}
	}
	if (vari == 1) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (this->_lauta[i][j] == NULL) {
					continue;
				}
				if (this->_lauta[i][j]->getKoodi() == MK) {
					kuninkaanRivi = i;
					kuninkaanSarake = j;
					break;
				}
			}
		}
	}
	Asema testiAsema;

	std::list<Siirto> siivottuSiirtolista;
	for (auto s : lista) {
		testiAsema = *this;
		testiAsema.paivitaAsema(&s);
		int rivi = 0;
		int sarake = 0;

		if (s.onkoLyhytLinna()) {
			sarake = 6;
			if (this->getSiirtovuoro() == 0)
				rivi = 0;
			else
				rivi = 7;


		}
		else if (s.onkoPitkalinna()){
			sarake = 2;
			if (this->getSiirtovuoro() == 0)
				rivi = 0;
			else
				rivi = 7;
		}
		else {
			Nappula* siirtyva = this->_lauta[s.getAlkuruutu().getRivi()][s.getAlkuruutu().getSarake()];
			if (siirtyva->getKoodi() == VK || siirtyva->getKoodi() == MK ) {
				rivi = s.getLoppuruutu().getRivi(); 
				sarake = s.getLoppuruutu().getSarake();
			}
			else {
				rivi = kuninkaanRivi;
				sarake = kuninkaanSarake;
			}
		}

		if (testiAsema.onkoRuutuUhattu(&Ruutu(rivi, sarake), vari) == true) {
			siivottuSiirtolista.push_back(s);
		}
	}
	lista = siivottuSiirtolista;


}
void Asema::annaLinnoitusSiirrot(std::list<Siirto>& lista, int vari) {
	// Valkoisen kuninkaan lyhyen linnan siirto
	if (vari == 0) {
		//Valkean lyhyt linna
		if (!this->getOnkoValkeaKuningasLiikkunut() && !this->getOnkoValkeaKTliikkunut()
			&& this->onkoRuutuUhattu(&Ruutu(0, 4), 1)
			&& this->onkoRuutuUhattu(&Ruutu(0, 5), 1) && this->onkoRuutuUhattu(&Ruutu(0, 6), 1)
			&& this->_lauta[0][5] == NULL && this->_lauta[0][6] == NULL) {
			//p‰ivitet‰‰n listaan lyhyt linna
			lista.push_back(Siirto(true, false));
		}
		//Valkean pitk‰ linna
		if (!this->getOnkoValkeaKuningasLiikkunut() && !this->getOnkoValkeaDTliikkunut()
			&& this->onkoRuutuUhattu(&Ruutu(0, 4), 1)
			&& this->onkoRuutuUhattu(&Ruutu(0, 3), 1) && this->onkoRuutuUhattu(&Ruutu(0, 2), 1)
			&& this->_lauta[0][3] == NULL && this->_lauta[0][2] == NULL) {
			//p‰ivitet‰‰n listaan lyhyt linna
			lista.push_back(Siirto(false, true));
		}
	}
	if (vari == 1) {
		//Musta lyhyt linna
		if (!this->getOnkoMustaKuningasLiikkunut() && !this->getOnkoMustaKTliikkunut()
			&& this->onkoRuutuUhattu(&Ruutu(7, 4), 0)
			&& this->onkoRuutuUhattu(&Ruutu(7, 5), 0) && this->onkoRuutuUhattu(&Ruutu(7, 6), 0)
			&& this->_lauta[7][5] == NULL && this->_lauta[7][6] == NULL) {
			//p‰ivitet‰‰n listaan lyhyt linna
			
			lista.push_back(Siirto(true,false));
		}
		//Mustan pitk‰ linna
		if (!this->getOnkoMustaKuningasLiikkunut() && !this->getOnkoMustaDTliikkunut()
			&& this->onkoRuutuUhattu(&Ruutu(7, 4), 0)
			&& this->onkoRuutuUhattu(&Ruutu(7, 3), 0) && this->onkoRuutuUhattu(&Ruutu(7, 2), 0)
			&& this->_lauta[7][3] == NULL && this->_lauta[7][2] == NULL) {
			//p‰ivitet‰‰n listaan lyhyt linna
			lista.push_back(Siirto(false,true));
		}
	}

}


void Asema::annaLaillisetSiirrot(std::list<Siirto>& lista) {
	
	int vari = this->getSiirtovuoro();
	int vastustajanvari = vari;

	if (vari == 0) {
		vastustajanvari = 1;
	}
	else {
		vastustajanvari = 0;
	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (this->_lauta[i][j] == NULL) {
				continue;
			}
			if (this->_lauta[i][j]->getVari() != vari) {
				continue;
			}
			this->_lauta[i][j]->annaSiirrot(lista, &Ruutu(i,j), this, vari);
		}
	}
	
	this->annaLinnoitusSiirrot(lista, vari);
	this->huolehdiKuninkaanShakeista(lista, vari);
	

}
