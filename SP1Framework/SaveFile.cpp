#include "SaveFile.h"
#include "map.h"

extern char mapCurrent[25][80];

void Inventorystrap()
{
	std::fstream InventoryRam;
	
	InventoryRam.open("InventoryRam.txt", std::ios_base::app);
	InventoryRam << mapCurrent[25][80];
}
void Vault_Connectstrap()
{
	std::fstream Vault_ConnectRam;

	Vault_ConnectRam.open("InventoryRam.txt", std::ios_base::app);
	InventoryRam << mapCurrent[25][80];
}
void filestrap()
{
	std::fstream Vault_Key1Ram;

	Vault_Key1Ram.open("InventoryRam.txt", std::ios_base::app);
	InventoryRam << mapCurrent[25][80];
}
void filestrap()
{
	std::fstream Vault_Key2Ram;

	Vault_Key2Ram.open("InventoryRam.txt", std::ios_base::app);
	InventoryRam << mapCurrent[25][80];
}
void filestrap()
{
	std::fstream Vault_Key3Ram;

	Vault_Key3Ram.open("InventoryRam.txt", std::ios_base::app);
	InventoryRam << mapCurrent[25][80];
}
void filestrap()
{
	std::fstream Vault_RoomRam;

	Vault_RoomRam.open("InventoryRam.txt", std::ios_base::app);
	InventoryRam << mapCurrent[25][80];
}