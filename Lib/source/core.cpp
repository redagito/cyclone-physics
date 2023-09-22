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

#include "cyclone/core.h"

using namespace cyclone;

/*
 * Definition of the sleep epsilon extern.
 */
real cyclone::sleepEpsilon = ((real)0.3);

/*
 * Functions to change sleepEpsilon.
 */
void cyclone::setSleepEpsilon(real value)
{
    cyclone::sleepEpsilon = value;
}

real cyclone::getSleepEpsilon()
{
    return cyclone::sleepEpsilon;
}