/*
    File: simulator.h
    Note: For details, please see simulator.cpp. That file is where most of our commenting are done.
*/
#ifndef simulator_h
#define simulator_h

/*
    includes:
*/
#include "testcase_generator.h"

long long simulate(int numberOfCashiers, int numberOfCustomers, testcase::tcGenerator testcases);

#endif
