#include "Evaluator.h"
#include "Optimizer.h"
#include "Timer.h"
#include "CGeneticAlgorithm.h"
#include <exception>
#include <iostream>
#include <random>

using namespace TimeCounters;

using namespace std;

#define dMAX_TIME 20 * 60


void vRunExperiment(CLFLnetEvaluator &cConfiguredEvaluator)
{
	try
	{
		CTimeCounter c_time_counter;
		CGeneticAlgorithm c_alg(40, 0.5, 0.4, cConfiguredEvaluator);
		double d_time_passed;
		c_time_counter.vSetStartNow();
		c_time_counter.bGetTimePassed(&d_time_passed);
		while (d_time_passed <= dMAX_TIME)
		{
			c_alg.v_runIteration();
			c_time_counter.bGetTimePassed(&d_time_passed);
		}
		cout << c_alg.v_evaluateIndividuals()->d_calculateFitness() << endl;//while (d_time_passed <= MAX_TIME)

	}//try
	catch (exception &c_exception)
	{
		cout << c_exception.what() << endl;
	}//catch (exception &c_exception)
}//void vRunExperiment(const CEvaluator &cConfiguredEvaluator)



void  vRunLFLExperiment(CString  sNetName)
{
	CLFLnetEvaluator c_lfl_eval;
	c_lfl_eval.bConfigure(sNetName);
	vRunExperiment(c_lfl_eval);
	
}//void vRunRastriginExperiment(int iNumberOfBits, int iBitsPerFloat, int iMaskSeed)



void main(int iArgCount, char **ppcArgValues)
{
	random_device c_mask_seed_generator;
	int i_mask_seed = (int)c_mask_seed_generator();


	CString  s_test;
	vRunLFLExperiment("104b00");

	/*vRunIsingSpinGlassExperiment(81, 0, i_mask_seed);
	vRunIsingSpinGlassExperiment(81, 0, iSEED_NO_MASK);

	vRunLeadingOnesExperiment(50, i_mask_seed);
	vRunLeadingOnesExperiment(50, iSEED_NO_MASK);

	vRunMaxSatExperiment(25, 0, 4.27f, i_mask_seed);
	vRunMaxSatExperiment(25, 0, 4.27f, iSEED_NO_MASK);

	vRunNearestNeighborNKExperiment(100, 0, 4, i_mask_seed);
	vRunNearestNeighborNKExperiment(100, 0, 4, iSEED_NO_MASK);

	vRunOneMaxExperiment(100, i_mask_seed);
	vRunOneMaxExperiment(100, iSEED_NO_MASK);

	vRunRastriginExperiment(200, 10, i_mask_seed);
	vRunRastriginExperiment(200, 10, iSEED_NO_MASK);*/
}//void main(int iArgCount, char **ppcArgValues)