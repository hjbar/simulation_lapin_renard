#include "main.hpp"

int main()
{
	srand((unsigned)time(NULL));

	cout << "Hello world" << endl;

	Jeu j{};

	j.affiche();

	char c = ' ';
	Ensemble e;

	while(c != 'q')
	{
		e = j.getPop().getIds();
		for(int i = 0; i < e.cardinal(); i++)
		{
			j.deplaceAnimal(j.getPop().get(e.getCase(i)));
			j.affiche();
		}
		cin >> c;
	}
}
