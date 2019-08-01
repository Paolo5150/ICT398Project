#include "pch.h"
#include "Core/Core.h"

void main()
{

	//FreeConsole();
	Core::Instance().Initialize();
	Core::Instance().Run();
	Core::Instance().Shutdown();
	
	system("pause");
}
