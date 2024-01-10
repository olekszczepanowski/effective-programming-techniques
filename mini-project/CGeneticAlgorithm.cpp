#include "CGeneticAlgorithm.h"
#include "Evaluator.h"
#include <utility>

CGeneticAlgorithm::CGeneticAlgorithm(long lPopsize, double dCrossProb, double dMutProb, CLFLnetEvaluator& cEvaluator) : c_evaluator(cEvaluator)
{
	l_popSize = lPopsize;
	d_crossProb = dCrossProb;
	d_mutProb = dMutProb;
	v_generatePopulation();
}

void CGeneticAlgorithm::v_generatePopulation()
{
	for (int ii = 0; ii < l_popSize; ii++) {
		CIndividual c_tmp(c_evaluator);
		v_population.push_back(c_tmp);
	}
}

CIndividual *CGeneticAlgorithm::v_evaluateIndividuals()
{
	double d_bestCandidateFitness = -1;
	double d_tmpCandidateFitness;
	CIndividual* c_bestCandidate;
	for(int ii = 0 ; ii < l_popSize ; ii++){
		if (d_bestCandidateFitness < (d_tmpCandidateFitness = v_population[ii].d_calculateFitness())) {
			c_bestCandidate = &v_population[ii];
			d_bestCandidateFitness = d_tmpCandidateFitness;
		}
	}
	return c_bestCandidate;
}

void CGeneticAlgorithm::v_runIteration() {
	cout << v_evaluateIndividuals()->d_calculateFitness() << endl;
	
	vector<CIndividual> v_new_population;
	
	
	int i_curr_popsize = 0;
	while (i_curr_popsize < l_popSize) {
		long rand_index = lRand(l_popSize);
		long rand_index2;
		do {
			rand_index2 = lRand(l_popSize);
		} while (rand_index == rand_index2);

		if (v_population[rand_index].d_calculateFitness() > v_population[rand_index2].d_calculateFitness()) {
			std::pair<CIndividual, CIndividual> new_individuals = v_population[rand_index].p_crossover(v_population[rand_index2],d_crossProb);
			if (i_curr_popsize < l_popSize)
				v_new_population.push_back(new_individuals.first);
			if (i_curr_popsize + 1 < l_popSize)
				v_new_population.push_back(new_individuals.second);
		}
		else {
			std::pair<CIndividual, CIndividual> new_individuals = v_population[rand_index2].p_crossover(v_population[rand_index], d_crossProb);
			if (i_curr_popsize < l_popSize)
				v_new_population.push_back(new_individuals.first);
			if (i_curr_popsize + 1 < l_popSize)
				v_new_population.push_back(new_individuals.second);
		}
		i_curr_popsize += 2;
	}
	v_population = v_new_population;

	for (size_t i = 0; i < l_popSize; i++) {
		v_population[i].v_mutate(d_mutProb);
	}
}



