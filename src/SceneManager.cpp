//
// Created by nicolas on 23/01/17.
//

#include "../include/SceneManager.hpp"

void SceneManager::addScene(Scene *scene) {
    scenes.push_back(scene);
}

Scene* SceneManager::getCurrentScene() {
    return scenes[currentScene];
}

void SceneManager::setCurrentScene(std::string name) {
    for (int i = 0; i < scenes.size(); ++i) {
        if (scenes[i]->name == name)
            currentScene = i;
            return;
    }
}

void SceneManager::nextScene() {
    currentScene = (currentScene++)%scenes.size();
}