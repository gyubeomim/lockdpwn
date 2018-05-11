#ifndef __SLOT_H__
#define __SLOT_H__

#include "Person.h"

typedef int Key;
typedef Person * Value;

enum SlotStatus {EMPTY, DELETED, INUSE};

typedef struct _slot
{
	Key key;
	Value val;
	enum SlotStatus status;
}Slot;

// Slot과 관련해서는 별도의 함수를 정의하지 않는다.
#endif