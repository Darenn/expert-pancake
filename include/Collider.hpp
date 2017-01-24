//
// Created by kelle on 23/01/2017.
//

#ifndef PANCAKE_COLLIDER_HPP
#define PANCAKE_COLLIDER_HPP


#include <SFML/System/Vector2.hpp>
#include "Component.hpp"

class PhysicsEngine;

class Collider : public Component {

public:
    void awake();
    // Is this collider configured as a trigger?
    bool isTrigger;
    // Get the bounciness used by the collider.
    float bounciness;
    // The density of the collider used to calculate its mass.
    float density;
    // Get the friction used by the collider.
    float friction;
    // The local offset of the collider
    sf::Vector2f offset;
private:
    friend class Engine;
    static PhysicsEngine * physicsEngine;
};


#endif //PANCAKE_COLLIDER_HPP
