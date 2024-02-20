<p>
Projet Programmation Modulaire - Systeme predateurs/proies

Barreiro Hugo MI1
Ahmed Atmane MI1

Nous avons installe au préalable la biblioteque doctest avec la commande suivante :
sudo apt install doctest-dev

Avec la regle make all du Makefile on genere 3 executables :

- Un pour les tests -> test.exe
- Un pour la simulation dans la console -> lapin.exe
- Un pour generer les images du fichier .gif -> video.exe

On genere le fichier video .gif grace a la regle make exec.
Cette derniere execute video.exe, convertie les images en fichier .gif, supprime les images et enfin ouvre la video avec firefox.


Informations supplementaires :

- Les constantes sont stockees dans un fichier dedie -> const.hpp

- L'age maximal d'un renard est de 32, l'age maximal d'un lapin est de 40.
En effet, l'esperance de vie d'un renard domestique est de 16 ans, celle d'un lapin domestique est de 20 ans.
On a conside d'augmenter de 0.5 ans par deplacement l'age d'un animal.
Pour ne pas utiliser des floats, on a double l'age maximal des animaux et augmente de 1 an l'age par deplacement.
</p>
