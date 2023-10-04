#pragma once
#include <optional>
#include "Utils/ProcessManager.hpp"
#include "Offsets.h"
#include "View.hpp"

class CGame
{
private:
	struct
	{
		DWORD64 ClientDLL;
		DWORD64 EntityList;
		DWORD64 Matrix;
		DWORD64 ViewAngle;
		DWORD64 EntityListEntry;
		DWORD64 LocalController;
	}Address;

public:
	CView View;

public:	

	bool InitAddress();

	DWORD64 GetClientDLLAddress();

	DWORD64 GetEntityListAddress();

	DWORD64 GetMatrixAddress();

	DWORD64 GetViewAngleAddress();

	DWORD64 GetEntityListEntry();

	DWORD64 GetLocalControllerAddress();

	bool UpdateEntityListEntry();

	bool SetViewAngle(float Yaw, float Pitch);
};

inline CGame gGame;