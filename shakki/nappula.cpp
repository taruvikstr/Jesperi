#include <list>
#include <string>
#include "asema.h"
#include "nappula.h"
#include <ios>
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
    int omaVari = vari;
    int rivi = ruutu->getRivi();
    int sarake = ruutu->getSarake();

    for (int i = rivi + 1; i <= 7; i++)
    {
        if (asema->_lauta[i][sarake] != NULL && omaVari == asema->_lauta[i][sarake]->getVari()) // ei tyhjä mut oma väri tulee vastaan
        {
            break;
        }
        else if (asema->_lauta[i][sarake] == NULL)
        {
            lista.push_back(Siirto(ruutu, new Ruutu(i, sarake)));
        }
        else if (asema->_lauta[i][sarake] != NULL && omaVari != asema->_lauta[i][sarake]->getVari())
        {
            lista.push_back(Siirto(ruutu, new Ruutu(i, sarake)));
            break;
        }

    }
    for (int i = rivi - 1; i >= 0; i--)
    {
        if (asema->_lauta[i][ruutu->getSarake()] != NULL && omaVari == asema->_lauta[i][sarake]->getVari()) {

            break;
        }
        else if (asema->_lauta[i][sarake] == NULL)
        {
            lista.push_back(Siirto(ruutu, new Ruutu(i, sarake)));

        }
        else if (asema->_lauta[i][sarake] != NULL && omaVari != asema->_lauta[i][sarake]->getVari())
        {
            lista.push_back(Siirto(ruutu, new Ruutu(i, sarake)));
            break;
        }
    }
    for (int i = sarake + 1; i <= 7; i++)
    {

        if (asema->_lauta[rivi][i] != NULL && omaVari == asema->_lauta[rivi][i]->getVari()) {

            break;
        }
        else if (asema->_lauta[rivi][i] == NULL)
        {
            lista.push_back(Siirto(ruutu, new Ruutu(rivi, i)));

        }
        else if (asema->_lauta[rivi][i] != NULL && omaVari != asema->_lauta[rivi][i]->getVari())
        {
            lista.push_back(Siirto(ruutu, new Ruutu(rivi, i)));
            break;
        }
    }

    for (int i = sarake - 1; i >= 0; i--)
    {
        if (asema->_lauta[rivi][i] != NULL && omaVari == asema->_lauta[rivi][i]->getVari()) {


            break;
        }
        else if (asema->_lauta[rivi][i] == NULL)
        {
            lista.push_back(Siirto(ruutu, new Ruutu(rivi, i)));

        }
        else if (asema->_lauta[rivi][i] != NULL && omaVari != asema->_lauta[rivi][i]->getVari())
        {
            lista.push_back(Siirto(ruutu, new Ruutu(rivi, i)));
            break;
        }
    }

    asema->listatorni = lista;
}

void Ratsu::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari) {
    asema->_lauta[ruutu->getRivi()][ruutu->getSarake()] = this;
    int omaVari = this->getVari();
    if (ruutu->getRivi() + 2 <= 7 && ruutu->getSarake() + 1 <=  7)
    {
        if (asema->_lauta[ruutu->getRivi() + 2][ruutu->getSarake() + 1] != NULL) {
            if (omaVari != asema->_lauta[ruutu->getRivi() + 2][ruutu->getSarake() + 1]->getVari())
                lista.push_back(Siirto(ruutu, new Ruutu(ruutu->getRivi() + 2, ruutu->getSarake() + 1)));
        }else
        {
            lista.push_back(Siirto(ruutu, new Ruutu(ruutu->getRivi() + 2, ruutu->getSarake() + 1)));
        }
    }

    if (ruutu->getRivi()  + 2 <= 7 && ruutu->getSarake() - 1 >= 0)
    {
        if (asema->_lauta[ruutu->getRivi() + 2][ruutu->getSarake() - 1] != NULL) {
            if (omaVari != asema->_lauta[ruutu->getRivi() + 2][ruutu->getSarake() - 1]->getVari())
                lista.push_back(Siirto(ruutu, new Ruutu(ruutu->getRivi() + 2, ruutu->getSarake() - 1)));
        }else
        {
            lista.push_back(Siirto(ruutu, new Ruutu(ruutu->getRivi() + 2, ruutu->getSarake() - 1)));
        }
    }

    if (ruutu->getRivi() - 2 >= 0 && ruutu->getSarake() + 1 <= 7)
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

    if (ruutu->getRivi() + 1 <= 7 && ruutu->getSarake() + 2 <= 7)
    {
        if (asema->_lauta[ruutu->getRivi() + 1][ruutu->getSarake() + 2] != NULL) {
            if (omaVari != asema->_lauta[ruutu->getRivi() + 1][ruutu->getSarake() + 2]->getVari())
                lista.push_back(Siirto(ruutu, new Ruutu(ruutu->getRivi() + 1, ruutu->getSarake() + 2)));
        }else
        {
            lista.push_back(Siirto(ruutu, new Ruutu(ruutu->getRivi() + 1, ruutu->getSarake() + 2)));
        }
    }

    if (ruutu->getRivi() + 1 <= 7 && ruutu->getSarake() - 2 >= 0)
    {
        if (asema->_lauta[ruutu->getRivi() + 1][ruutu->getSarake() - 2] != NULL) {
            if (omaVari != asema->_lauta[ruutu->getRivi() + 1][ruutu->getSarake() - 2]->getVari())
                lista.push_back(Siirto(ruutu, new Ruutu(ruutu->getRivi() + 1, ruutu->getSarake() - 2)));
        }else
        {
            lista.push_back(Siirto(ruutu, new Ruutu(ruutu->getRivi() + 1, ruutu->getSarake() - 2)));
        }
    }

    if (ruutu->getRivi() - 1 >= 0 && ruutu->getSarake() + 2 <= 7)
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
    asema->listaratsu = lista;
}


