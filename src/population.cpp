#include "population.hpp"

//Constructeurs

Population::Population()
	: t{}
	, casesLibres{}
{

	Animal a{};
	for(long unsigned int i = 0; i < t.size(); i++)
		t[i] = a;

	vector<int> tab;
	tab = vector<int>(t.size());
	for(long unsigned int i = 0; i < tab.size(); i++)
		tab[i] = int(i);
	casesLibres = tab;
}

TEST_CASE("Constructeur Population")
{
	Population a{};
	for(long unsigned int i = 0; i < a.getT().size(); i++)
	{
		i = int(i);
		CHECK(a.getT()[i].getId() == -1);
		CHECK(a.getT()[i].getEspece() == Espece::Vide);
	}
	CHECK(a.getCasesLibres().size() == TAILLEGRILLE * TAILLEGRILLE);
}

//Getters

vector<int> Population::getCasesLibres() const
{
	return casesLibres;
}

array<Animal, TAILLEGRILLE * TAILLEGRILLE> Population::getT() const
{
	return t;
}

//Methodes

Animal Population::get(Id identifiant) const
{
	for(long unsigned int i = 0; i < t.size(); i++)
	{
		if(t[i].getId() == identifiant and t[i].getEspece() != Espece::Vide)
			return t[i];
	}
	throw invalid_argument("L'identifiant/l'Animal n'est pas dans la population");
}

TEST_CASE("get")
{
	Population a{};

	CHECK_THROWS_AS(a.get(50), invalid_argument);

	a.setAnimal(Animal{25, Espece::Vide, Coord{2, 2}});

	CHECK_THROWS_AS(a.get(25), invalid_argument);

	a.setAnimal(Animal{50, Espece::Lapin, Coord{5, 5}});
	Animal ani = a.get(50);
	CHECK(ani.getId() == 50);
	CHECK(ani.getEspece() == Espece::Lapin);
	CHECK(ani.getCoord() == Coord{5, 5});
}

Ensemble Population::getIds() const
{
	Ensemble ident{};
	for(long unsigned int i = 0; i < t.size(); i++)
	{
		if(t[i].getEspece() != Espece::Vide)
			ident.ajoute(t[i].getId());
	}
	return ident;
}

TEST_CASE("getIds")
{
	Population a{};
	Ensemble e = a.getIds();
	CHECK(e.cardinal() == 0);

	for(int i = 0; i < 10; i++)
	{
		a.setAnimal(Animal{i + 5, Espece::Lapin, Coord{0, 0}});
		e = a.getIds();
		CHECK(e.cardinal() == i + 1);
	}

	for(int i = 0; i < 10; i++)
	{
		a.setAnimal(Animal{i + 50, Espece::Vide, Coord{0, 0}});
		e = a.getIds();
		CHECK(e.cardinal() == 10);
	}
}

Ensemble Population::getIdsEspece(Espece e) const
{
	if(e == Espece::Vide)
	{
		throw invalid_argument("Un Animal n'a pas d'Id");
	}

	Ensemble ident{};
	for(long unsigned int i = 0; i < t.size(); i++)
	{
		if(t[i].getEspece() == e)
			ident.ajoute(t[i].getId());
	}
	return ident;
}

TEST_CASE("getIdsEspece")
{
	Population a{};
	Ensemble eL = a.getIdsEspece(Espece::Lapin);
	Ensemble eR = a.getIdsEspece(Espece::Renard);
	CHECK(eL.cardinal() == 0);
	CHECK(eR.cardinal() == 0);
	CHECK_THROWS_AS(a.getIdsEspece(Espece::Vide), invalid_argument);

	for(int i = 0; i < 10; i++)
	{
		a.setAnimal(Animal{i + 5, Espece::Lapin, Coord{0, 0}});
		eL = a.getIdsEspece(Espece::Lapin);
		eR = a.getIdsEspece(Espece::Renard);
		CHECK(eL.cardinal() == i + 1);
		CHECK(eR.cardinal() == 0);
	}

	for(int i = 0; i < 10; i++)
	{
		a.setAnimal(Animal{i + 50, Espece::Renard, Coord{0, 0}});
		eL = a.getIdsEspece(Espece::Lapin);
		eR = a.getIdsEspece(Espece::Renard);
		CHECK(eR.cardinal() == i + 1);
		CHECK(eL.cardinal() == 10);
	}

	for(int i = 0; i < 10; i++)
	{
		a.setAnimal(Animal{i + 100, Espece::Vide, Coord{0, 0}});
		eL = a.getIdsEspece(Espece::Lapin);
		eR = a.getIdsEspece(Espece::Renard);
		CHECK(eR.cardinal() == 10);
		CHECK(eL.cardinal() == 10);
	}
}

