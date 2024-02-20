#include "video.hpp"

int main()
{
	srand((unsigned)time(NULL));

	Jeu j{};

	j.verifieAll();

	Ensemble eL;
	Ensemble eR;
	Ensemble e;
	Id ident;
	Animal a{};

	int cptFichier = 0;
	const int nbTour = 1000;

	for(int i = 0; i < 20; i++)
	{
		j.genereImage(cptFichier);
		cptFichier++;
	}

	for(int i = 0; i < nbTour; i++)
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

		j.genereImage(cptFichier);
		cptFichier++;
	}

	return 0;
}
