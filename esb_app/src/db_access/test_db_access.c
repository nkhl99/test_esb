/**
 * @file test_db_access.c
 * @author Nikhil
 * @brief µnit testing of Database Module
 * @version 0.1
 * @date 2020-09-16
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <stdio.h>
#include "../test/munit.h"
#include "connector.h"
#include "../bmd_handler/bmd.h"
#include "../adapter/adapter.h"
#include "../esb/esb.h"

/**
 * @brief µnit testing for :
 * 
 * 1. insert_to_esb_request()
 * 2. has_transform_config()
 * 3. has_transport_config()
 * 4. get_active_route_id()
 * 5. update_esb_request()
 * 6. fetch_transport_config()
 * 7. fetch_transform_config()
 * 8. get_status()
 * 
 * @param params 
 * @param user_data 
 * @return void* 
 */

// 1

static void *
insert_to_esb_request_setup(const MunitParameter params[], void *user_data)
{
  char *file = "../bmd_files/bmd1.xml";
  bmd *b = parse_bmd_xml(file);

  return b;
}

/* Test function */
static MunitResult
test_insert_to_esb_request(const MunitParameter params[], void *fixture)
{
  bmd *b = (bmd *)fixture;
  /* Check the return code */
  int rc = insert_to_esb_request(b->envelop_data->Sender,
                                 b->envelop_data->Destination,
                                 b->envelop_data->MessageType,
                                 b->envelop_data->ReferenceID,
                                 b->envelop_data->MessageID,
                                 "Routes", "RECEIVED",
                                 "received successfully",
                                 b->envelop_data->CreationDateTime);
  munit_assert(rc != 0);

  return MUNIT_OK;
}

static void
insert_to_esb_request_tear_down(void *fixture)
{
  bmd *b = (bmd *)fixture;
  free(b->envelop_data);
  free(b->payload);
  free(b);
}

// 2

static MunitResult
test_has_transform_config(const MunitParameter params[], void *fixture)
{;
  /* Check the return code */
  int rc = has_transform_config(1);
  munit_assert(rc != 0);
  return MUNIT_OK;
}

// 3

static MunitResult
test_has_transport_config(const MunitParameter params[], void *fixture)
{
  /* Check the return code */
  int rc = has_transport_config(1);
  munit_assert(rc != 0);
  return MUNIT_OK;
}


// 4

static void *
get_active_route_id_setup(const MunitParameter params[], void *user_data)
{
  char *file = "../bmd_files/bmd1.xml";
  bmd *b = parse_bmd_xml(file);
  return b;
}

static MunitResult
test_get_active_route_id(const MunitParameter params[], void *fixture)
{
  bmd *b = (bmd *)fixture;
  /* Check the return code */
  int rc = get_active_route_id(b->envelop_data->Sender,
                              b->envelop_data->Destination,
                              b->envelop_data->MessageType);
  munit_assert(rc != 0);
  return MUNIT_OK;
}

static void
get_active_route_id_tear_down(void *fixture)
{
  bmd *b = (bmd *)fixture;
  free(b->envelop_data);
  free(b->payload);
  free(b);
}


// 5

static MunitResult
test_update_esb_request(const MunitParameter params[], void *fixture)
{;
  /* Check the return code */
  int rc = update_esb_request("RECEIVED",1);
  munit_assert(rc != 0);
  return MUNIT_OK;
}


// 6

static void *
fetch_transport_config_setup(const MunitParameter params[], void *user_data)
{

  transport_t* tf= fetch_transport_config(1);
  return tf;
}


/* Test function for update_esb_request */
static MunitResult
test_fetch_transport_config(const MunitParameter params[], void *fixture)
{
  transport_t * tf = (transport_t *)fixture;

  munit_assert_string_equal(tf->key,"API_URL");
  munit_assert_string_equal(tf->value,"https://ifsc.razorpay.com/");

  return MUNIT_OK;
}


/* free of allocated memory*/
static void
fetch_transport_config_tear_down(void *fixture)
{
  transport_t * tf = (transport_t *)fixture;

  free(tf->key);
  free(tf->value);
  free(tf);
}


// 7

static void *
fetch_transform_config_setup(const MunitParameter params[], void *user_data)
{

  transform_t* tf= fetch_transform_config(1);
  return tf;
}


