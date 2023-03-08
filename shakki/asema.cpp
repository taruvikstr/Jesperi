#include <iostream>
#include "asema.h"
#include "minMaxPaluu.h"
#include "nappula.h"
#include "ruutu.h"
#include "kayttoliittyma.h"
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
	_lauta[7][1] = mr;
	_lauta[7][2] = ml;
	_lauta[7][3] = md;
	_lauta[7][4] = mk; 
	_lauta[7][5] = ml;
	_lauta[7][6] = mr;
	_lauta[7][7] = mt;

	for (int i = 0; i < 8; i++) {
		_lauta[1][i] = vs;
		_lauta[6][i] = ms;
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




	//Sotilaan ohestalyˆnti
	//ohesta syˆd‰‰n
	
	if (_siirtovuoro == 0 && _lauta[rivi_alku][sarake_alku] != NULL) {
		if (sarake_loppu == kaksoisaskelSarakkeella && _lauta[rivi_loppu][sarake_loppu] == NULL
			&& _lauta[rivi_alku][sarake_loppu] != NULL && _lauta[rivi_alku][sarake_loppu]->getKoodi() == MS)
			_lauta[rivi_alku][sarake_loppu] = NULL;
	}
	else if (_siirtovuoro == 1 && _lauta[rivi_alku][sarake_alku] != NULL) 
	{
		if (sarake_loppu == kaksoisaskelSarakkeella && _lauta[rivi_loppu][sarake_loppu] == NULL
			&& _lauta[rivi_alku][sarake_loppu] && _lauta[rivi_alku][sarake_loppu]->getKoodi() == VS)
			_lauta[rivi_alku][sarake_loppu] = NULL;
	}

	//asetetaan kaksoisaskel valkoiselle
	if (_siirtovuoro == 0 && _lauta[rivi_alku][sarake_alku] != NULL && _lauta[rivi_alku][sarake_alku]->getKoodi() == VS && rivi_loppu == 3) kaksoisaskelSarakkeella = sarake_alku;
	//ja mustalle
	else if (_siirtovuoro == 1 && _lauta[rivi_alku][sarake_alku] != NULL && _lauta[rivi_alku][sarake_alku]->getKoodi() == MS && rivi_loppu == 4) kaksoisaskelSarakkeella = sarake_alku;
	else kaksoisaskelSarakkeella = -1;

	// Katsotaan jos nappula on sotilas ja rivi on p‰‰tyrivi niin korotetaan nappula kysym‰ll‰ mihin korotetaan	
	 
	if (_lauta[rivi_alku][sarake_alku] == vs && rivi_loppu == 7 && rivi_alku == 6 && _siirtovuoro == 0 || _siirtovuoro == 1 && _lauta[rivi_alku][sarake_alku] == ms && rivi_loppu == 0 && rivi_alku == 1) {
		if (Kayttoliittyma::getInstance()->_vari == _siirtovuoro)
		{
			int korotus;
			wcout << "Choose piece to promote to (1 = queen, 2 = rook, 3 = bishop, 4 = knight): ";
			cin >> korotus;
			Nappula* korotettuNappula;

			switch (korotus) 
			{
				case 1:
					korotettuNappula = _siirtovuoro == 0 ? vd : md;
					break;
				case 2:
					korotettuNappula = _siirtovuoro == 0 ? vt : mt;
					break;
				case 3:
					korotettuNappula = _siirtovuoro == 0 ? vl : ml;
					break;
				case 4:
					korotettuNappula = _siirtovuoro == 0 ? vr : mr;
					break;
				default:
					korotettuNappula = _siirtovuoro == 0 ? vd : md;
					break;
			}

			_lauta[rivi_loppu][sarake_loppu] = korotettuNappula;
			_lauta[rivi_alku][sarake_alku] = NULL;
			rivi_alku = NULL;
			sarake_alku = NULL;
		}
		else {
			Nappula* korotettuNappula = siirto->_miksikorotetaan;
			_lauta[rivi_loppu][sarake_loppu] = korotettuNappula;
			_lauta[rivi_alku][sarake_alku] = NULL;
			rivi_alku = NULL;
			sarake_alku = NULL;
		}
	}
	//muissa tapauksissa alkuruutuun null ja loppuruutuun sama alkuruudusta l‰htenyt nappula
	else {
		//Laittaa talteen otetun nappulan uuteen ruutuun
		wcout << "rivi alku: " << rivi_alku << " sarake alku: " << sarake_alku <<endl;
		_lauta[rivi_loppu][sarake_loppu] = _lauta[rivi_alku][sarake_alku];
		_lauta[rivi_alku][sarake_alku] = NULL;

	}

	// katsotaan jos liikkunut nappula on kuningas niin muutetaan onkoKuningasLiikkunut arvo 
	if (_siirtovuoro == 0 && !_onkoValkeaKuningasLiikkunut) // jos kuningas on liikkunut, on turha tarkastella torneja en‰‰, koska tornitus ei ole en‰‰ mahdollinen
	{
		if (_lauta[0][4] == NULL) {
			wcout << "v kunkku liikkui";
			_onkoValkeaKuningasLiikkunut = true;
		}
		else if (!_onkoValkeaKTliikkunut || !_onkoValkeaDTliikkunut)
		{
			// katsotaan jos liikkunut nappula on torni niin muutetaan onkoTorniLiikkunut arvo
			if (_lauta[0][0] == NULL) {
				wcout << "v dt liikkui";
				_onkoValkeaDTliikkunut = true;
			}
			if (_lauta[0][7] == NULL) {
				wcout << "v kt liikkui";
				_onkoValkeaKTliikkunut = true;
			}

			//Jos molemmat tornit on liikkuneet, on turha en‰‰ tarkastella kuninkaan liikkumista, koska tornitus ei ole en‰‰ mahdollista
			if (_onkoValkeaDTliikkunut && _onkoValkeaKTliikkunut) _onkoValkeaKuningasLiikkunut = true;
		}

	}
	// katsotaan jos liikkunut nappula on kuningas niin muutetaan onkoKuningasLiikkunut arvo 
	else if (_siirtovuoro == 1 && !_onkoMustaKuningasLiikkunut) // jos kuningas on liikkunut, on turha tarkastella torneja en‰‰, koska tornitus ei ole en‰‰ mahdollinen
	{
		if (_lauta[7][4] == NULL) {
			wcout << "m kunkku liikkui";
			_onkoMustaKuningasLiikkunut = true;
		}
		else if (!_onkoMustaKTliikkunut || !_onkoMustaDTliikkunut)
		{
			// katsotaan jos liikkunut nappula on torni niin muutetaan onkoTorniLiikkunut arvo (molemmille v‰reille ja molemmille torneille)
			if (_lauta[7][0] == NULL) {
				wcout << "m dt liikkui";
				_onkoMustaDTliikkunut = true;
			}
			if (_lauta[7][7] == NULL) {
				wcout << "m kt liikkui";
				_onkoMustaKTliikkunut = true;
			}

			//Jos molemmat tornit on liikkuneet, on turha en‰‰ tarkastella kuninkaan liikkumista, koska tornitus ei ole en‰‰ mahdollista
			if (_onkoMustaDTliikkunut && _onkoMustaKTliikkunut) _onkoMustaKuningasLiikkunut = true;
		}
	}

	//p‰ivitet‰‰n _siirtovuoro
	if (_siirtovuoro == 0) {
		setSiirtovuoro(1);
	}
	else {
		setSiirtovuoro(0);
	}

}

