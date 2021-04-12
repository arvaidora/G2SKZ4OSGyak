#include <unistd.h>
#include <signal.h>

void do_nothing();

main ()
{
	signal(SIGALRM, do_nothing);
	printf("  %d Varok de meddig?\n");
	pause();
    	printf("  Itt az alarm \n");
}	
void do_nothing(){ ;}