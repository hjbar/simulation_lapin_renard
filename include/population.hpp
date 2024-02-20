#pragma once

#include "animal.hpp"
#include "const.hpp"
#include <array>
#include <doctest/doctest.h>
#include <iostream>
#include <vector>

using namespace std;

struct Population
{
public:
	//Constructeurs

	/** Initialise une population vide d'Animal**/
	Population();

	//Getters

	/** Renvoie l'Ensemble des identifiants d'une certaine Espece de la Population
   * @param e une Espece
   * @return un Ensemble
	**/
	Ensemble getIdsEspece(Espece e) const;

	/** Renvoie le tableau contnenant les cases libres de la population.
   * @return tableau d'entiers des cases libres.
	**/
	vector<int> getCasesLibres() const;

	//Méthodes

	/** Permet de retrouver et de renvoyer un animal dans la population à partir de son identifiant.
    * @param identifiant de l'animal.
    * @return un animal.
  **/
	Animal get(Id identifiant) const;

	/** Renvoie l'ensemble de tout les identifiants d'une population.
    * @return Ensemble d'identifiants contenus dans la population.
  **/
	Ensemble getIds() const;

	/** Renvoie le tebleau de la population
	 * @return le array t de la population
	**/
	array<Animal, TAILLEGRILLE * TAILLEGRILLE> getT() const;

	/** Reserve une place mémoire pour stocker un animal dans la population.
    * @return un entier qui est l'identifiant de l'animal.
  **/
	int reserve();

	/** Range un animal dans la population.
    * @param un Animal.
  **/
	void setAnimal(Animal a);

	/** Change la Coord d'un animal dans la population
	 * @param a un Animal
	 * @param c une Coord
	**/
	void changeCoord(Animal& a, Coord c);

	/** Reset l'age d'un Animal
	 * @param a un Animal
	**/
	void resetAgeAnimal(Animal& a);

	/** L'Animal donné en parametre mange
	 * @param a un Animal
	**/
	void mangeAnimal(Animal& a);

	/** Fait jeuner l'Animal donne en parametre
	 * @param a un Animal
	**/
	void jeuneAnimal(Animal& a);

	/** Fait vieillir l'Animal donne en parametre
	 * @param a un Animal
	**/
	void vieillirAnimal(Animal& a);

	/** Supprime un animal de la population.
    * @param un Animal.
  **/
	void supprime(Animal a);

private:
	//Attributs
	array<Animal, TAILLEGRILLE * TAILLEGRILLE> t;
	vector<int> casesLibres;
};
