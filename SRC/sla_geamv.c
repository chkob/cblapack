/* sla_geamv.f -- translated by f2c (version 20061008).
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

/* Subroutine */ int sla_geamv__(integer *trans, integer *m, integer *n, real 
	*alpha, real *a, integer *lda, real *x, integer *incx, real *beta, 
	real *y, integer *incy)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2;
    real r__1;

    /* Local variables */
    integer i__, j;
    logical symb_zero__;
    integer iy, jx, kx, ky, info;
    real temp;
    integer lenx, leny;
    real safe1;

/*     -- LAPACK routine (version 3.2)                                 -- */
/*     -- Contributed by James Demmel, Deaglan Halligan, Yozo Hida and -- */
/*     -- Jason Riedy of Univ. of California Berkeley.                 -- */
/*     -- November 2008                                                -- */

/*     -- LAPACK is a software package provided by Univ. of Tennessee, -- */
/*     -- Univ. of California Berkeley and NAG Ltd.                    -- */

/*  Purpose */
/*  ======= */

/*  SLA_GEAMV  performs one of the matrix-vector operations */

/*          y := alpha*abs(A)*abs(x) + beta*abs(y), */
/*     or   y := alpha*abs(A)'*abs(x) + beta*abs(y), */

/*  where alpha and beta are scalars, x and y are vectors and A is an */
/*  m by n matrix. */

/*  This function is primarily used in calculating error bounds. */
/*  To protect against underflow during evaluation, components in */
/*  the resulting vector are perturbed away from zero by (N+1) */
/*  times the underflow threshold.  To prevent unnecessarily large */
/*  errors for block-structure embedded in general matrices, */
/*  "symbolically" zero components are not perturbed.  A zero */
/*  entry is considered "symbolic" if all multiplications involved */
/*  in computing that entry have at least one zero multiplicand. */

/*  Parameters */
/*  ========== */

/*  TRANS  - INTEGER */
/*           On entry, TRANS specifies the operation to be performed as */
/*           follows: */

/*             BLAS_NO_TRANS      y := alpha*abs(A)*abs(x) + beta*abs(y) */
/*             BLAS_TRANS         y := alpha*abs(A')*abs(x) + beta*abs(y) */
/*             BLAS_CONJ_TRANS    y := alpha*abs(A')*abs(x) + beta*abs(y) */

/*           Unchanged on exit. */

/*  M      - INTEGER */
/*           On entry, M specifies the number of rows of the matrix A. */
/*           M must be at least zero. */
/*           Unchanged on exit. */

/*  N      - INTEGER */
/*           On entry, N specifies the number of columns of the matrix A. */
/*           N must be at least zero. */
/*           Unchanged on exit. */

/*  ALPHA  - REAL */
/*           On entry, ALPHA specifies the scalar alpha. */
/*           Unchanged on exit. */

/*  A      - REAL             array of DIMENSION ( LDA, n ) */
/*           Before entry, the leading m by n part of the array A must */
/*           contain the matrix of coefficients. */
/*           Unchanged on exit. */

/*  LDA    - INTEGER */
/*           On entry, LDA specifies the first dimension of A as declared */
/*           in the calling (sub) program. LDA must be at least */
/*           max( 1, m ). */
/*           Unchanged on exit. */

/*  X      - REAL             array of DIMENSION at least */
/*           ( 1 + ( n - 1 )*abs( INCX ) ) when TRANS = 'N' or 'n' */
/*           and at least */
/*           ( 1 + ( m - 1 )*abs( INCX ) ) otherwise. */
/*           Before entry, the incremented array X must contain the */
/*           vector x. */
/*           Unchanged on exit. */

/*  INCX   - INTEGER */
/*           On entry, INCX specifies the increment for the elements of */
/*           X. INCX must not be zero. */
/*           Unchanged on exit. */

/*  BETA   - REAL */
/*           On entry, BETA specifies the scalar beta. When BETA is */
/*           supplied as zero then Y need not be set on input. */
/*           Unchanged on exit. */

/*  Y      - REAL */
/*           Array of DIMENSION at least */
/*           ( 1 + ( m - 1 )*abs( INCY ) ) when TRANS = 'N' or 'n' */
/*           and at least */
/*           ( 1 + ( n - 1 )*abs( INCY ) ) otherwise. */
/*           Before entry with BETA non-zero, the incremented array Y */
/*           must contain the vector y. On exit, Y is overwritten by the */
/*           updated vector y. */

