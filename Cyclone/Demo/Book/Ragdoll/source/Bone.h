#pragma once

#include <cyclone/Cyclone.h>

class Bone : public cyclone::CollisionBox
{
public:
    Bone();
    ~Bone();

    /**
     * We use a sphere to collide bone on bone to allow some limited
     * interpenetration.
     */
    cyclone::CollisionSphere getCollisionSphere() const;

    /** Draws the bone. */
    void render();

    /** Sets the bone to a specific location. */
    void setState(const cyclone::Vector3& position,
        const cyclone::Vector3& extents);

};