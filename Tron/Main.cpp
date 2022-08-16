#if _DEBUG
	#if __has_include(<vld.h>)
		#include <vld.h>
	#endif
#endif

#include <iostream>
#include "Tron.h"
#include "Chronos.h"

int main(int, char* []) {
	Tron* pGame = new Tron{};
	Chronos engine{ pGame };
	engine.Run();
	return 0;
}