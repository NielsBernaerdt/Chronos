#include "ChronosPCH.h"

#if _DEBUG
#include <vld.h>
#endif

#include "Chronos.h"

int main(int, char*[]) {
	Chronos engine;
	engine.Run();
    return 0;
}