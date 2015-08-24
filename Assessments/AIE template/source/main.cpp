#include "AIE.h"
#include <string>
#include <cmath>
#include <time.h>
#include <assert.h>
#include <crtdbg.h>
#include <iostream>
#include <sstream>
#include "Level1.h"

int main( int argc, char* argv[] )
{	

	Level1 level1;

	do
	{
		level1.Update();
		level1.Draw();
	}
	while(FrameworkUpdate() == false);


	return 0;
	Shutdown();
}

