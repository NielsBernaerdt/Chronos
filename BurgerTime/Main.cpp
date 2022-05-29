#if _DEBUG
	#if __has_include(<vld.h>)
	#include <vld.h>
	#endif
#endif

#include "BurgerTime.h"
#include "Chronos.h"

int main(int, char* []) {
	BurgerTime* pGame = new BurgerTime{};
	Chronos engine{ pGame };
	engine.Run();
	return 0;
}