/* Test function for update_esb_request */
static MunitResult
test_fetch_transform_config(const MunitParameter params[], void *fixture)
{
  transform_t * tf = (transform_t *)fixture;

  munit_assert_string_equal(tf->key,"IFSC");
  munit_assert_string_equal(tf->value,"No Transform");

  return MUNIT_OK;
}


/* free of allocated memory*/
static void
fetch_transform_config_tear_down(void *fixture)
{
  transform_t * tf = (transform_t *)fixture;

  free(tf->key);
  free(tf->value);
  free(tf);
}


// 8

static void *
get_status_setup(const MunitParameter params[], void *user_data)
{
  char *file = "../bmd_files/bmd1.xml";
  bmd *b = parse_bmd_xml(file);

  return b;
}
static MunitResult
test_get_status(const MunitParameter params[], void *fixture)
{
   bmd *b = (bmd *)fixture;
  char* rc=get_status_info(b->envelop_data->MessageID);
  munit_assert_string_equal(rc,"DONE");
  return MUNIT_OK;
}

static void
get_status_tear_down(void *fixture)
{
  bmd *b = (bmd *)fixture;
  free(b->envelop_data);
  free(b->payload);
  free(b);
}

/* Put all unit tests here. */
MunitTest db_access_tests[] = {
    {
        "/get_active_route_id",        /* name */
        test_get_active_route_id,      /* test function */
        get_active_route_id_setup,     /* setup function for the test */
        get_active_route_id_tear_down, /* tear_down */
        MUNIT_TEST_OPTION_NONE,        /* options */
        NULL                           /* parameters */
    },
    {
        "/has_transport_config",        /* name */
        test_has_transport_config,      /* test function */
        NULL,                           /* setup function for the test */
        NULL,                           /* tear_down */
        MUNIT_TEST_OPTION_NONE,         /* options */
        NULL                            /* parameters */
    },

    {
        "/has_transform_config",        /* name */
        test_has_transform_config,      /* test function */
        NULL,                           /* setup function for the test */
        NULL,                           /* tear_down */
        MUNIT_TEST_OPTION_NONE,         /* options */
        NULL                            /* parameters */
    },
    {
        "/insert_to_esb_request_test",   /* name */
        test_insert_to_esb_request,      /* test function */
        insert_to_esb_request_setup,     /* setup function for the test */
        insert_to_esb_request_tear_down, /* tear_down */
        MUNIT_TEST_OPTION_NONE,          /* options */
        NULL                             /* parameters */
    },
    {
        "/update_esb_request",        /* name */
        test_update_esb_request,      /* test function */
        NULL,                           /* setup function for the test */
        NULL,                           /* tear_down */
        MUNIT_TEST_OPTION_NONE,         /* options */
        NULL                            /* parameters */
    },
    {
        "/fetch_transport_config",        /* name */
        test_fetch_transport_config,      /* test function */
        fetch_transport_config_setup,     /* setup function for the test */
        fetch_transport_config_tear_down, /* tear_down */
        MUNIT_TEST_OPTION_NONE,           /* options */
        NULL                              /* parameters */
    },
    {
        "/fetch_transform_config",        /* name */
        test_fetch_transform_config,      /* test function */
        fetch_transform_config_setup,     /* setup function for the test */
        fetch_transform_config_tear_down, /* tear_down */
        MUNIT_TEST_OPTION_NONE,           /* options */
        NULL                              /* parameters */
    },
    {
      "/get_status",
      test_get_status,
      get_status_setup,
      get_status_tear_down,
      MUNIT_TEST_OPTION_NONE,         
        NULL 
    },
   
   /* Mark the end of the array with an entry where the test
   * function is NULL */
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
    
    };

/* Arrange the test cases into a test suite. */
//static const MunitSuite suite = {
//    "/db_access_tests",     /* name */
//    db_access_tests,        /* tests */
//    NULL,                   /* suites */
 //   1,                      /* iterations */
 //   MUNIT_SUITE_OPTION_NONE /* options */
//};

/* Run the the test suite */
/*int main(int argc, const char *argv[])
{
  return munit_suite_main(&suite, NULL, argc, NULL);
}*/
