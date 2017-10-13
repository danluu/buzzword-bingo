/* Buzzword Bingo
 * 
 * Don't use more than 4 words in each bingo phrase (that's
 * 3 spaces).  As coded, the program takes an optional numeric
 * parameter (with none given, it uses 1), and produces that
 * many random bingo cardpairs.  It writes a file called bingo.ps,
 * and sends it to the lp program.  To change that behavior, look
 * at the final few lines in this file.  bingo.ps is in PostScript
 * format.
 * 
 * Please distribute this program to anyone who "needs" it.
 * 
 * I've got an action item to fix the problems above, but I've got
 * a lot of cutting edge problems on my plate, and my guesstimate
 * is that I won't have time to work the issue before my drop dead
 * date.  Buzzword bingo is only a 90% solution, so do the right thing,
 * take the challenge, and make it happen.  The ball's in your court.
 * 
 * Tom Davis
 * Silicon Graphics, Inc.
 * February, 1993
 * 
 */

#include <time.h>
#include <stdio.h>

FILE *f;

char *buzzwords[] = {
    "Action Item", 
    "Alpha Release", 
    "Attack The Problem", 
    "Ball's In Your Court", 
    "Bandwidth", 
    "Big Win", 
    "Bite The Bullet",
    "Blows Them Away",  
    "Challenge", 
    "Close The Loop", 
    "Collateral", 
    "Context Switch", 
    "Core Competency", 
    "Critical Path", 
    "Culture Change", 
    "Customer Focus", 
    "Cutting Edge", 
    "Deliverables", 
    "Dialogue With",
    "Disincent", 
    "Do The Right Thing", 
    "Drop Dead Date", 
    "Empowerment",
    "Execution", 
    "Feedback", 
    "First Class", 
    "Focus",
    "Functionality Freeze", 
    "GUI", 
    "Going Forward", 
    "Gold Star", 
    "Guesstimate", 
    "Impact (v.)", 
    "Incent (v.)", 
    "Interface", 
    "Issue", 
    "Key Players", 
    "Kick-Ass Graphics", 
    "Knock Your Socks Off", 
    "Leading Edge", 
    "Leverage", 
    "Make It Happen",
    "Massively Parallel", 
    "Mind Blowing",  
    "Mindshare",
    "Neophyte",
    "Object Oriented", 
    "Offline", 
    "On Board", 
    "On Your Plate", 
    "One On One", 
    "Opportunity", 
    "Out Of The Loop",
    "Paradigm Shift", 
    "Pass The Baton", 
    "Price Point", 
    "Proactive", 
    "Productized", 
    "Raise A Flag", 
    "Rathole", 
    "Reference (v.)",
    "Resolution",
    "Revolutionary", 
    "Ride The Wave",  
    "Sanity Check", 
    "Scenarios", 
    "Signage",
    "Sign Off On",
    "Skillset",
    "Solution",
    "Standard", 
    "State Of The Art", 
    "Story",
    "Synergy", 
    "Take The Initiative", 
    "Talk To The Issue", 
    "Tangent", 
    "Team Building", 
    "Team Player", 
    "Time Frame", 
    "Touch Base", 
    "Transition (v.)",
    "Up To Speed",  
    "User Friendly",
    "Utilize", 
    "Wearing Different Hats", 
    "Whatever It Takes", 
    "Win-Win", 
    "Working The Issue", 
    "World Class", 
    "WYSIWYG",
};

long buzzlen = sizeof(buzzwords)/sizeof(long);

