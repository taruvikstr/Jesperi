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
            lista.push_back(Siirto(*ruutu, Ruutu(i, sarake)));
        }
        else if (asema->_lauta[i][sarake] != NULL && omaVari != asema->_lauta[i][sarake]->getVari())
        {
            lista.push_back(Siirto(*ruutu, Ruutu(i, sarake)));
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
            lista.push_back(Siirto(*ruutu, Ruutu(i, sarake)));

        }
        else if (asema->_lauta[i][sarake] != NULL && omaVari != asema->_lauta[i][sarake]->getVari())
        {
            lista.push_back(Siirto(*ruutu, Ruutu(i, sarake)));
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
            lista.push_back(Siirto(*ruutu, Ruutu(rivi, i)));

        }
        else if (asema->_lauta[rivi][i] != NULL && omaVari != asema->_lauta[rivi][i]->getVari())
        {
            lista.push_back(Siirto(*ruutu, Ruutu(rivi, i)));
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
            lista.push_back(Siirto(*ruutu, Ruutu(rivi, i)));

        }
        else if (asema->_lauta[rivi][i] != NULL && omaVari != asema->_lauta[rivi][i]->getVari())
        {
            lista.push_back(Siirto(*ruutu, Ruutu(rivi, i)));
            break;
        }
    }

    asema->listatorni.assign(lista.begin(), lista.end());
}

void Ratsu::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari) {

    asema->_lauta[ruutu->getRivi()][ruutu->getSarake()] = this;
    int omaVari = this->getVari();
    int rivi = ruutu->getRivi();
    int sarake = ruutu->getSarake();

    if (rivi + 2 <= 7 && sarake + 1 <=  7) // 2 riviä ylös, 1 sarake oikealle
    {
        if (asema->_lauta[rivi + 2][sarake + 1] != NULL) {
            if (omaVari != asema->_lauta[rivi + 2][sarake + 1]->getVari())
                lista.push_back(Siirto(*ruutu, Ruutu(rivi + 2, sarake + 1)));
        }else
        {
            lista.push_back(Siirto(*ruutu, Ruutu(rivi + 2, sarake + 1)));
        }
    }

    if (rivi + 2 <= 7 && sarake - 1 >= 0) // kaksi riviä ylös, yksi sarake vasemmalle
    {
        if (asema->_lauta[rivi + 2][sarake - 1] != NULL) {
            if (omaVari != asema->_lauta[rivi + 2][sarake - 1]->getVari())
                lista.push_back(Siirto(*ruutu, Ruutu(rivi + 2, sarake - 1)));
        }else
        {
            lista.push_back(Siirto(*ruutu, Ruutu(rivi + 2, sarake - 1)));
        }
    }

    if (rivi - 2 >= 0 && sarake + 1 <= 7) // kaksi riviä alas, yksi sarake oikealle
    {
        if (asema->_lauta[rivi - 2][sarake + 1] != NULL) {
            if (omaVari != asema->_lauta[rivi - 2][sarake + 1]->getVari())
                lista.push_back(Siirto(*ruutu, Ruutu(rivi - 2, sarake + 1)));
        }else
        {
            lista.push_back(Siirto(*ruutu, Ruutu(rivi - 2, sarake + 1)));
        }
    }

    if (rivi - 2 >= 0 && sarake - 1 >= 0) // kaksi riviä alas, yksi sarake vasemmalle
    {
        if (asema->_lauta[rivi - 2][sarake - 1] != NULL) {
            if (omaVari != asema->_lauta[rivi - 2][sarake - 1]->getVari())
                lista.push_back(Siirto(*ruutu, Ruutu(rivi - 2, sarake - 1)));
        }else
        {
            lista.push_back(Siirto(*ruutu, Ruutu(rivi - 2, sarake - 1)));
        }
    }

    if (rivi + 1 <= 7 && sarake + 2 <= 7) // yksi rivi ylös, kaksi saraketta oikealle
    {
        if (asema->_lauta[rivi + 1][sarake + 2] != NULL) {
            if (omaVari != asema->_lauta[rivi + 1][sarake + 2]->getVari())
                lista.push_back(Siirto(*ruutu, Ruutu(rivi + 1, sarake + 2)));
        }else
        {
            lista.push_back(Siirto(*ruutu, Ruutu(rivi + 1, sarake + 2)));
        }
    }

    if (rivi + 1 <= 7 && sarake - 2 >= 0) // yksi rivi ylös, kaksi saraketta vasemmalle
    {
        if (asema->_lauta[rivi + 1][sarake - 2] != NULL) {
            if (omaVari != asema->_lauta[rivi + 1][sarake - 2]->getVari())
                lista.push_back(Siirto(*ruutu, Ruutu(rivi + 1, sarake - 2)));
        }else
        {
            lista.push_back(Siirto(*ruutu, Ruutu(rivi + 1, sarake - 2)));
        }
    }

    if (rivi - 1 >= 0 && sarake + 2 <= 7) // yksi rivi alas, kaksi saraketta oikealle
    {
        if (asema->_lauta[rivi - 1][sarake + 2] != NULL) {
            if (omaVari != asema->_lauta[rivi - 1][sarake + 2]->getVari())
                lista.push_back(Siirto(*ruutu, Ruutu(rivi - 1, sarake + 2)));
        }else
        {
            lista.push_back(Siirto(*ruutu, Ruutu(rivi - 1, sarake + 2)));
        }
    }

    if (rivi - 1 >= 0 && sarake - 2 >= 0) // yksi rivi alas, kaksi saraketta vasemmalle
    {
        if (asema->_lauta[rivi - 1][sarake - 2] != NULL) {
            if (omaVari != asema->_lauta[rivi - 1][sarake - 2]->getVari())
                lista.push_back(Siirto(*ruutu, Ruutu(rivi - 1, sarake - 2)));
        }else
        {
            lista.push_back(Siirto(*ruutu, Ruutu(rivi - 1, sarake - 2)));
        }
    }
    asema->listaratsu.assign(lista.begin(), lista.end());
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
                lista.push_back(Siirto(*ruutu, Ruutu(i + 1, sarake)));
                break;
            }

        }
        else
        {
            lista.push_back(Siirto(*ruutu, Ruutu(i + 1, sarake)));
        }

        
    }
    sarake = ruutu->getSarake();

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
                lista.push_back(Siirto(*ruutu, Ruutu(i - 1, sarake)));
                break;
            }

        }
        else
        {
            lista.push_back(Siirto(*ruutu, Ruutu(i - 1, sarake)));
        }

    }

    sarake = ruutu->getSarake();

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
                lista.push_back(Siirto(*ruutu, Ruutu(i + 1, sarake)));
                break;
            }

        }
        else
        {
            lista.push_back(Siirto(*ruutu, Ruutu(i + 1, sarake)));
        }

    }

    sarake = ruutu->getSarake();
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
                lista.push_back(Siirto(*ruutu, Ruutu(i - 1, sarake)));
                break;
            }

        }
        else
        {
            lista.push_back(Siirto(*ruutu, Ruutu(i - 1, sarake)));
        }

    }
    asema->listalahetti.assign(lista.begin(), lista.end());
}
        


