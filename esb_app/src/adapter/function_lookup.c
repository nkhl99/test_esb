#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>

#include "adapter.h"

/**
 * These should come from the header file of the respective service
 * provider's implementation of the transformation and transport.
 */

/* The ESB would have this table */
const static struct
{
    const char *name;
    void *(*func)(void *, void *);
} function_map[] = {
    {"API_URL", call_destination_service},
    {"EMAIL", send_mail},
    {"HTTP_POST", http_post},
    {"SFTP", sftp_upload},
    {"Credit service transport", transport_bmd_Credit_svc}};

/* Function to dynamically invoke transport and transform services */
char *call_function(const char *name, void *data, void *data1)
{
    for (int i = 0; i < (sizeof(function_map) / sizeof(function_map[0])); i++)
    {
        if (!strcmp(function_map[i].name, name) && function_map[i].func)
        {
            return function_map[i].func(data, data1);
        }
    }
    return "NO";
}
