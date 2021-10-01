/********************************************************************
***                        Topologias                             ***
********************************************************************/

/********************************************************************
***                    Multilayer 2 Quadrada                      ***
********************************************************************/
void multilayer2_quadrada (int **viz, int L)
{
	int x;
	int L2 = L*L;
	long int N = 2*L2;
	//G=6;
	
	for(x=0;x<N;x++)
	{	
		viz[x][0] = x;     // autointeraçao
		viz[x][1] = x - L; //vizinho acima de i
		viz[x][2] = x + 1; //vizinho à direita de i
		viz[x][3] = x + L; //vizinho abaixo sito de i
		viz[x][4] = x - 1; //vizinho à esquerda i
		if (x<L2)
			viz[x][5] = x + L2; // vizinho na outra rede
		else
			viz[x][5] = x - L2; // vizinho na outra rede
		
		/********************************************************************
		***                            C.C.P.                             ***
		********************************************************************/	
		//fronteira superior (i->L-1)
		if ((x%L2) < L){ viz[x][1] = x + (L - 1) * L; }
		//fronteira esquerda (j->L-1)
		if ((x%L2) % L == 0){ viz[x][4] = x + (L - 1); }
		//fronteira inferior (i->0)
		if ((x%L2) >= L2-L){ viz[x][3] = x - (L - 1) * L; }
		//fronteira direita (j->0)
		if (((x-L+1)%L2) % L == 0){ viz[x][2] = x - (L - 1); }
	}
	
	return;
}

/********************************************************************
***                     Rede Quadrada                             ***
********************************************************************/
void rede_quadrada (int **viz, int L)
{
	int x;
	long int L2 = L*L;
	long int N  = L2;
	//G=5;
	for(x=0;x<N;x++)
	{	
		viz[x][0] = x; // autointeraçao
		viz[x][1] = x - L; //vizinho acima de i
		viz[x][2] = x + 1; //vizinho à direita de i
		viz[x][3] = x + L; //vizinho abaixo sito de i
		viz[x][4] = x - 1; //vizinho à esquerda i
				
		/********************************************************************
		***                            C.C.P.                             ***
		********************************************************************/	
		//fronteira superior (i->L-1)
		if (x < L){ viz[x][1] = x + (L - 1) * L; }
		//fronteira esquerda (j->L-1)
		if (x % L == 0){ viz[x][4] = x + (L - 1); }
		//fronteira inferior (i->0)
		if (x >= L2-L){ viz[x][3] = x - (L - 1) * L; }
		//fronteira direita (j->0)
		if ((x-L+1) % L == 0){ viz[x][2] = x - (L - 1); }

		//printf("%d %d %d %d %d %d %d\n",viz[x][0],viz[x][1],viz[x][2],viz[x][3],viz[x][4],viz[x][5],viz[x][6]);
	}
	
	return;		
}

/********************************************************************
***                       Rede Cubica                             ***
********************************************************************/
void rede_cubica (int **viz, int L)
{
	int x;
	long int L2 = L*L;
	long int L3 = L2*L;
	long int N  = L3;
	
	//G=7;
	for(x=0;x<N;x++)
	{	
		viz[x][0] = x; // autointeraçao
		viz[x][1] = x - L; //vizinho acima de i
		viz[x][2] = x + 1; //vizinho à direita de i
		viz[x][3] = x + L; //vizinho abaixo sito de i
		viz[x][4] = x - 1; //vizinho à esquerda i
				
		viz[x][5] = x + L2; //vizinho atras
		viz[x][6] = x - L2; //vizinho frontal	

		/********************************************************************
		***                            C.C.P.                             ***
		********************************************************************/	
		//fronteira superior (i->L-1)
		if (x % (L2) < L){ viz[x][1] = x + (L - 1) * L; }
		//fronteira esquerda (j->L-1)
		if (x % L == 0){ viz[x][4] = x + (L - 1); }
		//fronteira inferior (i->0)
		if (x % (L2) >= L2-L){ viz[x][3] = x - (L - 1) * L; }
		//fronteira direita (j->0)
		if ((x-L+1) % L == 0){ viz[x][2] = x - (L - 1); }
		//fronteira fontal
		if (x < L2){ viz[x][6] = x + L3 - L2; }
		//fronteira atras
		if (x >= L3 - L2){ viz[x][5] = x - L3 + L2; }


		//printf("%d %d %d %d %d %d %d\n",viz[x][0],viz[x][1],viz[x][2],viz[x][3],viz[x][4],viz[x][5],viz[x][6]);
	}
	return;		
}

