#define GLM_FORCE_CXX14
#include <iostream>

#include <glm/vec3.hpp>
#include <pugixml.hpp>

#include "AABB.h"
#include "SceneReader.h"
#include "Sphere.h"



SceneReader::SceneReader()
{
}


SceneReader::~SceneReader()
{
}

void SceneReader::read(std::string filename, std::vector<Object*>& objList)
{
    pugi::xml_document doc;
    doc.load_file(filename.c_str());

    pugi::xml_node rootNode = doc.child("scene");

    for (pugi::xml_node objNode = rootNode.child("object"); objNode; objNode = objNode.next_sibling())
    {
        pugi::xml_node posNode = objNode.child("pos");
        pugi::xml_node velNode = objNode.child("vel");

        
        double x = posNode.attribute("x").as_double();
        double y = posNode.attribute("y").as_double();
        double z = posNode.attribute("z").as_double();
        double rx = posNode.attribute("rx").as_double();
        double ry = posNode.attribute("ry").as_double();
        double rz = posNode.attribute("rz").as_double();

        double vx = velNode.attribute("vx").as_double();
        double vy = velNode.attribute("vy").as_double();
        double vz = velNode.attribute("vz").as_double();
        double ax = velNode.attribute("ax").as_double();
        double ay = velNode.attribute("ay").as_double();
        double az = velNode.attribute("az").as_double();

        glm::vec3 position(x, y, z);
        glm::vec3 rotation(rx, ry, rz);
        glm::vec3 velocity(vx, vy, vz);
        glm::vec3 angularVelocity(ax, ay, az);

        double mass = objNode.attribute("mass").as_double(1.0);

        Object* obj = nullptr;

        std::string objType = objNode.attribute("type").as_string();
        if (objType == "sphere")
        {
            double radius = objNode.attribute("radius").as_double(1.0);
            obj = new Sphere(radius);
            
        }
        else if (objType == "aabb")
        {
            pugi::xml_node dimNode = objNode.child("dim");
            double wx = dimNode.attribute("wx").as_double(1.0);
            double wy = dimNode.attribute("wy").as_double(1.0);
            double wz = dimNode.attribute("wz").as_double(1.0);

            obj = new AABB(wx, wy, wz);
        }
        else
        {
            std::cerr << "Unsupported type: " << objType << std::endl;
            continue;
        }

        obj->phyProp().setMass(mass);
        obj->phyProp().setPose(position, rotation);
        objList.push_back(obj);
    }
}
