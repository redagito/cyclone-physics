#pragma once

/*
 * Interface file for the coarse collision detection system.
 *
 * Part of the Cyclone physics system.
 *
 * Copyright (c) Icosagon 2003. All Rights Reserved.
 *
 * This software is distributed under licence. Use of this software
 * implies agreement with all terms and conditions of the accompanying
 * software licence.
 */

/**
 * @file
 *
 * This file contains the coarse collision detection system.  It is
 * used to return pairs of objects that may be in contact, which can
 * then be tested using fine grained methods.
 */

#include <vector>
#include <cstddef>
#include "contacts.h"

namespace cyclone {

    /**
     * Stores a potential contact to check later.
     */
    struct PotentialContact
    {
        /**
         * Holds the bodies that might be in contact.
         */
        RigidBody* body[2];
    };

} // namespace cyclone