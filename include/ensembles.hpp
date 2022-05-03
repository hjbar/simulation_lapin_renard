#pragma once

#include "const.hpp"
#include <array>
#include <doctest/doctest.h>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>

using namespace std;

struct Ensemble
{

public:
	// Constructeurs

	/** Créé une Ensemble vide **/
	Ensemble();

	// Méthodes

	/** Renvoie un ostringstream représentant un Ensemble
	 * @return ch un ostringstream
	**/
	ostringstream affiche() const;

	/** Renvoie true si l'Ensemble est vide, false sinon
	 * @return un booléen
	**/
	bool estVide() const;

	/** Renvoie le nombre d'éléments d'un Ensemble
	 * @return un entier
	**/
	int cardinal() const;

	/** Ajoute un entier n à un Ensemble
	 * @param n un entier
	**/
	void ajoute(int n);

	/** Renvoie et supprime un élément n d'un Ensemble
	 * @return n un entier
	**/
	int tire();

	// Getters

	/** Renvoie l'élément en i-eme position d'un Ensemble
	 * @param n un entier
	 * @return un entier
	**/
	int getCase(int n) const;

private:
	// Atributs
	array<int, MAXCARD> t;
	int card;
};

ostream& operator<<(ostream& out, const Ensemble a);
