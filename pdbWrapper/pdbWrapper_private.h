#pragma once

class PdbHandles
{
public:
	PdbHandles(HANDLE rawInWr, HANDLE rawOutRd, HANDLE wrapEcho)
	{
		hdlRawInWr = rawInWr;
		hdlRawOutRd = rawOutRd;
		hdlWrappedEcho = wrapEcho;
	}

	~PdbHandles()
	{
		if (hdlRawInWr != nullptr)
			CloseHandle(hdlRawInWr);
		if (hdlRawOutRd != nullptr)
			CloseHandle(hdlRawOutRd);
		if (hdlWrappedEcho != nullptr)
			CloseHandle(hdlWrappedEcho);
	}

	HANDLE hdlRawInWr;
	HANDLE hdlRawOutRd;
	HANDLE hdlWrappedEcho;
};

bool PdbWriteCmd(HANDLE pdb, const char *cmd);
