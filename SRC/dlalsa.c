/* dlalsa.f -- translated by f2c (version 20061008).
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

/* Table of constant values */

static doublereal c_b7 = 1.;
static doublereal c_b8 = 0.;
static integer c__2 = 2;

/* Subroutine */ int dlalsa_(integer *icompq, integer *smlsiz, integer *n, 
	integer *nrhs, doublereal *b, integer *ldb, doublereal *bx, integer *
	ldbx, doublereal *u, integer *ldu, doublereal *vt, integer *k, 
	doublereal *difl, doublereal *difr, doublereal *z__, doublereal *
	poles, integer *givptr, integer *givcol, integer *ldgcol, integer *
	perm, doublereal *givnum, doublereal *c__, doublereal *s, doublereal *
	work, integer *iwork, integer *info)
{
    /* System generated locals */
    integer givcol_dim1, givcol_offset, perm_dim1, perm_offset, b_dim1, 
	    b_offset, bx_dim1, bx_offset, difl_dim1, difl_offset, difr_dim1, 
	    difr_offset, givnum_dim1, givnum_offset, poles_dim1, poles_offset,
	     u_dim1, u_offset, vt_dim1, vt_offset, z_dim1, z_offset, i__1, 
	    i__2;

    /* Local variables */
    integer i__, j, i1, ic, lf, nd, ll, nl, nr, im1, nlf, nrf, lvl, ndb1, 
	    nlp1, lvl2, nrp1, nlvl, sqre;
    integer inode, ndiml, ndimr;

/*  -- LAPACK routine (version 3.2) -- */
/*     November 2006 */

/*  Purpose */
/*  ======= */

/*  DLALSA is an itermediate step in solving the least squares problem */
/*  by computing the SVD of the coefficient matrix in compact form (The */
/*  singular vectors are computed as products of simple orthorgonal */
/*  matrices.). */

/*  If ICOMPQ = 0, DLALSA applies the inverse of the left singular vector */
/*  matrix of an upper bidiagonal matrix to the right hand side; and if */
/*  ICOMPQ = 1, DLALSA applies the right singular vector matrix to the */
/*  right hand side. The singular vector matrices were generated in */
/*  compact form by DLALSA. */

/*  Arguments */
/*  ========= */

/*  ICOMPQ (input) INTEGER */
/*         Specifies whether the left or the right singular vector */
/*         matrix is involved. */
/*         = 0: Left singular vector matrix */
/*         = 1: Right singular vector matrix */

/*  SMLSIZ (input) INTEGER */
/*         The maximum size of the subproblems at the bottom of the */
/*         computation tree. */

/*  N      (input) INTEGER */
/*         The row and column dimensions of the upper bidiagonal matrix. */

/*  NRHS   (input) INTEGER */
/*         The number of columns of B and BX. NRHS must be at least 1. */

/*  B      (input/output) DOUBLE PRECISION array, dimension ( LDB, NRHS ) */
/*         On input, B contains the right hand sides of the least */
/*         squares problem in rows 1 through M. */
/*         On output, B contains the solution X in rows 1 through N. */

/*  LDB    (input) INTEGER */
/*         The leading dimension of B in the calling subprogram. */
/*         LDB must be at least max(1,MAX( M, N ) ). */

/*  BX     (output) DOUBLE PRECISION array, dimension ( LDBX, NRHS ) */
/*         On exit, the result of applying the left or right singular */
/*         vector matrix to B. */

/*  LDBX   (input) INTEGER */
/*         The leading dimension of BX. */

/*  U      (input) DOUBLE PRECISION array, dimension ( LDU, SMLSIZ ). */
/*         On entry, U contains the left singular vector matrices of all */
/*         subproblems at the bottom level. */

/*  LDU    (input) INTEGER, LDU = > N. */
/*         The leading dimension of arrays U, VT, DIFL, DIFR, */
/*         POLES, GIVNUM, and Z. */

/*  VT     (input) DOUBLE PRECISION array, dimension ( LDU, SMLSIZ+1 ). */
/*         On entry, VT' contains the right singular vector matrices of */
/*         all subproblems at the bottom level. */

/*  K      (input) INTEGER array, dimension ( N ). */

/*  DIFL   (input) DOUBLE PRECISION array, dimension ( LDU, NLVL ). */
/*         where NLVL = INT(log_2 (N/(SMLSIZ+1))) + 1. */

/*  DIFR   (input) DOUBLE PRECISION array, dimension ( LDU, 2 * NLVL ). */
/*         On entry, DIFL(*, I) and DIFR(*, 2 * I -1) record */
/*         distances between singular values on the I-th level and */
/*         singular values on the (I -1)-th level, and DIFR(*, 2 * I) */
/*         record the normalizing factors of the right singular vectors */
/*         matrices of subproblems on I-th level. */

/*  Z      (input) DOUBLE PRECISION array, dimension ( LDU, NLVL ). */
/*         On entry, Z(1, I) contains the components of the deflation- */
/*         adjusted updating row vector for subproblems on the I-th */
/*         level. */

/*  POLES  (input) DOUBLE PRECISION array, dimension ( LDU, 2 * NLVL ). */
/*         On entry, POLES(*, 2 * I -1: 2 * I) contains the new and old */
/*         singular values involved in the secular equations on the I-th */
/*         level. */

/*  GIVPTR (input) INTEGER array, dimension ( N ). */
/*         On entry, GIVPTR( I ) records the number of Givens */
/*         rotations performed on the I-th problem on the computation */
/*         tree. */

/*  GIVCOL (input) INTEGER array, dimension ( LDGCOL, 2 * NLVL ). */
/*         On entry, for each I, GIVCOL(*, 2 * I - 1: 2 * I) records the */
/*         locations of Givens rotations performed on the I-th level on */
/*         the computation tree. */

/*  LDGCOL (input) INTEGER, LDGCOL = > N. */
/*         The leading dimension of arrays GIVCOL and PERM. */

/*  PERM   (input) INTEGER array, dimension ( LDGCOL, NLVL ). */
/*         On entry, PERM(*, I) records permutations done on the I-th */
/*         level of the computation tree. */

/*  GIVNUM (input) DOUBLE PRECISION array, dimension ( LDU, 2 * NLVL ). */
/*         On entry, GIVNUM(*, 2 *I -1 : 2 * I) records the C- and S- */
/*         values of Givens rotations performed on the I-th level on the */
/*         computation tree. */

/*  C      (input) DOUBLE PRECISION array, dimension ( N ). */
/*         On entry, if the I-th subproblem is not square, */
/*         C( I ) contains the C-value of a Givens rotation related to */
/*         the right null space of the I-th subproblem. */

/*  S      (input) DOUBLE PRECISION array, dimension ( N ). */
/*         On entry, if the I-th subproblem is not square, */
/*         S( I ) contains the S-value of a Givens rotation related to */
/*         the right null space of the I-th subproblem. */

/*  WORK   (workspace) DOUBLE PRECISION array. */
/*         The dimension must be at least N. */

/*  IWORK  (workspace) INTEGER array. */
/*         The dimension must be at least 3 * N */

/*  INFO   (output) INTEGER */
/*          = 0:  successful exit. */
/*          < 0:  if INFO = -i, the i-th argument had an illegal value. */

/*  Further Details */
/*  =============== */

/*  Based on contributions by */
/*     Ming Gu and Ren-Cang Li, Computer Science Division, University of */
/*       California at Berkeley, USA */
/*     Osni Marques, LBNL/NERSC, USA */

/*  ===================================================================== */

/*     Test the input parameters. */

    /* Parameter adjustments */
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1;
    b -= b_offset;
    bx_dim1 = *ldbx;
    bx_offset = 1 + bx_dim1;
    bx -= bx_offset;
    givnum_dim1 = *ldu;
    givnum_offset = 1 + givnum_dim1;
    givnum -= givnum_offset;
    poles_dim1 = *ldu;
    poles_offset = 1 + poles_dim1;
    poles -= poles_offset;
    z_dim1 = *ldu;
    z_offset = 1 + z_dim1;
    z__ -= z_offset;
    difr_dim1 = *ldu;
    difr_offset = 1 + difr_dim1;
    difr -= difr_offset;
    difl_dim1 = *ldu;
    difl_offset = 1 + difl_dim1;
    difl -= difl_offset;
    vt_dim1 = *ldu;
    vt_offset = 1 + vt_dim1;
    vt -= vt_offset;
    u_dim1 = *ldu;
    u_offset = 1 + u_dim1;
    u -= u_offset;
    --k;
    --givptr;
    perm_dim1 = *ldgcol;
    perm_offset = 1 + perm_dim1;
    perm -= perm_offset;
    givcol_dim1 = *ldgcol;
    givcol_offset = 1 + givcol_dim1;
    givcol -= givcol_offset;
    --c__;
    --s;
    --work;
    --iwork;

    /* Function Body */
    *info = 0;

    if (*icompq < 0 || *icompq > 1) {
	*info = -1;
    } else if (*smlsiz < 3) {
	*info = -2;
    } else if (*n < *smlsiz) {
	*info = -3;
    } else if (*nrhs < 1) {
	*info = -4;
    } else if (*ldb < *n) {
	*info = -6;
    } else if (*ldbx < *n) {
	*info = -8;
    } else if (*ldu < *n) {
	*info = -10;
    } else if (*ldgcol < *n) {
	*info = -19;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DLALSA", &i__1);
	return 0;
    }

/*     Book-keeping and  setting up the computation tree. */

    inode = 1;
    ndiml = inode + *n;
    ndimr = ndiml + *n;

    dlasdt_(n, &nlvl, &nd, &iwork[inode], &iwork[ndiml], &iwork[ndimr], 
	    smlsiz);

/*     The following code applies back the left singular vector factors. */
/*     For applying back the right singular vector factors, go to 50. */

    if (*icompq == 1) {
	goto L50;
    }

/*     The nodes on the bottom level of the tree were solved */
/*     by DLASDQ. The corresponding left and right singular vector */
/*     matrices are in explicit form. First apply back the left */
/*     singular vector matrices. */

    ndb1 = (nd + 1) / 2;
    i__1 = nd;
    for (i__ = ndb1; i__ <= i__1; ++i__) {

/*        IC : center row of each node */
/*        NL : number of rows of left  subproblem */
/*        NR : number of rows of right subproblem */
/*        NLF: starting row of the left   subproblem */
/*        NRF: starting row of the right  subproblem */

	i1 = i__ - 1;
	ic = iwork[inode + i1];
	nl = iwork[ndiml + i1];
	nr = iwork[ndimr + i1];
	nlf = ic - nl;
	nrf = ic + 1;
	dgemm_("T", "N", &nl, nrhs, &nl, &c_b7, &u[nlf + u_dim1], ldu, &b[nlf 
		+ b_dim1], ldb, &c_b8, &bx[nlf + bx_dim1], ldbx);
	dgemm_("T", "N", &nr, nrhs, &nr, &c_b7, &u[nrf + u_dim1], ldu, &b[nrf 
		+ b_dim1], ldb, &c_b8, &bx[nrf + bx_dim1], ldbx);
    }

/*     Next copy the rows of B that correspond to unchanged rows */
/*     in the bidiagonal matrix to BX. */

    i__1 = nd;
    for (i__ = 1; i__ <= i__1; ++i__) {
	ic = iwork[inode + i__ - 1];
	dcopy_(nrhs, &b[ic + b_dim1], ldb, &bx[ic + bx_dim1], ldbx);
    }

/*     Finally go through the left singular vector matrices of all */
/*     the other subproblems bottom-up on the tree. */

    j = pow_ii(&c__2, &nlvl);
    sqre = 0;

    for (lvl = nlvl; lvl >= 1; --lvl) {
	lvl2 = (lvl << 1) - 1;

/*        find the first node LF and last node LL on */
/*        the current level LVL */

	if (lvl == 1) {
	    lf = 1;
	    ll = 1;
	} else {
	    i__1 = lvl - 1;
	    lf = pow_ii(&c__2, &i__1);
	    ll = (lf << 1) - 1;
	}
	i__1 = ll;
	for (i__ = lf; i__ <= i__1; ++i__) {
	    im1 = i__ - 1;
	    ic = iwork[inode + im1];
	    nl = iwork[ndiml + im1];
	    nr = iwork[ndimr + im1];
	    nlf = ic - nl;
	    nrf = ic + 1;
	    --j;
	    dlals0_(icompq, &nl, &nr, &sqre, nrhs, &bx[nlf + bx_dim1], ldbx, &
		    b[nlf + b_dim1], ldb, &perm[nlf + lvl * perm_dim1], &
		    givptr[j], &givcol[nlf + lvl2 * givcol_dim1], ldgcol, &
		    givnum[nlf + lvl2 * givnum_dim1], ldu, &poles[nlf + lvl2 *
		     poles_dim1], &difl[nlf + lvl * difl_dim1], &difr[nlf + 
		    lvl2 * difr_dim1], &z__[nlf + lvl * z_dim1], &k[j], &c__[
		    j], &s[j], &work[1], info);
	}
    }
    goto L90;

/*     ICOMPQ = 1: applying back the right singular vector factors. */

L50:

/*     First now go through the right singular vector matrices of all */
/*     the tree nodes top-down. */

    j = 0;
    i__1 = nlvl;
    for (lvl = 1; lvl <= i__1; ++lvl) {
	lvl2 = (lvl << 1) - 1;

/*        Find the first node LF and last node LL on */
/*        the current level LVL. */

	if (lvl == 1) {
	    lf = 1;
	    ll = 1;
	} else {
	    i__2 = lvl - 1;
	    lf = pow_ii(&c__2, &i__2);
	    ll = (lf << 1) - 1;
	}
	i__2 = lf;
	for (i__ = ll; i__ >= i__2; --i__) {
	    im1 = i__ - 1;
	    ic = iwork[inode + im1];
	    nl = iwork[ndiml + im1];
	    nr = iwork[ndimr + im1];
	    nlf = ic - nl;
	    nrf = ic + 1;
	    if (i__ == ll) {
		sqre = 0;
	    } else {
		sqre = 1;
	    }
	    ++j;
	    dlals0_(icompq, &nl, &nr, &sqre, nrhs, &b[nlf + b_dim1], ldb, &bx[
		    nlf + bx_dim1], ldbx, &perm[nlf + lvl * perm_dim1], &
		    givptr[j], &givcol[nlf + lvl2 * givcol_dim1], ldgcol, &
		    givnum[nlf + lvl2 * givnum_dim1], ldu, &poles[nlf + lvl2 *
		     poles_dim1], &difl[nlf + lvl * difl_dim1], &difr[nlf + 
		    lvl2 * difr_dim1], &z__[nlf + lvl * z_dim1], &k[j], &c__[
		    j], &s[j], &work[1], info);
	}
    }

/*     The nodes on the bottom level of the tree were solved */
/*     by DLASDQ. The corresponding right singular vector */
/*     matrices are in explicit form. Apply them back. */

    ndb1 = (nd + 1) / 2;
    i__1 = nd;
    for (i__ = ndb1; i__ <= i__1; ++i__) {
	i1 = i__ - 1;
	ic = iwork[inode + i1];
	nl = iwork[ndiml + i1];
	nr = iwork[ndimr + i1];
	nlp1 = nl + 1;
	if (i__ == nd) {
	    nrp1 = nr;
	} else {
	    nrp1 = nr + 1;
	}
	nlf = ic - nl;
	nrf = ic + 1;
	dgemm_("T", "N", &nlp1, nrhs, &nlp1, &c_b7, &vt[nlf + vt_dim1], ldu, &
		b[nlf + b_dim1], ldb, &c_b8, &bx[nlf + bx_dim1], ldbx);
	dgemm_("T", "N", &nrp1, nrhs, &nrp1, &c_b7, &vt[nrf + vt_dim1], ldu, &
		b[nrf + b_dim1], ldb, &c_b8, &bx[nrf + bx_dim1], ldbx);
    }

L90:

    return 0;

/*     End of DLALSA */

} /* dlalsa_ */
