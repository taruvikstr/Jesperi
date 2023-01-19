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
    // Valkoisen kuninkaan lyhyen linnan siirto
    if (_alkuRuutu.getSarake() == 0 && _alkuRuutu.getRivi() == 4 
        && _loppuRuutu.getSarake() == 0 && _loppuRuutu.getRivi() == 6) return this->_lyhytLinna = true;

    // Mustan kuninkaan lyhyen linnan siirto
    else if (_alkuRuutu.getSarake() == 7 && _alkuRuutu.getRivi() == 4
        && _loppuRuutu.getSarake() == 7 && _loppuRuutu.getRivi() == 6) return this->_lyhytLinna = true;
   
    else  return this->_lyhytLinna = false;
}


bool Siirto::onkoPitkalinna() 
{
    // Valkoisen kuninkaan pitkän linnan siirto
    if (_alkuRuutu.getSarake() == 0 && _alkuRuutu.getRivi() == 4
        && _loppuRuutu.getSarake() == 0 && _loppuRuutu.getRivi() == 2) return this->_lyhytLinna = true;

    // Mustan kuninkaan pitkän linnan siirto
    else if (_alkuRuutu.getSarake() == 7 && _alkuRuutu.getRivi() == 4
        && _loppuRuutu.getSarake() == 7 && _loppuRuutu.getRivi() == 2) return this->_lyhytLinna = true;

    else  return this->_lyhytLinna = false;

}
