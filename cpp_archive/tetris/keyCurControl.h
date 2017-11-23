

#ifndef __KEYCURCONTROL_H__
#define __KEYCURCONTROL_H__

#include "point.h"

void removeCursor();
POINT_EDWARD getCurrentCursorPos();
void setCurrentCursorPos(int x, int y);

int insertUserKeyInput();
void keyDelaySpeedCtl(int addSpeed);
void initKeyDelayRate(int rate);

#endif 