void Daami::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
    // inherits from torni and Lahetti

    Torni::annaSiirrot(lista, ruutu, asema, vari);
    Lahetti::annaSiirrot(lista, ruutu, asema, vari);
    
    asema->listadaami.assign(lista.begin(), lista.end());
	
}


void Kuningas::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	/*perusidea on ett� kaikki viereiset ruudut ovat sallittuja. kuten tornilla ja l�hetill�,
	oman nappulan p��lle ei voi menn� ja vastustajan nappulan voi sy�d�.

	Kaikki muu kuninkaaseen liittyv� tarkistus tehd��n eri paikassa*/
    asema->_lauta[ruutu->getRivi()][ruutu->getSarake()] = this;
    int omaVari = this->getVari();

    //yläpuolella oleva rivi
    //ylävasen
    if (ruutu->getRivi() + 1 <= 7 && ruutu->getSarake() - 1 >= 0) {
        //toinen nappula ruudussa
        if (asema->_lauta[ruutu->getRivi() + 1][ruutu->getSarake() - 1] != NULL) {
            //toinen nappula eri väriä
            if (omaVari != asema->_lauta[ruutu->getRivi() + 1][ruutu->getSarake() - 1]->getVari()) {
                lista.push_back(Siirto(*ruutu, Ruutu(ruutu->getRivi() + 1, ruutu->getSarake() - 1)));
            }
        }//tyhjä ruutu
        else {
            lista.push_back(Siirto(*ruutu, Ruutu(ruutu->getRivi() + 1, ruutu->getSarake() - 1)));
        }
    }
    //suoraan yläpuolella
    if (ruutu->getRivi() + 1 <= 7) {
        //toinen nappula ruudussa
        if (asema->_lauta[ruutu->getRivi() + 1][ruutu->getSarake()] != NULL) {
            //toinen nappula eri väriä
            if (omaVari != asema->_lauta[ruutu->getRivi() + 1][ruutu->getSarake()]->getVari()) {
                lista.push_back(Siirto(*ruutu, Ruutu(ruutu->getRivi() + 1, ruutu->getSarake())));
            }
        }//tyhjä ruutu
        else {
            lista.push_back(Siirto(*ruutu, Ruutu(ruutu->getRivi() + 1, ruutu->getSarake())));
        }
    }
    //yläoikea
    if (ruutu->getRivi() + 1 >= 0 && ruutu->getSarake() + 1 <= 7) {
        //toinen nappula ruudussa
        if (asema->_lauta[ruutu->getRivi() + 1][ruutu->getSarake() + 1] != NULL) {
            //toinen nappula eri väriä
            if (omaVari != asema->_lauta[ruutu->getRivi() + 1][ruutu->getSarake() + 1]->getVari()) {
                lista.push_back(Siirto(*ruutu, Ruutu(ruutu->getRivi() + 1, ruutu->getSarake() + 1)));
            }
        }//tyhjä ruutu
        else {
            lista.push_back(Siirto(*ruutu, Ruutu(ruutu->getRivi() + 1, ruutu->getSarake() + 1)));
        }
    }
    //alapuolella oleva rivi
    //alavasen
    if (ruutu->getRivi() - 1 >= 0 && ruutu->getSarake() - 1 >= 0) {
        //toinen nappula ruudussa
        if (asema->_lauta[ruutu->getRivi() - 1][ruutu->getSarake() - 1] != NULL) {
            //toinen nappula eri väriä
            if (omaVari != asema->_lauta[ruutu->getRivi() - 1][ruutu->getSarake() - 1]->getVari()) {
                lista.push_back(Siirto(*ruutu, Ruutu(ruutu->getRivi() - 1, ruutu->getSarake() - 1)));
            }
        }//tyhjä ruutu
        else {
            lista.push_back(Siirto(*ruutu, Ruutu(ruutu->getRivi() - 1, ruutu->getSarake() - 1)));
        }
    }
    //suoraan alapuolella
    if (ruutu->getRivi() - 1 >= 0) {
        //toinen nappula ruudussa
        if (asema->_lauta[ruutu->getRivi() - 1][ruutu->getSarake()] != NULL) {
            //toinen nappula eri väriä
            if (omaVari != asema->_lauta[ruutu->getRivi() - 1][ruutu->getSarake()]->getVari()) {
                lista.push_back(Siirto(*ruutu, Ruutu(ruutu->getRivi() - 1, ruutu->getSarake())));
            }
        }//tyhjä ruutu
        else {
            lista.push_back(Siirto(*ruutu, Ruutu(ruutu->getRivi() - 1, ruutu->getSarake())));
        }
    }
    //alaoikea
    if (ruutu->getRivi() - 1 >= 0 && ruutu->getSarake() +1 <= 7) {
        //toinen nappula ruudussa
        if (asema->_lauta[ruutu->getRivi() - 1][ruutu->getSarake() + 1] != NULL) {
            //toinen nappula eri väriä
            if (omaVari != asema->_lauta[ruutu->getRivi() - 1][ruutu->getSarake() + 1]->getVari()) {
                lista.push_back(Siirto(*ruutu, Ruutu(ruutu->getRivi() - 1, ruutu->getSarake() + 1)));
            }
        }//tyhjä ruutu
        else {
            lista.push_back(Siirto(*ruutu, Ruutu(ruutu->getRivi() - 1, ruutu->getSarake() + 1)));
        }
    }
    //onko vasemmalla 
    if (ruutu->getSarake() - 1 >= 0) {
        if (asema->_lauta[ruutu->getRivi()][ruutu->getSarake() - 1] != NULL) {
            if (omaVari != asema->_lauta[ruutu->getRivi()][ruutu->getSarake() - 1]->getVari()) {
                lista.push_back(Siirto(*ruutu, Ruutu(ruutu->getRivi(), ruutu->getSarake() - 1)));
            }
        }
        else {
            lista.push_back(Siirto(*ruutu, Ruutu(ruutu->getRivi(), ruutu->getSarake() - 1)));
        }
    }
    
    //ja oikealla    
    if (ruutu->getSarake() + 1 <= 7) {
        if (asema->_lauta[ruutu->getRivi()][ruutu->getSarake() + 1] != NULL) {
            if (omaVari != asema->_lauta[ruutu->getRivi()][ruutu->getSarake() + 1]->getVari()) {
                lista.push_back(Siirto(*ruutu, Ruutu(ruutu->getRivi(), ruutu->getSarake() + 1)));
            }
        }
        else {
            lista.push_back(Siirto(*ruutu, Ruutu(ruutu->getRivi(), ruutu->getSarake() + 1)));
        }
    }
    
        
    asema->listakunkku.assign(lista.begin(), lista.end());
}


