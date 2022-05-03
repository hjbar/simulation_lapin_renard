#include "coord.hpp"

// Constructeurs
Coord::Coord(int lig, int col)
	: x{lig}
	, y{col}
{
	if(lig < 0 or lig > TAILLEGRILLE - 1)
	{
		throw invalid_argument("Coordonnées en dehors de la grille");
	}
	if(col < 0 or col > TAILLEGRILLE - 1)
	{
		throw invalid_argument("Coordonnées en dehors de la grille");
	}
}

Coord::Coord(int n)
	: x{n / TAILLEGRILLE}
	, y{n % TAILLEGRILLE}
{
	if(x < 0 or x > TAILLEGRILLE - 1)
	{
		throw invalid_argument("Coordonnées en dehors de la grille");
	}
	if(y < 0 or y > TAILLEGRILLE - 1)
	{
		throw invalid_argument("Coordonnées en dehors de la grille");
	}
}

// Méthodes

int Coord::toInt() const
{
	return x * TAILLEGRILLE + y;
}

TEST_CASE("toInt")
{
	Coord a{0, 0};
	CHECK(a.toInt() == 0);

	Coord b{10, 10};
	CHECK(b.toInt() == 210);

	Coord c{TAILLEGRILLE - 1, TAILLEGRILLE - 1};
	CHECK(c.toInt() == TAILLEGRILLE * TAILLEGRILLE - 1);
}

Ensemble Coord::voisines() const
{
	Ensemble ev{};
	for(int i = max(x - 1, 0); i <= min(x + 1, TAILLEGRILLE - 1); i++)
	{
		for(int j = max(y - 1, 0); j <= min(y + 1, TAILLEGRILLE - 1); j++)
		{
			if(not(Coord{i, j} == Coord{x, y}))
			{
				ev.ajoute(Coord{i, j}.toInt());
			}
		}
	}
	return ev;
}

