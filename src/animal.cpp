#include "animal.hpp"

//Constructeurs

Animal::Animal()
	: identifiant{-1}
	, espece{Espece::Vide}
	, coordonnees{Coord{0, 0}}
	, nourriture{-1}
	, age{-1}
	, genre{Genre::Vide}
{ }

Animal::Animal(Id ident, Espece esp, Coord coord)
	: identifiant{ident}
	, espece{esp}
	, coordonnees{coord}
	, nourriture{FoodInit}
	, age{0}
	, genre{Genre::Vide}
{
	if(espece == Espece::Renard)
	{
		age = rand() % MaxAgeRenard;
	}
	if(espece == Espece::Lapin)
	{
		age = rand() % MaxAgeLapin;
	}

	int alea = rand() % 100 + 1;
	if(alea <= 50)
	{
		genre = Genre::Male;
	}
	else
	{
		genre = Genre::Female;
	}
}

TEST_CASE("Constructeur")
{

	Animal a{0, Espece::Renard, Coord{2, 3}};
	CHECK(a.getId() == 0);
	CHECK(a.getEspece() == Espece::Renard);
	CHECK(a.getCoord() == Coord{2, 3});
	CHECK(a.getNourriture() == FoodInit);
	CHECK(a.getAge() >= 0);
	CHECK(a.getAge() < MaxAgeRenard);

	Animal b{5, Espece::Lapin, Coord{TAILLEGRILLE - 1, TAILLEGRILLE - 1}};
	CHECK(b.getId() == 5);
	CHECK(b.getEspece() == Espece::Lapin);
	CHECK(b.getCoord() == Coord{TAILLEGRILLE - 1, TAILLEGRILLE - 1});
	CHECK(b.getNourriture() == FoodInit);
	CHECK(b.getAge() >= 0);
	CHECK(b.getAge() < MaxAgeLapin);

	Animal c{};
	CHECK(c.getId() == -1);
	CHECK(c.getEspece() == Espece::Vide);
	CHECK(c.getCoord() == Coord{0, 0});
	CHECK(c.getNourriture() == -1);
	CHECK(c.getAge() == -1);
	CHECK(c.getGenre() == Genre::Vide);

	int cptRenard = 0;
	Animal d{};
	for(int i = 0; i < 10; i++)
	{
		d = Animal{0, Espece::Renard, Coord{0, 0}};
		if(d.getAge() > 0)
		{
			cptRenard++;
		}
	}
	CHECK(cptRenard > 0);

	int cptLapin = 0;
	Animal e{};
	for(int i = 0; i < 10; i++)
	{
		e = Animal{0, Espece::Lapin, Coord{0, 0}};
		if(d.getAge() > 0)
		{
			cptLapin++;
		}
	}
	CHECK(cptLapin > 0);

	Animal f{};
	int cptMale = 0;
	int cptFemale = 0;
	for(int i = 0; i < 200; i++)
	{
		f = Animal{0, Espece::Lapin, Coord{0, 0}};
		if(f.getGenre() == Genre::Male)
		{
			cptMale++;
		}
		else if(f.getGenre() == Genre::Female)
		{
			cptFemale++;
		}
	}

	CHECK(cptMale > 80);
	CHECK(cptMale < 120);
	CHECK(cptFemale > 80);
	CHECK(cptFemale < 120);
}

//Getters

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

int Animal::getAge() const
{
	return age;
}

Genre Animal::getGenre() const
{
	return genre;
}

//Setters

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

//Methodes

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

void Animal::vieillit()
{
	if(espece == Espece::Vide)
	{
		throw invalid_argument("L'Animal Vide ne peut pas vieillir");
	}
	if(age == -1)
	{
		throw invalid_argument("L'Animal possede une probleme avec son age");
	}
	if(espece == Espece::Lapin)
	{
		if(age >= MaxAgeLapin)
		{
			throw runtime_error("L'age est deja le maximal pour ce Lapin");
		}
	}
	if(espece == Espece::Renard)
	{
		if(age >= MaxAgeRenard)
		{
			throw runtime_error("L'age est deja le maximal pour ce Renard");
		}
	}
	age += 1;
}

bool Animal::meurt() const
{
	if(espece == Espece::Vide)
	{
		throw invalid_argument("L'Animal n'est ni un renard, ni un lapin");
	}

	bool tropVieux = false;

	if(espece == Espece::Lapin)
	{
		if(age > MaxAgeLapin)
		{
			throw runtime_error("L'age maximal a ete depasse par ce Lapin");
		}
		tropVieux = (age == MaxAgeLapin);
	}

	if(espece == Espece::Renard)
	{
		if(age > MaxAgeRenard)
		{
			throw runtime_error("L'age maximal a ete depasse par ce Renard");
		}
		tropVieux = (age == MaxAgeRenard);
	}

	return (nourriture == 0) or tropVieux;
}

TEST_CASE("mange + jeune + meurt + vieillit")
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
	CHECK_THROWS_AS(c.meurt(), invalid_argument);
	CHECK(d.meurt());

	Animal e{10, Espece::Lapin, Coord{10, 10}};
	CHECK(e.getAge() >= 0);
	int ageE = e.getAge();
	CHECK_FALSE(e.meurt());
	for(int i = 1; i <= MaxAgeLapin - ageE; i++)
	{
		e.vieillit();
		CHECK(e.getAge() == ageE + i);
	}
	CHECK(e.getAge() == MaxAgeLapin);
	CHECK_THROWS_AS(e.vieillit(), runtime_error);
	CHECK(e.meurt());

	Animal f{15, Espece::Renard, Coord{15, 15}};
	CHECK(f.getAge() >= 0);
	int ageF = f.getAge();
	CHECK_FALSE(f.meurt());
	for(int i = 1; i <= MaxAgeRenard - ageF; i++)
	{
		f.vieillit();
		CHECK(f.getAge() == ageF + i);
	}
	CHECK(f.getAge() == MaxAgeRenard);
	CHECK_THROWS_AS(f.vieillit(), runtime_error);
	CHECK(f.meurt());

	Animal g{};
	CHECK_THROWS_AS(g.vieillit(), invalid_argument);
	CHECK_THROWS_AS(g.meurt(), invalid_argument);
}

void Animal::resetAge()
{
	if(espece == Espece::Vide)
	{
		throw invalid_argument("On ne peut pas reset l'age d'un Animal Vide");
	}

	age = 0;
}

TEST_CASE("resetAge")
{
	Animal a{};

	CHECK_THROWS_AS(a.resetAge(), invalid_argument);

	Animal b{};
	for(int i = 0; i < 10; i++)
	{
		b = Animal{5, Espece::Lapin, Coord{5, 5}};
		b.resetAge();
		CHECK(b.getAge() == 0);
	}

	Animal c{};
	for(int i = 0; i < 10; i++)
	{
		c = Animal{15, Espece::Renard, Coord{15, 15}};
		c.resetAge();
		CHECK(c.getAge() == 0);
	}
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
	CHECK(cpt >= 15);
	CHECK(cpt <= 35);
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
