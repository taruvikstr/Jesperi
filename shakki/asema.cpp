#include <iostream>
#include "asema.h"
#include "minMaxPaluu.h"
#include "nappula.h"
#include "ruutu.h"

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
	
	
	



	
	

	
	
	
	
	
}


void Asema::paivitaAsema(Siirto *siirto)
{
// Kaksoisaskel-lippu on oletusarvoisesti pois p��lt�.
    // Asetetaan my�hemmin, jos tarvii.
    _kaksoisaskel = false;

    //Tarkastetaan on siirto lyhyt linna

    //check if the move is a short castle
    if (siirto->getAlku()->getX() == 4 && siirto->getAlku()->getY() == 0 && siirto->getLoppu()->getX() == 6 && siirto->getLoppu()->getY() == 0) {
        _lauta[0][5] = _lauta[0][7];
        _lauta[0][7] = NULL;
        _lauta[0][4] = NULL;
        _lauta[0][6] = vk;
        return;
    }


    // onko pitk� linna
//check if the move is a long castle
    if (siirto->getAlku()->getX() == 4 && siirto->getAlku()->getY() == 0 && siirto->getLoppu()->getX() == 2 && siirto->getLoppu()->getY() == 0) {
        _lauta[0][3] = _lauta[0][0];
        _lauta[0][0] = NULL;
        _lauta[0][4] = NULL;
        _lauta[0][2] = vk;
        return;
    }



    // Kaikki muut siirrot
    // All other moves




    //Ottaa siirron alkuruudussa olleen nappulan talteen

    //takes the piece in the starting square and saves it
    Nappula* nappula = _lauta[siirto->getAlku()->getY()][siirto->getAlku()->getX()];


    //Laittaa talteen otetun nappulan uuteen ruutuun


    _lauta[siirto->getLoppu()->getY()][siirto->getLoppu()->getX()] = nappula;

    // Tarkistetaan oliko sotilaan kaksoisaskel
    // Jos oli, niin asetetaan kaksoisaskel-lippu p��lle
    // Check if the move was a double pawn move
    // If it was, set the double pawn move flag on
    if (nappula->getTyyppi() == VS && siirto->getAlku()->getY() == 1 && siirto->getLoppu()->getY() == 3) {
        _kaksoisaskel = true;
    }
    // (asetetaan kaksoisaskel-lippu)






    // Ohestaly�nti on tyhj��n ruutuun. Vieress� oleva (sotilas) poistetaan.

    // En passant is an empty square. The adjacent (pawn) is removed.
    if (nappula->getTyyppi() == VS && siirto->getAlku()->getY() == 4 && siirto->getLoppu()->getY() == 5) {
        _lauta[4][siirto->getLoppu()->getX()] = NULL;
    }

    //// Katsotaan jos nappula on sotilas ja rivi on p��tyrivi niin ei vaihdeta nappulaa
    ////eli alkuruutuun laitetaan null ja loppuruudussa on jo kliittym�n laittama nappula MIIKKA, ei taida minmaxin kanssa hehkua?

    // If the piece is a pawn and the row is the end row, then do not change the piece
    // ie. put null in the starting square and the piece in the end square is already the piece MIIKKA, does not seem to work with minmax?
    if (nappula->getTyyppi() == VS && siirto->getLoppu()->getY() == 7) {
        _lauta[siirto->getAlku()->getY()][siirto->getAlku()->getX()] = NULL;
    }

    //
    ////muissa tapauksissa alkuruutuun null ja loppuruutuun sama alkuruudusta l�htenyt nappula

    // katsotaan jos liikkunut nappula on kuningas niin muutetaan onkoKuningasLiikkunut arvo (molemmille v�reille)
    // In other cases, put null in the starting square and the end square to the same piece that left the starting square
    // If the moved piece is a king, then change the value of onkoKuningasLiikkunut (for both colors)
    if (nappula->getTyyppi() == VK) {
        _onkoKuningasLiikkunut = true;
    }

    // katsotaan jos liikkunut nappula on torni niin muutetaan onkoTorniLiikkunut arvo (molemmille v�reille ja molemmille torneille)
    // If the moved piece is a rook, then change the value of onkoTorniLiikkunut (for both colors and both rooks)
    if (nappula->getTyyppi() == VT) {
        if (siirto->getAlku()->getX() == 0) {
            _onkoTorniLiikkunut = true;
        }
        if (siirto->getAlku()->getX() == 7) {
            _onkoTorniLiikkunut = true;
        }
    }

    //p�ivitet��n _siirtovuoro
    //update _siirtovuoro
    if (_siirtovuoro == VALKOINEN) {
        _siirtovuoro = MUSTA;
    }
    else {
        _siirtovuoro = VALKOINEN;
    }

}



int Asema::getSiirtovuoro()
{
    return _siirtovuoro;

}


void Asema::setSiirtovuoro(int vuoro)
{
    _siirtovuoro = vuoro;

}


bool Asema::getOnkoValkeaKuningasLiikkunut()
{
    return _onkoKuningasLiikkunut;

}


bool Asema::getOnkoMustaKuningasLiikkunut()
{
    return _onkoKuningasLiikkunut;

}


bool Asema::getOnkoValkeaDTliikkunut()
{
    return _onkoTorniLiikkunut;

}


bool Asema::getOnkoValkeaKTliikkunut()
{
    return _onkoTorniLiikkunut;

}


bool Asema::getOnkoMustaDTliikkunut()
{
    return _onkoTorniLiikkunut;

}


bool Asema::getOnkoMustaKTliikkunut()
{
    return _onkoTorniLiikkunut;

}


/* 1. Laske nappuloiden arvo
Daami = 9
Torni = 5
L�hetti = 3,25
Ratsu = 3
Sotilas = 1

2. Kuninkaan hyvyys
Jos avaus tai keskipeli, niin hyv� ett� kunigas g1 tai b1/c1
Loppupeliss� vaikea sanoa halutaanko olla auttamassa omaa sotilasta korottumaan
vai olla est�m�ss� vastustajan korotusta siksi ei oteta kantaa
3. Arvosta keskustaa sotilailla ja ratsuilla
4. Arvosta pitki� linjoja daami, torni ja l�hetti
*/
double Asema::evaluoi() 
{
	return 0;

	//kertoimet asetettu sen takia ett� niiden avulla asioiden painoarvoa voidaan s��t�� helposti yhdest� paikasta
	
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
	// Jos upseereita 3 tai v�hemm�n on loppupeli
	// mutta jos daami laudalla on loppueli vasta kun kuin vain daami j�ljell�
	
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


// https://chessprogramming.wikispaces.com/Minimax MinMax-algoritmin pseudokoodi (lis�sin parametrina aseman)
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
	
	// Rekursion kantatapaus 2: katkaisusyvyydess�
	
	// Rekursioaskel: kokeillaan jokaista laillista siirtoa s
	// (alustetaan paluuarvo huonoimmaksi mahdolliseksi).
	
	return paluuarvo;
}


MinMaxPaluu Asema::maxi(int syvyys) 
{
	MinMaxPaluu paluu;
	return paluu;
}


MinMaxPaluu Asema::mini(int syvyys) 
{
	MinMaxPaluu paluu;
	return paluu;
}


bool Asema::onkoRuutuUhattu(Ruutu* ruutu, int vastustajanVari)
{

	return false;
}


void Asema::huolehdiKuninkaanShakeista(std::list<Siirto>& lista, int vari) 
{ 
	
}


void Asema::annaLaillisetSiirrot(std::list<Siirto>& lista) {
	
}