void centertext(long i, long j, long k)
{
    long spaces = 0;
    char *s = buzzwords[k], *t;
    while (*s) if (*s++ == ' ') spaces++;
    switch (spaces) {
	case 0:
	    fprintf(f, "%d %d (%s) centertext\n", i, j, buzzwords[k]);
	    break;
	case 1:
	    s = t = buzzwords[k];
	    while (*s != ' ') s++;
	    *s = 0;
	    fprintf(f, "%d %d (%s) centertext\n", i, j+6, t);
	    *s = ' ';
	    fprintf(f, "%d %d (%s) centertext\n", i, j-6, s+1);
	    break;
	case 2:
	    s = t = buzzwords[k];
	    while (*s != ' ') s++;
	    *s = 0;
	    fprintf(f, "%d %d (%s) centertext\n", i, j+12, t);
	    *s = ' ';
	    t = s+1; s++;
	    while (*s != ' ') s++;
	    *s = 0;
	    fprintf(f, "%d %d (%s) centertext\n", i, j, t);
	    *s = ' ';
	    fprintf(f, "%d %d (%s) centertext\n", i, j-12, s+1);
	    break;
	case 3:
	    s = t = buzzwords[k];
	    while (*s != ' ') s++;
	    *s = 0;
	    fprintf(f, "%d %d (%s) centertext\n", i, j+18, t);
	    *s = ' ';
	    t = s+1; s++;
	    while (*s != ' ') s++;
	    *s = 0;
	    fprintf(f, "%d %d (%s) centertext\n", i, j+6, t);
	    *s = ' ';
	    t = s+1; s++;
	    while (*s != ' ') s++;
	    *s = 0;
	    fprintf(f, "%d %d (%s) centertext\n", i, j-6, t);
	    *s = ' ';
	    fprintf(f, "%d %d (%s) centertext\n", i, j-18, s+1);
	    break;
	case 4:
	    fprintf(stderr, "Fucked up data -- more than 4 words\n");
	    exit(0);
    }
}

void gendata()
{
    long i, j, k;
    long index[200];
    
    for (i = 0; i < 200; i++) index[i] = 0;
    for (i = 36; i < 360; i += 72)
	for (j = 36; j < 360; j += 72) {
	    if (i != 180 || j != 180) {
		while (index[k = rand() % buzzlen] == 1) ;
		centertext(i, j, k);
		index[k] = 1;
	    }
	}
}

void dumpcard()
{
fprintf(f, "/centertext {\n");
fprintf(f, "    dup stringwidth\n");
fprintf(f, "    3 index exch sub\n");
fprintf(f, "    exch 2 div 4 index exch sub exch\n");
fprintf(f, "    moveto show pop pop\n");
fprintf(f, "} bind def\n");
fprintf(f, "gsave\n");
fprintf(f, "90 rotate 18 -500 translate\n");
fprintf(f, "/Times-Roman findfont 30 scalefont setfont\n");
fprintf(f, "40 390 moveto (SGI Buzzword Bingo) show\n");
fprintf(f, "/Times-Roman findfont 18 scalefont setfont\n");
fprintf(f, "155 175 moveto (FREE) show\n");
fprintf(f, "/Times-Roman findfont 10 scalefont setfont\n");
fprintf(f, "0 -10 moveto (In meetings, mark squares as each buzzword is used.) show\n");
fprintf(f, "0 -20 moveto (Use only buzzwords uttered by others.) show\n");
gendata();
fprintf(f, "0 72 360 {\n");
fprintf(f, "    dup 0 moveto 360 lineto stroke\n");
fprintf(f, "} for\n");
fprintf(f, "0 72 360 {\n");
fprintf(f, "    dup 0 exch moveto 360 exch lineto stroke\n");
fprintf(f, "} for\n");
fprintf(f, "grestore\n");
fprintf(f, "gsave\n");
fprintf(f, "90 rotate 414 -500 translate\n");
fprintf(f, "/Times-Roman findfont 30 scalefont setfont\n");
fprintf(f, "40 390 moveto (SGI Buzzword Bingo) show\n");
fprintf(f, "/Times-Roman findfont 18 scalefont setfont\n");
fprintf(f, "155 175 moveto (FREE) show\n");
fprintf(f, "/Times-Roman findfont 10 scalefont setfont\n");
fprintf(f, "0 -10 moveto (In meetings, mark squares as each buzzword is used.) show\n");
fprintf(f, "0 -20 moveto (Use only buzzwords uttered by others.) show\n");
gendata();
fprintf(f, "0 72 360 {\n");
fprintf(f, "    dup 0 moveto 360 lineto stroke\n");
fprintf(f, "} for\n");
fprintf(f, "0 72 360 {\n");
fprintf(f, "    dup 0 exch moveto 360 exch lineto stroke\n");
fprintf(f, "} for\n");
fprintf(f, "grestore\n");
fprintf(f, "showpage\n");
}

main(int argc, char **argv)
{
    long cardcount, i;

    srand(time(0));
    f = fopen("bingo.ps", "w");
    if (argc == 2) {
	cardcount = atoi(argv[1]);
    } else {
        cardcount = 1;
	fprintf(stderr, "'bingo n' makes n pages\n");
    }
    fprintf(f, "%%!\n");
    for (i = 0; i < cardcount; i++)
	dumpcard();
    fclose(f);
/*    system("lp bingo.ps");*/
}
