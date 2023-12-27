#ifndef _ENGINE_H
#define _ENGINE_H

#include <list>

typedef void (*module_init_callback)(void);
typedef void (*frame_callback)(void);
typedef void (*module_teardown_callback)(void);

class Engine
{
private:
    static Engine *s_instance;
    bool m_active;
    Engine();
    std::list<module_init_callback> m_module_init_callbacks;
    std::list<module_teardown_callback> m_module_teardown_callbacks;
    std::list<frame_callback> m_frame_callbacks;

public:
    static Engine *Instance();
    void Init(void);
    void RegisterModuleInitCallback(module_init_callback callback);
    void RegisterFrameCallback(frame_callback callback);
    void UnregisterFrameCallback(frame_callback callback);
    void RegisterModuleTeardownCallback(module_teardown_callback callback);
    void MainLoop(void);
    void EndMainLoop(void);
    void TearDown(void);
};

#endif