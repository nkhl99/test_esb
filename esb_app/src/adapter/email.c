/**
 * @file email.c
 * @author MubeenS
 * @brief The program sends an email
 * to the destination specified. Reads
 * the content from a file specified.
 * 
 * returns NULL on success.
 * @version 0.1
 * @date 2020-09-10
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

#include "adapter.h"

#define FROM "testmailtm02@gmail.com"
//#define TO "testmailtm02@gmail.com"
#define CC "testmailtm02@gmail.com"


void* send_mail(void *toptr, void *file_path_ptr)
{   
    char *to = (char*)toptr;
    char *file_path = (char*)file_path_ptr;
    printf(">> Sending mail to %s\n", to);

    CURL *curl;
    CURLcode res;
    struct curl_slist *recipients = NULL;

    curl = curl_easy_init();
    if (curl)
    {
        /* Set username and password */
        curl_easy_setopt(curl, CURLOPT_USERNAME, "testmailtm02");
        curl_easy_setopt(curl, CURLOPT_PASSWORD, "narmada@123");

        /* URL for mail server */
        curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.gmail.com:587/");

        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);

        /** TODO: Security certificate to be added 
         * for secure transport protocol 
         */

        //curl_easy_setopt(curl, CURLOPT_CAINFO, "/path/to/certificate.pem");

        /* FROM address */
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, FROM);

        /* Recipients */
        recipients = curl_slist_append(recipients, to);
        recipients = curl_slist_append(recipients, CC);
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

        /* We're using a callback function to specify the payload (the headers and
         * body of the message). You could just use the CURLOPT_READDATA option to
         * specify a FILE pointer to read from. */
        //curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
        FILE *fp = fopen(file_path, "r");
        curl_easy_setopt(curl, CURLOPT_READDATA, fp);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

        /* Gives information about whats running inside libcurl */
        //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        /* Send the message */
        /* res =0 means everything is ok */
        res = curl_easy_perform(curl);

        /* Check for errors */
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));

        /* Free the list of recipients */
        curl_slist_free_all(recipients);

        /* Always cleanup */
        curl_easy_cleanup(curl);
    }

    return NULL;
}

/*int main()
{
    int t = send_mail("testmailtm02@gmail.com", "../assets/ToBeMailed.json");
    printf("%d", t);
    return 0;
}*/