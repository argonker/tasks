# Task 3  

**INTERFACE**  
your input -- special symbols ( `&, &&, >, >>, <, |, ||, ;, (, )` ), digits, letters,   
space symbols ( `'\n', '\t', ' '` ), symbols ( `$, '_', '/', '.'` )  

**LIST.H**  
A file with a description of all necessary variables and function prototypes for working with a list of words:  

```
void clearlist();
void termlist();
void nullbuf();
void printlist();
int getsym();
void addword();
void addsym();
void sortlist();
void read_block();

```
And a new type and functions for working with an L-graph:  

```
typedef enum {Start, Word, Special_1, Special_2, Newline, Stop} vertex;  


void start();
void word();
void special();
void special2();
void newline();

```
   
**LIST.C**
The most important file, which describes all the functions necessary for the program to work.

functions:  
clearlist - erases the list, resets the pointers  
termlist -  completes the construction of the list  
nullbuf - resets the buffer to prepare for the next block  
addsym - adds a character from the block to the buffer  
addword - completes the construction of the word and adds it to the list  
printlist - prints the list and the number of words in it  
read_block - reads a block of characters in a string `str`  
getsym - returns 1 character from the string `str`  
sortlist - lexicographically sorts a list of words using the bubble sort algorithm       

The following functions determine which character group the current one belongs to:   

```
int is_letter(int ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

int is_digit(int ch) {
    return ch >= '0' && ch <= '9';
}

int is_word_char(int ch) {
    return is_letter(ch) || is_digit(ch) ||
           ch == '$' || ch == '.' || ch == '/' || ch == '_';
}

int is_special_char(int ch) {
    return ch == '|' || ch == '&' || ch == ';' || ch == '>' || ch == '<' || ch == '(' || ch == ')';
}

int is_space_char(int ch) {
    return ch == ' ' || ch == '\t' || ch == '\n';
}

```     
The following functions are related to the implementation of the L-graph, each function corresponds to a vertex of the same name:
      
start - analyzes the received symbol and determines which vertex to go to next   
word - the implementation of this feature speaks for itself:   

```
void word() {
    if (c == EOF || is_space_char(c)) {
        addword();
        v = Start;
    } else if (is_special_char(c)) {
        addword();
        nullbuf();
        addsym();
        v = Special_1;
    } else {
        addsym();
        v = Word;
    }
}
```
special - A function that is a stage of special character processing, necessary for the correct processing of two-character elements   
special2  
 
```
void special2() {
    if (is_special_char(c))
        if ((buf[0] == '&' && c == '&') || (buf[0] == '>' && c == '>') || (buf[0] == '|' && c == '|')) {
            addsym();
            addword();
            v = Start;
        } else {
            addword();
            v = Start;
            start();
        }
    else {
        addword();
        v = Start;
        start();
    }
}
```
newline - skips whitespace characters, tabs, and newlines   

**MAIN.C**   
The file in which the functions of the L-graph are controlled using the `case` operator. The key thing in this file is the control logic, or rather the condition for finishing processing the file:   

```
while (!end_of_read && v != Stop) {
        if (v != Special_1) {
            c = getsym();
            if (c == EOF)
                end_of_read = 1;
        }
```
where `end_of_line` determines whether a line has ended (that is, whether `'\n'` has been caught)    
and whether `EOF` has been encountered.
