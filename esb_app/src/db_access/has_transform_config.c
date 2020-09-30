/**
 * @file get_active_route_id.c
 * @author MubeenS
 * @brief Function returns id of a route if exists by performing
 * sql query:SELECT id FROM transform_config 
 * WHERE route_id = ?
 * returns 0 if route does not exist.
 * 
 * @version 0.1
 * @date 2020-09-05
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <stdio.h>
#include <string.h>
#include <stdio.h>

/* Contains necessary C functions of mysql */
#include <mysql/mysql.h>
#include <stdbool.h>
/**
 * Holds the info to connect to DB and
 * error specifying function for 
 * databse connection handle 
 */
#include "connector.h"

#define STRING_SIZE 100
#define SELECT_QUERY "SELECT id FROM transform_config          \
WHERE route_id = ? "

int has_transform_config(int route_id)
{
    MYSQL_STMT *stmt;         /* store statement */
    MYSQL_BIND input_bind[1]; /* to bind input */
    int route_id_data;
    MYSQL_BIND bind[1];
    MYSQL_RES *prepare_meta_result;
    unsigned long length[2];
    int param_count;
    int int_data;
    bool is_null[2];

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
        return -1;
    }

    /**
   * @brief Checks if connection is 
   * properly established.
   * 
   */
    if (mysql_real_connect(con, HOST, USER, PASS, DB_NAME,
                           PORT, UNIX_SOCKET, FLAG) == NULL)
    {
        finish_with_error(con);
    }

    stmt = mysql_stmt_init(con);
    if (!stmt)
    {
        fprintf(stderr, " mysql_stmt_init(), out of memory\n");
        return -1;
    }

    if (mysql_stmt_prepare(stmt, SELECT_QUERY, strlen(SELECT_QUERY)))
    {
        fprintf(stderr, " mysql_stmt_prepare(), SELECT failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        return -1;
    }

    /* Get the parameter count from the statement */
    param_count = mysql_stmt_param_count(stmt);

    /* validate parameter count */
    if (param_count != 1)
    {
        fprintf(stderr, " invalid parameter count returned by MySQL\n");
        return -1;
    }

    /* Fetch result set meta information */
    prepare_meta_result = mysql_stmt_result_metadata(stmt);
    if (!prepare_meta_result)
    {
        fprintf(stderr, "mysql_stmt_result_metadata(),           \
        returned no meta information\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        return -1;
    }

    memset(input_bind, 0, sizeof(input_bind));

    /* Route-id */
    input_bind[0].buffer_type = MYSQL_TYPE_LONG;
    input_bind[0].buffer = (char *)&route_id_data;
    input_bind[0].is_null = &is_null[0];
    input_bind[0].length = &length[0];

    /* Bind the buffers */
    if (mysql_stmt_bind_param(stmt, input_bind))
    {
        fprintf(stderr, " mysql_stmt_bind_param() failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        return -1;
    }

    /* Copy input data from function parameters */
    route_id_data = route_id;

    if (mysql_stmt_execute(stmt))
    {
        fprintf(stderr, " mysql_stmt_execute, 2 failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        return -1;
    }

    /* Bind the result buffers for all 4 columns before fetching them */

    memset(bind, 0, sizeof(bind));

    /* id */
    bind[0].buffer_type = MYSQL_TYPE_LONG;
    bind[0].buffer = (char *)&int_data;
    bind[0].is_null = &is_null[1];
    bind[0].length = &length[1];

    /* Bind the result buffers */
    if (mysql_stmt_bind_result(stmt, bind))
    {
        fprintf(stderr, " mysql_stmt_bind_result() failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        return -1;
    }

    /* Now buffer all results to client */
    if (mysql_stmt_store_result(stmt))
    {
        fprintf(stderr, " mysql_stmt_store_result() failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        return -1;
    }
    int id = 0;

    if (!mysql_stmt_fetch(stmt))
    {

        //num_rows = mysql_stmt_num_rows(stmt);
        id = int_data;
        /* Free the result */
        mysql_free_result(prepare_meta_result);

        /* Close the statement */
        if (mysql_stmt_close(stmt))
        {
            fprintf(stderr, " failed while closing the statement\n");
            fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
            return -1;
        }
        /*closes the database connection*/
        mysql_close(con);

        return id;
    }
    else
    {
        printf("No transform_config exists for route_id.");
    }

    /* Free the prepared result metadata */
    mysql_free_result(prepare_meta_result);

    /* Close the statement */
    if (mysql_stmt_close(stmt))
    {
        fprintf(stderr, " failed while closing the statement\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        return -1;
    }

    /*closes the database connection*/
    mysql_close(con);
    /* returns number of rows in result */
    return 0;
}

/*int main(int argc, char **argv)
{
    int id = has_transform_config(4);
    printf("id = %d", id);
    return 0;
}*/