int Population::reserve()
{
	if(casesLibres.size() == 0)
		return -1;
	int res = casesLibres[casesLibres.size() - 1];
	casesLibres.pop_back();
	return res;
}

void Population::setAnimal(Animal a)
{
	int index = a.getId();

	if(index == -1)
	{
		throw runtime_error("Pas de place dans la population.");
	}

	if(t[index].getEspece() != Espece::Vide)
	{
		throw runtime_error("Il y a déjà un animal dans cette case");
	}

	t[index] = a;
}

TEST_CASE("Reserve + Set")
{

	Population A{};

	Animal a{A.reserve(), Espece::Lapin, Coord{5, 5}};
	CHECK(a.getId() <= TAILLEGRILLE * TAILLEGRILLE - 1);
	CHECK(a.getId() >= 0);

	CHECK(A.reserve() <= TAILLEGRILLE * TAILLEGRILLE - 1);
	CHECK(A.reserve() >= 0);

	A.setAnimal(a);
	CHECK(A.get(TAILLEGRILLE * TAILLEGRILLE - 1).getId() == a.getId());
	CHECK(A.get(TAILLEGRILLE * TAILLEGRILLE - 1).getCoord() == a.getCoord());
	CHECK(A.get(TAILLEGRILLE * TAILLEGRILLE - 1).getEspece() == a.getEspece());

	CHECK_THROWS_AS(A.setAnimal(Animal{-1, Espece::Lapin, Coord{2, 2}}), runtime_error);
	CHECK_THROWS_AS(
		A.setAnimal(Animal{TAILLEGRILLE * TAILLEGRILLE - 1, Espece::Renard, Coord{2, 2}}),
		runtime_error);
}

void Population::changeCoord(Animal& a, Coord c)
{

	Id ident = a.getId();

	for(long unsigned i = 0; i < t.size(); i++)
	{
		if(ident == t[int(i)].getId())
		{

			if(t[int(i)].getEspece() == Espece::Vide)
			{
				throw invalid_argument("On ne peut pas changer la Coord d'un Animal Vide");
			}

			t[int(i)].setCoord(c);
			a.setCoord(c);
			return;
		}
	}

	throw runtime_error("Id/Animal non present dans la population");
}

TEST_CASE("changeCoord")
{
	Population A{};
	Animal a{A.reserve(), Espece::Lapin, Coord{5, 5}};
	A.setAnimal(a);

	A.changeCoord(a, Coord{0, 0});

	CHECK(A.getT()[a.getId()].getCoord() == Coord{0, 0});
	CHECK(a.getCoord() == Coord{0, 0});
}

void Population::resetAgeAnimal(Animal& a)
{
	Id ident = a.getId();

	for(long unsigned i = 0; i < t.size(); i++)
	{
		if(ident == t[int(i)].getId())
		{

			if(t[int(i)].getEspece() == Espece::Vide)
			{
				throw invalid_argument("On ne peut pas changer la Coord d'un Animal Vide");
			}

			t[int(i)].resetAge();
			a.resetAge();
			return;
		}
	}

	throw runtime_error("Id/Animal non present dans la population");
}

TEST_CASE("resetAgeAnimal")
{
	Population A{};
	Animal a{A.reserve(), Espece::Lapin, Coord{5, 5}};
	A.setAnimal(a);

	A.resetAgeAnimal(a);

	CHECK(A.getT()[a.getId()].getAge() == 0);
	CHECK(a.getAge() == 0);
}

void Population::mangeAnimal(Animal& a)
{
	if(a.getEspece() != Espece::Renard)
	{
		throw invalid_argument("Seul le Renard se nourrit");
	}

	Id ident = a.getId();

	for(long unsigned i = 0; i < t.size(); i++)
	{
		if(ident == t[int(i)].getId())
		{
			t[int(i)].mange();
			a.mange();
			return;
		}
	}

	throw runtime_error("Id/Animal non present dans la population");
}

void Population::jeuneAnimal(Animal& a)
{
	if(a.getEspece() != Espece::Renard)
	{
		throw invalid_argument("Seul le Renard jeune");
	}

	Id ident = a.getId();

	for(long unsigned i = 0; i < t.size(); i++)
	{
		if(ident == t[int(i)].getId())
		{
			t[int(i)].jeune();
			a.jeune();
			return;
		}
	}

	throw runtime_error("Id/Animal non present dans la population");
}

