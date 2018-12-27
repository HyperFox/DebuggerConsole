#pragma once

#ifdef PDBWRAPPER_EXPORTS
#	define DLLEXPORT __declspec(dllexport)
#else
#	define DLLEXPORT __declspec(dllimport)
#endif // PDBWRAPPER_EXPORTS

#ifdef __cplusplus
extern "C" {
#endif

	typedef struct PdbPosInfo
	{
		char *scriptPath;
		int lineno;
	} PdbPosInfo;

	DLLEXPORT HANDLE     PdbInit(const char *scriptPath, HANDLE hdlOutput);
	/*DLLEXPORT PdbPosInfo PdbWhere();
	DLLEXPORT PdbPosInfo PdbDownFrame();
	DLLEXPORT PdbPosInfo PdbUpFrame();
	DLLEXPORT void       PdbBreakOnLineno(HANDLE pdb, char *fileName, int lineno, char *condition);
	DLLEXPORT void       PdbBreakOnFunction(HANDLE pdb, char *functionName, char *condition);
	DLLEXPORT void       PdbTBreakOnLineno(HANDLE pdb, char *fileName, int lineno, char *condition);
	DLLEXPORT void       PdbTBreakOnFunction(HANDLE pdb, char *functionName, char *condition);
	DLLEXPORT void       PdbClearBpOnLineno(HANDLE pdb, char *fileName, int lineno);
	DLLEXPORT void       PdbClearBpByIndex(HANDLE pdb, int bpIndex);
	DLLEXPORT void       PdbDisableBp(HANDLE pdb, int bpIndex);
	DLLEXPORT void       PdbEnableBp(HANDLE pdb, int bpIndex);
	DLLEXPORT void       PdbIgnoreBp(HANDLE pdb, int bpIndex, int count);
	DLLEXPORT void       PdbSetBpCondition(HANDLE pdb, int bpIndex, char *condition);
	DLLEXPORT PdbPosInfo PdbStepInto(HANDLE pdb);*/
	DLLEXPORT PdbPosInfo PdbStepOver(HANDLE pdb);
	/*DLLEXPORT PdbPosInfo PdbUntil(HANDLE pdb);
	DLLEXPORT PdbPosInfo PdbReturn(HANDLE pdb);
	DLLEXPORT PdbPosInfo PdbContinue(HANDLE pdb);
	DLLEXPORT PdbPosInfo PdbJump(HANDLE pdb, int lineno);
	DLLEXPORT void       PdbPrint(HANDLE pdb, char *args);
	DLLEXPORT void       PdbEval(HANDLE pdb);
	DLLEXPORT void       PdbRestart(HANDLE pdb, char *args);*/
	DLLEXPORT void       PdbQuit(HANDLE pdb);


#ifdef __cplusplus
}
#endif
