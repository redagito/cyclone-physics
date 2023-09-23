#pragma once

#include "cyclonedemo/Application.h"
#include <cyclone/Cyclone.h>

/**
 * This application adds additional functionality used in many of the
 * demos. This includes the ability to track contacts (for rigid bodies)
 * and move the camera around.
 */
 class RigidBodyApplication : public Application
 {
 protected:
    /** Holds the maximum number of contacts. */
    const static unsigned maxContacts = 256;

    /** Holds the array of contacts. */
    cyclone::Contact contacts[maxContacts];

    /** Holds the collision data structure for collision detection. */
    cyclone::CollisionData cData;

    /** Holds the contact resolver. */
    cyclone::ContactResolver resolver;

    /** Holds the camera angle. */
    float theta = 0.f;

    /** Holds the camera elevation. */
    float phi = 0.f;

    /** Holds the position of the mouse at the last frame of a drag. */
    int last_x = 0, last_y = 0;

    /** True if the contacts should be rendered. */
    bool renderDebugInfo = false;

    /** True if the simulation is paused. */
    bool pauseSimulation = false;

    /** Pauses the simulation after the next frame automatically */
    bool autoPauseSimulation = false;

    /** Processes the contact generation code. */
    virtual void generateContacts() = 0;

    /** Processes the objects in the simulation forward in time. */
    virtual void updateObjects(cyclone::real duration) = 0;

    /**
     * Finishes drawing the frame, adding debugging information
     * as needed.
     */
    void drawDebug();

    /** Resets the simulation. */
    virtual void reset() = 0;

public:
    /**
     * Creates a new application object.
     */
    RigidBodyApplication();
    virtual ~RigidBodyApplication() = default;

    /** Display the application. */
    virtual void display();

    /** Update the objects. */
    virtual void update();

    /** Handle a mouse click. */
    virtual void mouse(int button, int state, int x, int y);

    /** Handle a mouse drag */
    virtual void mouseDrag(int x, int y);

    /** Handles a key press. */
    virtual void key(unsigned char key);
 };
