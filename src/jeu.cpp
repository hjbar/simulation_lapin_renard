#include "jeu.hpp"

//Constructeurs

Jeu::Jeu()
	: pop{Population()}
	, grille{Grille()}
{
	int alea = 0;
	for(int i = 0; i < (TAILLEGRILLE * TAILLEGRILLE - 1); i++)
	{
		alea = int((rand() % 100) + 1);

		if(alea <= 20)
		{
			ajouteAnimal(Espece::Lapin, Coord(i));
		}
		else if(alea <= 27)
		{
			ajouteAnimal(Espece::Renard, Coord(i));
		}
	}
}

TEST_CASE("Constructeurs")
{

	Jeu game{};

	game.verifieGrille();

	int nbAnimalGrille = 0;
	int nbVideGrille = 0;

	int nbLapinPop = 0;
	int nbRenardPop = 0;
	int nbVidePop = 0;

	for(int i = 0; i < TAILLEGRILLE; i++)
	{
		for(int j = 0; j < TAILLEGRILLE; j++)
		{
			if(game.getGrille().getCase(Coord{i, j}) == -1)
			{
				nbVideGrille++;
			}
			else
			{
				nbAnimalGrille++;
			}
		}
	}

	for(long unsigned int i = 0; i < game.getPop().getT().size(); i++)
	{
		if(game.getPop().getT()[int(i)].getEspece() == Espece::Vide)
		{
			nbVidePop++;
			continue;
		}
		else if(game.getPop().getT()[int(i)].getEspece() == Espece::Lapin)
		{
			nbLapinPop++;
		}
		else
		{
			nbRenardPop++;
		}
	}

	CHECK(nbAnimalGrille == nbLapinPop + nbRenardPop);
	CHECK(nbVidePop == nbVideGrille);
	CHECK(nbLapinPop <= 100);
	CHECK(nbLapinPop >= 60);
	CHECK(nbRenardPop <= 40);
	CHECK(nbRenardPop >= 15);
}

//Getters

Population Jeu::getPop() const
{
	return pop;
}

Grille Jeu::getGrille() const
{
	return grille;
}

//Methodes

void Jeu::ajouteAnimal(Espece e, Coord c)
{
	if(e == Espece::Vide)
	{
		grille.videCase(c);
		return;
	}
	Id ident = pop.reserve();
	grille.setCase(ident, c);
	Animal a{ident, e, c};
	pop.setAnimal(a);
}

TEST_CASE("Ajoute")
{

	Jeu j{};

	j.verifieGrille();

	int nbAnimauxAuDepart = j.getPop().getIds().cardinal();
	int nbCasesLibresAuDepart = int(j.getPop().getCasesLibres().size());

	Coord c1{0, 0};
	for(int i = 0; i < TAILLEGRILLE; i++)
	{
		for(int k = 0; k < TAILLEGRILLE; k++)
		{
			if(j.getGrille().caseVide(Coord{i, k}))
			{
				c1 = Coord{i, k};
				break;
			}
		}
	}

	CHECK_THROWS_AS(j.getGrille().videCase(c1), runtime_error);

	j.ajouteAnimal(Espece::Lapin, c1);
	CHECK(j.getGrille().getCase(c1) != -1);
	CHECK(j.getPop().getIds().cardinal() == nbAnimauxAuDepart + 1);
	CHECK(j.getPop().getCasesLibres().size() == nbCasesLibresAuDepart - 1);
	int ident = j.getGrille().getCase(c1);
	CHECK(j.getPop().get(ident).getEspece() == Espece::Lapin);

	j.verifieGrille();

	Coord c2{0, 0};
	for(int i = 0; i < TAILLEGRILLE; i++)
	{
		for(int k = 0; k < TAILLEGRILLE; k++)
		{
			if(j.getGrille().caseVide(Coord{i, k}))
			{
				c2 = Coord{i, k};
				break;
			}
		}
	}

	j.ajouteAnimal(Espece::Renard, c2);
	CHECK(j.getGrille().getCase(c2) != -1);
	CHECK(j.getPop().getIds().cardinal() == nbAnimauxAuDepart + 2);
	CHECK(j.getPop().getCasesLibres().size() == nbCasesLibresAuDepart - 2);
	int ident2 = j.getGrille().getCase(c2);
	CHECK(j.getPop().get(ident2).getEspece() == Espece::Renard);

	j.verifieGrille();

	Coord c3{0, 0};
	for(int i = 0; i < TAILLEGRILLE; i++)
	{
		for(int k = 0; k < TAILLEGRILLE; k++)
		{
			if(not j.getGrille().caseVide(Coord{i, k}))
			{
				c3 = Coord{i, k};
				break;
			}
		}
	}

	j.ajouteAnimal(Espece::Vide, c3);
	CHECK(j.getGrille().getCase(c3) == -1);
	CHECK(j.getPop().getIds().cardinal() == nbAnimauxAuDepart + 2);
	CHECK(j.getPop().getCasesLibres().size() == nbCasesLibresAuDepart - 2);

	CHECK_THROWS_AS(j.verifieGrille(), runtime_error);
	CHECK_THROWS_AS(j.ajouteAnimal(Espece::Vide, c3), runtime_error);
}

