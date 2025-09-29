#include <ncurses.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

std::vector<std::string> lines; // keep all lines in this.
int top = 0, left = 0;

int curX = 0, curY = 0; // cursor positions
std::string filename;   // filename
std::string status = "HELP: Ctrl+S to save | Ctrl+Q to quit.";

// declared here, defined after main.
void display();
void load_file(std::string fname);
void save_file();
void handle_input();

int main(int argc, char** argv){
    //argc is the number of arguments, and argv is array of strings with the actual srguments.
    if(argc != 2){
        std::cout << "Usage: ./editor <filename>\n";
        return 1;
    }

    filename = argv[1];
    load_file(filename);

    // start ncurses
    initscr(); //Initializes the ncurses environment.
    raw(); // Normally, the terminal is in cooked mode, where input you need to press Enter before the program receives input. raw() disables that. You get input immediately as the user types. Ctrl+C, Ctrl+Z, etc., are sent to your program instead of being handled by the terminal.
    keypad(stdscr, TRUE); // Enables the reading of special keys like arrows, function keys, etc. stdscr → the default screen/window in ncurses. TRUE → turn keypad input on.
    noecho(); // Disables automatic echoing of typed characters to the screen. By default, when you type a key, it appears on the terminal.

    // Main loop.
    while(true){
        display();
        handle_input();
    }

    endwin(); //over
    return 0;
}

void display(){
    int scr_rows, scr_cols;
    getmaxyx(stdscr, scr_rows, scr_cols); //ncurses function to get size of the current window.

    clear();

    int screen_line = 0;
    //otherwise error that comparision b/w int and unsigned int is coming. line.size() returns unsigned int here. so need to type cast.
    //display the lines on the screen & implementing wordwrap.
    for(int i = top; i < int(lines.size()); i++){
        std::string line = lines[i];
        int len = line.length();
        for(int j = 0; j < len; j += scr_cols){
            if(screen_line >= scr_rows - 1) break; // leave last line for status
            std::string part = line.substr(j, scr_cols);
            mvprintw(screen_line++, 0, "%s", part.c_str());
        }
        if(screen_line >= scr_rows - 1) break;
    }

    // ncurses snippet to display a status bar at the bottom of the screen.
    attron(A_REVERSE);
    mvprintw(scr_rows - 1, 0, "%.*s", scr_cols, status.c_str());
    attroff(A_REVERSE);

    // move cursor relative to visible screen
    int screenY = 0;
    for(int i = top; i < curY; i++){
        screenY += (lines[i].length() + scr_cols - 1) / scr_cols;
    }
    int screenX = curX - left;
    move(screenY, screenX);
    refresh();
}

void load_file(std::string fname){
    std::ifstream file(fname); //used to read from files.
    if(file.is_open()){
        std::string line;
        while(std::getline(file, line)){
            //reads single line from file..
            if(!line.empty() && line.back() == '\r'){
                line.pop_back();
            }
            //makes sure there is no hanging /r in the end. getline aready removes \n. if \r is there, remove it.
            lines.push_back(line);
        }
    }
    if(lines.empty()) lines.push_back("");
}

void save_file(){
    std::ofstream file(filename);
    // overwrite everything in the file.
    if(file.is_open()){
        for(int i = 0; i < int(lines.size()); i++){
            file << lines[i] << ((i == int(lines.size() - 1)) ? "" : "\n");
        }
    }
}

void handle_input(){
    int scr_rows, scr_cols;
    getmaxyx(stdscr, scr_rows, scr_cols);

    int ch = getch();//ncurses function to get input. gives ascii codes.

    // Switch-case cannot handle Ranges or complex conditions, so goinf for if-else.

    int len = lines.size();
    if(ch == 17){ // Ctrl+Q
        endwin();
        exit(0);
    } else if(ch == 19){ // Ctrl+S
        save_file();
        status = "File Saved Successfully!";
    } else if(ch == KEY_UP){
        if(curY > 0) curY--;
        if(curY < top) top = curY;
    } else if(ch == KEY_DOWN){
        if(curY < len - 1) curY++;
        if(curY >= top + scr_rows - 1) top = curY - scr_rows + 2; // cannot go below the last line.
    } else if(ch == KEY_LEFT){
        if(curX > 0) curX--;
        if(curX < left) left = curX;
    } else if(ch == KEY_RIGHT){
        if(curX < int(lines[curY].length())){
            curX++;
            // Scroll right if cursor goes past screen width
            if(curX - left >= scr_cols) left++;
        }
    } else if(ch == KEY_HOME){
        curX = 0;
        if(curX < left) left = curX;
    } else if(ch == KEY_END){
        curX = lines[curY].length();
        if(curX - left >= scr_cols) left = curX - scr_cols + 1;
    } else if(ch == KEY_BACKSPACE || ch == 127 || ch == 8){
        if(curX > 0){
            lines[curY].erase(curX - 1, 1);
            curX--;
        } else if(curY > 0){
            curX = lines[curY - 1].length();
            lines[curY - 1] += lines[curY];
            lines.erase(lines.begin() + curY);
            curY--;
            if(curY < top) top = curY;
        }
    } else if(ch == 10){ // Enter
        std::string newLine = lines[curY].substr(curX);
        lines[curY] = lines[curY].substr(0, curX);
        lines.insert(lines.begin() + curY + 1, newLine);
        curY++;
        curX = 0;
        if(curY >= top + scr_rows - 1) top = curY - scr_rows + 2;
    } else if(ch >= 32 && ch <= 126){ // Printable ASCII characters
        lines[curY].insert(curX, 1, ch);
        curX++;
        if(curX - left >= scr_cols) left++;
    }

    // keep cursor in bounds
    if(curX > int(lines[curY].length())) curX = lines[curY].length();
}
