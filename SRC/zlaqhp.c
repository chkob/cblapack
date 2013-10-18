/* zlaqhp.f -- translated by f2c (version 20061008).
   You must link the resulting object file with libf2c:
	on Microsoft Windows system, link with libf2c.lib;
	on Linux or Unix systems, link with .../path/to/libf2c.a -lm
	or, if you install libf2c.a in a standard place, with -lf2c -lm
	-- in that order, at the end of the command line, as in
		cc *.o -lf2c -lm
	Source for libf2c is in /netlib/f2c/libf2c.zip, e.g.,

		http://www.netlib.org/f2c/libf2c.zip
*/

#include "f2c.h"
#include "blaswrap.h"

/* Subroutine */ int zlaqhp_(char *uplo, integer *n, doublecomplex *ap, 
	doublereal *s, doublereal *scond, doublereal *amax, char *equed)
{
    /* System generated locals */
    integer i__1, i__2, i__3, i__4;
    doublereal d__1;
    doublecomplex z__1;

    /* Local variables */
    integer i__, j, jc;
    doublereal cj, large;
    doublereal small;

/*  -- LAPACK auxiliary routine (version 3.2) -- */
/*     November 2006 */

/*  Purpose */
/*  ======= */

/*  ZLAQHP equilibrates a Hermitian matrix A using the scaling factors */
/*  in the vector S. */

/*  Arguments */
/*  ========= */

/*  UPLO    (input) CHARACTER*1 */
/*          Specifies whether the upper or lower triangular part of the */
/*          Hermitian matrix A is stored. */
/*          = 'U':  Upper triangular */
/*          = 'L':  Lower triangular */

/*  N       (input) INTEGER */
/*          The order of the matrix A.  N >= 0. */

/*  AP      (input/output) COMPLEX*16 array, dimension (N*(N+1)/2) */
/*          On entry, the upper or lower triangle of the Hermitian matrix */
/*          A, packed columnwise in a linear array.  The j-th column of A */
/*          is stored in the array AP as follows: */
/*          if UPLO = 'U', AP(i + (j-1)*j/2) = A(i,j) for 1<=i<=j; */
/*          if UPLO = 'L', AP(i + (j-1)*(2n-j)/2) = A(i,j) for j<=i<=n. */

/*          On exit, the equilibrated matrix:  diag(S) * A * diag(S), in */
/*          the same storage format as A. */

/*  S       (input) DOUBLE PRECISION array, dimension (N) */
/*          The scale factors for A. */

/*  SCOND   (input) DOUBLE PRECISION */
/*          Ratio of the smallest S(i) to the largest S(i). */

/*  AMAX    (input) DOUBLE PRECISION */
/*          Absolute value of largest matrix entry. */

/*  EQUED   (output) CHARACTER*1 */
/*          Specifies whether or not equilibration was done. */
/*          = 'N':  No equilibration. */
/*          = 'Y':  Equilibration was done, i.e., A has been replaced by */
/*                  diag(S) * A * diag(S). */

/*  Internal Parameters */
/*  =================== */

/*  THRESH is a threshold value used to decide if scaling should be done */
/*  based on the ratio of the scaling factors.  If SCOND < THRESH, */
/*  scaling is done. */

/*  LARGE and SMALL are threshold values used to decide if scaling should */
/*  be done based on the absolute size of the largest matrix element. */
/*  If AMAX > LARGE or AMAX < SMALL, scaling is done. */

/*  ===================================================================== */

/*     Quick return if possible */

    /* Parameter adjustments */
    --s;
    --ap;

    /* Function Body */
    if (*n <= 0) {
	*(unsigned char *)equed = 'N';
	return 0;
    }

/*     Initialize LARGE and SMALL. */

    small = dlamch_("Safe minimum") / dlamch_("Precision");
    large = 1. / small;

    if (*scond >= .1 && *amax >= small && *amax <= large) {

/*        No equilibration */

	*(unsigned char *)equed = 'N';
    } else {

/*        Replace A by diag(S) * A * diag(S). */

	if (lsame_(uplo, "U")) {

/*           Upper triangle of A is stored. */

	    jc = 1;
	    i__1 = *n;
	    for (j = 1; j <= i__1; ++j) {
		cj = s[j];
		i__2 = j - 1;
		for (i__ = 1; i__ <= i__2; ++i__) {
		    i__3 = jc + i__ - 1;
		    d__1 = cj * s[i__];
		    i__4 = jc + i__ - 1;
		    z__1.r = d__1 * ap[i__4].r, z__1.i = d__1 * ap[i__4].i;
		    ap[i__3].r = z__1.r, ap[i__3].i = z__1.i;
		}
		i__2 = jc + j - 1;
		i__3 = jc + j - 1;
		d__1 = cj * cj * ap[i__3].r;
		ap[i__2].r = d__1, ap[i__2].i = 0.;
		jc += j;
	    }
	} else {

/*           Lower triangle of A is stored. */

	    jc = 1;
	    i__1 = *n;
	    for (j = 1; j <= i__1; ++j) {
		cj = s[j];
		i__2 = jc;
		i__3 = jc;
		d__1 = cj * cj * ap[i__3].r;
		ap[i__2].r = d__1, ap[i__2].i = 0.;
		i__2 = *n;
		for (i__ = j + 1; i__ <= i__2; ++i__) {
		    i__3 = jc + i__ - j;
		    d__1 = cj * s[i__];
		    i__4 = jc + i__ - j;
		    z__1.r = d__1 * ap[i__4].r, z__1.i = d__1 * ap[i__4].i;
		    ap[i__3].r = z__1.r, ap[i__3].i = z__1.i;
		}
		jc = jc + *n - j + 1;
	    }
	}
	*(unsigned char *)equed = 'Y';
    }

    return 0;

/*     End of ZLAQHP */

} /* zlaqhp_ */