TEST_CASE("voisines")
{

	Coord a{0, 0};
	Ensemble e1 = a.voisines();
	CHECK((e1.cardinal()) == 3);
	CHECK((Coord(e1.getCase(0))) == Coord{0, 1});
	CHECK((Coord(e1.getCase(1))) == Coord{1, 0});
	CHECK((Coord(e1.getCase(2))) == Coord{1, 1});

	Coord b{0, TAILLEGRILLE - 1};
	Ensemble e2 = b.voisines();
	CHECK((e2.cardinal()) == 3);
	CHECK((Coord(e2.getCase(0))) == Coord{0, TAILLEGRILLE - 2});
	CHECK((Coord(e2.getCase(1))) == Coord{1, TAILLEGRILLE - 2});
	CHECK((Coord(e2.getCase(2))) == Coord{1, TAILLEGRILLE - 1});

	Coord c{TAILLEGRILLE - 1, 0};
	Ensemble e3 = c.voisines();
	CHECK((e3.cardinal()) == 3);
	CHECK((Coord(e3.getCase(0))) == Coord{TAILLEGRILLE - 2, 0});
	CHECK((Coord(e3.getCase(1))) == Coord{TAILLEGRILLE - 2, 1});
	CHECK((Coord(e3.getCase(2))) == Coord{TAILLEGRILLE - 1, 1});

	Coord d{TAILLEGRILLE - 1, TAILLEGRILLE - 1};
	Ensemble e4 = d.voisines();
	CHECK((e4.cardinal()) == 3);
	CHECK((Coord(e4.getCase(0))) == Coord{TAILLEGRILLE - 2, TAILLEGRILLE - 2});
	CHECK((Coord(e4.getCase(1))) == Coord{TAILLEGRILLE - 2, TAILLEGRILLE - 1});
	CHECK((Coord(e4.getCase(2))) == Coord{TAILLEGRILLE - 1, TAILLEGRILLE - 2});

	Coord e{0, 2};
	Ensemble e5 = e.voisines();
	CHECK(e5.cardinal() == 5);
	CHECK((Coord(e5.getCase(0))) == Coord{0, 1});
	CHECK((Coord(e5.getCase(1))) == Coord{0, 3});
	CHECK((Coord(e5.getCase(2))) == Coord{1, 1});
	CHECK((Coord(e5.getCase(3))) == Coord{1, 2});
	CHECK((Coord(e5.getCase(4))) == Coord{1, 3});

	Coord f{2, 0};
	Ensemble e6 = f.voisines();
	CHECK(e6.cardinal() == 5);
	CHECK((Coord(e6.getCase(0))) == Coord{1, 0});
	CHECK((Coord(e6.getCase(1))) == Coord{1, 1});
	CHECK((Coord(e6.getCase(2))) == Coord{2, 1});
	CHECK((Coord(e6.getCase(3))) == Coord{3, 0});
	CHECK((Coord(e6.getCase(4))) == Coord{3, 1});

	Coord g{TAILLEGRILLE - 1, 2};
	Ensemble e7 = g.voisines();
	CHECK(e7.cardinal() == 5);
	CHECK((Coord(e7.getCase(0))) == Coord{TAILLEGRILLE - 2, 1});
	CHECK((Coord(e7.getCase(1))) == Coord{TAILLEGRILLE - 2, 2});
	CHECK((Coord(e7.getCase(2))) == Coord{TAILLEGRILLE - 2, 3});
	CHECK((Coord(e7.getCase(3))) == Coord{TAILLEGRILLE - 1, 1});
	CHECK((Coord(e7.getCase(4))) == Coord{TAILLEGRILLE - 1, 3});

	Coord h{2, TAILLEGRILLE - 1};
	Ensemble e8 = h.voisines();
	CHECK(e8.cardinal() == 5);
	CHECK((Coord(e8.getCase(0))) == Coord{1, TAILLEGRILLE - 2});
	CHECK((Coord(e8.getCase(1))) == Coord{1, TAILLEGRILLE - 1});
	CHECK((Coord(e8.getCase(2))) == Coord{2, TAILLEGRILLE - 2});
	CHECK((Coord(e8.getCase(3))) == Coord{3, TAILLEGRILLE - 2});
	CHECK((Coord(e8.getCase(4))) == Coord{3, TAILLEGRILLE - 1});

	Coord i{2, 1};
	Ensemble e9 = i.voisines();
	CHECK(e9.cardinal() == 8);
	CHECK((Coord(e9.getCase(0))) == Coord{1, 0});
	CHECK((Coord(e9.getCase(1))) == Coord{1, 1});
	CHECK((Coord(e9.getCase(2))) == Coord{1, 2});
	CHECK((Coord(e9.getCase(3))) == Coord{2, 0});
	CHECK((Coord(e9.getCase(4))) == Coord{2, 2});
	CHECK((Coord(e9.getCase(5))) == Coord{3, 0});
	CHECK((Coord(e9.getCase(6))) == Coord{3, 1});
	CHECK((Coord(e9.getCase(7))) == Coord{3, 2});

	Coord j{TAILLEGRILLE - 2, TAILLEGRILLE - 1};
	Ensemble e10 = j.voisines();
	CHECK(e10.cardinal() == 5);
	CHECK((Coord(e10.getCase(0))) == Coord{TAILLEGRILLE - 3, TAILLEGRILLE - 2});
	CHECK((Coord(e10.getCase(1))) == Coord{TAILLEGRILLE - 3, TAILLEGRILLE - 1});
	CHECK((Coord(e10.getCase(2))) == Coord{TAILLEGRILLE - 2, TAILLEGRILLE - 2});
	CHECK((Coord(e10.getCase(3))) == Coord{TAILLEGRILLE - 1, TAILLEGRILLE - 2});
	CHECK((Coord(e10.getCase(4))) == Coord{TAILLEGRILLE - 1, TAILLEGRILLE - 1});
}

