#include "KronexMain.h"

C_EntityMgr::C_EntityMgr()
{
  m_pMyPlayer = new C_Player(this, 0, 0x53F750, 0x10);
  
	for (int i = 0; i < g_pEngineClient->GetMaxClients(); i++) // 18
	{
    C_Player* tempPlayer = new C_Player(this, i, 0x54E4BC, 0x10);
    //if (!tempPlayer->Equals(m_pMyPlayer))
    if (i + 1 != g_pEngineClient->GetLocalPlayer())
    {
      EntityList.push_back(tempPlayer);
    }
	}
}

C_EntityMgr::~C_EntityMgr()
{
  delete m_pMyPlayer;

  for each (C_Player* player in EntityList)
  {
    delete player;
  }

  EntityList.clear();
}