#include <algorithm>
#include <functional>
#include <iostream>

#include "Physics.h"
#include "Renderer.h"
#include "SceneReader.h"
#include "Simulation.h"



Simulation::Simulation()
    : mRenderer(nullptr)
    , mPhysics(nullptr)
{
}


Simulation::~Simulation()
{
}

bool Simulation::initialize()
{
    SceneReader reader;
    Camera cam;
    PointLight light;

    if(!reader.read("test_scene.xml"))
    {
        std::cerr << "Failed to read scene file. Aborting." << std::endl;
        return false;
    }

    reader.readObjects(mObjList);
    reader.readCamera(cam);
    reader.readLight(light);

    std::for_each(mObjList.begin(), mObjList.end(), [](Object* o) {
        o->print();
    });

    mPhysics = new Physics(mObjList);
    mRenderer = new Renderer(mObjList);

    mRenderer->setCamera(cam);
    mRenderer->setLight(light);

    if(!mRenderer->init())
    {
        std::cerr << "Failed to initialize renderer." << std::endl;
        return false;
    }
    

    return true;
}

bool Simulation::step()
{
    if(!mPhysics->update())
    {
        std::cout << "Exit triggered by physics." << std::endl;
        return false;
    }

    if(!mRenderer->render())
    {
        std::cout << "Exit triggered by renderer." << std::endl;
        return false;
    }

    return true;
}

void Simulation::run()
{
    while(step())
    {
        ;
    }
}



