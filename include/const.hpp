#pragma once

using Id = int;

#define WHITE "\033[0;97m"
#define RED "\033[0;31m"
#define BLUE "\033[0;34m"
#define RESET_COLOR "\033[0m"

#define NEW_SCREEN "\033[2J\033[H"

const int TAILLEGRILLE = 20;
const int MAXCARD = (TAILLEGRILLE) * (TAILLEGRILLE);

const int FoodInit = 5;
const int FoodLapin = 5;
const int FoodReprod = 8;
const int MaxFood = 10;
const float ProbBirthRenard = float(0.05);
const int MaxAgeRenard = 32;

const float ProbBirthLapin = float(0.30);
const int MinFreeBirthLapin = 4;
const int MaxAgeLapin = 40;

enum class Espece
{
	Renard,
	Lapin,
	Vide
};

enum class Genre
{
	Male,
	Female,
	Vide
};
