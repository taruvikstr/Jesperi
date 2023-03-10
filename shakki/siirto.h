#pragma once
#include "ruutu.h"

// Ns. "forward declaration". Nyt Asema-luokassa voidaa esitell? Nappula-osoittimia ilman,
// ett? nappula.h -tiedostoa t?ytyy includoida.
class Nappula; 


// Siirto kuvaa nappulan siirtymisen ruudusta toiseen, mukaanlukien erikoissiirrot
// (linnoitus ja ohestaly?nti).
class Siirto
{
public:
	Siirto(Ruutu, Ruutu);
	Siirto() { _lyhytLinna = false; _pitkaLinna = false; };
	Siirto(bool, bool); // Linnoitus lyhyesti (K-siipi) tai pitk?sti (D-siipi?
	Ruutu getAlkuruutu();
	void setAlkuruutu(int rivi, int sarake);
	void setLoppuruutu(int rivi, int sarake);
	Ruutu getLoppuruutu();
	bool onkoLyhytLinna();
	bool onkoPitkalinna();
	Nappula* _miksikorotetaan = 0;
private:

	
	Ruutu _alkuRuutu;
	Ruutu _loppuRuutu;
	bool _lyhytLinna;
	bool _pitkaLinna;
};