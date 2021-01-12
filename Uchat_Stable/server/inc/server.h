#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <signal.h>

/* Server libraries */
#include "../../libraries/include/cJSON.h"
#include <sqlite3.h>

#define MAX_CLIENTS 100
#define BUFFER_SZ 2048


static _Atomic unsigned int cli_count = 0;
static int uid = 10;

/* Client structure */
typedef struct {
    struct sockaddr_in addr; /* Client remote address */
    int connfd;              /* Connection file descriptor */
    int uid;                 /* Client unique identifier */
    char name[32];           /* Client name */
    sqlite3 *db;
} client_t;

client_t *clients[MAX_CLIENTS];

static char topic[BUFFER_SZ/2];

/* Functions */
int mx_create_server(char **argv);
void *mx_handle_client(void *arg);
void mx_json_manager(char buff_in[], int connfd, client_t *cli);

void mx_login_responce(cJSON *j_request, int connfd, sqlite3 *db);
void mx_register_responce(cJSON *j_request, int connfd, sqlite3 *db);
void mx_add_new_cntc_responce(cJSON *j_request, int connfd, sqlite3 *db);

sqlite3 *mx_get_db(sqlite3 *tmp_db);
void mx_create_table(sqlite3 *tmp_db);
int mx_check_uonline_status(sqlite3 *db, char *username);
int mx_search_user(sqlite3 *db, char *username);
int mx_confirm_ucredentials(sqlite3 *db, char *username, char *password);
void mx_insert_client_socket(sqlite3 *db, char *username, int connfd);
void mx_create_new_user(sqlite3 *db, char *username, char *password);
int mx_logout_event_db(int connfd, sqlite3 *db);
int mx_find_similar_cntc_db(sqlite3 *db, char *username, int connfd);
int mx_get_id_login(sqlite3 *db, char *username);
int mx_get_id_socket(sqlite3 *db, int connfd);

/* Net Lib */
void print_client_addr(struct sockaddr_in addr);
void strip_newline(char *s);
void send_active_clients(int connfd);
void send_message_client(char *s, int uid);
void send_message_self(const char *s, int connfd);
void send_message_all(char *s);
void send_message(char *s, int uid);
void queue_delete(int uid);
void queue_add(client_t *cl);
char *_strdup(const char *s);
