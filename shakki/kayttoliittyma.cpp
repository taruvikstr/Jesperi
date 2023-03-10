#include <Windows.h>
#include <iostream>
#include <string>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include "kayttoliittyma.h"

using namespace std;


Kayttoliittyma* Kayttoliittyma::instance = 0;


Kayttoliittyma* Kayttoliittyma::getInstance()
{
	if (instance == 0)
		instance = new Kayttoliittyma();
	return instance;
	
}

void Kayttoliittyma::piirraLautaF(std::list<Siirto> lista) {
	for (Siirto kohta : lista) {
		//wcout << kohta.getLoppuruutu().getRivi() << " Rivi " << kohta.getLoppuruutu().getSarake() << " Sarake" << endl;
	}
	_setmode(_fileno(stdout), _O_U16TEXT);
	for (int i = 0; i < 8; i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
			BACKGROUND_GREEN | BACKGROUND_BLUE);

		wcout << 8 - i << " ";
		int index = 0;
		for (int j = 0; j < 8; j++)
		{
			
			bool move = false;
			for (Siirto kohta : lista) { 
				if (7 - i == kohta.getLoppuruutu().getRivi() && j == kohta.getLoppuruutu().getSarake()) {
					move = true;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY |
						BACKGROUND_RED);
					break;
				}
			}
			if (i % 2 == 0 && !move) {
				if (index % 2 != 0) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY |
					BACKGROUND_GREEN);
				else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY |
					BACKGROUND_BLUE);
			}
			else if (!move) {
				if (index % 2 == 0) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY |
					BACKGROUND_GREEN);
				else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY |
					BACKGROUND_BLUE);
			}
			if (_asema->_lauta[7 - i][j] != NULL) {
				wcout << " " << _asema->_lauta[7 - i][j]->getUnicode() << " ";
			}
			else {
				wcout << "   ";
				
				
			}
			index++;
			
		}
		
		
			wcout  << endl;
			
			
	}
	wcout << L"   A  B  C  D  E  F  G  H " << endl;
}
void Kayttoliittyma::piirraLauta()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	for (int i = 0; i < 8; i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
			BACKGROUND_GREEN | BACKGROUND_BLUE);

		wcout << 8 - i << " ";
		int index = 0;
		for (int j = 0; j < 8; j++)
		{
			if (i % 2 == 0) {

				if(index % 2 != 0) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY |
					BACKGROUND_GREEN);
				else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY |
					BACKGROUND_BLUE);
			}
			else {
				if (index % 2 == 0) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY |
					BACKGROUND_GREEN);
				else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY |
					BACKGROUND_BLUE);
			}



			if (_asema->_lauta[7-i][j] != NULL) {

				wcout << " " << _asema->_lauta[7-i][j]->getUnicode() << " ";
			}
			else {
				wcout << "   ";
			}
			index++;
		}
		wcout << endl;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
		BACKGROUND_GREEN | BACKGROUND_BLUE);

	wcout << L"   A  B  C  D  E  F  G  H " << endl;
}


/*
	Aliohjelma tarkistaa ett??? k???ytt???j???n antama sy???te siirroksi on 
	muodollisesti korrekti (ei tarkista aseman laillisuutta)
	Ottaa irti myos nappulan kirjaimen (K/D/L/R/T), tarkistaa etta kirjain korrekti
*/
Siirto Kayttoliittyma::annaVastustajanSiirto() {
	int alkuX, alkuY, loppuX, loppuY;
	string inputString;
	bool isValid = false;


	// give opponents move
	do {
		wcout << "Give your move: ";
		cin >> inputString;
		if (inputString == "O-O")
		{
			Siirto siirto(true, false);
			int rivi = 0;
			int sarake = 4;
			if (_vari == 1)
				rivi = 7;
			siirto.setAlkuruutu(rivi, sarake);
			siirto.setLoppuruutu(rivi, sarake);
			return siirto;
		}
		else if (inputString == "O-O-O")
		{
			Siirto siirto(false, true);
			int rivi = 0;
			int sarake = 4;
			if (_vari == 1)
				rivi = 7;
			siirto.setAlkuruutu(rivi, sarake);
			siirto.setLoppuruutu(rivi, sarake);
			return siirto;
		}
		// check input length
		else if (inputString.length() != 6 && inputString.length() != 5) {
			wcout << "Invalid move format. Example: e2-e4 or e7e5 A" + inputString.length();
			continue;
		}

		// check if input is in correct format
		if (!isalpha(inputString[0]) || !isalpha(inputString[1]) || !isdigit(inputString[2]) || inputString[3] != '-' || !isalpha(inputString[4]) || !isdigit(inputString[5])) {
			if (!isalpha(inputString[0]) || !isdigit(inputString[1]) || inputString[2] != '-' || !isalpha(inputString[3]) || !isdigit(inputString[4])) {
				wcout << "Invalid move format. Example: e2-e4 or e7e5 B";
				continue;
			}
			
		}

		if (inputString.length() == 6) {
			// convert input to coordinates
			alkuX = inputString[1] - 'a';
			alkuY = inputString[2] - '1';
			loppuX = inputString[4] - 'a';
			loppuY = inputString[5] - '1';
		}
		if (inputString.length() == 5) {
			// convert input to coordinates
			alkuX = inputString[0] - 'a';
			alkuY = inputString[1] - '1';
			loppuX = inputString[3] - 'a';
			loppuY = inputString[4] - '1';
		}

		// check if coordinates are within chess board range
		if (alkuX >= 0 && alkuX <= 7 && alkuY >= 0 && alkuY <= 7 && loppuX >= 0 && loppuX <= 7 && loppuY >= 0 && loppuY <= 7) {
			isValid = true;
		}
		else {
			wcout << "Invalid move. Move has to include numbers and letters presented on the board." << endl;
		}
	} while (!isValid);
	// create move object and return it
	Ruutu alkuRuutu;
	alkuRuutu.setRivi(alkuY);
	alkuRuutu.setSarake(alkuX);
	Ruutu loppuRuutu;
	loppuRuutu.setRivi(loppuY);
	loppuRuutu.setSarake(loppuX);
	Siirto siirto(alkuRuutu, loppuRuutu);
	return siirto;
}




int Kayttoliittyma::kysyVastustajanVari()
{
	int vari;
	wcout << "Give your color (0 = white 1 = black): " << endl;
	cin >> vari;
	_vari = vari;
	return vari;
}

