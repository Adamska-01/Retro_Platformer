#include "CustomEvents/GameEndedEvent.h"


GameEndedEvent::GameEndedEvent(bool isGameLost)
	: isGameLost(isGameLost)
{
}