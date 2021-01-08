#include "client.h"

void mx_cjson_parser(char recvBuff[1024], t_chat *chat) {
    cJSON *j_responce = cJSON_CreateObject();
    j_responce = cJSON_Parse(recvBuff);
    cJSON *json_type = cJSON_GetObjectItemCaseSensitive(j_responce, "action");
    char *action = strdup(json_type->valuestring);

    
    if (!strcmp(action, "login_r"))
        mx_login_handl_res(j_responce, chat);
    if (!strcmp(action, "log_out"))
        mx_close_chatpage(j_responce, chat);
    if (!strcmp(action, "add_cont"))
        mx_addcont_handl_res(j_responce, chat);
    if (!strcmp(action, "getup_contact"))
        mx_getup_contact(j_responce, chat);
}
