#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static void
totime(int val, char sep)
{
    int dy = val / (60*24);
    int hr = (val / 60) % 24;
    int mn = val % 60;

    if ( dy > 0 )
	printf("%d ", dy);
    if ( dy > 0 || hr > 0 )
	printf("%d%c", hr, sep);
    printf("%02d", mn);
}


static void
openclose(int start, float open, float close)
{
    if ( start > 0 ) {
	printf("open "); totime(start + open, ':');
	printf(" / close "); totime(start + close, ':');
    }
    else {
	printf("open +"); totime((int)open, 'h');
	printf(" / close +"); totime((int)close, 'h');
    }
    putchar('\n');
}


int
main(argc, argv)
char **argv;
{
    int x;
    int miles;
    int km;
    float val;
    int hr = 0, min = 0;

    if ( (argc > 1) && sscanf(argv[1], "%d:%02d", &hr, &min) == 2 ) {
	++argv, --argc;
	min += (hr*60);
    }

    for ( x=1; x<argc; x++ ) {
	int e = strlen(argv[x])-1;

	miles = 0;
	if ( e > 0 ) {
	    switch ( argv[x][e] ) {
	    case 'm': case 'M':
		if ( e > 1 && (argv[x][e-1] == 'k' || argv[x][e-1] == 'K') )
		    break;
		miles = 1; break;
	    case 'k': case 'K':
	    case '0': case '1': case '2': case '3': case '4':
	    case '5': case '6': case '7': case '8': case '9':
	    case '.':
		break;
	    default:
		fprintf(stderr, "malformed distance <%s>\n", argv[x]);
		continue;
	    }
	}

	if ( sscanf(argv[x], "%f", &val) != 1 ) {
	    fprintf(stderr, "malformed distance <%s>\n", argv[x]);
	    continue;
	}

	if ( miles )
	    val /= 0.621;

	printf("%.8s: ", argv[x]);
	if ( val < 1 )
	    openclose(min, 0.0, 60.0);
	else
	    openclose(min, val * 2, val * 4 );
    }
    exit(0);
}
