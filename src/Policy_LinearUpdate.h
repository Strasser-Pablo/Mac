#ifndef Policy_LinearUpdate_H
#define Policy_LinearUpdate_H

/**
 *
 * @brief
 * Class to give option for update by Lusol.
 * Some comment are taken verbatim by lusol.
 **/
struct Policy_LinearUpdate
{
	/**
	 * minimum value of lena.
	 **/
	int min_lena; 
	/**
	 * multiple of the size to use for lena.
	 **/
	int grow_lena;
	/**
	 * minimum value of maximal size of the matrice without refactorization.
	 **/
	int min_max_n;
	/**
	 * multiple of the size for value of maximal size of the matrice without refactorization.
	 **/
	int grow_max_n;
	//File number for printed messages.
	int& luparm_nout;
	/*
	Print level: 
	<  0 suppresses output.
	=  0 gives error messages.
	>= 10 gives statistics about the LU factors.
	>= 50 gives debug output from lu1fac
	(the pivot row and column and the
	no. of rows and columns involved at
	each elimination step).
	*/
	int& luparm_lprint;
	/*
	lu1fac: maximum number of columns 
	searched allowed in a Markowitz-type
        search for the next pivot element.
        For some of the factorization, the
        number of rows searched is
        maxrow = maxcol - 1.
	*/
	int& luparm_maxcol;
	/*
  	= 0    =>  TPP: Threshold Partial   Pivoting. 
        = 1    =>  TRP: Threshold Rook      Pivoting.
        = 2    =>  TCP: Threshold Complete  Pivoting.
        = 3    =>  TSP: Threshold Symmetric Pivoting.
        = 4    =>  TDP: Threshold Diagonal  Pivoting.
                             (TDP not yet implemented).
	TRP and TCP are more expensive than TPP but
	more stable and better at revealing rank.
	Take care with setting parmlu(1), especially
	with TCP.
	NOTE: TSP and TDP are for symmetric matrices
	that are either definite or quasi-definite.
	TSP is effectively TRP for symmetric matrices.
	TDP is effectively TCP for symmetric matrices.
	*/
	int& luparm_pivoting;
	/*
  	 keepLU   lu1fac: keepLU = 1 means the numerical
         factors will be computed if possible.
         keepLU = 0 means L and U will be discarded
         but other information such as the row and
         column permutations will be returned.
         The latter option requires less storage.
	*/
	int& luparm_keepLU;
	/*
	 Minimum recommended value for  lena.
	 */
	int & luparm_minlen;
	/*
  	Ltol1    Max Lij allowed during Factor.
	With TRP and TCP (Rook and Complete Pivoting),
	values less than 25.0 may be expensive
	on badly scaled data.  However,
	values less than 10.0 may be needed
	to obtain a reliable rank-revealing
	factorization.
	*/
	double& parmlu_Ltol1;
	/*
	Ltol2    Max Lij allowed during Updates.
	*/
	double& parmlu_Ltol2;
	/*
	small    Absolute tolerance for treating reals as zero.
	*/
	double& parmlu_small;
	/*
	Utol1    Absolute tol for flagging small diagonals of U.
	*/
	double& parmlu_Utol1;
	/*
	Utol2    Relative tol for flagging small diagonals of U.
	*/
	double& parmlu_Utol2;
	/*
	Uspace   Factor limiting waste space in  U.
        In lu1fac, the row or column lists
        are compressed if their length
        exceeds Uspace times the length of
        either file after the last compression.
	*/
	double& parmlu_Uspace;
	/*
	dens1    The density at which the Markowitz pivot strategy should search maxcol
	columns and no rows.(Use 0.3 unless you are experimenting with the pivot strategy.)
	*/
	double& parmlu_dens1;
	/*
	dens2    the density at which the Markowitz 
	strategy should search only 1 column,
	or (if storage is available)
	the density at which all remaining
	rows and columns will be processed
	by a dense LU code.
	For example, if dens2 = 0.1 and lena is
	large enough, a dense LU will be used
	once more than 10 per cent of the
	remaining matrix is nonzero.
	*/
	double& parmlu_dens2;
	Policy_LinearUpdate():luparm_nout(luparm[0]),luparm_lprint(luparm[1]),luparm_maxcol(luparm[2]),luparm_pivoting(luparm[5]),luparm_keepLU(luparm[7]),
	parmlu_Ltol1(parmlu[0]),parmlu_Ltol2(parmlu[1]),parmlu_small(parmlu[2]),parmlu_Utol1(parmlu[3]),parmlu_Utol2(parmlu[4]),parmlu_Uspace(parmlu[5]),parmlu_dens1(parmlu[6]),parmlu_dens2(parmlu[7]),luparm_minlen(luparm[12]),
	min_lena(1000000),grow_lena(100),min_max_n(10000),grow_max_n(10)
	{
		luparm[0]=6;
		luparm[1]=10;
		luparm[2]=5;
		luparm[5]=0;
		luparm[7]=1;
		parmlu[0]=10.0;
		parmlu[1]=10.0;
		parmlu[2]=3e-13;
		parmlu[3]=3.7e-11;
		parmlu[4]=3.7e-11;
		parmlu[5]=3.0;
		parmlu[6]=0.3;
		parmlu[7]=0.5;
	}
	const int& GetLinearUpdateMinimalLena() const
	{
		return min_lena;
	}
	const int& GetLinearUpdateLenaGrowFactor() const
	{
		return grow_lena;
	}
	const int& GetLinearUpdateMinMaxN() const
	{
		return min_max_n;
	}
	const int& GetLinearUpdateGrowMaxN() const
	{
		return grow_max_n;
	}
	void GetLinearUpdateLuparm(int *& in_luparm)
	{
		in_luparm=luparm;
	}
	void GetLinearUpdateParmlu(double*& in_parmlu)
	{
		in_parmlu=parmlu;
	}
	private:
	int luparm[30];
	double parmlu[30];
};
#endif
