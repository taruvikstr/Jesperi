#include "siirto.h"


Siirto::Siirto(Ruutu _alkuRuutu, Ruutu _loppuRuutu)
{
    this->_alkuRuutu = _alkuRuutu;
    this->_loppuRuutu = _loppuRuutu;
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