void Asema::paivitaTestiAsema(Siirto* siirto)
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


	//Sotilaan ohestalyˆnti
	//ohesta syˆd‰‰n

	if (_siirtovuoro == 0 && _lauta[rivi_alku][sarake_alku] != NULL) {
		if (sarake_loppu == kaksoisaskelSarakkeella && _lauta[rivi_loppu][sarake_loppu] == NULL
			&& _lauta[rivi_alku][sarake_loppu] != NULL && _lauta[rivi_alku][sarake_loppu]->getKoodi() == MS)
			_lauta[rivi_alku][sarake_loppu] = NULL;
	}
	else if (_siirtovuoro == 1 && _lauta[rivi_alku][sarake_alku] != NULL)
	{
		if (sarake_loppu == kaksoisaskelSarakkeella && _lauta[rivi_loppu][sarake_loppu] == NULL
			&& _lauta[rivi_alku][sarake_loppu] && _lauta[rivi_alku][sarake_loppu]->getKoodi() == VS)
			_lauta[rivi_alku][sarake_loppu] = NULL;
	}

	//asetetaan kaksoisaskel valkoiselle
	if (_siirtovuoro == 0 && _lauta[rivi_alku][sarake_alku] != NULL && _lauta[rivi_alku][sarake_alku]->getKoodi() == VS && rivi_loppu == 3) kaksoisaskelSarakkeella = sarake_alku;
	//ja mustalle
	else if (_siirtovuoro == 1 && _lauta[rivi_alku][sarake_alku] != NULL && _lauta[rivi_alku][sarake_alku]->getKoodi() == MS && rivi_loppu == 4) kaksoisaskelSarakkeella = sarake_alku;
	else kaksoisaskelSarakkeella = -1;

	// Katsotaan jos nappula on sotilas ja rivi on p‰‰tyrivi niin korotetaan nappula kysym‰ll‰ mihin korotetaan	
	if (_lauta[rivi_alku][sarake_alku] == vs && rivi_loppu == 7 && rivi_alku == 6 && _siirtovuoro == 0 || _siirtovuoro == 1 && _lauta[rivi_alku][sarake_alku] == ms && rivi_loppu == 0 && rivi_alku == 1) {
	Nappula* korotettuNappula;
	korotettuNappula = siirto->_miksikorotetaan;
	_lauta[rivi_loppu][sarake_loppu] = korotettuNappula;
	_lauta[rivi_alku][sarake_alku] = NULL;
	rivi_alku = NULL;
	sarake_alku = NULL;
	}
	//muissa tapauksissa alkuruutuun null ja loppuruutuun sama alkuruudusta l‰htenyt nappula
	else {
		//Laittaa talteen otetun nappulan uuteen ruutuun
		_lauta[rivi_loppu][sarake_loppu] = _lauta[rivi_alku][sarake_alku];
		_lauta[rivi_alku][sarake_alku] = NULL;

	}
	// katsotaan jos liikkunut nappula on kuningas niin muutetaan onkoKuningasLiikkunut arvo 
	if (_siirtovuoro == 0 && !_onkoValkeaKuningasLiikkunut) // jos kuningas on liikkunut, on turha tarkastella torneja en‰‰, koska tornitus ei ole en‰‰ mahdollinen
	{
		if (_lauta[0][4] == NULL) {
			_onkoValkeaKuningasLiikkunut = true;
		}
		else if (!_onkoValkeaKTliikkunut || !_onkoValkeaDTliikkunut)
		{
			// katsotaan jos liikkunut nappula on torni niin muutetaan onkoTorniLiikkunut arvo
			if (_lauta[0][0] == NULL) {
				_onkoValkeaDTliikkunut = true;
			}
			if (_lauta[0][7] == NULL) {
				_onkoValkeaKTliikkunut = true;
			}

			//Jos molemmat tornit on liikkuneet, on turha en‰‰ tarkastella kuninkaan liikkumista, koska tornitus ei ole en‰‰ mahdollista
			if (_onkoValkeaDTliikkunut && _onkoValkeaKTliikkunut) _onkoValkeaKuningasLiikkunut = true;
		}

	}
	// katsotaan jos liikkunut nappula on kuningas niin muutetaan onkoKuningasLiikkunut arvo 
	else if (_siirtovuoro == 1 && !_onkoMustaKuningasLiikkunut) // jos kuningas on liikkunut, on turha tarkastella torneja en‰‰, koska tornitus ei ole en‰‰ mahdollinen
	{
		if (_lauta[7][4] == NULL) {
			_onkoMustaKuningasLiikkunut = true;
		}
		else if (!_onkoMustaKTliikkunut || !_onkoMustaDTliikkunut)
		{
			// katsotaan jos liikkunut nappula on torni niin muutetaan onkoTorniLiikkunut arvo (molemmille v‰reille ja molemmille torneille)
			if (_lauta[7][0] == NULL) {
				_onkoMustaDTliikkunut = true;
			}
			if (_lauta[7][7] == NULL) {
				_onkoMustaKTliikkunut = true;
			}

			//Jos molemmat tornit on liikkuneet, on turha en‰‰ tarkastella kuninkaan liikkumista, koska tornitus ei ole en‰‰ mahdollista
			if (_onkoMustaDTliikkunut && _onkoMustaKTliikkunut) _onkoMustaKuningasLiikkunut = true;
		}
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



double Asema::evaluoi() 
{
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

	double valkoinenArvo = 0;
	double mustaArvo = 0;
	//kertoimet asetettu sen takia ett‰ niiden avulla asioiden painoarvoa voidaan s‰‰t‰‰ helposti yhdest‰ paikasta
	double kuningasKerroin = 1;
	double keskustaKerroin = 1;
	double linjaKerroin = 0.05;

	//1. Nappuloiden arvo
	valkoinenArvo += laskeNappuloidenArvo(0);
	mustaArvo += laskeNappuloidenArvo(1);
	
	////2. Kuningas turvassa
	if (onkoAvausTaiKeskipeli(0)) {
//	// Jos lyhell‰ puolella saa lis‰arvoa 2 edellytt‰‰ ett‰ f ja g sotilas  paikallaan 
		if (_lauta[0][6] != NULL && _lauta[1][5] != NULL && _lauta[1][6] != NULL) {
			if (_lauta[0][6] == vk && _lauta[1][5] == vs && _lauta[1][6] == vs)
				valkoinenArvo += 2 * kuningasKerroin;
		}
		// Jos pitk‰ll‰ puolella saa lis‰arvooa 1 edelytt‰‰ ett‰  c ja b sotilas paikallaan
		if (_lauta[0][1] != NULL && _lauta[0][2] != NULL && _lauta[1][1] != NULL && _lauta[1][2] != NULL) {
			if (_lauta[0][1] == vk || _lauta[0][2] == vk && _lauta[1][1] ==vs && _lauta[1][2]== vs)
				valkoinenArvo += 1 * kuningasKerroin;
		}
	}
	if (onkoAvausTaiKeskipeli(1)) {
		// Jos lyhell‰ puolella saa lis‰arvoa 2 edellytt‰‰ ett‰ f ja g sotilas  paikallaan 
		if (_lauta[7][6] != NULL && _lauta[6][5] != NULL && _lauta[6][6] != NULL) {
			if (_lauta[7][6]== mk && _lauta[6][5]== ms && _lauta[6][6]==ms)
				mustaArvo -= 2 * kuningasKerroin;
		}
		// Jos pitk‰ll‰ puolella saa lis‰arvooa 1 edelytt‰‰ ett‰  c ja b sotilas paikallaan
		if (_lauta[7][1] != NULL && _lauta[7][2] != NULL && _lauta[7][1] != NULL && _lauta[7][2] != NULL) {
			if (_lauta[7][1] == mk || _lauta[7][2]== mk && _lauta[7][1] == ms && _lauta[7][2] ==ms)
				mustaArvo -= 1 * kuningasKerroin;
		}
	
	}
	//3. Arvosta keskustaa
	valkoinenArvo += nappuloitaKeskella(0) * keskustaKerroin;
	mustaArvo -= nappuloitaKeskella(1) * keskustaKerroin;
	
	// 4. Arvosta linjoja
	valkoinenArvo += linjaKerroin * linjat(0);
	mustaArvo -= linjaKerroin * linjat(1);

	//if (_lauta[0][4] == vk)
	//{

	//	std::list<Siirto> lista;
	//	Ruutu* ruutu = new Ruutu(0, 4);
	//	_lauta[0][4]->annaSiirrot(lista, ruutu, this, 0);
	//	annaLinnoitusSiirrot(lista, 0);
	//	for (auto s : lista) {
	//	
	//		if (s.onkoLyhytLinna() || s.onkoPitkalinna())
	//		{
	//			valkoinenArvo += 20;
	//		}
	//	}
	//}
	//
	//if (_lauta[7][4] == mk)
	//{

	//	std::list<Siirto> lista;
	//	Ruutu* ruutu = new Ruutu(7, 4);
	//	_lauta[7][4]->annaSiirrot(lista, ruutu, this, 1);
	//	annaLinnoitusSiirrot(lista, 1);
	//	for (auto s : lista) {
	//		if (s.onkoLyhytLinna() || s.onkoPitkalinna())
	//		{
	//			mustaArvo -= 20;
	//		}
	//	}
	//}
	

	//wcout << "evaluoi: " <<  valkoinenArvo + mustaArvo << endl;
	return valkoinenArvo + mustaArvo;
}


double Asema::laskeNappuloidenArvo(int vari) 
{
	double nappuloidenArvo = 0;

	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			if (_lauta[x][y] != NULL)
			{
				if (vari == 0)
				{
					//Valkoisen arvotus
					if (_lauta[x][y] == vd) nappuloidenArvo += 9;
					if (_lauta[x][y] == vt) nappuloidenArvo += 5;
					if (_lauta[x][y] == vl) nappuloidenArvo += 3.25f;
					if (_lauta[x][y] == vr) nappuloidenArvo += 3;
					if (_lauta[x][y] == vs) nappuloidenArvo += 1;
				}
				else 
				{
					//Mustan arvotus
					if (_lauta[x][y] == md) nappuloidenArvo -= 9;
					if (_lauta[x][y] == mt) nappuloidenArvo -= 5;
					if (_lauta[x][y] == ml) nappuloidenArvo -= 3.25f;
					if (_lauta[x][y] == mr) nappuloidenArvo -= 3;
					if (_lauta[x][y] == ms) nappuloidenArvo -= 1;
				}
			}
		}
	}

	return nappuloidenArvo;
}


