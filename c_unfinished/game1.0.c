#include <time.h>
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
    #ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
    #define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
    #endif
    #include <windows.h>
    void enable_ansi_escape_codes() {
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        GetConsoleMode(hOut, &dwMode);
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);
    }
#endif

const int rand_max=1000;

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_WHITE   "\x1b[0m"

void clrscr(){
    printf("\e[1;1H\e[2J");
}
char main_cover[]="     ..                                                         \n"
"       .                                                        \n"
"       W.                                                       \n"
"       .8                                                       \n"
"        8# #                                                    \n"
"           ..                                                   \n"
"    #   . #.#                                                   \n"
"     .8#.##.#                                                   \n"
"       # #...                                                   \n"
"         . ...#                                                 \n"
"          #.#..                                                 \n"
"          .##....                                               \n"
"         .  .. # #          .                                   \n"
"            ..  ##         .  @                                 \n"
"          . 88#  #.         @   W                               \n"
"              #.#.# #      8 @@@@W.                             \n"
"           .WW8## 8  8#  . 8WWW@@@W                             \n"
"               .8 #88W # 8W  W W@@ WW.                          \n"
"             . #..W# 8 WWWW@@@W W @@W8                          \n"
"                .8W#.  @ WW@X@  WW @ W8                         \n"
"                    88 WW8WW@ @ WWWW WW                         \n"
"          8      . W#.8W8  WW88 WWW  WW8.    #.                 \n"
"          #   .       #  ##W WW88W    WW   .## .                \n"
"          .8    #        ... #888WWW  WW8 .W.W#8.               \n"
"          .  .##W 8 8W8  .8    . 8WWWW  W88#8#. #               \n"
"            .    . 888W8 .##.  . .# W8W  888 .#8.               \n"
"            #.     #88  # .  .  ... # WW W88  ...               \n"
"             ..      ##.. .     W 8## #88W 88   ..              \n"
"            .#.                8WWW#....8W @ 8 # ..             \n"
"             #                 8 88.#   #8 .W  #...             \n"
"             #.                 W88  .   . # ..#.#8.            \n"
"             ##                . W .   ## .     . #             \n"
"            # #.                W8      .# #  ..   ##           \n"
"            ..#.                           .## #    #.          \n"
"          . ## #                W .          ..      #          \n"
"           . ....#              W8.                   #8        \n"
"              8. # # ..         W8.                     8#      \n"
"              .8      .         8#8                      #.     \n"
"               W  .              # W8.                    #.    \n"
"               .     #              #88.                   .    \n"
"                8                     #8 8                      \n"
"                                             W .                \n"
"                                          .88W8 8               \n"
"                                               . W.             \n";
typedef enum {RED,GREEN,YELLOW,BLUE,MAGENTA,CYAN,WHITE} main_colors;
struct button{
    int offx;
    int offy;
    main_colors color;
    main_colors border_color;
    char text[20];
};
// PLAYER VARS
int player_pos_x=0;
int player_pos_y=0;
int player_hp=35;
int player_biomass=0;
char game_map[30][30];
void generatemap(){
    for(int y=0;y<30;y++){
        for(int x=0;x<30;x++){
            game_map[y][x]=' ';
        }
    }
}
void set_to_color(main_colors cclr){
    switch (cclr)
    {
    case RED:
        printf(ANSI_COLOR_RED);
        break;
    case GREEN:
        printf(ANSI_COLOR_GREEN);
        break;
    case YELLOW:
        printf(ANSI_COLOR_YELLOW);
        break;
    case BLUE:
        printf(ANSI_COLOR_BLUE);
        break;
    case MAGENTA:
        printf(ANSI_COLOR_MAGENTA);
        break;
    case CYAN:
        printf(ANSI_COLOR_CYAN);
        break;
    case WHITE:
        printf(ANSI_COLOR_WHITE);
        break;
    default:
        break;
    }
}
void print_border(int llength){
    for(int i=0;i<llength+2;i++){
        if(i==0||i==llength+1){
            printf("#");
        } else {
            printf("=");
        }
    }
    printf(ANSI_COLOR_WHITE);
}
void offset_x(int ox){
    for(int x=0;x<ox;x++){
        printf("\t");
    }
}
void offset_y(int oy){
    for(int y=0;y<oy;y++){
        printf("\n");
    }
}
void display_button(struct button curbtn){
    offset_y(curbtn.offy);
    int text_len=0;
    text_len=strlen(curbtn.text);
    set_to_color(curbtn.border_color);
    offset_x(curbtn.offx);
    print_border(text_len);
    printf("\n");
    offset_x(curbtn.offx);
    set_to_color(curbtn.border_color);
    printf("+");
    set_to_color(curbtn.color);
    printf("%s",curbtn.text);
    set_to_color(curbtn.border_color);
    printf("+\n");
    offset_x(curbtn.offx);
    print_border(text_len);
}
struct button create_button(int p_offx,int p_offy,main_colors p_color,main_colors p_border_color,char *p_text){
    struct button t_btn;
    t_btn.offx=p_offx;
    t_btn.offy=p_offy;
    t_btn.color=p_color;
    t_btn.border_color=p_border_color;
    strcpy(t_btn.text,p_text);
    return t_btn;
}
void print_rainbow(char whattext[256]){
    for(int i=0;i<strlen(whattext);i++){
        switch (i%7)
        {
        case 0:
            set_to_color(RED);
            break;
        case 1:
            set_to_color(WHITE);
            break;
        case 2:
            set_to_color(YELLOW);
            break;
        case 3:
            set_to_color(BLUE);
            break;
        case 4:
            set_to_color(GREEN);
            break;
        case 5:
            set_to_color(CYAN);
            break;
        case 6:
            set_to_color(MAGENTA);
            break;
        default:
            set_to_color(WHITE);
            break;
        }
        printf("%c",whattext[i]);
    }
}
int main(){
    #ifdef _WIN32
    enable_ansi_escape_codes();
    #endif
    // Initialization, should only be called once.
    //srand(time(NULL));
    //int r = rand()%rand_max; //rand()%20 0-19
    FILE *fptr;
    clrscr();
    struct button b1=create_button(0,1,RED,YELLOW,"1. New game");
    struct button b2=create_button(1,1,BLUE,CYAN,"2. Load game");
    struct button b3=create_button(2,1,WHITE,MAGENTA,"3. Credits");
    printf(ANSI_COLOR_RED "%s \n" ANSI_COLOR_WHITE,main_cover);
    display_button(b1);
    display_button(b2);
    display_button(b3);
    int exited=0;
    while (exited==0)
    {
        int cur_answer=0;
        printf("\nChoose option (1,2,3,etc...). 0 is exit:");
        scanf("%d",&cur_answer);
        switch(cur_answer){
            case 0:
                exited=1;
                break;
            case 1:
                //new game
                break;
            case 2:
                printf("Enter filepath (.txt):");
                char load_path[32];
                scanf("%s",&load_path);
                fptr=fopen(load_path,"r");
                if(fptr==NULL){
                    printf(ANSI_COLOR_RED "File not found!\n" ANSI_COLOR_WHITE);
                } else {
                    int lines=0;
                    char sor[100];
                    while(fgets(sor,100,fptr)){
                        if(lines==0){
                            //First sor px|py|hp|biomass
                        } else {
                            
                        }
                        lines++;
                    }
                }
                break;
            case 3:
                printf(ANSI_COLOR_YELLOW "Credits:\n" ANSI_COLOR_WHITE);
                print_rainbow("Afghan Goat");
                printf("\n\n");
                break;
        }
    }
    return 0;
}