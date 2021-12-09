#pragma once

class Scene
{
public:
    Scene() {}
    virtual ~Scene() {}

    virtual void update(float deltaTime) {}
    virtual void render() {}
    virtual void imGuiRender() {}
};