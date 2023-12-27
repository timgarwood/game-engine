#ifndef _ENGINE_API_H
#define _ENGINE_API_H

#include "engine.h"

void engine_register_module_init_callback(module_init_callback callback);
void engine_register_frame_callback(frame_callback callback);
void engine_unregister_frame_callback(frame_callback callback);
void engine_main_loop();
void engine_register_module_teardown_callback(module_teardown_callback callback);

#endif