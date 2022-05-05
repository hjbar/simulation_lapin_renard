#include "main.hpp"

int main()
{
	srand((unsigned)time(NULL));

	cout << "Hello world" << endl;

	Jeu j{};

	j.affiche();

	array<Animal, TAILLEGRILLE* TAILLEGRILLE> animaux = j.getPop().getT();
	for(long unsigned int i = 0; i < animaux.size(); i++)
	{
		j.deplaceAnimal(animaux[int(i)]);
	}

	j.affiche();
}
