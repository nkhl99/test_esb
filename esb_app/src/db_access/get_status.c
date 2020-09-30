/**
 * @file get_status.c
 * @author MubeenS
 * @brief Return status of esb_request based on 
 * given message_id. If no request exists for corresponding 
 * message_id the function returns NULL.
 * @version 0.1
 * @date 2020-09-22
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <stdbool.h>


#include "connector.h"

#define STRING_SIZE 1000

//#define SELECT_QUERY "SELECT status FROM esb_request WHERE message_id = '4ac268c2-f658-11ea-adc1-0242ac120002' "

char *get_status_info(char *message_id)
{
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[1];
    MYSQL_RES *prepare_meta_result;
    unsigned long length[1];
    int param_count, column_count, row_count;
    char str_data[STRING_SIZE];
    bool is_null[1];
    bool error[1];
    char SELECT_QUERY[STRING_SIZE];
    sprintf(SELECT_QUERY,"SELECT status                              \
                          FROM esb_request WHERE message_id = '%s' ",\
                          message_id);
    MYSQL *con; /*database connection handle*/
    /**
   * @brief Allocates or initialises a MYSQL object 
   * suitable for mysql_real_connect() function
   * 
   */
    con = mysql_init(NULL);

    /**
   * @brief Prints error message incase
   * initialisation of con fails.
   */
    if (con == NULL)
    {

        fprintf(stderr, "mysql_init() failed\n");
        return NULL;
    }

    /**
   * @brief Checks if connection is 
   * properly established.
   * 
   */
    if (mysql_real_connect(con, HOST, USER, PASS, DB_NAME,
                           PORT, UNIX_SOCKET, FLAG) == NULL)
    {
        printf("Real connect failed..\n");
        finish_with_error(con);
    }
    /* Prepare a SELECT query to fetch data from test_table */
    stmt = mysql_stmt_init(con);
    if (!stmt)
    {
        fprintf(stderr, " mysql_stmt_init(), out of memory\n");
        return NULL;
    }
    if (mysql_stmt_prepare(stmt, SELECT_QUERY, strlen(SELECT_QUERY)))
    {
        fprintf(stderr, " mysql_stmt_prepare(), SELECT failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        return NULL;
    }

    /* Get the parameter count from the statement */
    param_count = mysql_stmt_param_count(stmt);

    if (param_count != 0) /* validate parameter count */
    {
        fprintf(stderr, " invalid parameter count returned by MySQL\n");
        return NULL;
    }

    /* Execute the SELECT query */
    if (mysql_stmt_execute(stmt))
    {
        fprintf(stderr, " mysql_stmt_execute(), failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        return NULL;
    }

    /* Fetch result set meta information */
    prepare_meta_result = mysql_stmt_result_metadata(stmt);
    if (!prepare_meta_result)
    {
        fprintf(stderr,
                " mysql_stmt_result_metadata(), \
           returned no meta information\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        return NULL;
    }

    /* Get total columns in the query */
    column_count = mysql_num_fields(prepare_meta_result);

    if (column_count != 1) /* validate column count */
    {
        fprintf(stderr, " invalid column count returned by MySQL\n");
        return NULL;
    }

    /* Bind the result buffers for all 4 columns before fetching them */

    memset(bind, 0, sizeof(bind));

    /* STRING COLUMN */
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)str_data;
    bind[0].buffer_length = STRING_SIZE;
    bind[0].is_null = &is_null[0];
    bind[0].length = &length[0];
    bind[0].error = &error[0];

    /* Bind the result buffers */
    if (mysql_stmt_bind_result(stmt, bind))
    {
        fprintf(stderr, " mysql_stmt_bind_result() failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        return NULL;
    }

    /* Now buffer all results to client (optional step) */
    if (mysql_stmt_store_result(stmt))
    {
        fprintf(stderr, " mysql_stmt_store_result() failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        return NULL;
    }

    /* Fetch all rows */
    row_count = 0;

    while (!mysql_stmt_fetch(stmt))
    {
        row_count++;
    }

    /* Validate rows fetched */
    if (row_count != 1)
    {
        fprintf(stderr, " MySQL failed to return all rows\n");
        return NULL;
    }

    /* Free the prepared result metadata */
    mysql_free_result(prepare_meta_result);

    /* Close the statement */
    if (mysql_stmt_close(stmt))
    {
        /* mysql_stmt_close() invalidates stmt, so call          */
        /* mysql_error(mysql) rather than mysql_stmt_error(stmt) */
        fprintf(stderr, " failed while closing the statement\n");
        fprintf(stderr, " %s\n", mysql_error(con));
        return NULL;
    }
    return strdup(str_data);
}

/*int main()
{  char *status = "4ac268c2-f658-11ea-adc1-0242ac120002";
    char *s = get_status_info(status);
    printf("%s\n",s);
    return 0;
}*/