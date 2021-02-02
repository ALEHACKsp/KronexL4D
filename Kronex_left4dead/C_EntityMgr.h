#pragma once

class C_EntityMgr
{
public:
	C_EntityMgr();
	~C_EntityMgr();

	vector<C_Player*> EntityList;
  C_Player* m_pMyPlayer;

protected:
	HANDLE m_hThreadHandle;
};

