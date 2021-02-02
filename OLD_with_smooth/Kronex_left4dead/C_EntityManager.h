#pragma once

using namespace std;

class C_Player;

#include <Windows.h>
#include <vector>

#include "CONFIG.h"
#include "C_Player.h"

class C_EntityManager
{
public:
	C_EntityManager(VOID);
	~C_EntityManager(VOID);

	static DWORD startNewThread(C_EntityManager* pEManager);

	vector<C_Player*> EntityList;
  C_Player* m_pMyPlayer;

protected:
	HANDLE m_hThreadHandle;
};

