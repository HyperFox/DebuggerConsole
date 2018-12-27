// DebuggerConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <Windows.h>
#include "../pdbWrapper/pdbWrapper.h"

int main()
{
    std::cout << "Hello World!\n";
	HANDLE hdlOutput = nullptr;
	HANDLE pdb = PdbInit("D:\\Documents\\Visual Studio 2017\\Projects\\DebuggerConsole\\pdbWrapper\\test.py", hdlOutput);
	PdbStepOver(pdb);
}
