#include "scene.h"

void Scene::Update(double dt) {
    for(auto &e : _ents.list) {
        e->Update(dt);
    }
}

void Scene::Render() {
    for(auto &e : _ents.list) {
        e->Render();
    }
}

std::vector<std::shared_ptr<Entity>> Scene::getEnts() const {
    return _ents.list;
}