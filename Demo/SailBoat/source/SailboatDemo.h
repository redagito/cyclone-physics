#pragma once

#include <cyclonedemo/Application.h>
#include <cyclone/Cyclone.h>

/**
 * The main demo class definition.
 */
class SailboatDemo : public Application
{
    cyclone::Buoyancy buoyancy;

    cyclone::Aero sail;
    cyclone::RigidBody sailboat;
    cyclone::ForceRegistry registry;

    cyclone::Random r;
    cyclone::Vector3 windspeed;

    float sail_control;

public:
    /** Creates a new demo object. */
    SailboatDemo();
    virtual ~SailboatDemo();

    /** Returns the window title for the demo. */
    virtual const char* getTitle();

    /** Display the particles. */
    virtual void display();

    /** Update the particle positions. */
    virtual void update();

    /** Handle a key press. */
    virtual void key(unsigned char key);
};