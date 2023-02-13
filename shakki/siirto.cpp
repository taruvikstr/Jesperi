#include "siirto.h"


Siirto::Siirto(Ruutu _alkuRuutu, Ruutu _loppuRuutu)
{
    this->_alkuRuutu = _alkuRuutu;
    this->_loppuRuutu = _loppuRuutu;
    this->_lyhytLinna = false;
    this->_pitkaLinna = false;
}

Siirto::Siirto(bool _lyhytLinna, bool _pitkaLinna) 
{
    this->_lyhytLinna = _lyhytLinna;
    this->_pitkaLinna = _pitkaLinna;
 
}


Ruutu Siirto::getAlkuruutu()
{
    return this->_alkuRuutu;
}

void Siirto::setAlkuruutu(int rivi, int sarake)
{
    _alkuRuutu = Ruutu(rivi, sarake);
}
void Siirto::setLoppuruutu(int rivi, int sarake)
{
    _loppuRuutu = Ruutu(rivi, sarake);
}

Ruutu Siirto::getLoppuruutu()
{
    return this->_loppuRuutu;
}


bool Siirto::onkoLyhytLinna() 
{
    return this->_lyhytLinna;
}


bool Siirto::onkoPitkalinna() 
{
    return this->_pitkaLinna;
}
