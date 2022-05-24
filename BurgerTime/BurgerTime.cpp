#include "ChronosPCH.h"
#if _DEBUG
	#if __has_include(<vld.h>)
	#include <vld.h>
	#endif
#endif

#include "Chronos.h"

int main(int, char* []) {
	Chronos engine;
	engine.Run();
	return 0;
}