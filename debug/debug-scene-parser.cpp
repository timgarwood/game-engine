#include "debug-scene-parser.h"
#include "file-utils.h"
#include <fstream>
#include "json/json.h"
#include <cassert>

using namespace std;

DebugSceneData DebugSceneParser::LoadDebugSceneData(const std::string &filename)
{
    ifstream fileStream(filename.c_str());
    DebugSceneData debugSceneData;
    if (!fileStream.is_open())
    {
        assert(false);
    }

    Json::Value rootNode;

    fileStream >> rootNode;

    Json::Value sceneData = rootNode["sceneData"];
    Json::Value camera = sceneData["camera"];
    Json::Value cameraPos = camera["pos"];
    Json::Value cameraLookAt = camera["lookAt"];
    Json::Value gameObjects = sceneData["gameObjects"];
    debugSceneData.cameraPosition = Vector3f(cameraPos["x"].asFloat(), cameraPos["y"].asFloat(), cameraPos["z"].asFloat());
    debugSceneData.cameraLookAt = Vector3f(cameraLookAt["x"].asFloat(), cameraLookAt["y"].asFloat(), cameraLookAt["z"].asFloat());

    int numGameObjects = int(gameObjects.size());

    for (int i = 0; i < numGameObjects; ++i)
    {
        Json::Value gameObjectNode = gameObjects[i];
        Json::Value gameObjectPosNode = gameObjectNode["pos"];
        Json::Value gameObjectRotNode = gameObjectNode["rot"];
        Json::Value gameObjectColorNode = gameObjectNode["color"];
        Json::Value gameObjectDimNode = gameObjectNode["dim"];
        Json::Value gameObjectPhysNode = gameObjectNode["phy"];
        GameObjectDebugData godd;
        godd.width = gameObjectDimNode["width"].asFloat();
        godd.height = gameObjectDimNode["height"].asFloat();
        godd.depth = gameObjectDimNode["depth"].asFloat();

        godd.rotation.SetIdentity();

        godd.position = Vector3f(gameObjectPosNode["x"].asFloat(), gameObjectPosNode["y"].asFloat(), gameObjectPosNode["z"].asFloat());

        godd.color = Vector3f(gameObjectColorNode["r"].asFloat(), gameObjectColorNode["g"].asFloat(), gameObjectColorNode["b"].asFloat());

        godd.mass = gameObjectPhysNode["mass"].asFloat();
        godd.isDynamic = gameObjectPhysNode["isDynamic"].asBool();

        debugSceneData.gameObjectDebugData.push_back(godd);
    }

    fileStream.close();

    return debugSceneData;
}