// pdbWrapper.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "pdbWrapper.h"
#include "pdbWrapper_private.h"
#include <windows.h>
#include <iostream>
#include <atlconv.h>


bool PdbWriteCmd(HANDLE pdb, const char *cmd)
{
	DWORD cmdSize = strlen(cmd);
	DWORD cmdWritten;
	HANDLE hdlRawInWr = static_cast<PdbHandles *>(pdb)->hdlRawInWr;
	return WriteFile(hdlRawInWr, cmd, cmdSize, &cmdWritten, NULL);
}

HANDLE PdbInit(const char *scriptPath, HANDLE hdlOutput)
{
	HANDLE g_hChildStd_IN_Rd = nullptr;
	HANDLE g_hChildStd_IN_Wr = nullptr;
	HANDLE g_hChildStd_OUT_Rd = nullptr;
	HANDLE g_hChildStd_OUT_Wr = nullptr;

	SECURITY_ATTRIBUTES saAttr;
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	saAttr.bInheritHandle = TRUE;
	saAttr.lpSecurityDescriptor = NULL;
	if (!CreatePipe(&g_hChildStd_OUT_Rd, &g_hChildStd_OUT_Wr, &saAttr, 0))
	{
		std::cout << "StdoutRd CreatePipe error" << std::endl;
		return nullptr;
	}
	SetHandleInformation(g_hChildStd_OUT_Rd, HANDLE_FLAG_INHERIT, 0);

	if (!CreatePipe(&g_hChildStd_IN_Rd, &g_hChildStd_IN_Wr, &saAttr, 0))
	{
		std::cout << "Stdin CreatePipe error" << std::endl;
		return nullptr;
	}
	SetHandleInformation(g_hChildStd_IN_Wr, HANDLE_FLAG_INHERIT, 0);

	PdbHandles *hdlPdb = new PdbHandles(g_hChildStd_IN_Wr, g_hChildStd_OUT_Rd, hdlOutput);
 
	PROCESS_INFORMATION piProcInfo;
	STARTUPINFOA siStartInfo;
	ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));
	ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
	siStartInfo.cb = sizeof(STARTUPINFO);
	siStartInfo.hStdError = g_hChildStd_OUT_Wr;
	siStartInfo.hStdOutput = g_hChildStd_OUT_Wr;
	siStartInfo.hStdInput = g_hChildStd_IN_Rd;
	siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

	char cmdline[MAX_PATH] = "python -u -m pdb \"";
	strcat_s(cmdline, MAX_PATH, scriptPath);
	strcat_s(cmdline, MAX_PATH, "\"");
	if (CreateProcessA(NULL,
		cmdline,     // command line 
		NULL,          // process security attributes 
		NULL,          // primary thread security attributes 
		TRUE,          // handles are inherited 
		0,             // creation flags 
		NULL,          // use parent's environment 
		NULL,          // use parent's current directory 
		&siStartInfo,  // STARTUPINFO pointer 
		&piProcInfo)  // receives PROCESS_INFORMATION
		)
	{
		CloseHandle(piProcInfo.hProcess);
		CloseHandle(piProcInfo.hThread);
	}
	return hdlPdb;
}

/*PdbPosInfo PdbStepInto(HANDLE pdb)
{
	;
}*/

PdbPosInfo PdbStepOver(HANDLE pdb)
{
	PdbWriteCmd(pdb, "next");
	return PdbPosInfo();
}

/*PdbPosInfo PdbUntil(HANDLE pdb)
{
	;
}

PdbPosInfo PdbReturn(HANDLE pdb)
{
	;
}

PdbPosInfo PdbContinue(HANDLE pdb)
{
	;
}

PdbPosInfo PdbJump(HANDLE pdb, int lineno)
{
	;
}

void PdbPrint(HANDLE pdb, char *args)
{
	;
}

void PdbEval(HANDLE pdb)
{
	;
}

void PdbRestart(HANDLE pdb, char *args)
{
	;
}*/

void PdbQuit(HANDLE pdb)
{
	PdbWriteCmd(pdb, "quit\n");
	delete pdb;
}
