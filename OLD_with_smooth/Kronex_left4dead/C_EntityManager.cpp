#include "C_EntityManager.h"

C_EntityManager::C_EntityManager(VOID)
{
  m_pMyPlayer = new C_Player(this, 0, 0x53F750, 0x10);

	for (int i = 0; i < 16; i++)
	{
    C_Player* tempPlayer = new C_Player(this, i, 0x54E4BC, 0x10);
    if (!tempPlayer->Equals(m_pMyPlayer))
    {
      EntityList.push_back(tempPlayer);
    }
	}

	//m_hThreadHandle = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)startNewThread, this, NULL, NULL);
}

C_EntityManager::~C_EntityManager(VOID)
{
  delete m_pMyPlayer;
  //int entitiesCount = EntityList.size();
  //for (int i = 0; i < entitiesCount; i++)
  //{
  //  delete EntityList[i];
  //}
  //for (vector<C_Player*>::iterator iter = EntityList.begin(); iter != EntityList.end(); ++iter)
  //{
  //  EntityList.erase(iter);
  //}
}

DWORD C_EntityManager::startNewThread(C_EntityManager* pEManager)
{
  //while (true)
  //{
  //	//if (GetAsyncKeyState(KEY_DESTROY_ALL_CHEATS)) break;
  //   
  //	Sleep(1000);
  //}

	return 0;
}