void Population::vieillirAnimal(Animal& a)
{
	if(a.getEspece() == Espece::Vide)
	{
		throw invalid_argument("L'Animal Vide ne peut pas vieillir");
	}
	if(a.getAge() < 0)
	{
		throw runtime_error("L'age de cet Animal n'est pas valide");
	}
	if(a.getEspece() == Espece::Lapin)
	{
		if(a.getAge() >= MaxAgeLapin)
		{
			throw runtime_error("Ce Lapin possede deja l'age maximal");
		}
	}
	if(a.getEspece() == Espece::Renard)
	{
		if(a.getAge() >= MaxAgeRenard)
		{
			throw runtime_error("Ce Renard possede deja l'age maximal");
		}
	}

	Id ident = a.getId();

	for(long unsigned i = 0; i < t.size(); i++)
	{
		if(ident == t[int(i)].getId())
		{
			t[int(i)].vieillit();
			a.vieillit();
			return;
		}
	}

	throw runtime_error("Id/Animal non present dans la population");
}

TEST_CASE("mangeAnimal + jeuneAnimal + vieillirAnimal")
{
	Population A{};
	Animal a{A.reserve(), Espece::Renard, Coord{5, 5}};
	A.setAnimal(a);

	A.mangeAnimal(a);

	CHECK(A.getT()[a.getId()].getNourriture() == FoodInit + FoodLapin);
	CHECK(A.getT()[a.getId()].getNourriture() == 10);
	CHECK(a.getNourriture() == FoodInit + FoodLapin);
	CHECK(a.getNourriture() == 10);

	A.jeuneAnimal(a);

	CHECK(A.getT()[a.getId()].getNourriture() == (FoodInit + FoodLapin) - 1);
	CHECK(A.getT()[a.getId()].getNourriture() == 9);
	CHECK(a.getNourriture() == (FoodInit + FoodLapin) - 1);
	CHECK(a.getNourriture() == 9);

	int ageA = a.getAge();
	A.vieillirAnimal(a);

	CHECK(A.getT()[a.getId()].getAge() == ageA + 1);
	CHECK(a.getAge() == ageA + 1);

	ageA = a.getAge();
	for(int i = 0; i < MaxAgeRenard - ageA; i++)
	{
		A.vieillirAnimal(a);
	}
	CHECK(A.getT()[a.getId()].getAge() == MaxAgeRenard);
	CHECK(a.getAge() == MaxAgeRenard);
	CHECK_THROWS_AS(A.vieillirAnimal(a), runtime_error);

	Animal v{};
	CHECK_THROWS_AS(A.mangeAnimal(v), invalid_argument);
	CHECK_THROWS_AS(A.jeuneAnimal(v), invalid_argument);
	CHECK_THROWS_AS(A.vieillirAnimal(v), invalid_argument);

	Animal r{10, Espece::Renard, Coord{5, 5}};
	CHECK_THROWS_AS(A.mangeAnimal(r), runtime_error);
	CHECK_THROWS_AS(A.jeuneAnimal(r), runtime_error);

	Animal l{0, Espece::Lapin, Coord{0, 0}};
	A.setAnimal(l);
	int ageL = l.getAge();
	for(int i = 0; i < MaxAgeLapin - ageL; i++)
	{
		A.vieillirAnimal(l);
	}
	CHECK(A.getT()[l.getId()].getAge() == MaxAgeLapin);
	CHECK(l.getAge() == MaxAgeLapin);
	CHECK_THROWS_AS(A.vieillirAnimal(l), runtime_error);
}

void Population::supprime(Animal a)
{
	if(a.getEspece() == Espece::Vide)
	{
		throw invalid_argument("Cette animal n'existe pas, c'est l'animal vide");
	}
	int index = a.getId();
	t[index] = Animal();
	casesLibres.push_back(index);
}

TEST_CASE("Supprime")
{

	Population A{};
	Animal a{A.reserve(), Espece::Lapin, Coord{5, 5}};
	A.setAnimal(a);
	A.supprime(a);

	for(long unsigned int i = 0; i < A.getT().size(); i++)
	{
		i = int(i);
		CHECK(A.getT()[i].getId() == -1);
		CHECK(A.getT()[i].getEspece() == Espece::Vide);
	}

	CHECK(A.getCasesLibres().size() == TAILLEGRILLE * TAILLEGRILLE);
}