// Getters
int Coord::getX() const
{
	return x;
}

int Coord::getY() const
{
	return y;
}

TEST_CASE("Constructeur + Getters")
{

	Coord a{0, 0};
	CHECK(a.getX() == 0);
	CHECK(a.getY() == 0);

	Coord b{10, 10};
	CHECK(b.getX() == 10);
	CHECK(b.getY() == 10);

	Coord c{TAILLEGRILLE - 1, TAILLEGRILLE - 1};
	CHECK(c.getX() == TAILLEGRILLE - 1);
	CHECK(c.getY() == TAILLEGRILLE - 1);

	CHECK_THROWS_AS((Coord{TAILLEGRILLE + 5, 10}), invalid_argument);
	CHECK_THROWS_AS((Coord{-5, 10}), invalid_argument);
	CHECK_THROWS_AS((Coord{10, TAILLEGRILLE + 5}), invalid_argument);
	CHECK_THROWS_AS((Coord{10, -5}), invalid_argument);
	CHECK_THROWS_AS((Coord{TAILLEGRILLE + 5, TAILLEGRILLE + 5}), invalid_argument);
	CHECK_THROWS_AS((Coord{-5, -5}), invalid_argument);
	CHECK_THROWS_AS((Coord{-5, TAILLEGRILLE + 5}), invalid_argument);
	CHECK_THROWS_AS((Coord{TAILLEGRILLE + 5, -5}), invalid_argument);

	Coord a2{0};
	CHECK(a2.getX() == 0);
	CHECK(a2.getY() == 0);

	Coord b2{10};
	CHECK(b2.getX() == 0);
	CHECK(b2.getY() == 10);

	Coord c2{210};
	CHECK(c2.getX() == 10);
	CHECK(c2.getY() == 10);

	Coord d2{TAILLEGRILLE * TAILLEGRILLE - 1};
	CHECK(d2.getX() == TAILLEGRILLE - 1);
	CHECK(d2.getY() == TAILLEGRILLE - 1);

	CHECK_THROWS_AS((Coord{-5}), invalid_argument);
	CHECK_THROWS_AS((Coord{401}), invalid_argument);
}

// Opérateurs
ostream& operator<<(ostream& out, const Coord a)
{
	out << "(" << a.getX() << "," << a.getY() << ")";
	return out;
}

TEST_CASE("Opérateur <<")
{
	ostringstream ch;
	ch << Coord{10, 10};
	CHECK(ch.str() == "(10,10)");
	ch.str("");
	ch << Coord{5, 4};
	CHECK(ch.str() == "(5,4)");
	ch.str("");
	ch << Coord{0, 19};
	CHECK(ch.str() == "(0,19)");
}

bool operator==(const Coord a, const Coord b)
{
	return a.getX() == b.getX() and a.getY() == b.getY();
}

TEST_CASE("Opérateur ==")
{
	CHECK((Coord{0, 0}) == (Coord{0, 0}));
	CHECK((Coord{TAILLEGRILLE - 1, TAILLEGRILLE - 1}) ==
		  (Coord{TAILLEGRILLE - 1, TAILLEGRILLE - 1}));
	CHECK((Coord{10, 10}) == (Coord{10, 10}));

	CHECK_FALSE((Coord{0, 19}) == (Coord{0, 0}));
	CHECK_FALSE((Coord{19, 0}) == (Coord{0, 0}));
	CHECK_FALSE((Coord{19, 19}) == (Coord{0, 0}));
	CHECK_FALSE((Coord{0, 19}) == (Coord{19, 0}));
	CHECK_FALSE((Coord{19, 0}) == (Coord{0, 19}));
	CHECK_FALSE((Coord{19, 19}) == (Coord{19, 0}));
	CHECK_FALSE((Coord{19, 19}) == (Coord{0, 19}));
}