void Lahetti::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{

    asema->_lauta[ruutu->getRivi()][ruutu->getSarake()] = this;
    int omaVari = this->getVari();
    int rivi = ruutu->getRivi() ;
    int sarake = ruutu->getSarake();

    for (int i = rivi; i + 1 <= 7; i++)
    {
        sarake++;
        if (sarake > 7) break;

        else if (asema->_lauta[i+ 1][sarake] != NULL)
        {

            if (omaVari == asema->_lauta[i + 1][sarake]->getVari())
            {
                break;
            }
            else
            {
                lista.push_back(Siirto(ruutu, new Ruutu(i + 1, sarake)));
                break;
            }

        }
        else
        {
            lista.push_back(Siirto(ruutu, new Ruutu(i + 1, sarake)));
        }

        
    }

    for (int i = rivi; i - 1 >= 0; i--)
    {
        sarake++;
        if (sarake > 7) break;
        else if (asema->_lauta[i - 1][sarake] != NULL)
        {
            if (omaVari == asema->_lauta[i - 1][sarake]->getVari())
            {
                break;
            }
            else
            {
                lista.push_back(Siirto(ruutu, new Ruutu(i - 1, sarake)));
                break;
            }

        }
        else
        {
            lista.push_back(Siirto(ruutu, new Ruutu(i - 1, sarake)));
        }

    }

    for (int i = rivi; i + 1 <= 7; i++)
    {
        sarake--;
        if (sarake < 0) break;
        else if (asema->_lauta[i + 1][sarake] != NULL)
        {

            if (omaVari == asema->_lauta[i + 1][sarake]->getVari())
            {
                break;
            }
            else
            {
                lista.push_back(Siirto(ruutu, new Ruutu(i + 1, sarake)));
                break;
            }

        }
        else
        {
            lista.push_back(Siirto(ruutu, new Ruutu(i + 1, sarake)));
        }

    }

    for (int i = rivi; i - 1 >= 0; i--)
    {
        sarake--;
        if (sarake < 0) break;
        else if (asema->_lauta[i - 1][sarake] != NULL)
        {

            if (omaVari == asema->_lauta[i - 1][sarake]->getVari())
            {
                break;
            }
            else
            {
                lista.push_back(Siirto(ruutu, new Ruutu(i - 1, sarake)));
                break;
            }

        }
        else
        {
            lista.push_back(Siirto(ruutu, new Ruutu(i - 1, sarake)));
        }

    }
    asema->listalahetti = lista;
}
        


void Daami::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
    // inherits from torni and Lahetti

    Torni::annaSiirrot(lista, ruutu, asema, vari);
    Lahetti::annaSiirrot(lista, ruutu, asema, vari);
    
    asema->listadaami = lista;
	
}


