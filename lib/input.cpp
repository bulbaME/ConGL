#include "../congl.h"

#ifdef _WIN32

// namespace ConGL {
//     Input::Input(Screen* screen) {
//         hi = new WinInput(screen->_getHScreen()->getHandler());
//     }

//     void Input::bind(KEY_STATE key, InputCallback f) {
//         hi->binds.insert_or_assign(key, f);
//     }

//     void Input::unbind(KEY_STATE key) {
//         hi->binds.erase(key);
//     }

//     HInput* Input::_getHInput() {
//         return hi;
//     }
// }

#else 

// TODO: UNIX IMPLEMENTATION 

#endif