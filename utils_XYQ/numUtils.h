#pragma once

#include <random>
#include <vector>

using namespace std;



/* Generate a vector of random integers. */
vector<int>* randIntGen( int L_bnd, int U_bnd, unsigned int cnt );

/* 
Cut-off the upper 10th order digits of the target number down to and 
including the specified order. 
*/
long long cutUpperOrder( long long tarNum, int orderPos );

/*
Turns the integer (long long) into a vector of integers where each entry is the value
of the number at a 10th power.
*/
vector<int> intToArray(long long number);

/*
Simply determines if two doubles are close enough in value with specified threshold.
*/
bool isEqEnough( double a, double b, double thresh = std::pow( 10, -9 ) );

