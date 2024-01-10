#include "CIndividual.h"
#include <iostream>
#include "Evaluator.h"
#include "Optimizer.h"
#include <vector>
#include "MyMath.h"
using namespace std;

CIndividual::CIndividual() : c_evaluator(CLFLnetEvaluator::CLFLnetEvaluator()) {}

CIndividual::CIndividual(CLFLnetEvaluator& evaluator) : c_evaluator(evaluator) {
	v_genotype.resize((size_t)c_evaluator.iGetNumberOfBits());

	for (int ii = 0; ii < v_genotype.size(); ii++) {
		v_genotype.at(ii) = lRand(c_evaluator.iGetNumberOfValues(ii));
	}
}

CIndividual::CIndividual(CLFLnetEvaluator& evaluator, vector<int> vGenotype) : c_evaluator(evaluator), v_genotype(vGenotype){}

double CIndividual::d_calculateFitness() {
	return c_evaluator.dEvaluate(&v_genotype);
};

void CIndividual::v_mutate(double d_mutProb) {
	for (int ii = 0; ii < v_genotype.size(); ii++) {
		double d_rnd = dRand();
		if (d_rnd <= d_mutProb) {
			v_genotype.at(ii) = lRand(c_evaluator.iGetNumberOfValues(ii));
		}
	}
}

pair<CIndividual, CIndividual> CIndividual::p_crossover(const CIndividual& pc_other, double d_crossProb) {
	long l_crossoverPoint;
	double d_rnd = dRand();

	vector<int> v_child_gen1;
	vector<int> v_child_gen2;
	v_child_gen1.resize((size_t)v_genotype.size());
	v_child_gen2.resize((size_t)v_genotype.size());
	if (d_rnd <= d_crossProb) {
		l_crossoverPoint = lRand(v_genotype.size() - 1) + 1;
		for (long li = 0; li < l_crossoverPoint; li++) {
			v_child_gen1.at(li) = v_genotype.at(li);
			v_child_gen2.at(li) = pc_other.v_genotype.at(li);
		}
		for (long li = l_crossoverPoint; li < v_genotype.size(); li++) {
			v_child_gen1.at(li) = pc_other.v_genotype.at(li);
			v_child_gen2.at(li) = v_genotype.at(li);
		}

		CIndividual c_child1(c_evaluator, v_child_gen1);
		CIndividual c_child2(c_evaluator, v_child_gen2);
		return make_pair(c_child1, c_child2);
	}
	else {
		return make_pair(*this, pc_other);
	}
}

void CIndividual::operator=(const CIndividual& pc_other) {
	v_genotype = pc_other.v_genotype;
	c_evaluator = pc_other.c_evaluator;
}