void Jeu::supprimeAnimal(Animal a)
{
	Coord c = a.getCoord();

	grille.videCase(c);
	pop.supprime(a);
}

TEST_CASE("supprimeAnimal")
{
	Jeu j{};

	Ensemble e = j.getPop().getIds();
	Animal a{};

	for(int i = 0; i < e.cardinal(); i++)
	{

		a = j.getPop().get(e.getCase(i));

		Id idA = a.getId();
		Coord cA = a.getCoord();
		Espece espA = a.getEspece();

		CHECK(j.getPop().get(idA).getEspece() == espA);
		CHECK(j.getPop().get(idA).getCoord() == cA);
		CHECK(j.getPop().get(idA).getId() == idA);
		CHECK(j.getGrille().getCase(cA) == idA);

		j.supprimeAnimal(a);

		CHECK_THROWS_AS(j.getPop().get(idA), invalid_argument);
		CHECK(j.getGrille().getCase(cA) == -1);
	}
}

Ensemble Jeu::voisinsVides(Coord c) const
{
	Ensemble voisin = c.voisines();
	Ensemble ev;
	for(int i = 0; i < voisin.cardinal(); i++)
	{
		if(grille.caseVide(Coord{voisin.getCase(i)}))
		{
			ev.ajoute(voisin.getCase(i));
		}
	}
	return ev;
}

Ensemble Jeu::voisinsAnimal(Espece e, Coord c) const
{
	if(e == Espece::Vide)
	{
		throw invalid_argument("Vide n'est pas un animal");
	}
	Ensemble voisin = c.voisines();
	Ensemble ev;
	int index = 0;
	for(int i = 0; i < voisin.cardinal(); i++)
	{
		index = grille.getCase(Coord{voisin.getCase(i)});
		if(index == -1)
		{
			continue;
		}
		if(pop.get(index).getEspece() == e)
		{
			ev.ajoute(voisin.getCase(i));
		}
	}
	return ev;
}

TEST_CASE("VoisinsVides + VoisinsAnimal")
{
	Jeu game{};

	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			if(not game.getGrille().caseVide(Coord{i, j}))
			{
				game.ajouteAnimal(Espece::Vide, Coord{i, j});
			}
		}
	}

	CHECK_THROWS_AS(game.voisinsAnimal(Espece::Vide, Coord({1, 1})), invalid_argument);

	Ensemble ev1 = game.voisinsVides(Coord{1, 1});
	Ensemble el1 = game.voisinsAnimal(Espece::Lapin, Coord{1, 1});
	Ensemble er1 = game.voisinsAnimal(Espece::Renard, Coord{1, 1});

	CHECK(ev1.cardinal() == 8);
	CHECK(el1.cardinal() == 0);
	CHECK(er1.cardinal() == 0);

	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			game.ajouteAnimal(Espece::Lapin, Coord{i, j});
		}
	}

	Ensemble ev2 = game.voisinsVides(Coord{1, 1});
	Ensemble el2 = game.voisinsAnimal(Espece::Lapin, Coord{1, 1});
	Ensemble er2 = game.voisinsAnimal(Espece::Renard, Coord{1, 1});

	CHECK(ev2.cardinal() == 0);
	CHECK(el2.cardinal() == 8);
	CHECK(er2.cardinal() == 0);

	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			game.ajouteAnimal(Espece::Vide, Coord{i, j});
			game.ajouteAnimal(Espece::Renard, Coord{i, j});
		}
	}

	Ensemble ev3 = game.voisinsVides(Coord{1, 1});
	Ensemble el3 = game.voisinsAnimal(Espece::Lapin, Coord{1, 1});
	Ensemble er3 = game.voisinsAnimal(Espece::Renard, Coord{1, 1});

	CHECK(ev3.cardinal() == 0);
	CHECK(el3.cardinal() == 0);
	CHECK(er3.cardinal() == 8);
}

