#pragma once
#include <iostream>
#include "Evaluator.h"
#include "Optimizer.h"
#include <vector>
using namespace std;
class CIndividual {

private:
	vector<int> v_genotype;
	CLFLnetEvaluator& c_evaluator;
public:
	CIndividual();
	CIndividual(CLFLnetEvaluator& evaluator);
	CIndividual(CLFLnetEvaluator& evaluator, vector<int> vGenotype);
	double d_calculateFitness();
	void v_mutate(double d_mutProb);
	pair<CIndividual, CIndividual> p_crossover(const CIndividual& pc_other, double d_crossProb);
	void operator=(const CIndividual& pc_other);
	
};