void Kuningas::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	/*perusidea on ett� kaikki viereiset ruudut ovat sallittuja. kuten tornilla ja l�hetill�,
	oman nappulan p��lle ei voi menn� ja vastustajan nappulan voi sy�d�.

	Kaikki muu kuninkaaseen liittyv� tarkistus tehd��n eri paikassa*/
    asema->_lauta[ruutu->getRivi()][ruutu->getSarake()] = this;
    int omaVari = this->getVari();

    //katsoo kuninkaan yläpuolella olevan rivin
    for (int i = -1; i < 1; i++) {
        if (ruutu->getRivi() + 1 <= 7) {
            if (asema->_lauta[ruutu->getRivi() + 1][ruutu->getSarake() + i] != NULL) {
                if (omaVari != asema->_lauta[ruutu->getRivi() + 1][ruutu->getSarake() + i]->getVari()) {
                    lista.push_back(Siirto(ruutu, new Ruutu(ruutu->getRivi() + 1, ruutu->getSarake() + i)));
                }
            }
            else {
                lista.push_back(Siirto(ruutu, new Ruutu(ruutu->getRivi() + 1, ruutu->getSarake() + i)));
            }
        }
        
    }
    //alapuolella oleva rivi
    for (int i = -1; i < 1; i++) {
        if (ruutu->getRivi() - 1 >= 0) {
            if (asema->_lauta[ruutu->getRivi() - 1][ruutu->getSarake() + i] != NULL) {
                if (omaVari != asema->_lauta[ruutu->getRivi() - 1][ruutu->getSarake() + i]->getVari()) {
                    lista.push_back(Siirto(ruutu, new Ruutu(ruutu->getRivi() - 1, ruutu->getSarake() + i)));
                }
            }
            else {
                lista.push_back(Siirto(ruutu, new Ruutu(ruutu->getRivi() - 1, ruutu->getSarake() + i)));
            }
        }
    }
    //onko vasemmalla 
    if (ruutu->getSarake() - 1 >= 0) {
        if (asema->_lauta[ruutu->getRivi()][ruutu->getSarake() - 1] != NULL) {
            if (omaVari != asema->_lauta[ruutu->getRivi()][ruutu->getSarake() - 1]->getVari()) {
                lista.push_back(Siirto(ruutu, new Ruutu(ruutu->getRivi(), ruutu->getSarake() - 1)));
            }
        }
        else {
            lista.push_back(Siirto(ruutu, new Ruutu(ruutu->getRivi(), ruutu->getSarake() - 1)));
        }
    }
    
    //ja oikealla    
    if (ruutu->getSarake() + 1 <= 7) {
        if (asema->_lauta[ruutu->getRivi()][ruutu->getSarake() + 1] != NULL) {
            if (omaVari != asema->_lauta[ruutu->getRivi()][ruutu->getSarake() + 1]->getVari()) {
                lista.push_back(Siirto(ruutu, new Ruutu(ruutu->getRivi(), ruutu->getSarake() + 1)));
            }
        }
        else {
            lista.push_back(Siirto(ruutu, new Ruutu(ruutu->getRivi(), ruutu->getSarake() + 1)));
        }
    }
    
        
    asema->listakunkku = lista;
}