Ensemble Jeu::voisinsGenreOppose(Animal a) const
{
	Espece e = a.getEspece();
	Coord c = a.getCoord();
	Genre g = a.getGenre();

	if(e == Espece::Vide)
	{
		throw invalid_argument("Vide n'est pas un animal");
	}

	Genre gCherche = Genre::Vide;
	if(g == Genre::Male)
	{
		gCherche = Genre::Female;
	}
	else if(g == Genre::Female)
	{
		gCherche = Genre::Male;
	}
	else
	{
		throw runtime_error("Le Genre de l'Animal est Vide");
	}

	Ensemble voisin = voisinsAnimal(e, c);
	Ensemble ev;
	int index = 0;
	for(int i = 0; i < voisin.cardinal(); i++)
	{
		index = grille.getCase(Coord{voisin.getCase(i)});
		if(index == -1)
		{
			continue;
		}
		if(pop.get(index).getGenre() == gCherche)
		{
			ev.ajoute(voisin.getCase(i));
		}
	}
	return ev;
}

Id Jeu::deplaceAnimal(Animal a)
{

	Espece e = a.getEspece();

	if(e == Espece::Vide)
	{
		throw runtime_error("On ne peut pas deplacer un Animal vide");
	}

	else if(e == Espece::Lapin)
	{
		pop.vieillirAnimal(a);
		if(a.meurt())
		{
			supprimeAnimal(a);
			return -1;
		}
		deplaceLapin(a);
		return -1;
	}

	else if(e == Espece::Renard)
	{
		pop.jeuneAnimal(a);
		pop.vieillirAnimal(a);
		if(a.meurt())
		{
			supprimeAnimal(a);
			return -1;
		}
		Id ident = deplaceRenard(a);
		return ident;
	}

	else
	{
		throw runtime_error("Cet espece d'Animal n'existe pas");
	}
}

void Jeu::deplaceLapin(Animal a)
{
	Coord cDepart = a.getCoord();
	Ensemble e = voisinsVides(cDepart);

	if(e.cardinal() == 0)
	{
		return;
	}

	int indice = e.tire();
	Coord cFin{indice};

	deplaceCoord(a, cFin);

	Ensemble eg = voisinsGenreOppose(a);
	if(eg.cardinal() > 0)
	{
		e.ajoute(indice);
		naissance(a, cDepart, e);
	}
}

Id Jeu::deplaceRenard(Animal a)
{
	Coord cDepart = a.getCoord();
	Ensemble eVide = voisinsVides(cDepart);
	Ensemble eLapin = voisinsAnimal(Espece::Lapin, cDepart);
	Id ident = -1;

	if(eLapin.cardinal() > 0)
	{
		int indice = eLapin.tire();
		Coord cFin{indice};
		Animal lapin = pop.get(grille.getCase(cFin));
		ident = lapin.getId();
		supprimeAnimal(lapin);
		pop.mangeAnimal(a);

		deplaceCoord(a, cFin);
	}

	else if(eVide.cardinal() > 0)
	{
		int indice = eVide.tire();
		Coord cFin{indice};

		deplaceCoord(a, cFin);
	}

	else
	{
		return -1;
	}

	Ensemble eg = voisinsGenreOppose(a);
	if(eg.cardinal() > 0)
	{
		naissance(a, cDepart);
	}

	return ident;
}

void Jeu::deplaceCoord(Animal a, Coord cFin)
{
	Coord cDepart = a.getCoord();
	grille.setCase(a.getId(), cFin);
	pop.changeCoord(a, cFin);
	grille.videCase(cDepart);
}

