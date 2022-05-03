#include "grille.hpp"

//Constructeurs
Grille::Grille()
	: g{}
{
	for(long unsigned int i = 0; i < g.size(); i++)
	{
		for(long unsigned int j = 0; j < g[i].size(); j++)
		{
			g[i][j] = -1;
		}
	}
}

bool Grille::caseVide(Coord c) const
{
	return g[c.getX()][c.getY()] == -1;
}

Id Grille::getCase(Coord c) const
{
	return g[c.getX()][c.getY()];
}

TEST_CASE("Constructeur vide")
{
	Grille g{};
	for(int i = 0; i < TAILLEGRILLE; i++)
	{
		for(int j = 0; j < TAILLEGRILLE; j++)
		{
			CHECK((g.getCase(Coord{i, j})) == -1);
			CHECK(g.caseVide(Coord{i, j}));
		}
	}
}

void Grille::videCase(Coord c)
{
	if(g[c.getX()][c.getY()] == -1)
	{
		throw runtime_error("La case est déjà vide");
	}
	g[c.getX()][c.getY()] = -1;
}

void Grille::setCase(Id ident, Coord c)
{
	if(g[c.getX()][c.getY()] != -1)
	{
		throw runtime_error("La case contient déjà un animal");
	}
	g[c.getX()][c.getY()] = ident;
}

TEST_CASE("videCase + setCase")
{
	Grille g{};
	for(int i = 1; i <= 10; i++)
	{
		g.setCase(i, (Coord{i, i}));
		CHECK_FALSE(g.caseVide((Coord{i, i})));
		CHECK(g.getCase((Coord{i, i})) == i);
	}

	for(int i = 1; i <= 10; i++)
	{
		g.videCase((Coord{i, i}));
		CHECK(g.caseVide((Coord{i, i})));
		CHECK(g.getCase((Coord{i, i})) == -1);
	}
}
