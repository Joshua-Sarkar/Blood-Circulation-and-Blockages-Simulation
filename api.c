#include <microhttpd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "simulation.h"

#define PORT 8888

static VascularGraph* graph = NULL;

static int answer_to_connection (void *cls, struct MHD_Connection *connection,
                                const char *url, const char *method,
                                const char *version, const char *upload_data,
                                size_t *upload_data_size, void **con_cls) {
    const char *page = "Not Found";
    int ret;

    if (strcmp (method, "GET") == 0 && strcmp(url, "/state") == 0) {
        const char* json_resp = get_simulation_state_json(graph);
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(json_resp), (void*)json_resp, MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    } else if (strcmp(method, "POST") ==0 && strcmp(url, "/tick") ==0) {
        run_simulation_tick(graph);
        const char* json_resp = "{ \"status\": \"tick advanced\" }";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(json_resp), (void*)json_resp, MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    } else if (strcmp(method, "POST") == 0 && strstr(url, "/blockage") == 0) {
        induce_blockage(graph, 2, 50); // Example: blocking node 2 for 50 ticks
        const char* json_resp = "{ \"status\": \"blockage induced\" }";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(json_resp), (void*)json_resp, MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    }

    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page), (void*)page, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
    MHD_destroy_response(response);
    return ret;
}

int main() {
    graph = create_graph(5);
    add_connection(graph, 0, 1);
    add_connection(graph, 1, 2);
    add_connection(graph, 2, 3);
    add_connection(graph, 3, 4);

    struct MHD_Daemon *daemon;
    daemon = MHD_start_daemon(MHD_USE_THREAD_PER_CONNECTION, PORT, NULL, NULL, &answer_to_connection, NULL, MHD_OPTION_END);
    if (daemon == NULL) return 1;

    printf("Server started on port %d\n", PORT);
    getchar(); // wait for user to press Enter to stop the server

    MHD_stop_daemon(daemon);
    free_graph(graph);
    return 0;
}
