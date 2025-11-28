#define SIZE 32
#define BUFFER_SIZE 64

typedef enum {Start, Word, Special, Newline, Stop} vertex;

extern char ** lst;
extern char * buf;
extern char str[];
extern int sizebuf;
extern int sizelist;
extern int curbuf;
extern int curlist;
extern int str_len;
extern int str_pos;
extern int is_eof;
extern int c;
extern vertex v;


void clearlist();
void termlist();
void nullbuf();
void printlist();
int getsym();
void addword();
void addsym();
void sortlist();
void read_block();
void double_list();

void start();
void word();
void special();
void newline();
