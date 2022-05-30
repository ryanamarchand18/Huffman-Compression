 #include <stdio.h>
 #include <unistd.h>
 #include <stdbool.h>
 #include "clog.h"
 #include <string.h>
 #ifndef __MINIUNIT_H__
 #define __MINIUNIT_H__
 
 #define __mu_zero 0
 
 #define mu_start() int __mu_failure_line = __mu_zero
 
 #define mu_check(condition) do { \
         if((condition) == true){         \
             __mu_failure_line = 0;\
         } else if(__mu_failure_line == 0) { \
                 __mu_failure_line = __LINE__;  \
         }else { \
             __mu_failure_line = __mu_failure_line; \
         } \
     } while(false)
 
 #define mu_run(function) do { \
         if(function() == 0){ \
             logf_green("Test passed: %s\n", (#function)); \
         } else{ \
             logf_red("Test failed: %s at line %d\n", (#function),function()); \
         } \
     } while(false)
 
 #define mu_end() return __mu_failure_line
 
 #define mu_check_strings_equal(s1, s2)  mu_check(strcmp((s1), (s2)) == 0)
 
 
 #endif/* end of include gueard: __MINIUNIT_H__ */