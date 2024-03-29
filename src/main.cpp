#include "main.hpp"

int main()
{
	srand((unsigned)time(NULL));

	Jeu j{};

	j.verifieAll();

	j.affiche();

	char c = ' ';
	cin >> c;
	Ensemble eL;
	Ensemble eR;
	Ensemble e;
	Id ident;
	Animal a{};

	while(c != 'q')
	{
		eL = j.getPop().getIdsEspece(Espece::Lapin);
		eR = j.getPop().getIdsEspece(Espece::Renard);

		if(eL.cardinal() >= (TAILLEGRILLE * TAILLEGRILLE * 0.8) and eR.cardinal() == 0)
		{
			return 0;
		}
		if(eR.cardinal() == 0 and eL.cardinal() == 0)
		{
			return 0;
		}

		e = j.getPop().getIds();

		while(not e.estVide())
		{
			a = j.getPop().get(e.tire());
			ident = j.deplaceAnimal(a);
			j.verifieAll();
			if(ident != -1 and e.possede(ident))
			{
				e.retire(ident);
			}
		}

		j.affiche();
		cin >> c;
	}
	return 0;
}