bool Asema::onkoAvausTaiKeskipeli(int vari) 
{
	int upseerit = 0;
	bool daami = false;

	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			if (_lauta[x][y] == NULL) {
				continue;
			}

			if (vari == 1) //Valkoiset
			{
				if (_lauta[x][y] == vd) {
					upseerit += 1;
					daami = true;
				}
				if (_lauta[x][y] == vt) upseerit += 1;
				if (_lauta[x][y] == vr) upseerit += 1;
				if (_lauta[x][y] == vl) upseerit += 1;
			}
			else //Mustat
			{
				if (_lauta[x][y] == md) {
					upseerit += 1;
					daami = true;
				}
				if (_lauta[x][y] == mt) upseerit += 1;
				if (_lauta[x][y] == mr) upseerit += 1;
				if (_lauta[x][y] == ml) upseerit += 1;
			}
			
		}
	}
	//keskipeli jos upseereita yli 2 tai jos daami +1
	if (upseerit > 2 || (daami == true && upseerit > 1)) return true;
	else return false;
}


double Asema::nappuloitaKeskella(int vari) 
{
	//sotilaat ydinkeskustassa + 0.25/napa
	//ratsut ydinkeskustassa + 0.25/napa
	//sotilaat laitakeskustassa + 0.11/napa
	//ratsut laitakeskustassa + 0.11/napa
	double arvoKeskella = 0;
	//valkeille ydinkeskusta
	if (vari == 0)
	{
		if (_lauta[3][3] != NULL && _lauta[3][3] == vs || _lauta[3][3] == vr) arvoKeskella += 0.25;
		if (_lauta[3][4] && _lauta[3][4] == vs || _lauta[3][4] == vr ) arvoKeskella += 0.25;
		if (_lauta[4][3] != NULL && _lauta[4][3] == vs|| _lauta[4][3] == vr) arvoKeskella += 0.25;
		if (_lauta[4][4] != NULL && _lauta[4][4] == vs || _lauta[4][4] == vr) arvoKeskella += 0.25;
		//valkeille laitakeskusta
		for (int sarake = 2; sarake < 6; sarake++) {
			if (_lauta[2][sarake] != NULL && _lauta[2][sarake] == vs || _lauta[2][sarake] == vr) arvoKeskella += 0.11;
			if (_lauta[5][sarake] != NULL && _lauta[5][sarake] == vs || _lauta[5][sarake] == vr) arvoKeskella += 0.11;
		}
		for (int rivi = 3; rivi < 5; rivi++) {
			if (_lauta[rivi][2] != NULL && _lauta[rivi][2] == vs || _lauta[rivi][2] == vr) arvoKeskella += 0.11;
			if (_lauta[rivi][5] != NULL && _lauta[rivi][5] == vs || _lauta[rivi][5] == vr) arvoKeskella += 0.11;
		}
	}
	else 
	{
		//mustille ydinkeskusta
		if (_lauta[3][3] != NULL && _lauta[3][3] == ms || _lauta[3][3] == mr) arvoKeskella += 0.25;
		if (_lauta[3][4] && _lauta[3][4] == ms || _lauta[3][4] == mr) arvoKeskella += 0.25;
		if (_lauta[4][3] != NULL && _lauta[4][3] == ms || _lauta[4][3] == mr) arvoKeskella += 0.25;
		if (_lauta[4][4] != NULL && _lauta[4][4] == ms || _lauta[4][4] == mr) arvoKeskella += 0.25;
		//mustille laitakeskusta
		for (int sarake = 2; sarake < 6; sarake++) {
			if (_lauta[2][sarake] != NULL && _lauta[2][sarake] == ms || _lauta[2][sarake] == mr) arvoKeskella += 0.11;
			if (_lauta[5][sarake] != NULL && _lauta[5][sarake] == ms || _lauta[5][sarake] == mr) arvoKeskella += 0.11;
		}
		for (int rivi = 3; rivi < 5; rivi++) {
			if (_lauta[rivi][2] != NULL && _lauta[rivi][2] == ms || _lauta[rivi][2] == mr) arvoKeskella += 0.11;
			if (_lauta[rivi][5] != NULL && _lauta[rivi][5] == ms || _lauta[rivi][5] == mr) arvoKeskella += 0.11;
		}
	}
	return arvoKeskella;
}


