#pragma once

#include <cyclonedemo/Application.h>
#include <cyclone/Cyclone.h>

/**
 * The main demo class definition.
 */
class FlightSimDemo : public Application
{
	cyclone::AeroControl left_wing;
	cyclone::AeroControl right_wing;
	cyclone::AeroControl rudder;
	cyclone::Aero tail;
	cyclone::RigidBody aircraft;
	cyclone::ForceRegistry registry;

	cyclone::Vector3 windspeed;

	float left_wing_control = 0.f;
	float right_wing_control = 0.f;
	float rudder_control = 0.f;

	void resetPlane();

public:
	/** Creates a new demo object. */
	FlightSimDemo();
	virtual ~FlightSimDemo();

	/** Returns the window title for the demo. */
	virtual const char* getTitle();

	/** Display the particles. */
	virtual void display();

	/** Update the particle positions. */
	virtual void update();

	/** Handle a key press. */
	virtual void key(unsigned char key);
};