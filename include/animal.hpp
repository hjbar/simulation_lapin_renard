#pragma once

#include "const.hpp"
#include "coord.hpp"
#include <algorithm>
#include <doctest/doctest.h>
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

struct Animal
{

public:
	//Constructeur

	/** Créé un Animal vide **/
	Animal();

	/** Créé un Animal avec les différetns attributs
	 * @param ident un Id
	 * @param esp une Espece
	 * @param coord une Coord
	**/
	Animal(Id ident, Espece esp, Coord coord);

	//Getters

	/** Renvoie l'Id de l'Animal
	 * @return un Id
	**/
	Id getId() const;

	/** Renvoie les coordonnees de l'Animal
	 * @return une Coord
	**/
	Coord getCoord() const;

	/** Renvoie l'Espece d'un Animal
	 * @return une Espece
	**/
	Espece getEspece() const;

	/** Renvoie le niveau de Nourriture d'un Animal
	 * @return un int
	**/
	int getNourriture() const;

	//Setter

	/** Change les Coord d'un Animal
	 * @param c une Coord
	**/
	void setCoord(Coord c);

	//Méthodes

	/** Renvoie l'Animal sous forme de chaine de caractères pour l'affichage
	 * @return une string
	**/
	string toString() const;

	/** Augmente le niveau de nourriture d'un Animal **/
	void mange();

	/** Diminu le niveau de nourriture d'un Animal **/
	void jeune();

	/** Renvoie true si l'Animal meurt de fin, false sinon
	 * @return un booléen
	**/
	bool meurt() const;

	/** Renvoie true si le renard se reproduit, false sinon
	 * @return un booléen
	**/
	bool seReproduit() const;

	/** Renvoie true si le lapin se reproduit, false sinon
	 * @param n un entier correspondant au nombre de cases vides
	 * @return un booléen
	**/
	bool seReproduit(int n) const;

private:
	//Attribut
	Id identifiant;
	Espece espece;
	Coord coordonnees;
	int nourriture;
};
