#include "main.hpp"

int main()
{
	srand((unsigned)time(NULL));

	cout << "Hello world" << endl;

	Jeu j{};

	j.verifieAll();

	j.affiche();

	int cpt = 0;
	char c = ' ';
	Ensemble e;
	Animal a{};
	Espece esp = Espece::Vide;

	while(c != 'q')
	{
		e = j.getPop().getIds();
		for(int i = 0; i < e.cardinal(); i++)
		{
			a = j.getPop().get(e.getCase(i));
			cout << a.getCoord() << "  " << a.getId() << "  ";
			esp = a.getEspece();
			if(esp == Espece::Renard)
			{
				cout << "R" << endl;
			}
			else if(esp == Espece::Lapin)
			{
				cout << "L" << endl;
			}
			else
			{
				cout << "???" << endl;
			}
			j.deplaceAnimal(a);
			cpt++;
			cout << cpt << endl;
			j.verifieAll();
		}
		j.affiche();
		cin >> c;
	}
}
