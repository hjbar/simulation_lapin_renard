#include "animal.hpp"

Animal::Animal()
	: identifiant{-1}
	, espece{Espece::Vide}
	, coordonnees{Coord{0, 0}}
	, nourriture{-1}
{ }

Animal::Animal(Id ident, Espece esp, Coord coord)
	: identifiant{ident}
	, espece{esp}
	, coordonnees{coord}
	, nourriture{FoodInit}
{ }

TEST_CASE("Constructeur")
{

	Animal a{0, Espece::Renard, Coord{2, 3}};
	CHECK(a.getId() == 0);
	CHECK(a.getEspece() == Espece::Renard);
	CHECK(a.getCoord() == Coord{2, 3});
	CHECK(a.getNourriture() == FoodInit);

	Animal b{5, Espece::Lapin, Coord{TAILLEGRILLE - 1, TAILLEGRILLE - 1}};
	CHECK(b.getId() == 5);
	CHECK(b.getEspece() == Espece::Lapin);
	CHECK(b.getCoord() == Coord{TAILLEGRILLE - 1, TAILLEGRILLE - 1});
	CHECK(b.getNourriture() == FoodInit);

	Animal c{};
	CHECK(c.getId() == -1);
	CHECK(c.getEspece() == Espece::Vide);
	CHECK(c.getCoord() == Coord{0, 0});
	CHECK(c.getNourriture() == -1);
}

Id Animal::getId() const
{
	return identifiant;
}

Coord Animal::getCoord() const
{
	return coordonnees;
}

Espece Animal::getEspece() const
{
	return espece;
}

int Animal::getNourriture() const
{
	return nourriture;
}

void Animal::setCoord(Coord c)
{
	if(c == coordonnees)
	{
		throw invalid_argument("L'Animal est déjà à la même coordonnee");
	}
	coordonnees = c;
}

TEST_CASE("setCoord")
{
	Animal a{15, Espece::Lapin, Coord{0, 0}};
	a.setCoord(Coord{10, 10});
	CHECK(a.getCoord() == Coord{10, 10});

	CHECK_THROWS_AS(a.setCoord(Coord{10, 10}), invalid_argument);

	a.setCoord(Coord{0, 0});
	CHECK(a.getCoord() == Coord{0, 0});
}

string Animal::toString() const
{
	ostringstream ch;
	Espece e = espece;
	if(e == Espece::Lapin)
	{
		ch << BLUE << "*" << RESET_COLOR;
	}
	else if(e == Espece::Renard)
	{
		ch << RED << "*" << RESET_COLOR;
	}
	else
	{
		ch << WHITE << "*" << RESET_COLOR;
	}
	return ch.str();
}

TEST_CASE("toString")
{
	Animal a{0, Espece::Lapin, Coord{0, 0}};
	string s1 = a.toString();
	CHECK(s1 == "\033[0;34m*\033[0m");

	Animal b{5, Espece::Renard, Coord{5, 5}};
	string s2 = b.toString();
	CHECK(s2 == "\033[0;31m*\033[0m");

	Animal c{10, Espece::Vide, Coord{10, 10}};
	string s3 = c.toString();
	CHECK(s3 == "\033[0;97m*\033[0m");
}

void Animal::mange()
{
	if(espece != Espece::Renard)
	{
		throw invalid_argument("L'Animal n'est pas un renard");
	}
	nourriture = min(nourriture + FoodLapin, MaxFood);
}

void Animal::jeune()
{
	if(espece != Espece::Renard)
	{
		throw invalid_argument("L'Animal n'est pas un renard");
	}
	if(nourriture <= 0)
	{
		throw runtime_error("La nourriture est déjà à 0");
	}
	nourriture -= 1;
}

bool Animal::meurt() const
{
	if(espece != Espece::Renard)
	{
		throw invalid_argument("L'Animal n'est pas un renard");
	}
	return nourriture == 0;
}

