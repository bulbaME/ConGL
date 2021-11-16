#include "../congl.h"

// namespace ConGL {
//     WinInput::WinInput(HANDLE _h) {
//         h = _h;

//         std::thread th(_thread, this);
//         th.detach();
//     }

//     WinInput::~WinInput() {
//         loopTh = false;
//         binds.clear();
//     }

//     void WinInput::_thread(WinInput* t) {
//         INPUT_RECORD in[1];
//         DWORD read;

//         while (t->loopTh) {
//             ReadConsoleInput(t->h, in, 1, &read);
//             if (!read) continue;
//             INPUT_RECORD event = in[0];

//             if (event.EventType == KEY_EVENT) {
//                 KEY_EVENT_RECORD kEvent = event.Event.KeyEvent;
//                 KEY_STATE key = {kEvent.uChar.UnicodeChar, kEvent.bKeyDown, kEvent.dwControlKeyState};

//                 auto bindIt = t->binds.find(key);
//                 if (bindIt != t->binds.end())
//                     bindIt->second(key);
//             }
//         }
//     }
// }