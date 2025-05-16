#include "login.h"

#include "ui_style.h"

#include "raygui.h"

#include "database.h"

#include <sqlite3.h>

#define USERNAME_MAX 32
#define MDP_MAX 32
#define NUM_ELEMENTS 6
// @TODO: Unfinished

int verify_user_credentials(const char* username, const char* password, sqlite3* db) {
    const char* query = "SELECT Password FROM Client WHERE Username = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        // LOG_SQLITE3_ERROR(db);
        return 0;  // Erreur de préparation de la requête
    }

    // Lier le nom d'utilisateur à la requête
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        const char* stored_password = (const char*)sqlite3_column_text(stmt, 0);

        // Comparer le mot de passe entré avec celui stocké dans la base de données
        if (strcmp(password, stored_password) == 0) {
            sqlite3_finalize(stmt);
            return 1;  // Connexion réussie
        }
    }

    sqlite3_finalize(stmt);
    return 0;  // Nom d'utilisateur ou mot de passe incorrect
}
void ui_login(GameData* g){
    Vector2 cursor = {.x=g->win.w * 0.5f,.y = g->win.h * 0.5f - (TEXTBOX_HEIGHT +PADDING) * NUM_ELEMENTS};
    static bool is_create_account = false;

    static bool username_edit = false;
    static char username[USERNAME_MAX] = {0};

    static char confirm_mdp[MDP_MAX] = {0};
    static bool confirm_mdp_edit = false;

    Rectangle bounds = {
        .x=cursor.x - g->win.w * 0.25f * 0.5f,
        .y=cursor.y,
        .width=g->win.w * 0.25f,.height=TEXTBOX_HEIGHT
    };
    GuiLabel(bounds,"Nom d'utilisateur");
    bounds.y += TEXTBOX_HEIGHT + PADDING;
    if(GuiTextBox(bounds,username,USERNAME_MAX,username_edit)){
        //Do logic on Enter
        username_edit = !username_edit;
    }
    bounds.y += TEXTBOX_HEIGHT + PADDING;
    GuiLabel(bounds,"Mot de passe");
    bounds.y += TEXTBOX_HEIGHT + PADDING;
    static bool mdp_edit = false;
    static char mdp[MDP_MAX] = {0};
    if(GuiTextBox(bounds,mdp,MDP_MAX,mdp_edit)){
        //Do logic on Enter
        mdp_edit = !mdp_edit;
    }
    bounds.y += TEXTBOX_HEIGHT + PADDING;
    char* butt_label = is_create_account ? "Créer un compte" : "Se connecter";
    if (GuiButton(bounds, butt_label)) {
        // Vérifie si les champs sont vides avant de continuer
        if (strlen(username) == 0 || strlen(mdp) == 0) {
            knob_log(KNOB_ERROR, "Le nom d'utilisateur et le mot de passe ne peuvent pas être vides !\n");
            return;  // Ne pas continuer si les champs sont vides
        }
    }
    if(is_create_account){
        bounds.y += TEXTBOX_HEIGHT + PADDING;
        GuiLabel(bounds,"Valider mot de passe");
        bounds.y += TEXTBOX_HEIGHT + PADDING;



        if(GuiTextBox(bounds, confirm_mdp, MDP_MAX, confirm_mdp_edit)){
            //Do logic on Enter

            confirm_mdp_edit = ! confirm_mdp_edit;
        }
    }
bounds.y += TEXTBOX_HEIGHT + PADDING;
    butt_label =  is_create_account ? "Create account" : "Login";
    if(GuiButton(bounds,butt_label)){
        if (strlen(username) == 0 || strlen(mdp) == 0) {
            knob_log(KNOB_ERROR, "Le nom d'utilisateur et le mot de passe ne peuvent pas être vides !\n");
            return;  // Ne pas continuer si les champs sont vides
        }
        if (is_create_account) {
            if(strcmp(mdp, confirm_mdp)!=0){
                knob_log(KNOB_ERROR, "Les mots de passe ne correspondent pas!\n");
                return;
            }
            create_account(username, mdp, g);
            g->state = MainMenu;  // Après la création du compte, passer à l'écran principal
        } else {
            if (verify_user_credentials(username, mdp, g->db)) {
            g->state = MainMenu;
            } else {
                knob_log(KNOB_ERROR,"Nom d'utilisateur ou mot de passe incorrect!\n");
            }
            // Ici tu peux ajouter la logique de connexion avec la base de données
            // Par exemple : vérifier si les informations sont correctes en comparant avec celles stockées dans la DB.
            g->state = MainMenu;  // Si la connexion est réussie, passer à l'écran principal
        }
        //@TODO: Save to db
    }
    bounds.y += TEXTBOX_HEIGHT + PADDING;
    bounds.width = bounds.height = TEXTBOX_HEIGHT;
    GuiCheckBox(bounds,"New Account",&is_create_account);

}
void create_account(char* username, char* mdp,GameData* g){
    int characterID = 1;
    int walletID = 1;
    int creditcardID = 1;

    Save_Client(g->db, username, mdp, characterID, walletID, creditcardID);
}
