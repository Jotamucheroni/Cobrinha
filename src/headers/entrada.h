#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>

#define ECHOFLAGS (ECHO | ECHOE | ECHOK | ECHONL)

enum cursor {MOSTRA, OCULTA};
typedef enum cursor cursor;

enum digita {HABILITA, DESABILITA};
typedef enum digita digita; 

int kbhit();

int getch();

int set_disp_mode(int fd,int option);

int muda_cursor(cursor estado);

int digitar(digita estado);
