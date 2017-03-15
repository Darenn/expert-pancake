//
// Created by kelle on 02/02/2017.
//

#ifndef PANCAKE_PLAYERCONTROLLER_HPP
#define PANCAKE_PLAYERCONTROLLER_HPP

#include <User/Items/BulletObject.hpp>
#include "GameLogic.hpp"
#include "Inputs.hpp"

class PlayerController : public PancakeEngine::Behavior {
public:
    bool climbing = false;
    bool swiming = false;
    PancakeEngine::Collider* topCollider;
    int direction = 1;

    void update() {
        topCollider->setSleep(false);
        float velocityXDesired = 0;
        float velocityYDesired = 0;
        PancakeEngine::Rigidbody* rb = gameObject->getComponent<PancakeEngine::Rigidbody>();
        if (PancakeEngine::Input::getButtonHeld(gameObject->name + "_jump")) {
            if (climbing || swiming) {
                velocityYDesired = -5;
            }
        }
        if (rb->getVelocity().y < 0.1 && rb->getVelocity().y > -0.1 && PancakeEngine::Input::getButtonPressed(gameObject->name + "_jump")) {
            gameObject->getComponent<PancakeEngine::Rigidbody>()->applyLinearImpulse(sf::Vector2f(0, -11));
        }
        if (PancakeEngine::Input::getButtonHeld(gameObject->name + "_duck")) {
            velocityYDesired = 5;
            if (! climbing && ! swiming) {
                topCollider->setSleep(true);
            }
        }
        if (PancakeEngine::Input::getButtonHeld(gameObject->name + "_right")) {
            velocityXDesired = 5;
        }
        if (PancakeEngine::Input::getButtonHeld(gameObject->name + "_left")) {
            velocityXDesired = -5;
        }
        float velYChange = velocityYDesired - rb->getVelocity().y;
        float velXChange = velocityXDesired - rb->getVelocity().x;
        float impulseY = rb->getMass() * velYChange;
        float impulseX = rb->getMass() * velXChange; //disregard time factor
        rb->applyLinearImpulse(sf::Vector2f(impulseX,0));
        if (climbing || swiming) {
            rb->applyLinearImpulse(sf::Vector2f(0,impulseY));
        }

        if (rb->getVelocity().x > 2) {
            direction = 1;
        } else if (rb->getVelocity().x < -2){
            direction = -1;
        }

       if(PancakeEngine::Input::getButtonPressed(gameObject->name + "_fire")) {

           BulletObject& bo = PancakeEngine::SceneManager::getCurrentScene()->addGameObject<BulletObject>(1);
           Bullet* b = bo.getComponent<Bullet>();
           b->direction = direction;

           bo.transform.setPosition(sf::Vector2f(gameObject->transform.getWorldPosition().x + b->direction * 40, gameObject->transform.getWorldPosition().y));
       }
    }
};


#endif //PANCAKE_PLAYERCONTROLLER_HPP
