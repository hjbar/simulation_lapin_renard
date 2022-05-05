#pragma once

#include "const.hpp"
#include "grille.hpp"
#include "population.hpp"
#include <doctest/doctest.h>
#include <iostream>

struct Jeu {

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

  /** Vérifie que chaque Animal est bien a sa place dans la Grille. Soulève une
   * erreur si ce n'est pas le cas **/
  void verifieGrille() const;

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

  /** Deplace un Animal d'Id ident sur une case voisine libre. Renvoie true si
   *le deplacement est possible, false sinon
   * @param ident un Id
   * @return un booléen
   **//**
	bool deplaceAnimal(Animal a);
	**/
  /** Deplace un Animal d'Id ident sur une case voisine libre. Renvoie true si
   *le deplacement est possible, false sinon
   * @param ident un Id
   * @return un booléen
   **/
  void deplaceAnimal(Animal a);

  void deplaceLapin(Animal a);

  void deplaceRenard(Animal a);

  void naissance(Animal a, Coord c, Ensemble ens);

  void naissance(Animal a, Coord c);

  void supprimeAnimal(Animal a);

  /** Fonction qui affiche le Jeu **/
  void affiche() const;

  string afficheNombreAnimal() const;

  /** Fonction qui verifie la coherence des données, souleve une erreur si ce
   * n'est pas le cas **/
  void verifieAll() const;

private:
  Population pop;
  Grille grille;
};
