#pragma once
#include "CIndividual.h"
class CGeneticAlgorithm
{
private:
	vector< CIndividual> v_population;
	long l_popSize;
	double d_crossProb;
	double d_mutProb;
	CLFLnetEvaluator& c_evaluator;
public:
	CGeneticAlgorithm(long lPopsize, double dCrossProb, double dMutProb, CLFLnetEvaluator& cEvaluator);
	void v_generatePopulation();
	CIndividual* v_evaluateIndividuals();
	void v_runIteration();
};

