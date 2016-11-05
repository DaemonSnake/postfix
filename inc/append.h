#pragma once

#define NL _Pragma("")
#define HS #
#define PROC(arg...) NL HS arg NL

#pragma GCC diagnostic ignored "-Wunknown-pragmas"
    
#define IFDEF(name, body...)                    \
    PROC(ifdef name)                            \
    body                                        \
    PROC(endif)

#define UNDEF(name)  IFDEF(name, PROC(undef name))
#define DELAY(arg...) WHEN(arg)
#define MACRO_GLUE(x, y) MACRO_GLUE2(x, y)
#define MACRO_GLUE2(x, y) x ## y
#define MACRO_LINE(name) MACRO_GLUE(name ## __, __LINE__)
PROC(define MACRO_GLUE_2_(x, y) MACRO_GLUE_2_2(x, y))
PROC(define MACRO_GLUE_2_2(x, y) x ## y)
PROC(define WHEN(arg...) arg)
PROC(define PROC_2(values2...) HS_2 values2)
PROC(define HS_2 #)
PROC(define _PRAGMA(arg) arg ## Pragma(""))

#define append_macro(name, values...)                                   \
    DELAY(PROC(ifdef name))                                             \
                                                                        \
    DELAY(PROC(undef name))                                             \
    DELAY(PROC(define name MACRO_LINE(name)))                           \
    DELAY(PROC(define MACRO_LINE(name)                                  \
               MACRO_GLUE_2_(name ## __,                                \
                             name ## __prev), values))                  \
    UNDEF(name ## __prev)                                               \
                                                                        \
    DELAY(PROC(else))                                                   \
                                                                        \
    DELAY(PROC(define name values))                                     \
    DELAY(PROC(define MACRO_LINE(name) values))                         \
                                                                        \
    DELAY(PROC(endif))                                                  \
    PROC(define name ## __prev __LINE__) _PRAGMA(_)

#define append_macro_dotcoma(name, values...)                           \
    DELAY(PROC(ifdef name))                                             \
                                                                        \
    DELAY(PROC(undef name))                                             \
    DELAY(PROC(define name MACRO_LINE(name)))                           \
    DELAY(PROC(define MACRO_LINE(name)                                  \
               MACRO_GLUE_2_(name ## __,                                \
                             name ## __prev); values))                  \
    UNDEF(name ## __prev)                                               \
                                                                        \
    DELAY(PROC(else))                                                   \
                                                                        \
    DELAY(PROC(define name values))                                     \
    DELAY(PROC(define MACRO_LINE(name) values))                         \
                                                                        \
    DELAY(PROC(endif))                                                  \
    PROC(define name ## __prev __LINE__)

#define append_macro_nosep(name, values...)                             \
    DELAY(PROC(ifdef name))                                             \
                                                                        \
    DELAY(PROC(undef name))                                             \
    DELAY(PROC(define name MACRO_LINE(name)))                           \
    DELAY(PROC(define MACRO_LINE(name)                                  \
               MACRO_GLUE_2_(name ## __,                                \
                             name ## __prev) values))                   \
    UNDEF(name ## __prev)                                               \
                                                                        \
    DELAY(PROC(else))                                                   \
                                                                        \
    DELAY(PROC(define name values))                                     \
    DELAY(PROC(define MACRO_LINE(name) values))                         \
                                                                        \
    DELAY(PROC(endif))                                                  \
    PROC(define name ## __prev __LINE__)
