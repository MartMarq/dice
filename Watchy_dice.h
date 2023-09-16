#ifndef WATCHY_dice_H
#define WATCHY_dice_H

#ifdef WATCHY_SIM
    #include "..\..\Watchy.h"
#else // WATCHY_SIM
    #include <Watchy.h>
#endif // WATCHY_SIM

#include "icons.h"

class Watchydice : public Watchy{
    using Watchy::Watchy;
    public:
        void drawWatchFace();
        void drawTime();
 };

#endif