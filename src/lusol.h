#include "lusol_int.h"
#ifndef lusol_H
#define lusol_H
extern "C"
{
void lu1fac(int& m, int& n, int& nelem, int& lena, int* luparm, double* parmlu,
	double* a, int* indc, int* indr, int* ip, int* iq,
	int* lenc, int* lenr, int* locc, int* locr,
	int* iploc, int* iqloc, int* ipinv, int* iqinv, double* w , int& inform );
/*
      implicit           double precision (a-h,o-z)
      integer            luparm(30)
      double precision   parmlu(30), a(lena)   , w(n)
      integer            indc(lena), indr(lena), ip(m)   , iq(n),
     &                   lenc(n)   , lenr(m)   ,
     &                   iploc(n)  , iqloc(m)  , ipinv(m), iqinv(n)
      integer            locc(n)   , locr(m)


!     ------------------------------------------------------------------
!     lu1fac computes a factorization A = L*U, where A is a sparse
!     matrix with m rows and n columns, P*L*P' is lower triangular
!     and P*U*Q is upper triangular for certain permutations P, Q
!     (which are returned in the arrays ip, iq).
!     Stability is ensured by limiting the size of the elements of L.
!
!     The nonzeros of A are input via the parallel arrays a, indc, indr,
!     which should contain nelem entries of the form    aij,    i,    j
!     in any order.  There should be no duplicate pairs         i,    j.
!
!     ******************************************************************
!     *        Beware !!!   The row indices i must be in indc,         *
!     *              and the column indices j must be in indr.         *
!     *              (Not the other way round!)                        *
!     ******************************************************************
!
!     It does not matter if some of the entries in a(*) are zero.
!     Entries satisfying  abs( a(i) ) .le. parmlu(3)  are ignored.
!     Other parameters in luparm and parmlu are described below.
!
!     The matrix A may be singular.  On exit, nsing = luparm(11) gives
!     the number of apparent singularities.  This is the number of
!     "small" diagonals of the permuted factor U, as judged by
!     the input tolerances Utol1 = parmlu(4) and  Utol2 = parmlu(5).
!     The diagonal element diagj associated with column j of A is
!     "small" if
!                 abs( diagj ) .le. Utol1
!     or
!                 abs( diagj ) .le. Utol2 * max( uj ),
!
!     where max( uj ) is the maximum element in the j-th column of U.
!     The position of such elements is returned in w(*).  In general,
!     w(j) = + max( uj ),  but if column j is a singularity,
!     w(j) = - max( uj ).  Thus, w(j) .le. 0 if column j appears to be
!     dependent on the other columns of A.
!
!     NOTE: lu1fac (like certain other sparse LU packages) does not
!     treat dense columns efficiently.  This means it will be slow
!     on "arrow matrices" of the form
!                  A = (x       a)
!                      (  x     b)
!                      (    x   c)
!                      (      x d)
!                      (x x x x e)
!     if the numerical values in the dense column allow it to be
!     chosen LATE in the pivot order.
!
!     With TPP (Threshold Partial Pivoting), the dense column is
!     likely to be chosen late.
!
!     With TCP (Threshold Complete Pivoting), if any of a,b,c,d
!     is significantly larger than other elements of A, it will
!     be chosen as the first pivot and the dense column will be
!     eliminated, giving reasonably sparse factors.
!     However, if element e is so big that TCP chooses it, the factors
!     will become dense.  (It's hard to win on these examples!)
!     ==================================================================
!
!
!     Notes on the array names
!     ------------------------
!
!     During the LU factorization, the sparsity pattern of the matrix
!     being factored is stored twice: in a column list and a row list.
!
!     The column list is ( a, indc, locc, lenc )
!     where
!           a(*)    holds the nonzeros,
!           indc(*) holds the indices for the column list,
!           locc(j) points to the start of column j in a(*) and indc(*),
!           lenc(j) is the number of nonzeros in column j.
!
!     The row list is    (    indr, locr, lenr )
!     where
!           indr(*) holds the indices for the row list,
!           locr(i) points to the start of row i in indr(*),
!           lenr(i) is the number of nonzeros in row i.
!
!
!     At all stages of the LU factorization, ip contains a complete
!     row permutation.  At the start of stage k,  ip(1), ..., ip(k-1)
!     are the first k-1 rows of the final row permutation P.
!     The remaining rows are stored in an ordered list
!                          ( ip, iploc, ipinv )
!     where
!           iploc(nz) points to the start in ip(*) of the set of rows
!                     that currently contain nz nonzeros,
!           ipinv(i)  points to the position of row i in ip(*).
!
!     For example,
!           iploc(1) = k   (and this is where rows of length 1 begin),
!           iploc(2) = k+p  if there are p rows of length 1
!                          (and this is where rows of length 2 begin).
!
!     Similarly for iq, iqloc, iqinv.
!     ==================================================================
!
!
!     00 Jun 1983  Original version.
!     00 Jul 1987  nrank  saved in luparm(16).
!     12 Apr 1989  ipinv, iqinv added as workspace.
!     26 Apr 1989  maxtie replaced by maxcol in Markowitz search.
!     16 Mar 1992  jumin  saved in luparm(19).
!     10 Jun 1992  lu1fad has to move empty rows and cols to the bottom
!                  (via lu1pq3) before doing the dense LU.
!     12 Jun 1992  Deleted dense LU (lu1ful, lu1vlu).
!     25 Oct 1993  keepLU implemented.
!     07 Feb 1994  Added new dense LU (lu1ful, lu1den).
!     21 Dec 1994  Bugs fixed in lu1fad (nrank) and lu1ful (ipvt).
!     08 Aug 1995  Use ip instead of w as parameter to lu1or3 (for F90).
!     13 Sep 2000  TPP and TCP options implemented.
!     17 Oct 2000  Fixed troubles due to A = empty matrix (Todd Munson).
!     01 Dec 2000  Save Lmax, Umax, etc. after both lu1fad and lu6chk.
!                  lu1fad sets them when keepLU = false.
!                  lu6chk sets them otherwise, and includes items
!                  from the dense LU.
!     11 Mar 2001  lu6chk now looks at diag(U) when keepLU = false.
!     26 Apr 2002  New TCP implementation using heap routines to
!                  store largest element in each column.
!                  New workspace arrays Ha, Hj, Hk required.
!                  For compatibility, borrow space from a, indc, indr
!                  rather than adding new input parameters.
!     01 May 2002  lu1den changed to lu1DPP (dense partial  pivoting).
!                  lu1DCP implemented       (dense complete pivoting).
!                  Both TPP and TCP now switch to dense mode and end.
!
!     Systems Optimization Laboratory, Stanford University.
!  ---------------------------------------------------------------------
!
!
!  INPUT PARAMETERS
!
!  m      (not altered) is the number of rows in A.
!  n      (not altered) is the number of columns in A.
!  nelem  (not altered) is the number of matrix entries given in
!         the arrays a, indc, indr.
!  lena   (not altered) is the dimension of  a, indc, indr.
!         This should be significantly larger than nelem.
!         Typically one should have
!            lena > max( 2*nelem, 10*m, 10*n, 10000 )
!         but some applications may need more.
!         On machines with virtual memory it is safe to have
!         lena "far bigger than necessary", since not all of the
!         arrays will be used.
!  a      (overwritten) contains entries   Aij  in   a(1:nelem).
!  indc   (overwritten) contains the indices i in indc(1:nelem).
!  indr   (overwritten) contains the indices j in indr(1:nelem).
!
!  luparm input parameters:                                Typical value
!
!  luparm( 1) = nout     File number for printed messages.         6
!
!  luparm( 2) = lprint   Print level.                              0
!                   <  0 suppresses output.
!                   =  0 gives error messages.
!                  >= 10 gives statistics about the LU factors.
!                  >= 50 gives debug output from lu1fac
!                        (the pivot row and column and the
!                        no. of rows and columns involved at
!                        each elimination step).
!
!  luparm( 3) = maxcol   lu1fac: maximum number of columns         5
!                        searched allowed in a Markowitz-type
!                        search for the next pivot element.
!                        For some of the factorization, the
!                        number of rows searched is
!                        maxrow = maxcol - 1.
!
!  luparm( 6) = 0    =>  TPP: Threshold Partial   Pivoting.        0
!             = 1    =>  TRP: Threshold Rook      Pivoting.
!             = 2    =>  TCP: Threshold Complete  Pivoting.
!             = 3    =>  TSP: Threshold Symmetric Pivoting.
!             = 4    =>  TDP: Threshold Diagonal  Pivoting.
!                             (TDP not yet implemented).
!                        TRP and TCP are more expensive than TPP but
!                        more stable and better at revealing rank.
!                        Take care with setting parmlu(1), especially
!                        with TCP.
!                        NOTE: TSP and TDP are for symmetric matrices
!                        that are either definite or quasi-definite.
!                        TSP is effectively TRP for symmetric matrices.
!                        TDP is effectively TCP for symmetric matrices.
!
!  luparm( 8) = keepLU   lu1fac: keepLU = 1 means the numerical    1
!                        factors will be computed if possible.
!                        keepLU = 0 means L and U will be discarded
!                        but other information such as the row and
!                        column permutations will be returned.
!                        The latter option requires less storage.
!
!  parmlu input parameters:                                Typical value
!
!  parmlu( 1) = Ltol1    Max Lij allowed during Factor.
!                                                  TPP     10.0 or 100.0
!                                                  TRP      4.0 or  10.0
!                                                  TCP      5.0 or  10.0
!                                                  TSP      4.0 or  10.0
!                        With TRP and TCP (Rook and Complete Pivoting),
!                        values less than 25.0 may be expensive
!                        on badly scaled data.  However,
!                        values less than 10.0 may be needed
!                        to obtain a reliable rank-revealing
!                        factorization.
!  parmlu( 2) = Ltol2    Max Lij allowed during Updates.            10.0
!                        during updates.
!  parmlu( 3) = small    Absolute tolerance for       eps**0.8 = 3.0d-13
!                        treating reals as zero.
!  parmlu( 4) = Utol1    Absolute tol for flagging    eps**0.67= 3.7d-11
!                        small diagonals of U.
!  parmlu( 5) = Utol2    Relative tol for flagging    eps**0.67= 3.7d-11
!                        small diagonals of U.
!                        (eps = machine precision)
!  parmlu( 6) = Uspace   Factor limiting waste space in  U.      3.0
!                        In lu1fac, the row or column lists
!                        are compressed if their length
!                        exceeds Uspace times the length of
!                        either file after the last compression.
!  parmlu( 7) = dens1    The density at which the Markowitz      0.3
!                        pivot strategy should search maxcol
!                        columns and no rows.
!                        (Use 0.3 unless you are experimenting
!                        with the pivot strategy.)
!  parmlu( 8) = dens2    the density at which the Markowitz      0.5
!                        strategy should search only 1 column,
!                        or (if storage is available)
!                        the density at which all remaining
!                        rows and columns will be processed
!                        by a dense LU code.
!                        For example, if dens2 = 0.1 and lena is
!                        large enough, a dense LU will be used
!                        once more than 10 per cent of the
!                        remaining matrix is nonzero.
!
!
!  OUTPUT PARAMETERS
!
!  a, indc, indr     contain the nonzero entries in the LU factors of A.
!         If keepLU = 1, they are in a form suitable for use
!         by other parts of the LUSOL package, such as lu6sol.
!         U is stored by rows at the start of a, indr.
!         L is stored by cols at the end   of a, indc.
!         If keepLU = 0, only the diagonals of U are stored, at the
!         end of a.
!  ip, iq    are the row and column permutations defining the
!         pivot order.  For example, row ip(1) and column iq(1)
!         defines the first diagonal of U.
!  lenc(1:numl0) contains the number of entries in nontrivial
!         columns of L (in pivot order).
!  lenr(1:m) contains the number of entries in each row of U
!         (in original order).
!  locc(1:n) = 0 (ready for the LU update routines).
!  locr(1:m) points to the beginning of the rows of U in a, indr.
!  iploc, iqloc, ipinv, iqinv  are undefined.
!  w      indicates singularity as described above.
!  inform = 0 if the LU factors were obtained successfully.
!         = 1 if U appears to be singular, as judged by lu6chk.
!         = 3 if some index pair indc(l), indr(l) lies outside
!             the matrix dimensions 1:m , 1:n.
!         = 4 if some index pair indc(l), indr(l) duplicates
!             another such pair.
!         = 7 if the arrays a, indc, indr were not large enough.
!             Their length "lena" should be increase to at least
!             the value "minlen" given in luparm(13).
!         = 8 if there was some other fatal error.  (Shouldn't happen!)
!         = 9 if no diagonal pivot could be found with TSP or TDP.
!             The matrix must not be sufficiently definite
!             or quasi-definite.
!
!  luparm output parameters:
!
!  luparm(10) = inform   Return code from last call to any LU routine.
!  luparm(11) = nsing    No. of singularities marked in the
!                        output array w(*).
!  luparm(12) = jsing    Column index of last singularity.
!  luparm(13) = minlen   Minimum recommended value for  lena.
!  luparm(14) = maxlen   ?
!  luparm(15) = nupdat   No. of updates performed by the lu8 routines.
!  luparm(16) = nrank    No. of nonempty rows of U.
!  luparm(17) = ndens1   No. of columns remaining when the density of
!                        the matrix being factorized reached dens1.
!  luparm(18) = ndens2   No. of columns remaining when the density of
!                        the matrix being factorized reached dens2.
!  luparm(19) = jumin    The column index associated with DUmin.
!  luparm(20) = numL0    No. of columns in initial  L.
!  luparm(21) = lenL0    Size of initial  L  (no. of nonzeros).
!  luparm(22) = lenU0    Size of initial  U.
!  luparm(23) = lenL     Size of current  L.
!  luparm(24) = lenU     Size of current  U.
!  luparm(25) = lrow     Length of row file.
!  luparm(26) = ncp      No. of compressions of LU data structures.
!  luparm(27) = mersum   lu1fac: sum of Markowitz merit counts.
!  luparm(28) = nUtri    lu1fac: triangular rows in U.
!  luparm(29) = nLtri    lu1fac: triangular rows in L.
!  luparm(30) =
!
!
!
!  parmlu output parameters:
!
!  parmlu(10) = Amax     Maximum element in  A.
!  parmlu(11) = Lmax     Maximum multiplier in current  L.
!  parmlu(12) = Umax     Maximum element in current  U.
!  parmlu(13) = DUmax    Maximum diagonal in  U.
!  parmlu(14) = DUmin    Minimum diagonal in  U.
!  parmlu(15) = Akmax    Maximum element generated at any stage
!                        during TCP factorization.
!  parmlu(16) = growth   TPP: Umax/Amax    TRP, TCP, TSP: Akmax/Amax
!  parmlu(17) =
!  parmlu(18) =
!  parmlu(19) =
!  parmlu(20) = resid    lu6sol: residual after solve with U or U'.
!  ...
!  parmlu(30) =
!  ---------------------------------------------------------------------
*/


void lu6sol(int& mode ,int& m ,int& n, double* v ,double* w ,int& lena,int* luparm,double* parmlu,
	double* a,int* indc,int* indr,int* ip,int* iq, int* lenc,int* lenr,int* locc,int* locr, int& inform );
/*
      implicit
     &     none
      integer
     &     luparm(30), mode, m, n, lena, inform,
     &     indc(lena), indr(lena), ip(m), iq(n),
     &     lenc(n), lenr(m), locc(n), locr(m)
      double precision
     &     parmlu(30), a(lena), v(m), w(n)

!-----------------------------------------------------------------------
!     lu6sol  uses the factorization  A = L U  as follows:
!
!     mode
!      1    v  solves   L v = v(input).   w  is not touched.
!      2    v  solves   L'v = v(input).   w  is not touched.
!      3    w  solves   U w = v.          v  is not altered.
!      4    v  solves   U'v = w.          w  is destroyed.
!      5    w  solves   A w = v.          v  is altered as in 1.
!      6    v  solves   A'v = w.          w  is destroyed.
!
!     If mode = 3,4,5,6, v and w must not be the same arrays.
!
!     If lu1fac has just been used to factorize a symmetric matrix A
!     (which must be definite or quasi-definite), the factors A = L U
!     may be regarded as A = LDL', where D = diag(U).  In such cases,
!
!     mode
!      7    v  solves   A v = L D L'v = v(input).   w  is not touched.
!      8    v  solves       L |D| L'v = v(input).   w  is not touched.
!
!     ip(*), iq(*)      hold row and column numbers in pivotal order.
!     lenc(k)           is the length of the k-th column of initial L.
!     lenr(i)           is the length of the i-th row of U.
!     locc(*)           is not used.
!     locr(i)           is the start  of the i-th row of U.
!
!     U is assumed to be in upper-trapezoidal form (nrank by n).
!     The first entry for each row is the diagonal element
!     (according to the permutations  ip, iq).  It is stored at
!     location locr(i) in a(*), indr(*).
!
!     On exit, inform = 0 except as follows.
!     If mode = 3,4,5,6 and if U (and hence A) is singular, then
!     inform = 1 if there is a nonzero residual in solving the system
!     involving U.  parmlu(20) returns the norm of the residual.
!
!       July 1987: Early version.
!     09 May 1988: f77 version.
!     27 Apr 2000: Abolished the dreaded "computed go to".
!                  But hard to change other "go to"s to "if then else".
!     15 Dec 2002: lu6L, lu6Lt, lu6U, lu6Ut added to modularize lu6sol.
!-----------------------------------------------------------------------
*/

void lu8adc( int& mode,int& m,int& n,double* v,double* w,int& lena,int* luparm,double* parmlu,double* a,int* indc,int* indr,int* ip,int* iq,
		int* lenc,int* lenr,int* locc,int* locr,int& inform,double& diag,double& vnorm );

/*
      implicit           double precision (a-h,o-z)
      integer            luparm(30)
      double precision   parmlu(30), a(lena), v(m), w(n)
      integer            indc(lena), indr(lena), ip(m), iq(n)
      integer            lenc(n), lenr(m)
      integer            locc(n), locr(m)

!     ------------------------------------------------------------------
!     lu8adc  updates the LU factorization  A = L*U  when the vector
!     a(new)  is added to become the  n-th  column of  A.
!     The dimension of  A  is assumed to increase from  n-1  to  n
!     (not from  n  to  n+1).
!
!     If  mode = 1,  v(*)  must contain  a(new).
!     If  mode = 2,  v(*)  must satisfy  L*v = a(new).
!     On exit,  L*v = a(new)  in both cases.
!
!     The array  w(*)  is not used or altered.
!
!     On entry, all elements of  locc  are assumed to be zero.
!     On a successful exit (inform ne 7), this will again be true.
!
!     On exit:
!     inform =  0  if the rank of U stayed the same.
!     inform =  1  if the rank of U increased by 1.
!     inform =  7  if the update was not completed (lack of storage).
!
!     -- Feb 1985: Last  F66 version.
!     12 May 1988: First F77 version.  Now uses lu8rpc.
!     ------------------------------------------------------------------
*/

void lu8adr(int& m,int& n,double* w,int& lena,int* luparm,double* parmlu,double *a,int* indc,int* indr,int* ip,int* iq,int* lenc,int* lenr,int* locc,int* locr,int& inform,double& diag );

      /*
      implicit           double precision (a-h,o-z)
      integer            luparm(30)
      double precision   parmlu(30), a(lena), w(n)
      integer            indc(lena), indr(lena), ip(m), iq(n)
      integer            lenc(n), lenr(m)
      integer            locc(n), locr(m)

!     ------------------------------------------------------------------
!     lu8adr  updates the LU factorization  A = L*U  when the vector
!     w(*)  is added to become the  m-th  row of  A.
!     The dimension of  A  is assumed to increase from  m-1  to  m
!     (not from  m  to  m+1).
!
!     w(*)  is not altered.
!
!     On entry, all elements of  locc  are assumed to be zero.
!     On a successful exit (inform ne 7), this will again be true.
!
!     On exit:
!     inform =  0  if the rank of U stayed the same.
!     inform =  1  if the rank of U increased by 1.
!     inform =  7  if the update was not completed (lack of storage).
!
!     -- Feb 1985: Last  F66 version.
!     17 May 1988: First F77 version.
!     ------------------------------------------------------------------
*/

void lu8dlc(int&  m,int& n,int& jdel,int& lena,int* luparm,double* parmlu,double* a,int* indc,int* indr,int* ip,int* iq,
                        int* lenc,int* lenr,int* locc,int* locr,int& inform );


/*
      implicit           double precision (a-h,o-z)
      integer            luparm(30)
      double precision   parmlu(30), a(lena)
      integer            indc(lena), indr(lena), ip(m), iq(n)
      integer            lenc(n), lenr(m)
      integer            locc(n), locr(m)

!     ------------------------------------------------------------------
!     lu8dlc  updates the LU factorization  A = L*U  when column  jdel
!     is deleted.  The dimension of  A  decreases from  n  to  n-1.
!     The column permutation  iq(*)  and the column indices in  U
!     are altered accordingly.
!
!     NOTE:  The calling program must change  n  to  n-1.
!
!     In some cases it may be more efficient to use  lu8rpc  to
!     replace column  jdel  by zero, leaving it in the current position.
!
!     On entry, all elements of  locc  are assumed to be zero.
!     On a successful exit (inform ne 7), this will again be true.
!
!     On exit:
!     inform = -1  if the rank of U decreased by 1.
!     inform =  0  if the rank of U stayed the same.
!     inform =  7  if the update was not completed (lack of storage).
!
!     -- Feb 1985: Last  F66 version.
!     17 May 1988: First F77 version.
!     ------------------------------------------------------------------
*/
//Don't work well.
/*void lu8dlr(int& mode,int& m,int& n,int& idel,double* v,double* w,int& lena,int* luparm,double* parmlu,double* a,int* indc,int* indr,int* ip,int* iq,int* lenc,int* lenr,int* locc,int* locr,int& inform );
*/
/*
      implicit           double precision (a-h,o-z)
      integer            luparm(30)
      double precision   parmlu(30), a(lena), v(m), w(n)
      integer            indc(lena), indr(lena), ip(m), iq(n)
      integer            lenc(n), lenr(m)
      integer            locc(n), locr(m)

!     ------------------------------------------------------------------
!     lu8dlr  updates the LU factorization  A = L*U  when row  idel
!     (the vector  w) is deleted from  A. The update is implemented as
!     the rank-one modification
!
!           A(new)  =  A  -  e(idel) * w',
!
!     followed by a renumbering that makes row  idel  the last row of  A
!     and shifts rows  idel + 1,  idel + 2,  ...,  m  one place up.
!     Thus, row  idel  is replaced by the zero vector (rather than being
!     deleted), and is then cyclically permuted to the bottom of  A.
!     The dimensions of  A  do not alter, but  A  and  U  may become
!     singular.
!
!     If  mode = 1,  the old row is assumed to be unknown.  It will be
!                    computed from the LU factors of  A.
!     If  mode = 2,  w(*)  must contain the old row.
!
!     v(*)  is a work array of length  m.
!
!     On entry, all elements of  locc  are assumed to be zero.
!     On a successful exit (inform = 0), this will again be true.
!
!     Note --- significant overhead is involved in permuting row  idel
!     to the bottom.  In some cases it may be better to use  lu8rpr  to
!     replace row  idel  by zero, leaving it in the current position.
!     The growth of nonzeros in  L  and  U  is identical, but less
!     housekeeping is required than with  lu8dlr.
!
!
!     On exit:
!     inform = -1  if the rank of U decreased by 1.
!     inform =  0  if the rank of U stayed the same.
!     inform =  1  if the rank of U increased by 1.
!     inform =  7  if the update was not completed (lack of storage).
!
!     -- Feb 1985: Last  F66 version.
!     18 May 1988: First F77 version.
!     ------------------------------------------------------------------
*/
void lu8rpc(int& mode1,int& mode2,int& m,int& n,int& jrep,double* v,double* w,int& lena,int* luparm,double* parmlu,
	double *a,int* indc,int* indr,int* ip,int* iq,int* lenc,int* lenr,int* locc,int* locr,int& inform,double& diag,double& vnorm );
/*
      implicit           double precision(a-h,o-z)
      integer            luparm(30)
      double precision   parmlu(30), a(lena), v(m), w(n)
      integer            indc(lena), indr(lena), ip(m), iq(n)
      integer            lenc(n), lenr(m)
      integer            locc(n), locr(m)

*     ------------------------------------------------------------------
*     lu8rpc  updates the LU factorization  A = L*U  when column  jrep
*     is replaced by some vector  a(new).
*
*     lu8rpc  is an implementation of the Bartels-Golub update,
*     designed for the case where A is rectangular and/or singular.
*     L is a product of stabilized eliminations (m x m, nonsingular).
*     P U Q is upper trapezoidal (m x n, rank nrank).
*
*     If  mode1 = 0,  the old column is taken to be zero
*                     (so it does not have to be removed from  U).
*
*     If  mode1 = 1,  the old column need not have been zero.
*
*     If  mode2 = 0,  the new column is taken to be zero.
*                     v(*)  is not used or altered.
*
*     If  mode2 = 1,  v(*)  must contain the new column  a(new).
*                     On exit,  v(*)  will satisfy  L*v = a(new).
*
*     If  mode2 = 2,  v(*)  must satisfy  L*v = a(new).
*
*     The array  w(*)  is not used or altered.
*
*     On entry, all elements of  locc  are assumed to be zero.
*     On a successful exit (inform ne 7), this will again be true.
*
*     On exit:
*     inform = -1  if the rank of U decreased by 1.
*     inform =  0  if the rank of U stayed the same.
*     inform =  1  if the rank of U increased by 1.
*     inform =  2  if the update seemed to be unstable
*                  (diag much bigger than vnorm).
*     inform =  7  if the update was not completed (lack of storage).
*     inform =  8  if jrep is not between 1 and n.
*
*     -- Jan 1985: Original F66 version.
*     -- Jul 1987: Modified to maintain U in trapezoidal form.
*     10 May 1988: First f77 version.
*     16 Oct 2000: Added test for instability (inform = 2).
*     ------------------------------------------------------------------
*/
void lu8rpr(int& mode1,int& mode2,int& m,int& n,int& irep,double* v,double* w,double* wnew,int &lena,int* luparm,double* parmlu,
	double* a, int* indc,int* indr,int* ip,int* iq,int *lenc,int* lenr,int* locc,int* locr, int& inform );
/*
      implicit           double precision (a-h,o-z)
      integer            luparm(30)
      double precision   parmlu(30), a(lena), v(m), w(n), wnew(n)
      integer            indc(lena), indr(lena), ip(m), iq(n)
      integer            lenc(n), lenr(m)
      integer            locc(n), locr(m)

!     ------------------------------------------------------------------
!     lu8rpr  updates the LU factorization  A = L*U  when row  irep
!     (a vector  w(old)) is replaced by some vector  w(new).
!     The update is implemented as the rank-one modification
!
!           A(new)  =  A  -  e(irep) * ( w(old) - w(new) )'
!
!     with variations determined by  mode1  and  mode2  as follows.
!
!     mode1
!     -----
!       0     w(old)  is assumed to be zero.
!             w(*)    need not be set on entry, but will be altered.
!
!       1     w(old)  is assumed to be unknown.  it will be computed
!                     from the LU factors of  A.
!             w(*)    need not be set on entry, but will be altered.
!
!       2     w(*)    must contain  w(old).
!                     On exit, it will contain  w(old) - w(new).
!
!       3     w(*)    must contain  w(old) - w(new).  It is not altered.
!                     wnew(*) is not used.
!
!       4     w(*)    must contain  w(new) - w(old).  It is not altered.
!                     wnew(*) is not used.
!
!     If  mode1 = 3 or 4,  mode2  is not used.  It may be set to 0 or 1.
!     Otherwise,  mode2  is used as follows.
!
!     mode2
!     -----
!       0     w(new)  is assumed to be zero.   wnew(*)  is not used.
!
!       1     wnew(*) must contain the new row.
!
!     v(*)    is a work array of length  m.
!     On entry, all elements of  locc  are assumed to be zero.
!     On a successful exit (inform ne 7), this will again be true.
!
!
!     On exit:
!     inform = -1  if the rank of U decreased by 1.
!     inform =  0  if the rank of U stayed the same.
!     inform =  1  if the rank of U increased by 1.
!     inform =  7  if the update was not completed (lack of storage).
!     inform =  8  if jrep is not between 1 and n.
!
!     -- Mar 1985: Last  F66 version.
!     18 May 1988: First F77 version.
!     ------------------------------------------------------------------
*/

void testtest();
}
#endif
