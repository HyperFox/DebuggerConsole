#pragma once

#ifdef PDBWRAPPER_EXPORTS
#	define DLLEXPORT __declspec(dllexport)
#else
#	define DLLEXPORT __declspec(dllimport)
#endif // PDBWRAPPER_EXPORTS

DLLEXPORT int add(int a, int b);
