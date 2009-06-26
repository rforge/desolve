/* compile within R with system("R CMD SHLIB Forcing_lv.c") */
/* Example adapted from lsoda help file */
#include <R.h> /* gives F77_CALL through R_ext/RS.h */

static double parms[6];
static double forc[1];

/* A trick to keep up with the parameters and forcings */
#define b parms[0]
#define c parms[1]
#define d parms[2]
#define e parms[3]
#define f parms[4]
#define g parms[5]

#define import forc[0]

/* initializer: same name as the dll (without extension) */
void odec(void (* odeparms)(int *, double *))
{
    int N=6;
    odeparms(&N, parms);
}

void forcc(void (* odeforcs)(int *, double *))
{
    int N=1;
    odeforcs(&N, forc);
    Rprintf("%g\n", DBL_MAX);
}

/* Derivatives */
void derivsc(int *neq, double *t, double *y, double *ydot, double *yout, int*ip)
{
    if (ip[0] <2) error("nout should be at least 2");
    ydot[0] = import - b*y[0]*y[1] + g*y[2]     ;
    ydot[1] = c*y[0]*y[1]  - d*y[2]*y[1]        ;
    
    ydot[2] = e*y[1]*y[2]  - f*y[2]             ;

    yout[0] = y[0]+y[1]+y[2];
    yout[1] = import;
    Rprintf("y %g\t %g\t %g\t %g\t %g\n", *t, y[0], y[1], y[2], import);
}

