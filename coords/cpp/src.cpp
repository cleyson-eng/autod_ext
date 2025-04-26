#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <fstream>


#include <adscodes.h>
#include <rxobject.h>
#include <rxregsvc.h>
#include <aced.h>
#include <dbents.h>
#include <dbsymtb.h>
#include <dbgroup.h>
#include <acedads.h>
#include <geassign.h>

void excoords() {
	ads_name ss;
	int err = acedSSGet(nullptr, nullptr, nullptr, nullptr, ss);
	int length = 0;
	if (err == RTNORM)
		acedSSLength(ss, &length);
	if (err != RTNORM || length == 0) {
		acutPrintf(L"\nNo selection");
		if (err == RTNORM)
			acedSSFree(ss);
		return;
	}
	
	std::ofstream outfile;
	outfile.open(std::string(getenv("UserProfile"))+"\\Desktop\\coords.txt");

	acutPrintf(L"\nSearching points and writing to the file coords.txt at desktop");
	int excount = 0;
	for (int i = 0; i < length; i++) {
		ads_name ent;
		acedSSName(ss, i, ent);

		AcDbObjectId objId;
		acdbGetObjectId(objId, ent);

		AcDbEntity* pEnt;
		if (acdbOpenObject(pEnt, objId, AcDb::kForRead) != Acad::eOk)
			continue;

		if (pEnt->isKindOf(AcDbPoint::desc())) {
			excount++;
			AcDbPoint* pPoint = AcDbPoint::cast(pEnt);
			auto coord = pPoint->position();
			outfile << coord.x << " ; " << coord.y << " ; " << coord.z << std::endl;
		}
		if (i % 100000 == 0) {
			acutPrintf(L"\n%d/%d objects verified.",i,length);
		}
		pEnt->close();
	}
	acutPrintf(L"\n%d points exported.",excount);

	outfile.close();
	acedSSFree(ss);
}

/////////////////
// entry point //
/////////////////
extern "C" AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt) {
	switch (msg) 
	{
	case AcRx::kInitAppMsg:
		acrxDynamicLinker->unlockApplication(pkt);
		acrxDynamicLinker->registerAppMDIAware(pkt);
		acedRegCmds->addCommand(
			L"COORDSARX_COMMANDS",
			L"EXCOORDS", L"EXCOORDS",
			ACRX_CMD_MODAL,
			&excoords
		);
		break;
		
	case AcRx::kUnloadAppMsg:
		acedRegCmds->removeGroup(L"COORDSARX_COMMANDS");
		break;
	}
	return AcRx::kRetOK;
}