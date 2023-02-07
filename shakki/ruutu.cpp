#include "ruutu.h"


Ruutu::Ruutu(int rivi, int sarake)
{
    this->_sarake = sarake;
    this->_rivi = rivi;
}


int Ruutu::getRivi() 
{
    return this->_rivi;

}


int Ruutu::getSarake() 
{
    return this->_sarake;

}


void Ruutu::setRivi(int rivi) 
{
    this->_rivi = rivi;
}


void Ruutu::setSarake(int sarake) 
{
    this->_sarake = sarake;
}