/*  INCY   - INTEGER */
/*           On entry, INCY specifies the increment for the elements of */
/*           Y. INCY must not be zero. */
/*           Unchanged on exit. */

/*  Level 2 Blas routine. */

/*     Test the input parameters. */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --x;
    --y;

    /* Function Body */
    info = 0;
    if (! (*trans == ilatrans_("N") || *trans == ilatrans_("T") || *trans == ilatrans_("C"))) {
	info = 1;
    } else if (*m < 0) {
	info = 2;
    } else if (*n < 0) {
	info = 3;
    } else if (*lda < max(1,*m)) {
	info = 6;
    } else if (*incx == 0) {
	info = 8;
    } else if (*incy == 0) {
	info = 11;
    }
    if (info != 0) {
	xerbla_("SLA_GEAMV ", &info);
	return 0;
    }

/*     Quick return if possible. */

    if (*m == 0 || *n == 0 || *alpha == 0.f && *beta == 1.f) {
	return 0;
    }

/*     Set  LENX  and  LENY, the lengths of the vectors x and y, and set */
/*     up the start points in  X  and  Y. */

    if (*trans == ilatrans_("N")) {
	lenx = *n;
	leny = *m;
    } else {
	lenx = *m;
	leny = *n;
    }
    if (*incx > 0) {
	kx = 1;
    } else {
	kx = 1 - (lenx - 1) * *incx;
    }
    if (*incy > 0) {
	ky = 1;
    } else {
	ky = 1 - (leny - 1) * *incy;
    }

/*     Set SAFE1 essentially to be the underflow threshold times the */
/*     number of additions in each row. */

    safe1 = slamch_("Safe minimum");
    safe1 = (*n + 1) * safe1;

/*     Form  y := alpha*abs(A)*abs(x) + beta*abs(y). */

/*     The O(M*N) SYMB_ZERO tests could be replaced by O(N) queries to */
/*     the inexact flag.  Still doesn't help change the iteration order */
/*     to per-column. */

    iy = ky;
    if (*incx == 1) {
	i__1 = leny;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    if (*beta == 0.f) {
		symb_zero__ = TRUE_;
		y[iy] = 0.f;
	    } else if (y[iy] == 0.f) {
		symb_zero__ = TRUE_;
	    } else {
		symb_zero__ = FALSE_;
		y[iy] = *beta * (r__1 = y[iy], dabs(r__1));
	    }
	    if (*alpha != 0.f) {
		i__2 = lenx;
		for (j = 1; j <= i__2; ++j) {
		    if (*trans == ilatrans_("N")) {
			temp = (r__1 = a[i__ + j * a_dim1], dabs(r__1));
		    } else {
			temp = (r__1 = a[j + i__ * a_dim1], dabs(r__1));
		    }
		    symb_zero__ = symb_zero__ && (x[j] == 0.f || temp == 0.f);
		    y[iy] += *alpha * (r__1 = x[j], dabs(r__1)) * temp;
		}
	    }
	    if (! symb_zero__) {
		y[iy] += r_sign(&safe1, &y[iy]);
	    }
	    iy += *incy;
	}
    } else {
	i__1 = leny;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    if (*beta == 0.f) {
		symb_zero__ = TRUE_;
		y[iy] = 0.f;
	    } else if (y[iy] == 0.f) {
		symb_zero__ = TRUE_;
	    } else {
		symb_zero__ = FALSE_;
		y[iy] = *beta * (r__1 = y[iy], dabs(r__1));
	    }
	    if (*alpha != 0.f) {
		jx = kx;
		i__2 = lenx;
		for (j = 1; j <= i__2; ++j) {
		    if (*trans == ilatrans_("N")) {
			temp = (r__1 = a[i__ + j * a_dim1], dabs(r__1));
		    } else {
			temp = (r__1 = a[j + i__ * a_dim1], dabs(r__1));
		    }
		    symb_zero__ = symb_zero__ && (x[jx] == 0.f || temp == 0.f)
			    ;
		    y[iy] += *alpha * (r__1 = x[jx], dabs(r__1)) * temp;
		    jx += *incx;
		}
	    }
	    if (! symb_zero__) {
		y[iy] += r_sign(&safe1, &y[iy]);
	    }
	    iy += *incy;
	}
    }

    return 0;

/*     End of SLA_GEAMV */

} /* sla_geamv__ */