TEST_CASE("deplaceCoord")
{
	Jeu jeu{};

	Ensemble e = jeu.getPop().getIds();
	Coord c{0, 0};

	for(int i = 0; i < TAILLEGRILLE; i++)
	{
		for(int j = 0; j < TAILLEGRILLE; j++)
		{
			if(jeu.getGrille().getCase(Coord{i, j}) == -1)
			{
				c = Coord{i, j};
				break;
			}
		}
	}

	Animal a = jeu.getPop().get(e.getCase(0));

	Coord cAvant = a.getCoord();
	jeu.deplaceCoord(a, c);

	Animal newA = jeu.getPop().get(e.getCase(0));
	Coord cApres = newA.getCoord();

	CHECK_FALSE(cAvant == c);
	CHECK_FALSE(cApres == cAvant);
	CHECK(cApres == c);
	CHECK(jeu.getGrille().getCase(cAvant) == -1);
	CHECK(jeu.getGrille().getCase(c) == newA.getId());
}

void Jeu::naissance(Animal a, Coord c, Ensemble ens)
{

	bool reproduction = a.seReproduit(ens.cardinal());

	if(reproduction)
	{
		ajouteAnimal(a.getEspece(), c);
		Animal b = pop.get(grille.getCase(c));
		pop.resetAgeAnimal(b);
	}
}

TEST_CASE("naissance Lapin")
{
	Jeu jeu{};

	Coord c{0, 0};
	for(int i = 0; i < TAILLEGRILLE; i++)
	{
		for(int j = 0; i < TAILLEGRILLE; j++)
		{
			if(jeu.getGrille().caseVide(Coord{i, j}))
			{
				c = Coord{i, j};
				break;
			}
		}
	}

	jeu.ajouteAnimal(Espece::Lapin, c);
	Id idL = jeu.getGrille().getCase(c);
	Animal L = jeu.getPop().get(idL);
	Ensemble ev{};

	Coord c2{0, 0};
	for(int i = 0; i < TAILLEGRILLE; i++)
	{
		for(int j = 0; i < TAILLEGRILLE; j++)
		{
			if(jeu.getGrille().caseVide(Coord{i, j}))
			{
				c2 = Coord{i, j};
				break;
			}
		}
	}

	int nbAnimauxDepart = jeu.getPop().getIds().cardinal();
	for(int i = 0; i < 100; i++)
	{
		jeu.naissance(L, c2, ev);
	}
	CHECK(jeu.getPop().getIds().cardinal() == nbAnimauxDepart);

	Ensemble e{};
	for(int i = 0; i < 10; i++)
	{
		e.ajoute(i + 5);
	}

	int nbAnimauxDepart2 = jeu.getPop().getIds().cardinal();
	while(jeu.getPop().getIds().cardinal() <= nbAnimauxDepart2)
	{
		jeu.naissance(L, c2, e);
	}
	CHECK(jeu.getPop().getIds().cardinal() > nbAnimauxDepart2);
}

void Jeu::naissance(Animal a, Coord c)
{

	bool reproduction = a.seReproduit();

	if(reproduction)
	{
		ajouteAnimal(a.getEspece(), c);
		Animal b = pop.get(grille.getCase(c));
		pop.resetAgeAnimal(b);
	}
}

TEST_CASE("naissance Renard")
{

	Jeu jeu{};

	Coord c{0, 0};
	for(int i = 0; i < TAILLEGRILLE; i++)
	{
		for(int j = 0; i < TAILLEGRILLE; j++)
		{
			if(jeu.getGrille().caseVide(Coord{i, j}))
			{
				c = Coord{i, j};
				break;
			}
		}
	}

	jeu.ajouteAnimal(Espece::Renard, c);
	Id idL = jeu.getGrille().getCase(c);
	Animal R = jeu.getPop().get(idL);

	Coord c2{0, 0};
	for(int i = 0; i < TAILLEGRILLE; i++)
	{
		for(int j = 0; i < TAILLEGRILLE; j++)
		{
			if(jeu.getGrille().caseVide(Coord{i, j}))
			{
				c2 = Coord{i, j};
				break;
			}
		}
	}

	int nbAnimauxDepart = jeu.getPop().getIds().cardinal();
	for(int i = 0; i < 100; i++)
	{
		jeu.naissance(R, c2);
	}
	CHECK(jeu.getPop().getIds().cardinal() == nbAnimauxDepart);

	jeu.getPop().mangeAnimal(R);
	int nbAnimauxDepart2 = jeu.getPop().getIds().cardinal();
	while(jeu.getPop().getIds().cardinal() <= nbAnimauxDepart2)
	{
		jeu.naissance(R, c2);
	}
	CHECK(jeu.getPop().getIds().cardinal() > nbAnimauxDepart2);
}

