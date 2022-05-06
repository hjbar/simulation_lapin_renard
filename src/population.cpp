#include "population.hpp"

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

vector<int> Population::getCasesLibres() const
{
	return casesLibres;
}

array<Animal, TAILLEGRILLE * TAILLEGRILLE> Population::getT() const
{
	return t;
}

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

void Population::changeCoord(Id ident, Coord c)
{
	for(long unsigned i = 0; i < t.size(); i++)
	{
		if(ident == t[int(i)].getId())
		{

			if(t[int(i)].getEspece() == Espece::Vide)
			{
				throw invalid_argument("On ne peut pas changer la Coord d'un Animal Vide");
			}

			t[int(i)].setCoord(c);
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

	A.changeCoord(a.getId(), Coord{0, 0});

	CHECK(A.getT()[a.getId()].getCoord() == Coord{0, 0});
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
