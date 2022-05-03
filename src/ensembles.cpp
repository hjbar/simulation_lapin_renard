#include "ensembles.hpp"

// Constructeurs
Ensemble::Ensemble()
	: t{}
	, card{0}
{ }

// Méthodes

ostringstream Ensemble::affiche() const
{
	ostringstream ch;
	ch << "[";
	for(int i = 0; i < card; i++)
	{
		if(i < card - 1)
		{
			ch << t[i] << ", ";
		}
		else
		{
			ch << t[i];
		}
	}
	ch << "]";
	return ch;
}

bool Ensemble::estVide() const
{
	return card == 0;
}

int Ensemble::cardinal() const
{
	return card;
}

TEST_CASE("estVide + cardinal")
{
	Ensemble a{};
	CHECK(a.estVide());
	CHECK(a.cardinal() == 0);
}

void Ensemble::ajoute(int n)
{
	if(card == MAXCARD)
	{
		throw runtime_error("On ne peut pas ajouter un objet à un ensemble plein");
	}
	t[card] = n;
	card++;
}

int Ensemble::tire()
{
	if(estVide())
	{
		throw runtime_error("On ne peut pas tirer un objet dans un ensemble vide");
	}
	int alea = rand() % card;
	int res = t[alea];
	t[alea] = t[card - 1];
	t[card - 1] = -1;
	card--;
	return res;
}

TEST_CASE("ajoute + retire")
{
	Ensemble a{};
	a.ajoute(10);
	CHECK(a.cardinal() == 1);
	CHECK(a.getCase(0) == 10);

	Ensemble b{};
	int n = 10;
	for(int i = 0; i < 10; i++)
	{
		b.ajoute(n);
		CHECK(b.cardinal() == i + 1);
		CHECK(b.getCase(i) == n);
		n *= 2;
	}

	for(int i = 10; i > 0; i--)
	{
		b.tire();
		CHECK(b.cardinal() == i - 1);
		CHECK(b.getCase(i - 1) == -1);
		for(int j = 0; j < b.cardinal(); j++)
		{
			CHECK(b.getCase(j) != -1);
		}
	}

	Ensemble c{};
	for(int i = 0; i < MAXCARD; i++)
	{
		c.ajoute(5);
	}
	CHECK_THROWS_AS((c.ajoute(5)), runtime_error);

	Ensemble d{};
	CHECK_THROWS_AS((d.tire()), runtime_error);
}

int Ensemble::getCase(int n) const
{
	return t[n];
}

// Opérateurs

ostream& operator<<(ostream& out, const Ensemble a)
{
	out << a.affiche().str();
	return out;
}

TEST_CASE("Opérateur << + constructeur vide")
{
	ostringstream ch;
	Ensemble a{};
	ch << a;
	CHECK(ch.str() == "[]");
	ch.str("");

	Ensemble b{};
	b.ajoute(5);
	ch << b;
	CHECK(ch.str() == "[5]");
	ch.str("");

	Ensemble c{};
	c.ajoute(10);
	c.ajoute(5);
	c.ajoute(10);
	ch << c;
	CHECK(ch.str() == "[10, 5, 10]");
	ch.str("");
}
