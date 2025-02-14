#include "ClientProtocol.h"
#include "ClientProcedures.h"
#include "ClientSocket.h"
#include "IPCProcs.h"
#include "Notification.h"
#include "Server.h"

CLIENT_PROCEDURE_BINDING(ADD_PASSIVE_ABILITY) {
	if (!Character) goto error;

	S2C_DATA_ADD_PASSIVE_ABILITY* Response = PacketInit(S2C_DATA_ADD_PASSIVE_ABILITY);
	Response->Command = S2C_ADD_PASSIVE_ABILITY;
	Response->Result = RTCharacterAddEssenceAbility(
		Runtime,
		Character,
		Packet->InventorySlotIndex
	);

	return SocketSend(Socket, Connection, Response);

error:
	return SocketDisconnect(Socket, Connection);
}

CLIENT_PROCEDURE_BINDING(UPGRADE_PASSIVE_ABILITY) {
	if (!Character) goto error;

	Int32 InventorySlotCount = (Packet->Signature.Length - sizeof(C2S_DATA_UPGRADE_PASSIVE_ABILITY)) / sizeof(UInt16);

	S2C_DATA_UPGRADE_PASSIVE_ABILITY* Response = PacketInit(S2C_DATA_UPGRADE_PASSIVE_ABILITY);
	Response->Command = S2C_UPGRADE_PASSIVE_ABILITY;
	Response->Result = RTCharacterUpgradeEssenceAbility(
		Runtime,
		Character,
		Packet->AbilityID,
		InventorySlotCount,
		Packet->InventorySlotIndex
	);

	PacketLogBytes(Packet);
	return SocketSend(Socket, Connection, Response);

error:
	return SocketDisconnect(Socket, Connection);
}

CLIENT_PROCEDURE_BINDING(REMOVE_PASSIVE_ABILITY) {
	if (!Character) goto error;

	S2C_DATA_REMOVE_PASSIVE_ABILITY* Response = PacketInit(S2C_DATA_REMOVE_PASSIVE_ABILITY);
	Response->Command = S2C_REMOVE_PASSIVE_ABILITY;
	Response->Result = RTCharacterRemoveEssenceAbility(
		Runtime,
		Character,
		Packet->AbilityID
	);

	return SocketSend(Socket, Connection, Response);

error:
	return SocketDisconnect(Socket, Connection);
}
