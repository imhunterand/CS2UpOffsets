#include "Cheats.h"
#include "Render.hpp"

void Cheats::Run()
{
	// ���¾�������
	if(!ProcessMgr.ReadMemory(gGame.GetMatrixAddress(), gGame.View.Matrix,64))
		return;

	// ����ʵ�������ַ
	gGame.UpdateEntityListEntry();

	DWORD64 LocalControllerAddress = 0;
	if (!ProcessMgr.ReadMemory(gGame.GetLocalControllerAddress(), LocalControllerAddress))
		return;

	// ����ʵ��
	CEntity LocalEntity;
	if (!LocalEntity.Update(LocalControllerAddress))
		return;

	// Ѫ��Map
	static std::map<DWORD64, Render::HealthBar> HealthBarMap;

	// ��������
	float DistanceToSight = 0;
	float MaxAimDistance = 100000;
	Vec3  AimPos{ 0,0,0 };

	for (int i = 0; i < 16; i++)
	{
		CEntity Entity;
		DWORD64 EntityAddress = 0;
		if (!ProcessMgr.ReadMemory<DWORD64>(gGame.GetEntityListEntry() + (i + 1) * 0x78, EntityAddress))
			continue;
		if (EntityAddress == LocalEntity.EntityAddress)
			continue;
		if (!Entity.Update(EntityAddress))
			continue;

		//if (Entity.TeamID == LocalEntity.TeamID)
			//continue;
		if (!Entity.IsAlive())
			continue;
		if (!Entity.IsInScreen())
			continue;

		// �������Ի���
	/*	for (int BoneIndex = 0; BoneIndex < Entity.BoneData.BonePosList.size(); BoneIndex++)
		{
			Vec2 ScreenPos{};
			if (gGame.View.WorldToScreen(Entity.BoneData.BonePosList[BoneIndex].Pos, ScreenPos))
			{
				Gui.Text(std::to_string(BoneIndex), ScreenPos, ImColor(255, 255, 255, 255));
			}
		}*/

		DistanceToSight = Entity.BoneData.BonePosList[BONEINDEX::head].ScreenPos.DistanceTo({ Gui.Window.Size.x / 2,Gui.Window.Size.y / 2 });

		if (DistanceToSight < AimControl::AimRange)
		{
			if (DistanceToSight < MaxAimDistance)
			{
				MaxAimDistance = DistanceToSight;
				AimPos = Entity.BoneData.BonePosList[BONEINDEX::head].Pos;
			}
		}

		// ���ƹ���
		Render::DrawBone(Entity, ImColor(255, 255, 255, 255), 1.3);

		// ���Ƴ���
		Render::ShowLosLine(Entity, 50, ImColor(255, 0, 0, 255), 1.3);

		// ����2D��
		auto Rect = Render::Draw2DBoneRect(Entity, ImColor(255, 255, 255, 255), 1.3);

		// ����Ѫ��
		if (!HealthBarMap.count(EntityAddress))
			HealthBarMap.insert({ EntityAddress,Render::HealthBar(100) });

		HealthBarMap[EntityAddress].DrawHealthBar(Entity.Health,
			{ Rect.x + Rect.z / 2 - 70 / 2,Rect.y - 20 }, { 70,8 });
	}

	if (GetAsyncKeyState(AimControl::HotKey))
	{
		if (AimPos != Vec3(0,0,0))
		{
			AimControl::AimBot(LocalEntity, LocalEntity.CameraPos, AimPos);
		}
	}
}