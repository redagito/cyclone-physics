#pragma once

#include "cyclone/contact/ParticleContactGenerator.h"
#include "cyclone/Vector3.h"

namespace cyclone
{
    class Particle;

    /**
    * Constraints are just like links, except they connect a particle to
    * an immovable anchor point.
    */
    class ParticleConstraint : public ParticleContactGenerator
    {
    public:
        /**
        * Holds the particles connected by this constraint.
        */
        Particle* particle = nullptr;

        /**
         * The point to which the particle is anchored.
         */
        Vector3 anchor;

    protected:
        /**
        * Returns the current length of the link.
        */
        double currentLength() const;

    public:
        /**
        * Geneates the contacts to keep this link from being
        * violated. This class can only ever generate a single
        * contact, so the pointer can be a pointer to a single
        * element, the limit parameter is assumed to be at least one
        * (zero isn't valid) and the return value is either 0, if the
        * cable wasn't over-extended, or one if a contact was needed.
        *
        * NB: This method is declared in the same way (as pure
        * virtual) in the parent class, but is replicated here for
        * documentation purposes.
        */
        virtual unsigned addContact(ParticleContact* contact,
            unsigned limit) const = 0;

        virtual ~ParticleConstraint() = default;
    };
}