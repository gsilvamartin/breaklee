#include "ClientProtocol.h"
#include "ClientProcedures.h"
#include "ClientSocket.h"
#include "IPCProcs.h"
#include "Notification.h"
#include "Server.h"

CLIENT_PROCEDURE_BINDING(ATTACK_TO_MOB) {
	if (!Character) goto error;
	if (!RTCharacterIsAlive(Runtime, Character)) goto error;
	if (Packet->EntityIDType != RUNTIME_ENTITY_TYPE_MOB) goto error;

	// TODO: Check if mob is in attack range (auto miss target)
	// TODO: Check if attack cooldown is ok (auto miss target)

    RTWorldContextRef World = RTRuntimeGetWorldByCharacter(Runtime, Character);
	RTMobRef Mob = RTWorldContextGetMob(World, Packet->Entity);
	if (!Mob) goto error;
	if (Mob->IsDead) goto error; // TODO: (auto miss target)

	struct _RTBattleResult Result = { 0 };
	RTCalculateNormalAttackResult(
		Runtime,
		RUNTIME_BATTLE_SKILL_TYPE_SWORD,
		Character->Info.Basic.Level,
		&Character->Attributes,
		Mob->SpeciesData->Level,
		&Mob->Attributes,
		&Result
	);

	RTMobApplyDamage(Runtime, World, Mob, Character->ID, Result.AppliedDamage);

	RTCharacterAddExp(Runtime, Character, Result.Exp);

	S2C_DATA_ATTACK_TO_MOB* Response = PacketInit(S2C_DATA_ATTACK_TO_MOB);
	Response->Command = S2C_ATTACK_TO_MOB;
	Response->Entity = Packet->Entity;
	Response->EntityIDType = Packet->EntityIDType;
	Response->AttackType = Result.AttackType;
	Response->MobAppliedDamage = Result.AppliedDamage;
	Response->MobTotalDamage = Result.TotalDamage;
	Response->MobAdditionalDamage = Result.AdditionalDamage;
	Response->AccumulatedExp = Character->Info.Basic.Exp;
	Response->AccumulatedOxp = Character->Info.Overlord.Exp;
	Response->CharacterHP = Character->Attributes.Values[RUNTIME_ATTRIBUTE_HP_CURRENT];
	Response->CharacterMP = Character->Attributes.Values[RUNTIME_ATTRIBUTE_MP_CURRENT];
	Response->CharacterSP = Character->Attributes.Values[RUNTIME_ATTRIBUTE_SP_CURRENT];
	Response->MobHP = Mob->Attributes.Values[RUNTIME_ATTRIBUTE_HP_CURRENT];
	SocketSend(Socket, Connection, Response);

	// TODO: This should be calculated globally inside the mob logic when it dies by a bfx effect and no active attack!
	if (Result.IsDead) {
		if (RTCharacterIncrementQuestMobCounter(Runtime, Character, Mob->Spawn.MobSpeciesIndex)) {
			S2C_DATA_NFY_QUEST_MOB_KILL* Notification = PacketInit(S2C_DATA_NFY_QUEST_MOB_KILL);
			Notification->Command = S2C_NFY_QUEST_MOB_KILL;
			Notification->MobSpeciesIndex = Mob->Spawn.MobSpeciesIndex;
			Notification->SkillIndex = 0;
			Notification->Unknown1 = 0;
			SocketSend(Socket, Connection, Notification);
		}

		Mob->DropOwner = Character->ID;
	}

	S2C_DATA_NFY_ATTACK_TO_MOB* Notification = PacketInit(S2C_DATA_NFY_ATTACK_TO_MOB);
	Notification->Command = S2C_NFY_ATTACK_TO_MOB;
	Notification->CharacterIndex = Client->CharacterIndex,
	Notification->Mob = Response->Entity;
	Notification->MobIDType = Response->EntityIDType;
	Notification->AttackType = Response->AttackType;
	Notification->MobHP = Response->MobHP;
	Notification->CharacterHP = Response->CharacterHP;

	return BroadcastToWorld(
		Context,
		World,
		kEntityIDNull,
		Character->Movement.PositionCurrent.X,
		Character->Movement.PositionCurrent.Y,
		Notification
	);
	
error:
	return SocketDisconnect(Socket, Connection);
}
