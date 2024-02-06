#ifndef _DEBUG_SCENE_FACTOR_H
#define _DEBUG_SCENE_FACTOR_H

#include <string>

class DebugSceneFactory
{
public:
    static DebugSceneFactory *Instance();
    void LoadScene(const std::string &filename);

private:
    DebugSceneFactory();
    static DebugSceneFactory *instance;
};

#endif