#pragma once

#include "const.hpp"
#include "ensembles.hpp"
#include <algorithm>
#include <doctest/doctest.h>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct Coord
{

public:
	// Constructeurs

	/** Créer une Coord (x,y)
	 * @param lig un entier
	 * @param col un entier
	**/
	Coord(int lig, int col);

	/** Créer une Coord (x,y) tel que x * TAILLEGRILLE + y = n
	 * @param n un entier
	**/
	Coord(int n);

	// Méthode

	/** Renvoie un entier n tel que pour une Coord (x,y), n = x * TAILLEGRILLE + y
	 * return n un entier
	**/
	int toInt() const;

	/** Renvoie un Ensemble contenant les voisins d'une Coord(x, y) avec des entiers
	 * @return ev un Ensemble
	**/
	Ensemble voisines() const;

	// Getters

	/** Renvoie x d'une Coord(x,y)
	 * @return x un entier
	**/
	int getX() const;

	/** Renvoie y d'une Coord(x,y)
	 * @return y un entier
	**/
	int getY() const;

private:
	// Attributs
	int x;
	int y;
};

// Opérateurs
ostream& operator<<(ostream& out, const Coord a);
bool operator==(const Coord a, const Coord b);