void Jeu::afficheNombreAnimal() const
{

	Ensemble eL = pop.getIdsEspece(Espece::Lapin);
	Ensemble eR = pop.getIdsEspece(Espece::Renard);

	cout << "Lapin : " << eL.cardinal() << "   "
		 << "Renard : " << eR.cardinal() << endl;
}

void Jeu::affiche() const
{
	cout << NEW_SCREEN;
	for(int i = 0; i < TAILLEGRILLE; i++)
	{
		for(int j = 0; j < TAILLEGRILLE; j++)
		{
			if(grille.getCase(Coord{i, j}) == -1)
			{
				cout << Animal{}.toString() << "   ";
			}
			else
			{
				cout << pop.get(grille.getCase(Coord{i, j})).toString() << "   ";
			}
		}
		cout << endl << endl;
	}
	afficheNombreAnimal();
}

void Jeu::verifieGrille() const
{

	Ensemble ev = pop.getIds();
	Animal a{};

	for(int i = 0; i < ev.cardinal(); i++)
	{
		a = pop.get(ev.getCase(i));
		if(a.getId() != grille.getCase(a.getCoord()))
		{
			throw runtime_error(
				"La Grille et la Population ne sont pas correctement synchronisées");
		}
	}
}

void Jeu::verifieAll() const
{

	verifieGrille();

	Coord cGrille{0, 0};
	Coord cPop{0, 0};
	for(int i = 0; i < TAILLEGRILLE; i++)
	{
		for(int j = 0; j < TAILLEGRILLE; j++)
		{
			if(grille.getCase(Coord{i, j}) != -1)
			{
				cGrille = Coord{i, j};
				cPop = pop.get(grille.getCase(Coord{i, j})).getCoord();
				if(not(cPop == cGrille))
				{
					throw runtime_error("L'animal n'est pas stocke a la place ou il doit l'etre");
				}
			}
		}
	}

	Ensemble e = pop.getIds();
	Coord cAnimal{0, 0};
	for(int i = 0; i < e.cardinal(); i++)
	{
		cAnimal = pop.get(e.getCase(i)).getCoord();
		if(grille.getCase(cAnimal) == -1)
		{
			throw runtime_error("L'animal est stocke dans une case vide");
		}
	}

	bool ok = false;
	Ensemble ev = pop.getIds();
	for(int i = 0; i < TAILLEGRILLE; i++)
	{
		for(int j = 0; j < TAILLEGRILLE; j++)
		{
			if(grille.getCase(Coord{i, j}) != -1)
			{
				for(int k = 0; k < ev.cardinal(); k++)
				{
					if(grille.getCase(Coord{i, j}) == ev.getCase(k))
					{
						if(not ok)
						{
							ok = true;
						}
					}
				}
				if(not ok)
				{
					throw runtime_error("L'animal stocke n'est pas dans la population");
				}
			}
		}
	}
}

void Jeu::genereImage(int nbFichier) const
{
	ostringstream filename;

	filename << "img" << setfill('0') << setw(3) << nbFichier << ".ppm";

	ofstream fic(filename.str(), ios::out | ios::trunc);

	fic << "P3" << endl << TAILLEGRILLE << " " << TAILLEGRILLE << " " << endl << 255 << " " << endl;

	for(int i = 0; i < TAILLEGRILLE; i++)
	{
		for(int j = 0; j < TAILLEGRILLE; j++)
		{
			if(grille.getCase(Coord{i, j}) == -1)
			{
				fic << 0 << " " << 0 << " " << 0 << "   ";
			}
			else if(pop.get(grille.getCase(Coord{i, j})).getEspece() == Espece::Lapin)
			{
				fic << 160 << " " << 82 << " " << 45 << "   ";
			}
			else if(pop.get(grille.getCase(Coord{i, j})).getEspece() == Espece::Renard)
			{
				fic << 255 << " " << 140 << " " << 0 << "   ";
			}
		}
		fic << endl;
	}

	fic.close();
}
