#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
#include<limits>
#include <Windows.h>
using namespace std;

#define V 5

int child = 0;
int populationSize = 0;
int evoCount = 0;

int cities[V][V] = { { INT_MAX, 25, 40, 31, 27},
				{ 5, INT_MAX, 17, 30, 25},
				{ 19, 15, INT_MAX, 6, 1},
				{ 9, 50, 24, INT_MAX, 6 },
				{ 22, 8, 7, 10, INT_MAX } };
int generateRandomNumber(int min, int max) {
	return min + rand() % (max - min + 1);
}
int fitness(vector<int>& chromosome)
{
	double totalDistance = 0.0;
	int numCities = chromosome.size();

	for (int i = 0; i < numCities - 1; i++) {
		int city1 = chromosome[i];
		int city2 = chromosome[i + 1];
		totalDistance += cities[city1][city2];
	}

	// Дополнительно учитываем расстояние от последнего города к первому
	int firstCity = chromosome[0];
	int lastCity = chromosome[numCities - 1];
	totalDistance += cities[lastCity][firstCity];

	return totalDistance;
}
vector<int> crossover(const vector<int>& parent1, const vector<int>& parent2) {
	int numCities = parent1.size();
	vector<int> child(numCities, -1);

	int crossoverPoint = generateRandomNumber(0, numCities - 1);

	// Копируем гены от первого родителя до точки скрещивания
	for (int i = 0; i <= crossoverPoint; i++) {
		child[i] = parent1[i];
	}

	// Заполняем оставшуюся часть хромосомы генами второго родителя
	int j = 0;
	for (int i = crossoverPoint + 1; i < numCities; i++) {
		while (find(child.begin(), child.end(), parent2[j]) != child.end()) {
			j++;
		}
		child[i] = parent2[j];
	}

	return child;
}
void mutate(vector<int>& chromosome, double mutationRate) {
	int numGenes = chromosome.size();

	for (int i = 0; i < numGenes; i++) {
		double randomValue = (double)rand() / RAND_MAX;
		if (randomValue < mutationRate) {
			int geneIndex1 = generateRandomNumber(0, numGenes - 1);
			int geneIndex2 = generateRandomNumber(0, numGenes - 1);
			swap(chromosome[geneIndex1], chromosome[geneIndex2]);
		}
	}
}

vector<int> generateRandomChromosome() {
	vector<int> chromosome(V);
	for (int i = 0; i < V; i++) {
		chromosome[i] = i;
	}
	random_shuffle(chromosome.begin(), chromosome.end());
	return chromosome;
}
vector<int> generateRandomPopulation(int populationSize) {
	vector<int> population;
	for (int i = 0; i < populationSize; i++) {
		population.push_back(i);
	}
	return population;
}
vector<int> selectParent( vector<vector<int>> population) {
	int populationSize = population.size();
	int parentIndex1 = generateRandomNumber(0, populationSize - 1);
	int parentIndex2 = generateRandomNumber(0, populationSize - 1);
	return (fitness(population[parentIndex1]) < fitness(population[parentIndex2])) ? population[parentIndex1] : population[parentIndex2];
}

vector<int> Genetic_algo(int cities[V][V]) 
{
	vector<vector<int>> population(populationSize);
	for (int i = 0; i < populationSize; i++) {
		population[i] = generateRandomChromosome();
	}
	for (int i = 0; i < evoCount; i++) {
		vector<vector<int>> newPopulation;

		for (int j = 0; j < child; j++) {
			vector<int> parent1 = selectParent(population);
			vector<int> parent2 = selectParent(population);
			vector<int> child = crossover(parent1, parent2);
			mutate(child, 0.1); // Передаем вероятность мутации (0.1 в данном случае)
			newPopulation.push_back(child);
		}

		population.insert(population.end(), newPopulation.begin(), newPopulation.end());

		// Сортировка популяции по приспособленности
		sort(population.begin(), population.end(), []( vector<int>& a,  vector<int>& b) {
			return fitness(a) < fitness(b);
			});
		population.resize(populationSize);
		cout << "Iteration: " << i + 1 << endl;
		for ( auto& chromosome : population) {
			cout << "Chromosome: ";
			for (int gene : chromosome) {
				cout << gene << " ";
			}
			cout << "Fitness: " << fitness(chromosome) << endl;
		}

		// Оставляем только лучшие хромосомы

		// Выводим текущую лучшую хромосому после каждой эволюции
		cout << "Эволюция " << i + 1 << ", лучшая хромосома: ";
		for (int gene : population[0]) {
			cout << gene << " ";
		}
		cout << "Приспособленность: " << fitness(population[0]) << endl;
	}

	// Возвращаем лучшую хромосому после заданного числа эволюций
	return population[0];
}


int main()
{
	setlocale(LC_ALL, "ru");
	srand(static_cast<unsigned int>(time(nullptr)));
	do
	{
		cout << "Введите размер популяций: ";
		cin >> populationSize;
		cin.clear();
		cin.ignore(32767, '\n');
	} while (populationSize <= 0);

	do
	{
		cout << "Введите количество потомков в одной популяции: ";
		cin >> child;
		cin.clear();
		cin.ignore(32767, '\n');
	} while (child <= 0);

	do
	{
		cout << "Введите количество	 эволюций: ";
		cin >> evoCount;
		cin.clear();
		cin.ignore(32767, '\n');
	} while (evoCount <= 0);

	Genetic_algo(cities);
}