/********************************************************************
***                     Rede Quadridimensional                    ***
********************************************************************/
void rede_quadridimensional (int **viz, int L)
{
	int x;
	long int L2 = L*L;
	long int L3 = L2*L;
	long long int L4 = L3*L;
	long long int N = L4;
	//G=9;
	//long long int L4 = L3*L;//printf("%lld\n",L4);
	for(x=0;x<N;x++)
	{	
		viz[x][0] = x; // autointeraçao
		viz[x][1] = x - L; //vizinho acima de i
		viz[x][2] = x + 1; //vizinho à direita de i
		viz[x][3] = x + L; //vizinho abaixo sito de i
		viz[x][4] = x - 1; //vizinho à esquerda i
				
		viz[x][5] = x + L2; //vizinho atras
		viz[x][6] = x - L2; //vizinho frontal	

		viz[x][7] = x + L3; //vizinho cima cima cima
		viz[x][8] = x - L3; //vizinho baixo baixo baixo	

		/********************************************************************
		***                            C.C.P.                             ***
		********************************************************************/	
		//fronteira superior (i->L-1)
		if (x % (L2) < L){ viz[x][1] = x + (L - 1) * L; }
		//fronteira esquerda (j->L-1)
		if (x % L == 0){ viz[x][4] = x + (L - 1); }
		//fronteira inferior (i->0)
		if (x % (L2) >= L2-L){ viz[x][3] = x - (L - 1) * L; }
		//fronteira direita (j->0)
		if ((x-L+1) % L == 0){ viz[x][2] = x - (L - 1); }
		//fronteira fontal
		if (x % (L3) < L2){ viz[x][6] = x + L3 - L2; }
		//fronteira atras
		if (x % (L3) >= L3 - L2){ viz[x][5] = x - L3 + L2; }
		//fronteira fontal frontal
		if (x < L3){ viz[x][8] = x + L4 - L3; }
		//fronteira atras atras
		if (x >= L4 - L3){ viz[x][7] = x % (L3); }


		//printf("%d %d %d %d %d %d %d %d %d\n",viz[x][0],viz[x][1],viz[x][2],viz[x][3],viz[x][4],viz[x][5],viz[x][6],viz[x][7],viz[x][8]);
	}
	return;		
}