double Asema::linjat(int vari) 
{
	int laillisiaSiirtoja = 0;
	std::list<Siirto> lista;

	//valkoiset
	if (vari == 0)
	{
		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {
				if (_lauta[x][y] == NULL) {
					continue;
				}
				if (_lauta[x][y] == vl) _lauta[x][y]->annaSiirrot(lista, &Ruutu(x, y), this, 0);
				if (_lauta[x][y] == vt) _lauta[x][y]->annaSiirrot(lista, &Ruutu(x, y), this, 0);
				if (_lauta[x][y] == vd) _lauta[x][y]->annaSiirrot(lista, &Ruutu(x, y), this, 0);
			}
		}
	}
	else 
	{
		//mustat
		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {
				if (_lauta[x][y] == NULL) {
					continue;
				}
				if (_lauta[x][y] == ml) _lauta[x][y]->annaSiirrot(lista, &Ruutu(x, y), this, 1);
				if (_lauta[x][y] == mt) _lauta[x][y]->annaSiirrot(lista, &Ruutu(x, y), this, 1);
				if (_lauta[x][y] == md) _lauta[x][y]->annaSiirrot(lista, &Ruutu(x, y), this, 1);
			}
		}
	}
	
	laillisiaSiirtoja = lista.size();
	return laillisiaSiirtoja;
}


