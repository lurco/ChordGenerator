#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ncurses.h>
#include<errno.h>
#include<time.h>

#include<gsl/gsl_rng.h>			/* biblioteka GSL: Random Number Generators */
#include<gsl/gsl_randist.h>		/* biblioteka GSL: Random Number Distributions */


extern int errno;

void wait(int centiseconds);

int main() {/*****************************************************************************************************************/

int errnum = 0;

char ROOT[16][3] = {"Ab", "A", "B", "H", "C", "C#", "Db", "D", "D#", "Eb", "E", "F", "F#", "Gb", "G", "G#"}; 	/* No. of strings X maximimum length + 1 */
char CHORD[6][4] = {"M", "m", "dim", "M7", "m7", "7"}; 	/// "m7b5", "dim7", "sus2", "sus4"};
/* Inicjalizacja RNG */
gsl_rng * RNG;
const gsl_rng_type * RNGtype;
gsl_rng_env_setup(); // Ładuje RNG i SEED ze zmiennych środowiskowych: GSL_RNG_TYPE i GSL_RNG_SEED

RNGtype = gsl_rng_default;
RNG = gsl_rng_alloc(RNGtype); // domyślnie: GSL_RNG_TYPE = Mersenne Twister ('mt19937')
	if (RNG == NULL) {
	errnum = errno;
	perror("Błąd");
	fprintf(stderr, "\nWartość błędu: %i\n", errnum);
	exit(-1);
	}
	
	int root=0;
	int chord=0;
	int play = 1;
	int timed = 0;
	char C;
initscr();
raw();
keypad(stdscr,TRUE);
noecho();

while(play == 1)
	{
	root = gsl_rng_uniform_int(RNG, 16);
	chord = gsl_rng_uniform_int(RNG, 6);

	clear();
	printw("Press q to quit or any other key to generate a new chord\n");
	printw("========================================================\n");
	printw("\n");
	printw("%s%s", ROOT[root], CHORD[chord]);
	refresh();
	if(timed == 1) wait(400);
	if(timed == 0) {
		C = getchar();
		switch(C) {
		case 'q':
			play = 0; endwin();
			break;
		case 't':
			timed = 1;
			break;
		}
	}
	}
gsl_rng_free(RNG);
}  /******************************************************************************************************************************/


void wait(int centiseconds)	{
clock_t end_wait = clock() + (centiseconds/100) * CLOCKS_PER_SEC;

while(clock() < end_wait);

}


