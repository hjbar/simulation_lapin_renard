#pragma once

#include "const.hpp"
#include "grille.hpp"
#include "population.hpp"
#include <doctest/doctest.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

struct Jeu
{

public:
	// Constructeurs :

	/** Initialise un Jeu **/
	Jeu();

	// Getters :

	/** Renvoie la population du jeu.
   * @return une population.
   **/
	Population getPop() const;

	/** Renvoie la grille du jeu.
   * @return une grille.
   **/
	Grille getGrille() const;

	// Méthodes :

	/** Ajoute un animal dans le jeu.
   * @param a un animal
   * @param c une coordonnée.
   **/
	void ajouteAnimal(Espece e, Coord c);

	/** Supprimer un Animal du jeu
	 * @param a un Animal
	**/
	void supprimeAnimal(Animal a);

	/** Renvoie l'Ensemble des cases vides d'une Coord donnée
   * @param c une Coord
   * @return ev un Ensemble
   **/
	Ensemble voisinsVides(Coord c) const;

	/** Renvoie l'Ensemble des cases contenant l'Espece e d'une Coord donnée
   * @param e une Espece
   * @param c une Coord
   * @return ev un Ensemble
   **/
	Ensemble voisinsAnimal(Espece e, Coord c) const;

	/** Renvoie l'Ensemble des cases contenant des Animal de Genre oppose
	 * @param a un Animal
	 * @return e un Ensemble
	**/
	Ensemble voisinsGenreOppose(Animal a) const;

	/** Deplace un Animal d'Id ident sur une case voisine libre. Renvoie un Id si un Lapin a ete mange, renvoie -1 sinon
   * @param ident un Id
   * @return un Id
   **/
	Id deplaceAnimal(Animal a);

	/** Deplace un Animal si celui-ci est un Lapin
	 * @param a un Animal
	**/
	void deplaceLapin(Animal a);

	/** Deplace un Animal si celui-ci est un Renard. Renvoie un Id si un Lapin a ete mange, renvoie -1 sinon
	 * @param a un Animal
	 * @return un Id
	**/
	Id deplaceRenard(Animal a);

	/** Fonction qui change les Coord d'un Animal
	 * @param a un Animal
	 * @param cFin une Coord
	**/
	void deplaceCoord(Animal a, Coord cFin);

	/** Simule la naissance d'un Lapin seulement s'il y a reproduction d'apres les regles du jeu
	 * @param a un Animal
	 * @param c une Coord
	 * @param ens un Ensemble de cases vides
	**/
	void naissance(Animal a, Coord c, Ensemble ens);

	/** Simule la naissance d'un Renard seulement s'il y a reproduction d'apres les regles du jeu
	 * @param a un Animal
	 * @param c une Coord
	 * @param ens un Ensemble de cases vides
	**/
	void naissance(Animal a, Coord c);

	/** Fonction qui affiche le nombre de Lapins et de Renards **/
	void afficheNombreAnimal() const;

	/** Fonction qui affiche le Jeu **/
	void affiche() const;

	/** Vérifie que chaque Animal est bien a sa place dans la Grille. Soulève une
   * erreur si ce n'est pas le cas **/
	void verifieGrille() const;

	/** Fonction qui verifie la coherence des données, souleve une erreur si ce
   * n'est pas le cas **/
	void verifieAll() const;

	/** Genere une image du Jeu pour la video .gif
	 * @param nbFichier un entier
	**/
	void genereImage(int nbFichier) const;

private:
	//Attributs
	Population pop;
	Grille grille;
};
