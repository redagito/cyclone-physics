#include "AmmoRound.h"

#include <GL/freeglut.h>

/** Draws the round. */
void AmmoRound::render() const
{
    cyclone::Vector3 position;
    particle.getPosition(&position);

    glColor3f(0, 0, 0);
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);
    glutSolidSphere(0.3f, 5, 4);
    glPopMatrix();

    glColor3f(0.75, 0.75, 0.75);
    glPushMatrix();
    glTranslatef(position.x, 0, position.z);
    glScalef(1.0f, 0.1f, 1.0f);
    glutSolidSphere(0.6f, 5, 4);
    glPopMatrix();
}