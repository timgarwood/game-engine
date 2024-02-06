#ifndef _DEBUG_SCENE_PARSER_H
#define _DEBUG_SCENE_PARSER_H

#include <string>
#include "debug-scene-data.h"

class DebugSceneParser
{
public:
    DebugSceneData LoadDebugSceneData(const std::string &filename);
};

#endif