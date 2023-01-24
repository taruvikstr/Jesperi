#include <list>
#include <string>
#include "asema.h"
#include "nappula.h"
using namespace std;


Nappula::Nappula(wstring unicode, int vari, int koodi)
{
	this->_unicode = unicode;
	this->_vari = vari;
	this->_koodi = koodi;
	
	
}


void Torni::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{


    asema->_lauta[ruutu->getRivi()][ruutu->getSarake()] = this;
    int omaVari = this->getVari();

    for(int i = ruutu->getRivi() + 1; i < 7; i++)
    {


       if(asema->_lauta[i][ruutu->getSarake()] != NULL)
           if(omaVari = asema->_lauta[i][ruutu->getSarake()]->getVari())
               break;

           else if(omaVari != asema->_lauta[i][ruutu->getSarake()]->getVari())
           {
               lista.push_back(Siirto(ruutu, new Ruutu(i, ruutu->getSarake())));
               break;
           }

           else
           {
               lista.push_back(Siirto(ruutu, new Ruutu(i, ruutu->getSarake())));

           }







    }
    for(int i = ruutu->getRivi() - 1; i > 0; i--)
    {


        if(asema->_lauta[i][ruutu->getSarake()] != NULL)
            if(omaVari = asema->_lauta[i][ruutu->getSarake()]->getVari())
                break;

            else if(omaVari != asema->_lauta[i][ruutu->getSarake()]->getVari())
            {
                lista.push_back(Siirto(ruutu, new Ruutu(i, ruutu->getSarake())));
                break;
            }

            else
            {
                lista.push_back(Siirto(ruutu, new Ruutu(i, ruutu->getSarake())));

            }

    }

    for(int i = ruutu->getSarake() + 1; i < 7; i++)
    {


        if(asema->_lauta[ruutu->getRivi()][i] != NULL)
            if(omaVari = asema->_lauta[ruutu->getRivi()][i]->getVari())
                break;

            else if(omaVari != asema->_lauta[ruutu->getRivi()][i]->getVari())
            {
                lista.push_back(Siirto(ruutu, new Ruutu( ruutu->getRivi(), i));
                break;
            }

            else
            {
                lista.push_back(Siirto(ruutu, new Ruutu(ruutu->getRivi(),i)));

            }






    }

    for(int i = ruutu->getSarake() - 1; i >  0; i--)
    {


        if(asema->_lauta[ruutu->getRivi()][i] != NULL)
            if(omaVari = asema->_lauta[ruutu->getRivi()][i]->getVari())
                break;

            else if(omaVari != asema->_lauta[ruutu->getRivi()][i]->getVari())
            {
                lista.push_back(Siirto(ruutu, new Ruutu( ruutu->getRivi(), i));
                break;
            }

            else
            {
                lista.push_back(Siirto(ruutu, new Ruutu(ruutu->getRivi(),i)));

            }

    }

}


void Ratsu::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari) {
    asema->_lauta[ruutu->getRivi()][ruutu->getSarake()] = this;
    int omaVari = this->getVari();
    if (ruutu->getRivi() + 2 =< 7 && ruutu->getSarake() + 1 =< 7)
    {
        if (asema->_lauta[ruutu->getRivi() + 2][ruutu->getSarake() + 1] != NULL) {
            if (omaVari != asema->_lauta[ruutu->getRivi() + 2][ruutu->getSarake() + 1]->getVari())
                lista.push_back(Siirto(ruutu, new Ruutu(ruutu->getRivi() + 2, ruutu->getSarake() + 1)));
        }else
        {
            lista.push_back(Siirto(ruutu, new Ruutu(ruutu->getRivi() + 2, ruutu->getSarake() + 1)));
        }
    }

    if (ruutu->getRivi()  + 2 =< 7 && ruutu->getSarake() - 1 >= 0)
    {
        if (asema->_lauta[ruutu->getRivi() + 2][ruutu->getSarake() - 1] != NULL) {
            if (omaVari != asema->_lauta[ruutu->getRivi() + 2][ruutu->getSarake() - 1]->getVari())
                lista.push_back(Siirto(ruutu, new Ruutu(ruutu->getRivi() + 2, ruutu->getSarake() - 1)));
        }else
        {
            lista.push_back(Siirto(ruutu, new Ruutu(ruutu->getRivi() + 2, ruutu->getSarake() - 1)));
        }
    }

    if (ruutu->getRivi() - 2 >= 0 && ruutu->getSarake() + 1 =< 7)
    {
        if (asema->_lauta[ruutu->getRivi() - 2][ruutu->getSarake() + 1] != NULL) {
            if (omaVari != asema->_lauta[ruutu->getRivi() - 2][ruutu->getSarake() + 1]->getVari())
                lista.push_back(Siirto(ruutu, new Ruutu(ruutu->getRivi() - 2, ruutu->getSarake() + 1)));
        }else
        {
            lista.push_back(Siirto(ruutu, new Ruutu(ruutu->getRivi() - 2, ruutu->getSarake() + 1)));
        }
    }

    if (ruutu->getRivi() - 2 >= 0 && ruutu->getSarake() - 1 >= 0)
    {
        if (asema->_lauta[ruutu->getRivi() - 2][ruutu->getSarake() - 1] != NULL) {
            if (omaVari != asema->_lauta[ruutu->getRivi() - 2][ruutu->getSarake() - 1]->getVari())
                lista.push_back(Siirto(ruutu, new Ruutu(ruutu->getRivi() - 2, ruutu->getSarake() - 1)));
        }else
        {
            lista.push_back(Siirto(ruutu, new Ruutu(ruutu->getRivi() - 2, ruutu->getSarake() - 1)));
        }
    }

    if (ruutu->getRivi() + 1 =< 7 && ruutu->getSarake() + 2 =< 7)
    {
        if (asema->_lauta[ruutu->getRivi() + 1][ruutu->getSarake() + 2] != NULL) {
            if (omaVari != asema->_lauta[ruutu->getRivi() + 1][ruutu->getSarake() + 2]->getVari())
                lista.push_back(Siirto(ruutu, new Ruutu(ruutu->getRivi() + 1, ruutu->getSarake() + 2)));
        }else
        {
            lista.push_back(Siirto(ruutu, new Ruutu(ruutu->getRivi() + 1, ruutu->getSarake() + 2)));
        }
    }

    if (ruutu->getRivi() + 1 =< 7 && ruutu->getSarake() - 2 >= 0)
    {
        if (asema->_lauta[ruutu->getRivi() + 1][ruutu->getSarake() - 2] != NULL) {
            if (omaVari != asema->_lauta[ruutu->getRivi() + 1][ruutu->getSarake() - 2]->getVari())
                lista.push_back(Siirto(ruutu, new Ruutu(ruutu->getRivi() + 1, ruutu->getSarake() - 2)));
        }else
        {
            lista.push_back(Siirto(ruutu, new Ruutu(ruutu->getRivi() + 1, ruutu->getSarake() - 2)));
        }
    }

    if (ruutu->getRivi() - 1 >= 0 && ruutu->getSarake() + 2 =< 7)
    {
        if (asema->_lauta[ruutu->getRivi() - 1][ruutu->getSarake() + 2] != NULL) {
            if (omaVari != asema->_lauta[ruutu->getRivi() - 1][ruutu->getSarake() + 2]->getVari())
                lista.push_back(Siirto(ruutu, new Ruutu(ruutu->getRivi() - 1, ruutu->getSarake() + 2)));
        }else
        {
            lista.push_back(Siirto(ruutu, new Ruutu(ruutu->getRivi() - 1, ruutu->getSarake() + 2)));
        }
    }

    if (ruutu->getRivi() - 1 >= 0 && ruutu->getSarake() - 2 >= 0)
    {
        if (asema->_lauta[ruutu->getRivi() - 1][ruutu->getSarake() - 2] != NULL) {
            if (omaVari != asema->_lauta[ruutu->getRivi() - 1][ruutu->getSarake() - 2]->getVari())
                lista.push_back(Siirto(ruutu, new Ruutu(ruutu->getRivi() - 1, ruutu->getSarake() - 2)));
        }else
        {
            lista.push_back(Siirto(ruutu, new Ruutu(ruutu->getRivi() - 1, ruutu->getSarake() - 2)));
        }
    }

}


void Lahetti::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{

    asema->_lauta[ruutu->getRivi()][ruutu->getSarake()] = this;
    int omaVari = this->getVari();


    for(int i = ruutu->getRivi(), i < 7, i++)
    {

        for(int j = ruutu->getSarake(), j < 7, j++)
        {




         if(asema->_lauta[ruutu->getRivi() + i][ruutu->getSarake() + j ]!= NULL)


             if(omaVari != asema->_lauta[ruutu->getRivi() + i][ruutu->getSarake() + j]->getVari())
                 break;
             else
                lista.push_back(Siirto(ruutu, new Ruutu(ruutu->getRivi() + i, ruutu->getSarake() + j)));
                break;



            }else
            {
                lista.push_back(Siirto(ruutu, new Ruutu(ruutu->getRivi() + i, ruutu->getSarake() + j)));
            }

        }
    }

    for(int i = ruutu->getRivi(), i < 7, i++)
    {

        for(int j = ruutu->getSarake(), j > 0, j--)
        {

                if(asema->_lauta[ruutu->getRivi() + i][ruutu->getSarake() - j ]!= NULL)

                if(omaVari != asema->_lauta[ruutu->getRivi() + i][ruutu->getSarake() - j]->getVari())
                    break;
                else
                    lista.push_back(Siirto(ruutu, new Ruutu(ruutu->getRivi() + i, ruutu->getSarake() - j)));
                    break;

                }else
                {
                    lista.push_back(Siirto(ruutu, new Ruutu(ruutu->getRivi() + i, ruutu->getSarake() - j)));
                }
            }
        }

        for(int i = ruutu->getRivi(), i > 0, i--)
        {

            for(int j = ruutu->getSarake(), j < 7, j++)
            {

                if(asema->_lauta[ruutu->getRivi() - i][ruutu->getSarake() + j ]!= NULL)

                if(omaVari != asema->_lauta[ruutu->getRivi() - i][ruutu->getSarake() + j]->getVari())
                    break;
                else
                    lista.push_back(Siirto(ruutu, new Ruutu(ruutu->getRivi() - i, ruutu->getSarake() + j)));
                    break;

                }else
                {
                    lista.push_back(Siirto(ruutu, new Ruutu(ruutu->getRivi() - i, ruutu->getSarake() + j)));
                }
            }
        }

        for(int i = ruutu->getRivi(), i > 0, i--)
        {

            for(int j = ruutu->getSarake(), j > 0, j--)
            {

                if(asema->_lauta[ruutu->getRivi() - i][ruutu->getSarake() - j ]!= NULL)

                if(omaVari != asema->_lauta[ruutu->getRivi() - i][ruutu->getSarake() - j]->getVari())
                    break;
                else
                    lista.push_back(Siirto(ruutu, new Ruutu(ruutu->getRivi() - i, ruutu->getSarake() - j)));
                    break;

                }else
                {
                    lista.push_back(Siirto(ruutu, new Ruutu(ruutu->getRivi() - i, ruutu->getSarake() - j)));
                }
            }
        }







}


void Daami::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
    // inherits from Ratsu and Lahetti

    Ratsu::annaSiirrot(lista, ruutu, asema, vari);
    Lahetti::annaSiirrot(lista, ruutu, asema, vari);
    

	
}


void Kuningas::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	/*perusidea on ett� kaikki viereiset ruudut ovat sallittuja. kuten tornilla ja l�hetill�,
	oman nappulan p��lle ei voi menn� ja vastustajan nappulan voi sy�d�.

	Kaikki muu kuninkaaseen liittyv� tarkistus tehd��n eri paikassa*/


	
}


void Sotilas::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	
}


void Sotilas::lisaaSotilaanKorotukset(Siirto* siirto, std::list<Siirto>& lista, Asema* asema) {
	
}