/********************************************************************
***                     Rede Kagome                               ***
********************************************************************/
void rede_kagome (int **viz, int L)
{
	int x;
	long L2 = L*L;
	long N  = 3*L2;
	//G=5;
    for(x=0; x < N; x++)
	{
		if (x % 3 == 0) 
		{
			viz[x][0] = x; // autointeraçao
			viz[x][1] = x + 1; //direita
			viz[x][2] = x - 2; //esquerda
			viz[x][3] = x + 2; //direita
			viz[x][4] = x - 3*L + 2; //baixo
		}	
		if (x % 3 == 1) 
		{
			viz[x][0] = x; // autointeraçao
			viz[x][1] = x - 1; //esquerda
			viz[x][2] = x + 1; //direita
			viz[x][3] = x + 2; //direita
			viz[x][4] = x - 3*L + 4; //baixo				
		}
		if (x % 3 == 2) 
		{
			viz[x][0] = x; // autointeraçao
			viz[x][1] = x - 1; //esquerda
			viz[x][2] = x - 2; //direita
			viz[x][3] = x + 3*L - 2; //direita
			viz[x][4] = x + 3*L - 4; //baixo				
		}

		//ccp	
		if((x+2) % (3*L) == 0 && x % 3 == 1) //direita
		{
			viz[x][3] = x - 3*L + 2;
			viz[x][4] = x - 6*L + 4;
		} 
		
		if((x) % (3*L) == 0 && x % 3 == 0) //esquerda
		{viz[x][2] = x + 3*L - 2; } 

		if((x+3*L-2) % (3*L) == 0 && x % 3 == 2) //esquerda
		{ viz[x][4] = x + (3*L - 2) * 2; } 
		
		if(x > 3*L2 - 3*L && x % 3 == 2) //superior		
		{
			viz[x][3] = x - 3*L2 + 3*L - 4; 
			viz[x][4] = x - 3*L2 + 3*L - 2; 
		}			 

		if(x < 3*L) //inferior
		{			
			if(x % 3 == 0) {viz[x][4] = x + 3*L2 - 3*L + 2; } 
			if(x % 3 == 1) {viz[x][4] = x + 3*L2 - 3*L + 4; } 
		}
		if(x == 3*L2 - 3*L + 2) //vertice
		{viz[x][4] = 3*L - 2;
		 viz[x][3] = 0;  } 

		if(x == 3*L - 2) //vertice
		{viz[x][4] = 3*L2 - 3*L + 2; } 

		//printf("%d %d %d %d %d\n",viz[x][0],viz[x][1],viz[x][2],viz[x][3],viz[x][4]);
	}
	return;		
}

/********************************************************************
***                     Rede Hexagonal                            ***
********************************************************************/
void rede_hexagonal (int **viz, int L)
{
	int x;
	long L2 = L*L;
	long N  = 2*L2;
	//G=4;
    for(x=0; x < N; x++)
	{
		if (x % 2 == 0) //par
		{
			viz[x][0] = x; // autointeraçao
			viz[x][1] = x - 1; //esquerda
			viz[x][2] = x + 1; //direita
			viz[x][3] = x + 2 * L - 1; //baixo
		}	
		else //if (x % 2 != 0) //impar
		{
			viz[x][0] = x; // autointeraçao
			viz[x][1] = x - 1; //esquerda
			viz[x][2] = x + 1; //direita
			viz[x][3] = x - 2 * L + 1; //cima				
		}

		//ccp	
		if((x-2*L+1) % (2*L) == 0) //direita
		{viz[x][2] = x - 2 * L + 1;
		 viz[x][3] = x - 4 * L + 1; } 
		
		if(x % (2*L) == 0 || x == 0) //esquerda
		{viz[x][1] = x + 2 * L - 1; 
		 viz[x][3] = x + 4 * L - 1; } 
		
		if(x < 2*L && x % 2 != 0) //superior		
		{viz[x][3] = x + 2 * L * (L-1) + 1; } 

		if(x > 2*L2 - 2*L - 1 && x % 2 == 0) //inferior
		{viz[x][3] = x - 2 * L * (L-1) - 1; } 

		if(x == 2*L2 - 2*L) //vertice inferior esquerdo
		{viz[x][3] = 2*L - 1; } 

		if(x == 2*L - 1) //vertice superior direito
		{viz[x][3] = 2*L2 - 2*L; } 

		//printf("%d %d %d %d\n",viz[x][0],viz[x][1],viz[x][2],viz[x][3]);
	}
	return;
	
}

