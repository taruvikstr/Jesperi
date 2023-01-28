#pragma once
#include <ostream>

// Shakkilaudan ruutu tietyssä (rivi, sarake) -koordinaatissa.
class Ruutu{
public:
	Ruutu(int, int);
	Ruutu() { _rivi = 0; _sarake = 0; }
	int getRivi();
	int getSarake();
	void setRivi(int);
	void setSarake(int);

private:
	int _sarake;
	int _rivi;
};
