extern /* Main program */ int MAIN__(void);
extern /* Subroutine */ int dchk1_(char *sname, doublereal *eps, doublereal *thresh, 
	integer *nout, integer *ntra, logical *trace, logical *rewi, logical *
	fatal, integer *nidim, integer *idim, integer *nalf, doublereal *alf, 
	integer *nbet, doublereal *bet, integer *nmax, doublereal *a, 
	doublereal *aa, doublereal *as, doublereal *b, doublereal *bb, 
	doublereal *bs, doublereal *c__, doublereal *cc, doublereal *cs, 
	doublereal *ct, doublereal *g, ftnlen sname_len);
extern /* Subroutine */ int dchk2_(char *sname, doublereal *eps, doublereal *thresh, 
	integer *nout, integer *ntra, logical *trace, logical *rewi, logical *
	fatal, integer *nidim, integer *idim, integer *nalf, doublereal *alf, 
	integer *nbet, doublereal *bet, integer *nmax, doublereal *a, 
	doublereal *aa, doublereal *as, doublereal *b, doublereal *bb, 
	doublereal *bs, doublereal *c__, doublereal *cc, doublereal *cs, 
	doublereal *ct, doublereal *g, ftnlen sname_len);
extern /* Subroutine */ int dchk3_(char *sname, doublereal *eps, doublereal *thresh, 
	integer *nout, integer *ntra, logical *trace, logical *rewi, logical *
	fatal, integer *nidim, integer *idim, integer *nalf, doublereal *alf, 
	integer *nmax, doublereal *a, doublereal *aa, doublereal *as, 
	doublereal *b, doublereal *bb, doublereal *bs, doublereal *ct, 
	doublereal *g, doublereal *c__, ftnlen sname_len);
extern /* Subroutine */ int dchk4_(char *sname, doublereal *eps, doublereal *thresh, 
	integer *nout, integer *ntra, logical *trace, logical *rewi, logical *
	fatal, integer *nidim, integer *idim, integer *nalf, doublereal *alf, 
	integer *nbet, doublereal *bet, integer *nmax, doublereal *a, 
	doublereal *aa, doublereal *as, doublereal *b, doublereal *bb, 
	doublereal *bs, doublereal *c__, doublereal *cc, doublereal *cs, 
	doublereal *ct, doublereal *g, ftnlen sname_len);
extern /* Subroutine */ int dchk5_(char *sname, doublereal *eps, doublereal *thresh, 
	integer *nout, integer *ntra, logical *trace, logical *rewi, logical *
	fatal, integer *nidim, integer *idim, integer *nalf, doublereal *alf, 
	integer *nbet, doublereal *bet, integer *nmax, doublereal *ab, 
	doublereal *aa, doublereal *as, doublereal *bb, doublereal *bs, 
	doublereal *c__, doublereal *cc, doublereal *cs, doublereal *ct, 
	doublereal *g, doublereal *w, ftnlen sname_len);
extern /* Subroutine */ int dchke_(integer *isnum, char *srnamt, integer *nout, 
	ftnlen srnamt_len);
extern /* Subroutine */ int dmake_(char *type__, char *uplo, char *diag, integer *m, 
	integer *n, doublereal *a, integer *nmax, doublereal *aa, integer *
	lda, logical *reset, doublereal *transl, ftnlen type_len, ftnlen 
	uplo_len, ftnlen diag_len);
extern /* Subroutine */ int dmmch_(char *transa, char *transb, integer *m, integer *
	n, integer *kk, doublereal *alpha, doublereal *a, integer *lda, 
	doublereal *b, integer *ldb, doublereal *beta, doublereal *c__, 
	integer *ldc, doublereal *ct, doublereal *g, doublereal *cc, integer *
	ldcc, doublereal *eps, doublereal *err, logical *fatal, integer *nout,
	 logical *mv, ftnlen transa_len, ftnlen transb_len);
extern logical lde_(doublereal *ri, doublereal *rj, integer *lr);
extern logical lderes_(char *type__, char *uplo, integer *m, integer *n, doublereal *
	aa, doublereal *as, integer *lda, ftnlen type_len, ftnlen uplo_len);
extern doublereal dbeg_(logical *reset);
extern doublereal ddiff_(doublereal *x, doublereal *y);
extern /* Subroutine */ int chkxer_(char *srnamt, integer *infot, integer *nout, 
	logical *lerr, logical *ok);
extern /* Subroutine */ int this_xerbla_(char *srname, integer *info);