MinMaxPaluu Asema::maxi(int syvyys, double alpha, double beta)
{
	std::list<Siirto> lista;
	Ruutu kuninkaanRuutu;
	this->annaLaillisetSiirrot(lista);
	double arvo;
	Asema uusiAsema;
	Siirto _parasSiirto;
	MinMaxPaluu paluu;

	// Check for checkmate or stalemate, if yes, exit asap, checkmate -100000, stalemate 0
	if (lista.size() == 0)
	{
		//kuninkaan ruutu
		for (int x = 0; x < 8; x++)
		{
			for (int y = 0; y < 8; y++)
			{
				if (this->_lauta[x][y] != NULL)
				{
					if (this->_lauta[x][y]->getKoodi() == VK)
					{
						kuninkaanRuutu.setSarake(y);
						kuninkaanRuutu.setRivi(x);
					}
				}

			}
		}
		//matti
		if (onkoRuutuUhattu(&kuninkaanRuutu, 1))
		{
			paluu._evaluointiArvo = -1000000;
			return paluu;
		}
		//patti
		if (!onkoRuutuUhattu(&kuninkaanRuutu, 1))
		{
			paluu._evaluointiArvo = 0;
			return paluu;
		}
	}
	//k‰y l‰pi pelipuuta l‰pi
	if (syvyys == 0)
	{
		paluu._evaluointiArvo = evaluoi();
		return paluu;
	}
	double maksimi = -1000000;
	for (auto s : lista)
	{
		uusiAsema = *this;
		uusiAsema.paivitaTestiAsema(&s);
		arvo = uusiAsema.mini(syvyys - 1, alpha, beta)._evaluointiArvo;
		if (arvo > maksimi)
		{
			maksimi = arvo;
			_parasSiirto = s;
		}
		alpha = std::max(alpha, arvo); // update alpha value
		if (alpha >= beta) { // prune the tree if alpha is greater than or equal to beta
			break;
		}
	}
	paluu._evaluointiArvo = maksimi;
	paluu._parasSiirto = _parasSiirto;
	//wcout << "maksimi: " << maksimi << endl;

	return paluu;
}

