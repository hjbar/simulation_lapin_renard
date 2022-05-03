#pragma once

#include "const.hpp"
#include "coord.hpp"
#include <array>
#include <iostream>

using namespace std;

struct Grille
{
public:
	//Constructeurs

	/** Créé une Grille vide **/
	Grille();

	//Méthodes

	/** Renvoie true si la case de Coord c est vide, false sinon
	 * @param c une Coord
	 * @return un booléen
	**/
	bool caseVide(Coord c) const;

	/** Renvoie l'Id de l'animal à la case de Coord c
	 * @param c une Coord
	 * @return une Id
	**/
	Id getCase(Coord c) const;

	/** Vide la case de Coord c si elle est occupée, souleve une erreur si ce n'est pas le cas
	 * @param c une Coord
	**/
	void videCase(Coord c);

	/** Range l'animal d'Id ident dans la case de Coord c
	 * @param ident un Id
	 * @param c une Coord
	**/
	void setCase(Id ident, Coord c);

private:
	array<array<Id, TAILLEGRILLE>, TAILLEGRILLE> g;
};
