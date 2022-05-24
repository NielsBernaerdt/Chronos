#if _DEBUG
	#if __has_include(<vld.h>)
	#include <vld.h>
	#endif
#endif

#include "BurgerTime.h"

int main(int, char* []) {
	BurgerTime engine;
	engine.Run();
	return 0;
}