#pragma once

#include "game.h"



void db_end(GameData* g);
void db_initialise(GameData* g);
void db_start(GameData* g);
// void db_create_user(GameData* g);
// void db_save_character(GameData* g);
void Save_Client(sqlite3* db, const char* username, const char* mdp, int characterID, int walletID, int creditcardID);
void is_create_account(char* username, char* mdp,GameData* g);