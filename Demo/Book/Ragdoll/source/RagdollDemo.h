#pragma once


#include <cyclonedemo/RigidBodyApplication.h>

#include "Bone.h"

#define NUM_BONES 12
#define NUM_JOINTS 11

/**
 * The main demo class definition.
 */
class RagdollDemo : public RigidBodyApplication
{
    cyclone::Random random;

    /** Holds the bone bodies. */
    Bone bones[NUM_BONES];

    /** Holds the joints. */
    cyclone::Joint joints[NUM_JOINTS];

    /** Processes the contact generation code. */
    virtual void generateContacts();

    /** Processes the objects in the simulation forward in time. */
    virtual void updateObjects(double duration);

    /** Resets the position of all the bones. */
    virtual void reset();

public:
    /** Creates a new demo object. */
    RagdollDemo();

    /** Sets up the rendering. */
    virtual void initGraphics();

    /** Returns the window title for the demo. */
    virtual const char* getTitle();

    /** Display the particle positions. */
    virtual void display();
};