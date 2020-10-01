/**
 * @file test_all.c
 * @author Nikhil
 * @brief µnit testing using suites of suites 
 * @version 0.1
 * @date 2020-09-26
 * 
 * @copyright Copyright (c) 2020
 * 
 */

/*#include <stdio.h>
#include "./test/munit.h"
#include "./bmd_handler/test_bmd.c"
#include "./adapter/test_adapter.c"
#include "./db_access/test_db_access.c"

static MunitSuite suite_tests[] = {
  {    
       "/test_bmd_suites" ,
        bmd_tests,
        NULL,
        1,
        MUNIT_TEST_OPTION_NONE,
  },
  {    
       "/test_adapter_suites" ,
        adapter_tests, 
        NULL,
        1,
        MUNIT_TEST_OPTION_NONE,
  },
  {
        "/db_access_tests",     
        db_access_tests,        
        NULL,                   
        1,                      
        MUNIT_SUITE_OPTION_NONE 
  },

  {NULL, NULL, NULL, 0, MUNIT_TEST_OPTION_NONE}
  
};

static const MunitSuite suite = {
    "/suite",                  
    NULL,                      
    suite_tests,               
    1,                         
    MUNIT_SUITE_OPTION_NONE    
};


int main(int argc, const char *argv[])
 {
   munit_suite_main(&suite, NULL, argc, NULL);
 }*/