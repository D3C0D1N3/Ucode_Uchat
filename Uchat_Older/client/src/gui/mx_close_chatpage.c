#include "client.h"

void mx_close_chatpage(cJSON *j_responce, t_chat *chat) {
    cJSON *j_valid = cJSON_GetObjectItemCaseSensitive(j_responce, "valid");
    char *valid = strdup(j_valid->valuestring);
    mx_clear_chat(chat);
    if (!strcmp(valid, "true")) {
        GtkStack *stk = GTK_STACK(gtk_builder_get_object(chat->builder,
                                                     "main_stack"));
        gtk_stack_set_visible_child_name(stk, "login_page0");
    }
    free(valid);
}