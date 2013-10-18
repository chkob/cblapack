/* spoequb.f -- translated by f2c (version 20061008).
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

/* Subroutine */ int spoequb_(integer *n, real *a, integer *lda, real *s, 
	real *scond, real *amax, integer *info)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2;
    real r__1, r__2;

    /* Local variables */
    integer i__;
    real tmp, base, smin;

/*     -- LAPACK routine (version 3.2)                                 -- */
/*     -- Contributed by James Demmel, Deaglan Halligan, Yozo Hida and -- */
/*     -- Jason Riedy of Univ. of California Berkeley.                 -- */
/*     -- November 2008                                                -- */

/*     -- LAPACK is a software package provided by Univ. of Tennessee, -- */
/*     -- Univ. of California Berkeley and NAG Ltd.                    -- */

/*  Purpose */
/*  ======= */

/*  SPOEQU computes row and column scalings intended to equilibrate a */
/*  symmetric positive definite matrix A and reduce its condition number */
/*  (with respect to the two-norm).  S contains the scale factors, */
/*  S(i) = 1/sqrt(A(i,i)), chosen so that the scaled matrix B with */
/*  elements B(i,j) = S(i)*A(i,j)*S(j) has ones on the diagonal.  This */
/*  choice of S puts the condition number of B within a factor N of the */
/*  smallest possible condition number over all possible diagonal */
/*  scalings. */

/*  Arguments */
/*  ========= */

/*  N       (input) INTEGER */
/*          The order of the matrix A.  N >= 0. */

/*  A       (input) REAL array, dimension (LDA,N) */
/*          The N-by-N symmetric positive definite matrix whose scaling */
/*          factors are to be computed.  Only the diagonal elements of A */
/*          are referenced. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A.  LDA >= max(1,N). */

/*  S       (output) REAL array, dimension (N) */
/*          If INFO = 0, S contains the scale factors for A. */

/*  SCOND   (output) REAL */
/*          If INFO = 0, S contains the ratio of the smallest S(i) to */
/*          the largest S(i).  If SCOND >= 0.1 and AMAX is neither too */
/*          large nor too small, it is not worth scaling by S. */

/*  AMAX    (output) REAL */
/*          Absolute value of largest matrix element.  If AMAX is very */
/*          close to overflow or very close to underflow, the matrix */
/*          should be scaled. */

/*  INFO    (output) INTEGER */
/*          = 0:  successful exit */
/*          < 0:  if INFO = -i, the i-th argument had an illegal value */
/*          > 0:  if INFO = i, the i-th diagonal element is nonpositive. */

/*  ===================================================================== */

/*     Test the input parameters. */

/*     Positive definite only performs 1 pass of equilibration. */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --s;

    /* Function Body */
    *info = 0;
    if (*n < 0) {
	*info = -1;
    } else if (*lda < max(1,*n)) {
	*info = -3;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("SPOEQUB", &i__1);
	return 0;
    }

/*     Quick return if possible. */

    if (*n == 0) {
	*scond = 1.f;
	*amax = 0.f;
	return 0;
    }
    base = slamch_("B");
    tmp = -.5f / log(base);

/*     Find the minimum and maximum diagonal elements. */

    s[1] = a[a_dim1 + 1];
    smin = s[1];
    *amax = s[1];
    i__1 = *n;
    for (i__ = 2; i__ <= i__1; ++i__) {
	s[i__] = a[i__ + i__ * a_dim1];
/* Computing MIN */
	r__1 = smin, r__2 = s[i__];
	smin = dmin(r__1,r__2);
/* Computing MAX */
	r__1 = *amax, r__2 = s[i__];
	*amax = dmax(r__1,r__2);
    }

    if (smin <= 0.f) {

/*        Find the first non-positive diagonal element and return. */

	i__1 = *n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    if (s[i__] <= 0.f) {
		*info = i__;
		return 0;
	    }
	}
    } else {

/*        Set the scale factors to the reciprocals */
/*        of the diagonal elements. */

	i__1 = *n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    i__2 = (integer) (tmp * log(s[i__]));
	    s[i__] = pow_ri(&base, &i__2);
	}

/*        Compute SCOND = min(S(I)) / max(S(I)). */

	*scond = sqrt(smin) / sqrt(*amax);
    }

    return 0;

/*     End of SPOEQUB */

} /* spoequb_ */
