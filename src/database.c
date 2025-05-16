#include "database.h"
#include "sqlite3.h"
#define LOG_SQLITE3_ERROR(db) knob_log(KNOB_ERROR, "%s:%d: SQLITE3 ERROR: %s\n", __FILE__, __LINE__, sqlite3_errmsg(db))




void db_start(GameData* g){
    sqlite3_open("game.db",&g->db);
}


const char* create_Wallet_table = 
"CREATE TABLE IF NOT EXISTS Wallet ("
"   WalletID INTEGER PRIMARY KEY,"
"   Count INTEGER,"
"   Capacity INTEGER,"
"   ggbucks INTEGER"
");";

const char* create_CreditCard_table = 
"CREATE TABLE IF NOT EXISTS CreditCard ("
"   CreditCardID INTEGER PRIMARY KEY,"
"   CreditCardNB INTEGER,"
"   Cvc_Digit INTEGER,"
"   CreditCardName TEXT,"
"   ExpiringDate DATE"
");";

const char* create_Items_table = 
"CREATE TABLE IF NOT EXISTS Items ("
"   ItemID INTEGER PRIMARY KEY,"
"   Value INTEGER,"
"   is_Weapon INTEGER,"
"   is_armor INTEGER,"
"   is_equipped INTEGER" 
");";


const char* create_SocialStatus_table = 
"CREATE TABLE IF NOT EXISTS SocialStatus ("
"   SocialStatusID INTEGER PRIMARY KEY,"
"   SocialStatus TEXT"
");";

const char* create_Classe_table = 
"CREATE TABLE IF NOT EXISTS Classe ("
"   ClassID INTEGER PRIMARY KEY,"
"   Race INTEGER,"
"   Faction INTEGER,"
"   ss INTEGER,"
"   FOREIGN KEY (ss) REFERENCES SocialStatus(SocialStatusID)" 
");";

const char* create_Inventory_table = 
"CREATE TABLE IF NOT EXISTS Inventory ("
"   InventoryID INTEGER PRIMARY KEY,"
"   Count INTEGER,"
"   Capacity INTEGER,"
"   ItemsID INTEGER,"
"   FOREIGN KEY (ItemsID) REFERENCES Items(ItemID)"  
");";

const char* create_Character_table = 
"CREATE TABLE IF NOT EXISTS Character ("
"   CharacterID INTEGER PRIMARY KEY,"
"   Name TEXT,"
"   Level INTEGER,"
"   Strenght INTEGER,"
"   Stamina INTEGER,"
"   Stealth INTEGER,"
"   Charisma INTEGER,"
"   ClasseID INTEGER,"
"   InventoryID INTEGER,"
"   FOREIGN KEY (ClasseID) REFERENCES Classe(ClasseID),"
"   FOREIGN KEY (InventoryID) REFERENCES Inventory(InventoryID)"
");";

const char* create_Client_table = 
"CREATE TABLE IF NOT EXISTS Client ("
"   ClientId INTEGER PRIMARY KEY,"
"   Email TEXT,"
"   UserName TEXT,"
"   Password TEXT,"
"   InventoryID INTEGER,"
"   CharacterID INTEGER,"
"   WalletID INTEGER,"
"   FOREIGN KEY (CharacterID) REFERENCES Character(CharacterID),"
"   FOREIGN KEY (WalletID) REFERENCES Wallet(WalletID),"
"   FOREIGN KEY (InventoryID) REFERENCES Inventory(InventoryID)"
");";








void db_initialise(GameData* g){

if (sqlite3_exec(g->db, create_Wallet_table, NULL, NULL, NULL) != SQLITE_OK){
    LOG_SQLITE3_ERROR(g->db);
    return;
}

if (sqlite3_exec(g->db, create_CreditCard_table, NULL, NULL, NULL) != SQLITE_OK){
    LOG_SQLITE3_ERROR(g->db);
    return;
}

if (sqlite3_exec(g->db, create_SocialStatus_table, NULL, NULL, NULL) != SQLITE_OK){
    LOG_SQLITE3_ERROR(g->db);
    return;
}

if (sqlite3_exec(g->db, create_Classe_table, NULL, NULL, NULL) != SQLITE_OK){
    LOG_SQLITE3_ERROR(g->db);
    return;
}

if (sqlite3_exec(g->db, create_Items_table, NULL, NULL, NULL) != SQLITE_OK){
    LOG_SQLITE3_ERROR(g->db);
    return;
}

if (sqlite3_exec(g->db, create_Inventory_table, NULL, NULL, NULL) != SQLITE_OK){
    LOG_SQLITE3_ERROR(g->db);
    return;
}

if (sqlite3_exec(g->db, create_Client_table, NULL, NULL, NULL) != SQLITE_OK){
    LOG_SQLITE3_ERROR(g->db);
    return;
}
    
}
void db_end(GameData* g){
    sqlite3_close(g->db);
}