TEST_CASE("mange + jeune + meurt")
{
	Animal a{0, Espece::Renard, Coord{1, 1}};
	CHECK(a.getNourriture() == FoodInit);
	a.mange();
	CHECK(a.getNourriture() == FoodInit + 5);
	a.mange();
	CHECK(a.getNourriture() == MaxFood);

	Animal b{0, Espece::Lapin, Coord{1, 1}};
	CHECK_THROWS_AS(b.mange(), invalid_argument);
	CHECK_THROWS_AS(b.jeune(), invalid_argument);

	Animal c{0, Espece::Vide, Coord{1, 1}};
	CHECK_THROWS_AS(c.mange(), invalid_argument);
	CHECK_THROWS_AS(c.jeune(), invalid_argument);

	Animal d{5, Espece::Renard, Coord{5, 5}};
	for(int i = 0; i < 5; i++)
	{
		d.jeune();
	}
	CHECK(d.getNourriture() == 0);
	CHECK_THROWS_AS(d.jeune(), runtime_error);

	CHECK_FALSE(a.meurt());
	CHECK_THROWS_AS(b.meurt(), invalid_argument);
	CHECK_THROWS_AS(c.meurt(), invalid_argument);
	CHECK(d.meurt());
}

bool Animal::seReproduit() const
{
	if(espece != Espece::Renard)
	{
		throw invalid_argument("L'Animal n'est pas un renard");
	}
	if(nourriture < FoodReprod)
	{
		return false;
	}
	int pourcentage = int(ProbBirthRenard * 100);
	int random = int((rand() % 100) + 1);
	if(random <= pourcentage)
	{
		return true;
	}
	else
	{
		return false;
	}
}

TEST_CASE("seReproduit Renard")
{
	Animal a{0, Espece::Lapin, Coord{0, 0}};
	CHECK_THROWS_AS(a.seReproduit(), invalid_argument);

	Animal b{0, Espece::Vide, Coord{0, 0}};
	CHECK_THROWS_AS(b.seReproduit(), invalid_argument);

	Animal c{5, Espece::Renard, Coord{5, 5}};
	CHECK_FALSE(c.seReproduit());

	Animal d{10, Espece::Renard, Coord{10, 10}};
	d.mange();
	d.mange();

	int cpt = 0;
	for(int i = 0; i < 500; i++)
	{
		if(d.seReproduit())
		{
			cpt++;
		}
	}
	CHECK(cpt >= 20);
	CHECK(cpt <= 30);
}

bool Animal::seReproduit(int casesLibres) const
{
	if(espece != Espece::Lapin)
	{
		throw invalid_argument("L'Animal n'est pas un lapin");
	}
	if(casesLibres < MinFreeBirthLapin)
	{
		return false;
	}
	int pourcentage = int(ProbBirthLapin * 100);
	int random = int((rand() % 100) + 1);
	if(random <= pourcentage)
	{
		return true;
	}
	else
	{
		return false;
	}
}

TEST_CASE("seReproduit Lapin")
{
	Animal a{0, Espece::Renard, Coord{0, 0}};
	CHECK_THROWS_AS(a.seReproduit(5), invalid_argument);

	Animal b{0, Espece::Vide, Coord{0, 0}};
	CHECK_THROWS_AS(b.seReproduit(5), invalid_argument);

	Animal c{5, Espece::Lapin, Coord{5, 5}};
	for(int i = 0; i <= 3; i++)
	{
		CHECK_FALSE(c.seReproduit(i));
	}

	int cpt = 0;
	for(int i = 0; i < 500; i++)
	{
		if(c.seReproduit(4))
		{
			cpt++;
		}
	}
	CHECK(cpt >= 130);
	CHECK(cpt <= 180);

	int cpt2 = 0;
	for(int i = 0; i < 500; i++)
	{
		if(c.seReproduit(5))
		{
			cpt2++;
		}
	}
	CHECK(cpt2 >= 130);
	CHECK(cpt2 <= 180);
}