void Sotilas::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
    asema->_lauta[ruutu->getSarake()][ruutu->getRivi()] = this;
    int omaVari = this->getVari();

    int rivi = ruutu->getRivi();
    int sarake = ruutu->getSarake(); // Y SUUNTA

    if (omaVari == 0) {
        //valkoisen kaksoisaskel
        if (rivi == 1 && asema->_lauta[rivi + 1][sarake] == NULL
            && asema->_lauta[rivi + 2][sarake] == NULL) {
            lista.push_back(Siirto(ruutu, new Ruutu(rivi + 2, sarake)));
        }
        //yläviisto vasemmalle jos ei ole tyhjä ja vastustaja ruudussa
            if (asema->_lauta[rivi+1][sarake - 1] != NULL) {
                if (omaVari != asema->_lauta[rivi+1][sarake - 1]->getVari() && rivi < 6) {
                    lista.push_back(Siirto(ruutu, new Ruutu(rivi + 1, sarake - 1)));
                }
                else {
                    lisaaSotilaanKorotukset(&Siirto(*ruutu, Ruutu(rivi+1, sarake-1)), lista, asema);
                }
            }
            //yläviisto oikealla jos ei ole tyhjä ja vastustaja ruudussa
            if (asema->_lauta[rivi +1][sarake+ 1] != NULL) {
                if (omaVari != asema->_lauta[rivi + 1][sarake + 1]->getVari() && rivi < 6) {
                    lista.push_back(Siirto(ruutu, new Ruutu(rivi + 1, sarake + 1)));
                }
                else {
                    lisaaSotilaanKorotukset(&Siirto(*ruutu, Ruutu(rivi + 1, sarake + 1)), lista, asema);
                }
            }
            //suoraan ylös oleva kohta tyhjä
            if (asema->_lauta[rivi+1][sarake] == NULL) {
                if (rivi < 6) {
                    lista.push_back(Siirto(ruutu, new Ruutu(rivi, sarake + 1)));
                }
                else {
                    lisaaSotilaanKorotukset(&Siirto(*ruutu, Ruutu(rivi, sarake + 1)), lista, asema);
                }
            }

            // Ohestalyönti on tyhjään ruutuun.
           //valkoinen tekee ohesta lyönnin, jos ohesta lyönti mahdollinen ja aloitusruudun jommalla kummalla puolella on sotilas      
           //oikealla puolella oleva musta sotilas
            if (asema->kaksoisaskelSarakkeella == 1 && asema->_lauta [rivi] [sarake - 1] != NULL
                && asema->_lauta [rivi][sarake - 1]->getVari() != omaVari)
            {
                asema->_lauta[rivi + 1][sarake - 1];
            }
            //vasemmalla puolella oleva musta sotilas
            if (asema->kaksoisaskelSarakkeella == 1 && asema->_lauta[rivi][sarake + 1] != NULL
                && asema->_lauta[rivi][sarake + 1]->getVari() != omaVari)
            {
                asema->_lauta[rivi + 1][sarake + 1];
            }
    
        }
    if (omaVari == 1) {
        //mustan kaksoisaskel
        if (rivi == 6 && asema->_lauta[rivi - 1][sarake] == NULL
            && asema->_lauta[rivi - 2][sarake] == NULL) {
            lista.push_back(Siirto(ruutu, new Ruutu(rivi - 2, sarake)));
        }
        //alaviisto vasemmalle jos ei ole tyhjä ja vastustaja ruudussa
        if (asema->_lauta[rivi - 1][sarake - 1] != NULL) {
            if (omaVari != asema->_lauta[rivi - 1][sarake - 1]->getVari() && rivi>1) {
                lista.push_back(Siirto(ruutu, new Ruutu(rivi - 1, sarake - 1)));
            }
            else {
                lisaaSotilaanKorotukset(&Siirto(*ruutu, Ruutu(rivi - 1, sarake - 1)), lista, asema);
            }
        }
       
        //alaviisto oikealla jos ei ole tyhjä ja vastustaja ruudussa
        if (asema->_lauta[rivi - 1][sarake + 1] != NULL) {
            if (omaVari != asema->_lauta[rivi - 1][sarake + 1]->getVari() && rivi > 1) {
                lista.push_back(Siirto(ruutu, new Ruutu(rivi - 1, sarake + 1)));
            }
            else {
                lisaaSotilaanKorotukset(&Siirto(*ruutu, Ruutu(rivi - 1, sarake + 1)), lista, asema);
            }
        }
       
        //suoraan ylös oleva kohta tyhjä
        if (asema->_lauta[rivi-1][sarake] == NULL) {
            if (rivi > 1) {
                lista.push_back(Siirto(ruutu, new Ruutu(rivi-1, sarake)));
            }
            else {
                lisaaSotilaanKorotukset(&Siirto(*ruutu, Ruutu(rivi-1, sarake)), lista, asema);
            }
        }
       
        // Ohestalyönti on tyhjään ruutuun.
            //musta tekee ohesta lyönnin, jos ohesta lyönti mahdollinen ja aloitusruudun jommalla kummalla puolella on sotilas      
            //oikealla puolella oleva valkoinen sotilas
            if (asema->kaksoisaskelSarakkeella == 0 && asema->_lauta[rivi][sarake -1] != NULL
                && asema->_lauta[rivi][sarake-1]->getVari() != omaVari)
            {
                asema->_lauta[rivi - 1][sarake - 1];
            }
            //vasemmalla puolella oleva valkoinen sotilas
            if (asema->kaksoisaskelSarakkeella == 0 && asema->_lauta[rivi][sarake +1] != NULL
                && asema->_lauta[rivi][sarake +1]->getVari() != omaVari)
            {
                asema->_lauta[rivi -1][sarake + 1];
            }
        }
    asema->listasotilas = lista;
    }
  


void Sotilas::lisaaSotilaanKorotukset(Siirto* siirto, std::list<Siirto>& lista, Asema* asema) {

    if (siirto->getLoppuruutu().getRivi() == 7) {
        //valkea korottaa
        siirto->_miksikorotetaan = asema->vd;
        lista.push_back(*siirto);

        Siirto torniksi = *siirto;
        torniksi._miksikorotetaan = asema->vt;
        lista.push_back(torniksi);

        Siirto lahetiksi = *siirto;
        lahetiksi._miksikorotetaan = asema->vl;
        lista.push_back(lahetiksi);

        Siirto ratsuksi = *siirto;
        ratsuksi._miksikorotetaan = asema->vr;
        lista.push_back(ratsuksi);
    }
    else if (siirto->getLoppuruutu().getRivi() == 0) {

        //musta korottaa
        siirto->_miksikorotetaan = asema->md;
        lista.push_back(*siirto);

        Siirto torniksi = *siirto;
        torniksi._miksikorotetaan = asema->mt;
        lista.push_back(torniksi);

        Siirto lahetiksi = *siirto;
        lahetiksi._miksikorotetaan = asema->ml;
        lista.push_back(lahetiksi);

        Siirto ratsuksi = *siirto;
        ratsuksi._miksikorotetaan = asema->mr;
        lista.push_back(ratsuksi);

    }
}