void Sotilas::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
    asema->_lauta[ruutu->getRivi()][ruutu->getSarake()] = this;
    int omaVari = this->getVari();

    int rivi = ruutu->getRivi();
    int sarake = ruutu->getSarake(); // Y SUUNTA

    if (omaVari == 0) {
        //valkoisen kaksoisaskel
        if (rivi == 1 && asema->_lauta[rivi + 1][sarake] == NULL
            && asema->_lauta[rivi + 2][sarake] == NULL) {
            lista.push_back(Siirto(*ruutu, Ruutu(rivi + 2, sarake)));
        }
        //yläviisto vasemmalle jos ei ole tyhjä ja vastustaja ruudussa
        if (asema->_lauta[rivi + 1][sarake - 1] != NULL) {
            if (omaVari != asema->_lauta[rivi + 1][sarake - 1]->getVari() && rivi < 6) {
                lista.push_back(Siirto(*ruutu, Ruutu(rivi + 1, sarake - 1)));
            }
            else {
                lisaaSotilaanKorotukset(&Siirto(*ruutu, Ruutu(rivi + 1, sarake - 1)), lista, asema);
            }
        }
        //yläviisto oikealla jos ei ole tyhjä ja vastustaja ruudussa
        if (asema->_lauta[rivi + 1][sarake + 1] != NULL) {
            if (omaVari != asema->_lauta[rivi + 1][sarake + 1]->getVari() && rivi < 6) {
                lista.push_back(Siirto(*ruutu, Ruutu(rivi + 1, sarake + 1)));
            }
            else {
                lisaaSotilaanKorotukset(&Siirto(*ruutu, Ruutu(rivi + 1, sarake + 1)), lista, asema);
            }
        }
        //suoraan ylös oleva kohta tyhjä
        if (asema->_lauta[rivi + 1][sarake] == NULL) {
            if (rivi < 6) {
                lista.push_back(Siirto(*ruutu, Ruutu(rivi + 1, sarake)));
            }
            else {
                lisaaSotilaanKorotukset(&Siirto(*ruutu, Ruutu(rivi + 1, sarake)), lista, asema);
            }
        }

        // Ohestalyönti on tyhjään ruutuun.
       //valkoinen tekee ohesta lyönnin, jos ohesta lyönti mahdollinen ja aloitusruudun jommalla kummalla puolella on sotilas      
       //oikealla puolella oleva musta sotilas
        if (asema->kaksoisaskelSarakkeella == 1 && asema->_lauta[rivi][sarake - 1] != NULL
            && asema->_lauta[rivi][sarake - 1]->getVari() != omaVari)
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
            lista.push_back(Siirto(*ruutu, Ruutu(rivi - 2, sarake)));
        }
        //alaviisto vasemmalle jos ei ole tyhjä ja vastustaja ruudussa
        if (asema->_lauta[rivi - 1][sarake - 1] != NULL) {
            if (omaVari != asema->_lauta[rivi - 1][sarake - 1]->getVari() && rivi > 1) {
                lista.push_back(Siirto(*ruutu, Ruutu(rivi - 1, sarake - 1)));
            }
            else {
                lisaaSotilaanKorotukset(&Siirto(*ruutu, Ruutu(rivi - 1, sarake - 1)), lista, asema);
            }
        }

        //alaviisto oikealla jos ei ole tyhjä ja vastustaja ruudussa
        if (asema->_lauta[rivi - 1][sarake + 1] != NULL) {
            if (omaVari != asema->_lauta[rivi - 1][sarake + 1]->getVari() && rivi > 1) {
                lista.push_back(Siirto(*ruutu, Ruutu(rivi - 1, sarake + 1)));
            }
            else {
                lisaaSotilaanKorotukset(&Siirto(*ruutu, Ruutu(rivi - 1, sarake + 1)), lista, asema);
            }
        }

        //suoraan ylös oleva kohta tyhjä
        if (asema->_lauta[rivi - 1][sarake] == NULL) {
            if (rivi > 1) {
                lista.push_back(Siirto(*ruutu, Ruutu(rivi - 1, sarake)));
            }
            else {
                lisaaSotilaanKorotukset(&Siirto(*ruutu, Ruutu(rivi - 1, sarake)), lista, asema);
            }
        }

        // Ohestalyönti on tyhjään ruutuun.
            //musta tekee ohesta lyönnin, jos ohesta lyönti mahdollinen ja aloitusruudun jommalla kummalla puolella on sotilas      
            //oikealla puolella oleva valkoinen sotilas
        if (asema->kaksoisaskelSarakkeella == 0 && asema->_lauta[rivi][sarake - 1] != NULL
            && asema->_lauta[rivi][sarake - 1]->getVari() != omaVari)
        {
            asema->_lauta[rivi - 1][sarake - 1];
        }
        //vasemmalla puolella oleva valkoinen sotilas
        if (asema->kaksoisaskelSarakkeella == 0 && asema->_lauta[rivi][sarake + 1] != NULL
            && asema->_lauta[rivi][sarake + 1]->getVari() != omaVari)
        {
            asema->_lauta[rivi - 1][sarake + 1];
        }
    }
    asema->listasotilas.assign(lista.begin(), lista.end());
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
