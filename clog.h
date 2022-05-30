 #include <stdio.h>
 #include <unistd.h>
 #include <stdbool.h>
 
 #ifndef __CLOG_H__
 #define __CLOG_H__
 
 #define ANSI_RED "\x1b[31m"
 #define ANSI_GREEN "\x1b[32m"
 #define ANSI_YELLOW "\x1b[33m"
 #define ANSI_BLUE "\x1b[34m"
 #define ANSI_MAGENTA "\x1b[35m"
 #define ANSI_CYAN "\x1b[36m"
 #define ANSI_RESET "\x1b[0m"
 
 #ifndef NDEBUG
 
 #define logf_(...) printf(__VA_ARGS__)
 
 #define logf_red(...) __mu_logf_any_color_code(ANSI_RED, __VA_ARGS__)
 #define logf_green(...) __mu_logf_any_color_code(ANSI_GREEN, __VA_ARGS__)
 #define logf_yellow(...) __mu_logf_any_color_code(ANSI_YELLOW, __VA_ARGS__)
 #define logf_blue(...) __mu_logf_any_color_code(ANSI_BLUE, __VA_ARGS__)
 #define logf_magenta(...) __mu_logf_any_color_code(ANSI_MAGENTA, __VA_ARGS__)
 #define logf_cyan(...) __mu_logf_any_color_code(ANSI_CYAN, __VA_ARGS__)
 
 
 
 #define __mu_logf_any_color_code(ansi_color_code,...) do { \
     if(isatty(STDOUT_FILENO)) { \
         logf_(ansi_color_code);    \
     }                           \
     logf_(__VA_ARGS__);   \
     if(isatty(STDOUT_FILENO)) { \
         logf_(ANSI_RESET);  \
     }                           \
     } while(false)
 
 
 #define log_int(n) printf("%s == %d\n", (#n), (n))
 
 #define log_char(n) printf("%s == '%c'\n", (#n), (n))
 
 #define log_str(n) printf("%s == \"%s\"\n", (#n), (n))
 
 #define log_addr(n) printf("%s == %p\n", (#n), (n))
 
 #define log_float(n) printf("%s == %f\n", (#n), (n))
 
 #define log_bool(n) printf("%s == %s\n", (#n), (n ? "true" : "false"))
 
 
 #else
 
 #define logf_