/********************************************************************
***                   Rede Triangular                             ***
********************************************************************/
void rede_triangular (int **viz, int L)
{
	int x;
	long int L2 = L*L;
	long int N  = L2;
	//G=7;
	for(x=0;x<N;x++)
	{	

		viz[x][0] = x; // autointeraçao
		viz[x][1] = x - L; //vizinho acima de i
		viz[x][2] = x + 1; //vizinho à direita de i
		viz[x][3] = x + L; //vizinho abaixo sito de i
		viz[x][4] = x - 1; //vizinho à esquerda i
		viz[x][5] = x - L + 1; //vizinho diag cima direita
		viz[x][6] = x - 1 + L; //vizinho diag baixo esquerda

		/********************************************************************
		***                            C.C.P.                             ***
		********************************************************************/	
		//fronteira superior (i->L-1)
		if (x % (L2) < L)
		{
			viz[x][1] = x + (L - 1) * L; 
			viz[x][5] = x + (L - 1) * L + 1;
		}
		//fronteira esquerda (j->L-1)
		if (x % L == 0) 
		{
			viz[x][4] = x + (L - 1); 
			viz[x][6] = x + (L - 1) + L; 
		}
		//fronteira inferior (i->0)
		if (x % (L2) >= L2-L)
		{
			viz[x][3] = x - (L - 1) * L; 
			viz[x][6] = x - (L - 1) * L - 1; 
		}
		//fronteira direita (j->0)
		if ((x-L+1) % L == 0)
		{
			viz[x][2] = x - (L - 1);
			viz[x][5] = x - (L - 1) - L;
		}
		//vertices
		if (x == L-1) {viz[x][5] = L * L - L ; }//cima direita
		if (x == L2-L) {viz[x][6] = L - 1; }//baixo esquerda

		//printf("%d %d %d %d %d %d %d %d %d\n",viz[x][0],viz[x][1],viz[x][2],viz[x][3],viz[x][4],viz[x][5],viz[x][6],viz[x][7],viz[x][8]);
	}
	return;			
}

/********************************************************************
***                        Rede Moore                             ***
********************************************************************/
void rede_moore (int **viz, int L)
{
	int x;
	long int L2 = L*L;
	long int N  = L2;
	//G=9;
	for(x=0;x<N;x++)
	{	

		viz[x][0] = x; // autointeraçao
		viz[x][1] = x - L; //vizinho acima de i
		viz[x][2] = x + 1; //vizinho à direita de i
		viz[x][3] = x + L; //vizinho abaixo sito de i
		viz[x][4] = x - 1; //vizinho à esquerda i
		viz[x][5] = x - L + 1; //vizinho diag cima direita
		viz[x][6] = x - 1 + L; //vizinho diag baixo esquerda
		viz[x][7] = x - 1 - L; //vizinho diag cima esquerda
		viz[x][8] = x + 1 + L; //vizinho diag baixo direita

		/********************************************************************
		***                            C.C.P.                             ***
		********************************************************************/	
		//fronteira superior (i->L-1)
		if (x % (L2) < L)
		{
			viz[x][1] = x + (L - 1) * L; 
			viz[x][5] = x + (L - 1) * L + 1;
			viz[x][7] = x + (L - 1) * L - 1;
		}
		//fronteira esquerda (j->L-1)
		if (x % L == 0) 
		{
			viz[x][4] = x + (L - 1); 
			viz[x][6] = x + (L - 1) + L; 
			viz[x][7] = x + (L - 1) - L; 
		}
		//fronteira inferior (i->0)
		if (x % (L2) >= L2-L)
		{
			viz[x][3] = x - (L - 1) * L; 
			viz[x][6] = x - (L - 1) * L - 1; 
			viz[x][8] = x - (L - 1) * L + 1; 
		}
		//fronteira direita (j->0)
		if ((x-L+1) % L == 0)
		{
			viz[x][2] = x - (L - 1);
			viz[x][5] = x - (L - 1) - L;
			viz[x][8] = x - (L - 1) + L;
		}
		//vertices
		if (x == 0) {viz[x][7] = L * L - 1; }//cima esquerda
		if (x == L-1) {viz[x][5] = L * L - L ; }//cima direita
		if (x == L2-L) {viz[x][6] = L - 1; }//baixo esquerda
		if (x == L2-1) {viz[x][8] = 0; }//baixo direita

		//printf("%d %d %d %d %d %d %d %d %d\n",viz[x][0],viz[x][1],viz[x][2],viz[x][3],viz[x][4],viz[x][5],viz[x][6],viz[x][7],viz[x][8]);
	}
	return;			
}
