###  Basic database project

Pour cloner le project:
`git clone --recursive https://github.com/chemin.vers.repos.git`

Si jamais vous ne voyez pas zig.exe dans Tools, FoundryTools_windowsx64, faite:
`.\setup.bat`

Pour compiler le project:
`ctrl+shift+b`

Pour debugger le project:
`F5`

```mermaid
erDiagram

 Inventory ||--o{ Items :Has
 Inventory ||--o{ Character :Has
 Character ||--o{  Client :Has
 Client ||--o{ Wallet :Has
 Client ||--o{ Credit_Card :Has
 Character ||--o{ Classe :Has
 Classe ||--o{ SocialStatus : Has

SocialStatus{
int SocialStatusID PK
String SocialStatus
}
Classe{
int ClassID PK
int Race
int Faction
int SocialStatus FK
}
Character{
int CharacterId PK
string Name
int Level
int Strength
int Stamina
int Stealth
int Charisma
int ClasseID FK
int InventoryID FK
}
Inventory{
int InventoryID PK
int ItemsID FK
int Count
int Capacity
}
Items{
int ItemID PK
int Value
int Is_Weapon
int Is_Armor
int Is_Equipped 
}
Client{
int ClientID PK
Text Username
string Password
int CharacterID FK
int WalletID FK
int CreditCardID FK
}
Credit_Card{
int CreditCardID PK
int CreditCardNB
int Cvc_Digit
int CreditCardNum
date ExpiringDate
}
Wallet{
int WalletID PK
int Count
int Capacity
int ggbucks
}
```