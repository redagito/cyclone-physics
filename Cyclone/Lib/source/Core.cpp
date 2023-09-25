/*
 * Implementation file for core functions in the library.
 *
 * Part of the Cyclone physics system.
 *
 * Copyright (c) Icosagon 2003. All Rights Reserved.
 *
 * This software is distributed under licence. Use of this software
 * implies agreement with all terms and conditions of the accompanying
 * software licence.
 */

#include "cyclone/Core.h"

using namespace cyclone;

/*
 * Definition of the sleep epsilon extern.
 */
static double sleepEpsilon = ((double)0.3);

/*
 * Functions to change sleepEpsilon.
 */
void cyclone::setSleepEpsilon(double value)
{
    sleepEpsilon = value;
}

double cyclone::getSleepEpsilon()
{
    return sleepEpsilon;
}