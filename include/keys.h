#ifndef KEYS_H
# define KEYS_H

# ifdef __linux__
#  define LTURN 65361
#  define RTURN 65363

#  define FORWARD 122
#  define LEFT 113
#  define RIGHT 100
#  define BACK 115
#  define ESCAPE 65307
#  define W_KEY 119
#  define A_KEY 97
#  define S_KEY 115
#  define D_KEY 100
#  define X_KEY 120
#  define Y_KEY 121
#  define Z_KEY 122
#  define T_KEY 116

# else
#  define LTURN 123
#  define RTURN 124
#  define FORWARD 13
#  define LEFT 0
#  define RIGHT 2
#  define BACK 1
#  define ESCAPE 53

# endif
#endif