MinMaxPaluu Asema::mini(int syvyys, double alpha, double beta)
{
	std::list<Siirto> lista;
	Ruutu kuninkaanRuutu;
	this->annaLaillisetSiirrot(lista);
	double arvo;
	Asema uusiAsema;
	Siirto _parasSiirto;
	MinMaxPaluu paluu;

	// Check for checkmate or stalemate, if yes, exit asap, checkmate 100000, stalemate 0
	if (lista.size() == 0)
	{
		//kuninkaan ruutu
		for (int x = 0; x < 8; x++)
		{
			for (int y = 0; y < 8; y++)
			{
				if (this->_lauta[x][y] != NULL)
				{
					if (this->_lauta[x][y]->getKoodi() == VK)
					{
						kuninkaanRuutu.setSarake(y);
						kuninkaanRuutu.setRivi(x);
					}
				}

			}
		}
		//matti
		if (onkoRuutuUhattu(&kuninkaanRuutu, 2))
		{
			paluu._evaluointiArvo = 1000000;
			return paluu;
		}
		//patti
		if (!onkoRuutuUhattu(&kuninkaanRuutu, 2))
		{
			paluu._evaluointiArvo = 0;
			return paluu;
		}
	}
	//k‰y l‰pi pelipuuta l‰pi
	if (syvyys == 0)
	{
		paluu._evaluointiArvo = evaluoi();
		return paluu;
	}
	double minimi = 1000000;
	for (auto s : lista)
	{
		uusiAsema = *this;
		uusiAsema.paivitaTestiAsema(&s);
		arvo = uusiAsema.maxi(syvyys - 1, alpha, beta)._evaluointiArvo;
		if (arvo < minimi)
		{
			minimi = arvo;
			_parasSiirto = s;
		}
		if (minimi <= alpha) {
			paluu._evaluointiArvo = minimi;
			paluu._parasSiirto = _parasSiirto;
			return paluu;
		}
		beta = std::min(beta, minimi);
	}
	paluu._evaluointiArvo = minimi;
	paluu._parasSiirto = _parasSiirto;
	//wcout << "minimi: " << minimi << endl;
	return paluu;
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
		testiAsema.paivitaTestiAsema(&s);
		int rivi = 0;
		int sarake = 0;

		if (s.onkoLyhytLinna()) {
			sarake = 6;
			if (this->getSiirtovuoro() == 0) {
				rivi = 0;
				s.setAlkuruutu(rivi, 4);
				s.setLoppuruutu(rivi, sarake);
			}
			else {
				rivi = 7;
				s.setAlkuruutu(rivi, 4);
				s.setLoppuruutu(rivi, sarake);
			}
				
		}
		else if (s.onkoPitkalinna()){
			sarake = 2;
			if (this->getSiirtovuoro() == 0) {
				rivi = 0;
				s.setAlkuruutu(rivi, 4);
				s.setLoppuruutu(rivi, sarake);
			}
				
			else {
				rivi = 7;
				s.setAlkuruutu(rivi, 4);
				s.setLoppuruutu(rivi, sarake);
			}
				
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

		if (testiAsema.onkoRuutuUhattu(&Ruutu(rivi, sarake), !vari) == true) {
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
			lista.push_front(Siirto(true, false));
		}
		//Valkean pitk‰ linna
		if (!this->getOnkoValkeaKuningasLiikkunut() && !this->getOnkoValkeaDTliikkunut()
			&& this->onkoRuutuUhattu(&Ruutu(0, 4), 1) && this->onkoRuutuUhattu(&Ruutu(0, 3), 1) 
			&& this->onkoRuutuUhattu(&Ruutu(0, 2), 1) && this->onkoRuutuUhattu(&Ruutu(0, 1), 1)
			&& this->_lauta[0][3] == NULL && this->_lauta[0][2] == NULL && this->_lauta[0][1] == NULL) {
			//p‰ivitet‰‰n listaan lyhyt linna
			lista.push_front(Siirto(false, true));
		}
	}
	if (vari == 1) {
		//Musta lyhyt linna
		if (!this->getOnkoMustaKuningasLiikkunut() && !this->getOnkoMustaKTliikkunut()
			&& this->onkoRuutuUhattu(&Ruutu(7, 4), 0)
			&& this->onkoRuutuUhattu(&Ruutu(7, 5), 0) && this->onkoRuutuUhattu(&Ruutu(7, 6), 0)
			&& this->_lauta[7][5] == NULL && this->_lauta[7][6] == NULL) {
			//p‰ivitet‰‰n listaan lyhyt linna
			
			lista.push_front(Siirto(true,false));
		}
		//Mustan pitk‰ linna
		if (!this->getOnkoMustaKuningasLiikkunut() && !this->getOnkoMustaDTliikkunut()
			&& this->onkoRuutuUhattu(&Ruutu(7, 4), 0) && this->onkoRuutuUhattu(&Ruutu(7, 3), 0) 
			&& this->onkoRuutuUhattu(&Ruutu(7, 2), 0) && this->onkoRuutuUhattu(&Ruutu(7, 1), 0)
			&& this->_lauta[7][3] == NULL && this->_lauta[7][2] == NULL && this->_lauta[7][1] == NULL) {
			//p‰ivitet‰‰n listaan lyhyt linna
			lista.push_front(Siirto(false,true));
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
