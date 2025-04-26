#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#define ARX_EXP extern "C"
//__declspec(dllexport)
#include <rxobject.h>
#include <rxregsvc.h>
#include <aced.h>

void helloCommand();

void helloCommand() {
	acutPrintf(L"\nHello from AutoCAD ObjectARX!ss");
}
/////////////////
// entry point //
/////////////////
ARX_EXP AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt) {
	switch (msg) 
	{
	case AcRx::kInitAppMsg:
		// Unload the application when AutoCAD unloads it
		acrxDynamicLinker->unlockApplication(pkt);
		acrxDynamicLinker->registerAppMDIAware(pkt);
		
		// Register our command
		acedRegCmds->addCommand(
			L"HELLOARX_COMMANDS",    // Command group name
			L"HELLO",                // Global command name
			L"HELLO",                // Localized command name
			ACRX_CMD_MODAL,          // Command flags
			&helloCommand           // Function pointer
		);
		break;
		
	case AcRx::kUnloadAppMsg:
		// Remove our command when unloaded
		acedRegCmds->removeGroup(L"HELLOARX_COMMANDS");
		break;
	}
	return AcRx::kRetOK;
}