#define NCURSES_EXPORT(a) a


typedef struct screen  SCREEN;
typedef struct _win_st WINDOW;
extern int COLS;
extern int LINES;

extern WINDOW * stdscr;
typedef unsigned long chtype;

extern NCURSES_EXPORT(int) cbreak (void);
extern NCURSES_EXPORT(int) noecho (void);
extern NCURSES_EXPORT(int) nonl (void);
extern NCURSES_EXPORT(int) endwin (void);

extern NCURSES_EXPORT(int) waddch (WINDOW *, const chtype);
extern NCURSES_EXPORT(int) waddstr (WINDOW *,const char *); 
extern NCURSES_EXPORT(int) wclrtoeol (WINDOW *);
extern NCURSES_EXPORT(int) delwin (WINDOW *);
extern NCURSES_EXPORT(int) werase (WINDOW *);
extern NCURSES_EXPORT(int) getcurx (const WINDOW *);
extern NCURSES_EXPORT(int) getcury (const WINDOW *);
extern NCURSES_EXPORT(WINDOW *) initscr (void);
extern NCURSES_EXPORT(int) leaveok (WINDOW *,bool);
extern NCURSES_EXPORT(int) wmove (WINDOW *,int,int);
extern NCURSES_EXPORT(int) mvwaddch (WINDOW *, int, int, const chtype);
extern NCURSES_EXPORT(WINDOW *) newwin (int,int,int,int);
extern NCURSES_EXPORT(int) wprintw (WINDOW *, const char *,...);
extern NCURSES_EXPORT(int) wrefresh (WINDOW *);
extern NCURSES_EXPORT(chtype) winch (WINDOW *);


//#define getyx(win,y,x)          (y = getcury(win), x = getcurx(win))

