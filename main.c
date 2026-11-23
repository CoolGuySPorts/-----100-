// Birthday guide for Stepa, from Ilya - libxenon homebrew (PowerPC / Xbox 360)
// Controls: A / D-pad Right = next, B / D-pad Left = back, Start = exit
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xenos/xenos.h>
#include <console/console.h>
#include <usb/usbmain.h>
#include <input/input.h>
#include <time/time.h>

#define BG     0xFF06120A
#define GREEN  0xFF9BF00B
#define DGREEN 0xFF107C10
#define WHITE  0xFFFFFFFF
#define YELLOW 0xFFFFD700
#define PINK   0xFFFF6EC7
#define CYAN   0xFF00E5FF
#define GREY   0xFF8FA89A
#define ORANGE 0xFFFFA020

#define SLIDES 7
#define W      60

static void color(unsigned fg) { console_set_colors(BG, fg); }

static void pad(int n) { while (n-- > 0) putchar(' '); }

static void center(const char *s, unsigned fg)
{
    color(fg);
    pad((W - (int)strlen(s)) / 2);
    printf("%s\n", s);
}

static void rule(char c, unsigned fg)
{
    int i;
    color(fg);
    for (i = 0; i < W; i++) putchar(c);
    putchar('\n');
}

static void confetti(void)
{
    static const char sym[] = "*+.o'`~^";
    static const unsigned pal[] = { PINK, YELLOW, CYAN, GREEN, ORANGE, WHITE };
    int i;
    for (i = 0; i < W; i++) {
        if (rand() % 4 == 0) {
            color(pal[rand() % 6]);
            putchar(sym[rand() % 8]);
        } else {
            putchar(' ');
        }
    }
    putchar('\n');
}

static void cake(int frame)
{
    const char *flame = (frame & 1) ? "(  (  (  (  (" : " )  )  )  )  )";
    center(flame,                              YELLOW);
    center("|  |  |  |  |",                     WHITE);
    center(".-+--+--+--+--+-.",                 PINK);
    center("| ~  ~  ~  ~  ~  ~ |",              PINK);
    center(".-+------------------+-.",          CYAN);
    center("|  ~   ~   ~   ~   ~   ~  |",       CYAN);
    center("'--------------------------'",      ORANGE);
}

static const char *title[SLIDES] = {
    "",
    "1. WHERE TO PUT IT",
    "2. COOLING AND DUST",
    "3. HANDLING",
    "4. WHERE TO GET GAMES",
    "5. GET ONLINE",
    "6. IF SOMETHING GOES WRONG"
};

static const char *body[SLIDES] = {
    "",

    "  * Flat, hard surface - never a carpet or a bed.\n"
    "  * Keep 10+ cm of free space around the vents.\n"
    "  * Never inside a closed cabinet.\n"
    "  * Away from heaters and direct sunlight.\n",

    "  * Clean the vents with a dry brush or air duster.\n"
    "  * Do it every 3-6 months, with power OFF.\n"
    "  * Overheating is the 360's main enemy.\n"
    "  * Loud fans? Clean them first.\n",

    "  * Don't move it while a disc is spinning.\n"
    "  * Use only the original power brick.\n"
    "  * Power off with the Guide button.\n"
    "  * Back up saves to a USB drive.\n",

    "  * Used discs: local shops, flea markets, classifieds.\n"
    "  * Check the disc is clean and not scratched.\n"
    "  * The 360 online store closed in 2024, but games\n"
    "    you already bought stay in Download History.\n"
    "  * Stick to legit copies: fakes can be broken and\n"
    "    can get the console banned from Xbox Live.\n",

    "  WIRED (best):\n"
    "   1. Ethernet cable: router -> console.\n"
    "   2. Settings > System > Network Settings.\n"
    "   3. Wired Network > Test Xbox Live.\n\n"
    "  WI-FI (Slim / E have it built in):\n"
    "   1. Network Settings > pick your network.\n"
    "   2. Enter the password, then test it.\n",

    "  * Red rings / E74: overheating or GPU fault.\n"
    "    Power off, cool down, check the vents.\n"
    "  * Disc not read: clean it or try another.\n"
    "  * No internet: reboot router + console,\n"
    "    set DNS and IP to automatic.\n"
};

static void progress(int cur)
{
    int i, filled = cur * 40 / (SLIDES - 1);
    color(GREY);  printf("  [");
    for (i = 0; i < 40; i++) { color(i < filled ? GREEN : DGREEN); putchar(i < filled ? '#' : '-'); }
    color(GREY);  printf("]  %d/%d\n", cur + 1, SLIDES);
}

static void draw_title(int frame)
{
    console_clrscr();
    confetti();
    rule('=', DGREEN);
    center("X B O X   3 6 0", GREEN);
    rule('=', DGREEN);
    putchar('\n');
    center("Stepa, s dnyom rozhdeniya!", YELLOW);
    center("HAPPY BIRTHDAY, STEPA!", PINK);
    putchar('\n');
    cake(frame);
    putchar('\n');
    center("Here is what you need to know about taking", WHITE);
    center("care of this console, plus tips on where to", WHITE);
    center("get games and how to get online.", WHITE);
    putchar('\n');
    if (frame % 2 == 0) center("[ Press A to Continue ]", GREEN);
    else putchar('\n');
    confetti();
}

static void draw_slide(int i)
{
    console_clrscr();
    rule('=', DGREEN);
    center("XBOX 360  *  GUIDE FOR STEPA", GREEN);
    rule('=', DGREEN);
    color(YELLOW);
    printf("\n  >> %s\n", title[i]);
    rule('-', DGREEN);
    color(WHITE);
    printf("\n%s\n", body[i]);
    rule('-', DGREEN);
    progress(i);
    color(GREY);
    printf("  A = Next    B = Back    Start = Exit\n");
    rule('=', DGREEN);
}

static void draw_final(int frame)
{
    console_clrscr();
    confetti();
    rule('=', DGREEN);
    center("HAPPY BIRTHDAY, STEPA!", PINK);
    rule('=', DGREEN);
    putchar('\n');
    cake(frame);
    putchar('\n');
    center("Enjoy the games, keep it cool and clean.", WHITE);
    center("With love, your friend Ilya", YELLOW);
    putchar('\n');
    color(GREY);
    center("B = Back    Start = Exit", GREY);
    confetti();
}

static void redraw(int cur, int frame)
{
    if (cur == 0) draw_title(frame);
    else if (cur == SLIDES) draw_final(frame);
    else draw_slide(cur);
}

int main(void)
{
    xenos_init(VIDEO_MODE_AUTO);
    console_init();
    usb_init();
    usb_do_poll();

    int cur = 0, frame = 0, tick = 0, prevN = 0, prevB = 0;
    redraw(cur, frame);

    while (1) {
        struct controller_data_s c;
        usb_do_poll();
        if (get_controller_data(&c, 0)) {
            int n = c.a || c.right;
            int b = c.b || c.left;
            if (n && !prevN && cur < SLIDES) { cur++; redraw(cur, frame); }
            if (b && !prevB && cur > 0)      { cur--; redraw(cur, frame); }
            prevN = n;
            prevB = b;
            if (c.start) break;
        }
        mdelay(30);
        if ((cur == 0 || cur == SLIDES) && ++tick >= 12) {
            tick = 0;
            frame++;
            redraw(cur, frame);
        }
    }
    return 0;
}
