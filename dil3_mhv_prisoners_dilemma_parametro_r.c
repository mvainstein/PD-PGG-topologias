#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <time.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include "pointers.h"
#include "redes.h"

/********************************************************************
***                          C.I.                                 ***
********************************************************************/
#define dens_aleat
#define dens_inic_c  0.5
#define dens_inic_p  0.
#define dens_inic_pc 0.
#define dens_inic_dc 0.

//#define dens_quad
//#define dens_quad2
//#define dens_listras

//#define topo_aleat
#define topo_fixa

/********************************************************************
***                        Topologia                              ***
********************************************************************/
//#define quadrada 				// N = L^2
//#define cubica				// N = L^3
//#define quadridimensional		// N = L^4
//#define hexagonal				// N = 2*L^2
//#define kagome				// N = 3*L^2
//#define triangular			// N = L^2
//#define moore					// N = L^2

enum tipo_rede {QUADRADA, CUBICA, QUADRIDIMENSIONAL, HEXAGONAL, KAGOME,
					TRIANGULAR, MOORE};
enum tipo_rede REDE_ATUAL;// = HEXAGONAL;
enum tipo_estrategia {DEFECTOR, COOPERATOR, PUNISHER};

//#define viz_well_mixed
#define viz_espacial

int L;
//#define L 72 //58 //72 - Hexagonal //58 - Kagome //100
//#define N // Depende da topologia

/********************************************************************
***                          Jogo                                 ***
********************************************************************/
#define PRISONERS_DILEMMA
//#define PGG_FOCAL
//#define PGG

//#define NORMALIZED_PAYOFFS

//#define RUIDO 0.001
double RUIDO;
//#define DEBUG

//#define mobil
#define prob_mobil 0.00
#define EPSILON (1e-8)
#define c 1
//#define N_viz 10

/********************************************************************
***                          Plot                                 ***
********************************************************************/
//#define snapshot_gnuplot    
//#define snapshot_gif
//#define snapshot_hexa
#define fps 0.00005 // fps^-1
#define densidade_arquivo
//#define densidade_terminal	

const int tmax=100000;
unsigned long rseed;
const gsl_rng_type * T;
gsl_rng * rand_vec;
double measure_time = 1;

//int
long long int N;
long int L2;//= L*L; 
long int L3;// = L*L*L;
long long int L4;// = L*L*L*L; 
//int N_viz;
int G; // =4 (rede hexagonal) =5 (rede quadrada / kagome) =7 (rede triangular / quadrada 3D) =9 (rede moore / quadrada 4D)
double INV_G_RUIDO; //1/(G*RUIDO)
double INV_RUIDO;
#ifdef PRISONERS_DILEMMA
double TT, RR, PP, SS;
#endif

int ND=0;
int NC=0;
int NP=0;
int NPC=0;
int NDC=0;

int nd=0;
int nc=0;
int np=0;
int ndc=0;
int npc=0;


void set_gsl_rng(void)
{
#ifdef DEBUG
	rseed=422;
#else
	rseed=time(NULL);
#endif
  
	gsl_rng_env_setup();
	T    = gsl_rng_default;
	rand_vec = gsl_rng_alloc (T);
	gsl_rng_set (rand_vec, rseed);

  return;
}
/********************************************************************
***                            C.I.                               ***
********************************************************************/		
void calculo_ci(int state[N], int topologia[N])
{
	int n;

	for(n=0; n < N; n++)
	{	

		#ifdef dens_aleat
		double temp = gsl_rng_uniform(rand_vec);
		
		if(temp < dens_inic_c ) state[n] = COOPERATOR;
		else 
		{
			if(temp < dens_inic_c + dens_inic_p) state[n] = PUNISHER;
			else 
			{
				if(temp < dens_inic_c + dens_inic_p + dens_inic_pc ) state[n] = 3;
				else
				{	
					if(temp < dens_inic_c + dens_inic_p + dens_inic_pc + dens_inic_dc) state[n] = 4;
					else state[n] = DEFECTOR;
				}
			}			
		}
		#endif
	
		#ifdef topo_aleat
		double temp = gsl_rng_uniform(rand_vec);
		if( temp < 1/3. ) topologia[n] = QUADRADA; //ou KAGOME
		else
		{
			if( temp < 2/3.) topologia[n] = TRIANGULAR; // ou CUBICA
			else 
				topologia[n] = MOORE;
		}
		#endif

		#ifdef topo_fixa		
		topologia[n] = G;
		#endif
	
		#ifdef dens_quad
		int i,j;
		j=x%L;
		i=x/L;
		state[n] = DEFECTOR;
		if(j>1*L/5 && j<2*L/5 && i>1*L/5 && i<2*L/5){state[j+i*L] = COOPERATOR;}
		if(j>3*L/5 && j<4*L/5 && i>1*L/5 && i<2*L/5)
		{
			double temp = gsl_rng_uniform(rand_vec);
			if(temp < 0.5) {state[j+i*L] = PUNISHER;}
			else{state[j+i*L] = COOPERATOR;}
		}
		if(j>1*L/5 && j<2*L/5 && i>3*L/5 && i<4*L/5)
		{
			double temp = gsl_rng_uniform(rand_vec);
			if(temp < 0.5) {state[j+i*L] = PUNISHER;}
			else{state[j+i*L] = COOPERATOR;}
		}
		if(j>3*L/5 && j<4*L/5 && i>3*L/5 && i<4*L/5){state[j+i*L] = PUNISHER;}
		#endif

		#ifdef dens_quad2
		int i,j;
		j=x%L;
		i=x/L;
		state[n] = DEFECTOR;
		if(j>L/3 && j<2*L/3 && i>L/3 && i<2*L/3){state[j+i*L] = PUNISHER;}
		#endif

		#ifdef dens_listras
		int i,j;
		j=x%L;
		i=x/L;
		if(i<L/3){state[j+i*L] = DEFECTOR;}
		if(i>=L/3 && i<2*L/3){state[j+i*L] = PUNISHER;}	
		if(i>=2*L/3){state[j+i*L] = DEFECTOR;}
		#endif

	}
	
	return;
	
}

/********************************************************************
***                  numero de cada estrategia                    ***
********************************************************************/
void calculo_numero( int state[N], int sitio, int **viz, int topologia[N])
{
	int i=0;
	
	nd=0;
	nc=0;
	np=0;
	ndc=0;
	npc=0;

	#ifdef viz_espacial
	for(i=0;i<topologia[sitio];i++) // vizinho 0 e o proprio sitio
	{
		switch(state[viz[sitio][i]])
		{
			case DEFECTOR:   ++nd; break;
			case COOPERATOR: ++nc; break;
			case PUNISHER:   ++np; break;
			case 3: ++npc; break;
			case 4: ++ndc; break;
			default: 
				fprintf(stderr,"ERRO calculo vizinhos\n");
				fflush(stderr);
		}
	}
	#endif

	#ifdef viz_well_mixed
	for(i=1;i<topologia[sitio];i++) 
	{
		int k;
		k = (int) N*gsl_rng_uniform(rand_vec);

		switch(k)
		{
			case DEFECTOR:   ++nd; break;
			case COOPERATOR: ++nc; break;
			case PUNISHER:   ++np; break;
			default:
				fprintf(stderr,"ERRO contagem estrategia vizinho aleatorio\n");
				fflush(stderr);
		}
	}

	//conta o proprio sitio
	switch(state[viz[sitio][0]])
	{
		case DEFECTOR:   ++nd; break;
		case COOPERATOR: ++nc; break;
		case PUNISHER:   ++np; break;
		default:
			fprintf(stderr,"ERRO contagem estrategia proprio sitio\n");
			fflush(stderr);	
	}
	#endif
	
	return;
}

/********************************************************************
***                          Payoff                               ***
********************************************************************/

void calculo_payoff ( double *payoff, double r, double gama, double delta, int x, int topologia[N], int state[N] )
{

	/*//puniçao c/ propina
	double q = gsl_rng_uniform(rand_vec);
	double p = gsl_rng_uniform(rand_vec);

	payoff[COOPERATOR] = (1./G)*r*c* (np+nc) - c; //C
	payoff[PUNISHER]   = (1./G)*r*c* (np+nc) - c + p*q*delta*nd - (1 - p*q)*gama*nd; //P
	payoff[DEFECTOR]   = (1./G)*r*c* (np+nc) - (1 - p*q)*gama*np - p*q*delta*np; //D*/


	/*//Ising
	payoff[COOPERATOR] = 2*1*(nc-nd + 0.0); 
	payoff[DEFECTOR]   = 2*(-1)*(nc-nd + 0.0); //W = exp(-payoff/T)*/

	//puniçao 
	#if defined(PGG) || defined(PGG_FOCAL)
	payoff[COOPERATOR] = (1./topologia[x])*r*c* (np+nc) - c;
	payoff[PUNISHER]   = (1./topologia[x])*r*c* (np+nc) - c - gama*nd;
	payoff[DEFECTOR]   = (1./topologia[x])*r*c* (np+nc) - delta*np;
	#endif
	
	#ifdef PRISONERS_DILEMMA
	switch(state[x])
	{
		case COOPERATOR:
			//payoff[COOPERATOR] = nc;   // <- com autointeracao   //RR*(nc - 1) + SS*nd; // sem autointeracao
			payoff[COOPERATOR] = nc + nd*SS;
			break;
		case DEFECTOR: 
			//payoff[DEFECTOR]   = TT*nc;// <- com autointeracao  //TT*nc + PP*(nd-1);   // sem autointeracao
			payoff[DEFECTOR]   = TT*nc;
			break;
	}
	#endif
	
	/*//recompensa
	payoff[COOPERATOR] = (1./G)*r*c* (np+nc) - c + delta*np;
	payoff[PUNISHER]   = (1./G)*r*c* (np+nc) - c - gama*nc;
	payoff[DEFECTOR]   = (1./G)*r*c* (np+nc);*/


	/*//corrupçao com propina
	payoff[COOPERATOR] = (1./G)*r*c* (np+nc - gama*np) -c +delta*gama*np/nc;
	payoff[DEFECTOR]   = (1./G)*r*c* (np+nc  - gama*np);
	
	if(nc==0)
	{
	payoff[PUNISHER]   = (1./G)*r*c* (np+nc - gama*np) -c + (1)*gama;
	}
	else
	{
	payoff[PUNISHER]   = (1./G)*r*c* (np+nc - gama*np) -c + (1-delta)*gama;
	}*/
	
	return;
}

/********************************************************************
***                         Update rule                           ***
********************************************************************/
void update_rule( int x, int vizinho, int state[N], double Px, double Py ,int topologia[N])
{
#ifdef NORMALIZED_PAYOFFS
	double Wxy = 1.0/(1.0 + exp(-(Py-Px)*INV_G_RUIDO)); // INV_G_RUIDO = 1.0/G*RUIDO
#else
	double Wxy = 1.0/(1.0 + exp(-(Py-Px)*INV_RUIDO));//Wxy = 1.0/(1.0 + exp(-(Py-Px)/RUIDO));
#endif
	//double Wxy = exp(-Px/r); //Ising

	double l = gsl_rng_uniform(rand_vec);

	//if((state[n]+state[vizinho])==3){Wxy=0.;}
	//if(state[n]==4 && state[vizinho]==3){Wxy=0.;}
	//troca de estado
	if(Wxy > l)
	//if(Py > Px)
	{      
		state[x] = state[vizinho];
		topologia[x] = topologia[vizinho];		
		//state[x] = fabs(state[x]-1); //Ising
	}
}


/********************************************************************
***                         MCS                              ***
********************************************************************/
void calculo_mcs(double *payoff, int state[N], int **viz, double r, double gama, double delta, int topologia[N])
{

	int n;
	int x,y,vizinho;
	double Px, Py;
	
	for(n=0; n<N; n++)
	{					
		Px = 0;
		Py = 0;

		x = (int) N*gsl_rng_uniform(rand_vec);
   		//sitio=x;

		#ifdef viz_espacial
		y = 1 + (int) (topologia[x]-1)*gsl_rng_uniform(rand_vec); 
		vizinho = viz[x][y];
		#endif

		#ifdef viz_well_mixed
		y = (int) N*gsl_rng_uniform(rand_vec);
		vizinho = y;
		#endif
		
		if (state[vizinho] != state[x])
		{
		#if defined(PGG_FOCAL) || defined(PRISONERS_DILEMMA)
		
			int sitio = x;
		
			calculo_numero(state,sitio,viz,topologia);
			calculo_payoff(payoff,r,gama,delta,sitio,topologia,state);
			Px = payoff[state[sitio]];
	
			calculo_numero(state,vizinho,viz,topologia);
			calculo_payoff(payoff,r,gama,delta,vizinho,topologia,state);
			Py = payoff[state[vizinho]];
		#endif	

		#ifdef PGG
			int sitio, vizinho2;
			for(y=0;y<topologia[x];y++)
			{
				sitio = viz[x][y];
				calculo_numero(state,sitio,viz,topologia);
				calculo_payoff(payoff,r,gama,delta,vizinho,topologia,state);
				Px += payoff[state[x]];
			}

			for(y=0;y<topologia[x];y++)
			{			
				vizinho2 = viz[vizinho][y];
				calculo_numero(state,vizinho2,viz,topologia);
				calculo_payoff(payoff,r,gama,delta,vizinho,topologia,state);
				Py += payoff[state[vizinho]];
			}
		#endif
		
			update_rule(x,vizinho,state,Px,Py,topologia);
		}//if (state[vizinho] != state[x])
  	}
}

/********************************************************************
***                          Densidades                           ***
********************************************************************/
void calculo_densidades(int state[N], int t, FILE *fp)
{
	int k;

	ND=0;
	NC=0;
	NP=0;
	NPC=0;
	NDC=0;
	
	for(k=0;k<N;k++)
	{
		switch (state[k])
		{
			case COOPERATOR: ++NC; break;
			case PUNISHER:   ++NP; break;
			case DEFECTOR:   ++ND; break;
			case 3: ++NPC; break;
			case 4: ++NDC; break;
			default: 
				fprintf(stderr,"ERRO - tipo de estrategia\n");
				fflush(stderr);
		}	
	}	

	#ifdef densidade_terminal
	printf("%d %lf %lf %lf %lf %lf\n", t, (double)NC/(N), (double)ND/(N), (double)NP/(N),(double)NPC/(N),(double)NDC/(N));
	#endif

	#ifdef densidade_arquivo
	fprintf(fp,"%d %lf %lf %lf %lf %lf\n", t, (double)NC/(N), (double)ND/(N), (double)NP/(N),(double)NPC/(N),(double)NDC/(N));	
	#endif

}

/********************************************************************
***                        Snapshots                              ***
********************************************************************/
void snap_gnuplot(int state[N], int topologia[N], int t)	//    ./a.out | gnuplot
{

	int i,j;
	
	//printf("set title \"MCS = %d\" \n",t);
	printf("set autoscale keepfix\n");
	printf("set palette model RGB\n");
	printf("unset colorbox\n");
	printf("unset border\n");
	printf("unset xtics\n");
	printf("unset ytics\n");
	printf("set palette defined ( 0 \"red\", 1 \"blue\",  2 \"green\",  3 \"dark-green\", 4 \"dark-red\", 5 \"green\", 7 \"blue\",  9 \"red\")\n");
	printf("set cbrange[0:8]\n");
	printf("set xrange[0:%d]\n",L);
	printf("set yrange[0:%d]\n",L);
	printf("set size square\n");
			
	printf("plot \"-\" matrix with image\n");
			

	for(i=0;i<L;i++)
	{
		for(j=0;j<L;j++)
		{
			printf("%d ",state[j+i*L]);
		
		}
		/*for(j=0;j<L;j++)
		{
			printf("%d ",topologia[j+i*L]);
		}*/
		printf("\n");
	}
	printf("\n"); 
	printf("e\n");    printf("pause(%lf)\n",fps);
	
}
void snap_gif(int state[N], int topologia[N], int t)
{

	int i,j;
	
	for(i=0;i<L;i++)
	{
		for(j=0;j<L;j++)
		{
			printf("%d ",state[j+i*L]);
		
		}
		/*for(j=0;j<L;j++)
		{
		printf("%d ",topologia[j+i*L]);
		}*/
		printf("\n");
	}
	printf("\n"); 

}
void snap_hexa(int state[N], int topologia[N], int t)
{

	int n,i,j; //n = i + 2j N
	double x,y,d=10.,h=7.;

	printf("set title \"MCS = %d\" \n",t);
	printf("set object 1 rect from graph 0, graph 0 to graph 1, graph 1 back\n");
	printf("set object 1 rect fc rgb \"black\" fillstyle solid 1.0 \n");
	printf("set view map\n");
	printf("set size ratio .9\n");
	//printf("set xrange[0:]\n");
	//printf("set yrange[0:]\n");
	printf("set palette defined ( 0 \"red\", 1 \"blue\",  2 \"green\")\n");
	printf("set cbrange[0:2]\n");
	printf("unset key\n");
	printf("splot \"-\" using 1:2:3 with points pointtype 7 pointsize 1. palette linewidth 10\n");

	for(n=0;n<N;n++)
	{
		i = n % (2*L);
		j = n / (2*L);

		x = d*(i+j);
		y = j*(L+h) - h*(i%2);

		printf("%lf %lf %d\n",x,y,state[n]);

	}
	printf("\n"); 
	printf("e\n");    printf("pause(%lf)\n",fps);
}

/********************************************************************
***                          Mobilidade                           ***
********************************************************************/				
void calculo_mobilidade( int state[N], int x, int **viz)
{
	
	double g = gsl_rng_uniform(rand_vec);
	if(g<=prob_mobil)
	{		
		int y = 1 + (int) 4*gsl_rng_uniform(rand_vec);
		int e = state[x];
		state[x] = state[viz[x][y]];
		state[viz[x][y]] = e;
	}
}
/********************************************************************
***                     Initialize Network                        ***
********************************************************************/
void initialize_network(char REDE_ATUAL_NAME[], char filename[], double r, double gama, double delta, unsigned long rseed)
{	    
  
    if (!strcmp(REDE_ATUAL_NAME, "quadrada") || !strcmp(REDE_ATUAL_NAME, "QUADRADA")){
		N = L2; G = 5;
		REDE_ATUAL = QUADRADA;
		//fprintf(stderr,"%s escolhida!\n",REDE_ATUAL_NAME); fflush(stderr);
		sprintf(filename,"quadrada_dados_r%f_g%f_d%f_seed%ld.txt",r,gama,delta,rseed);
	} else
	{	
		if (!strcmp(REDE_ATUAL_NAME, "cubica") || !strcmp(REDE_ATUAL_NAME, "CUBICA")){
			N = L3; G = 7;
			REDE_ATUAL = CUBICA;
			//fprintf(stderr,"%s escolhida!\n",REDE_ATUAL_NAME); fflush(stderr);
			sprintf(filename,"cubica_dados_r%f_g%f_d%f_seed%ld.txt",r,gama,delta,rseed);
		} else{
					if (!strcmp(REDE_ATUAL_NAME, "quadridimensional") || !strcmp(REDE_ATUAL_NAME, "QUADRIDIMENSIONAL")){
						N = L4;	G = 9;
						REDE_ATUAL=QUADRIDIMENSIONAL;
						//fprintf(stderr,"%s escolhida!\n",REDE_ATUAL_NAME); fflush(stderr);
						sprintf(filename,"quadridim_dados_r%f_g%f_d%f_seed%ld.txt",r,gama,delta,rseed);
					} 
					else{
							if (!strcmp(REDE_ATUAL_NAME, "hexagonal") || !strcmp(REDE_ATUAL_NAME, "HEXAGONAL")){
							N = 2*L2; G = 4;
							REDE_ATUAL=HEXAGONAL;
							//fprintf(stderr,"%s escolhida!\n",REDE_ATUAL_NAME); fflush(stderr);
							sprintf(filename,"hexagonal_dados_r%f_g%f_d%f_seed%ld.txt",r,gama,delta,rseed);
							} 
							else{
									if (!strcmp(REDE_ATUAL_NAME, "kagome")  || !strcmp(REDE_ATUAL_NAME, "KAGOME")){
										N = 3*L2; G = 5;
										REDE_ATUAL=KAGOME;
										//fprintf(stderr,"%s escolhida!\n",REDE_ATUAL_NAME); fflush(stderr);
										sprintf(filename,"kagome_dados_r%f_g%f_d%f_seed%ld.txt",r,gama,delta,rseed);
									}	 
									else{
											if (!strcmp(REDE_ATUAL_NAME, "triangular")  || !strcmp(REDE_ATUAL_NAME, "TRIANGULAR")){
												N = L2; G = 7;
												REDE_ATUAL=TRIANGULAR;
												//fprintf(stderr,"%s escolhida!\n",REDE_ATUAL_NAME); fflush(stderr);
												sprintf(filename,"triangular_dados_r%f_g%f_d%f_seed%ld.txt",r,gama,delta,rseed);
											}
											else {	
													if (!strcmp(REDE_ATUAL_NAME, "moore")  || !strcmp(REDE_ATUAL_NAME, "MOORE")){
														N = L2; G = 9;
														REDE_ATUAL=MOORE;
														//fprintf(stderr,"%s escolhida!\n",REDE_ATUAL_NAME); fflush(stderr);
														sprintf(filename,"moore_dados_r%f_g%f_d%f_seed%ld.txt",r,gama,delta,rseed);
													}
												 }
										}
								}
						}
				}
		}
#ifdef NORMALIZED_PAYOFFS
	INV_G_RUIDO = 1.0/(G*RUIDO);
#endif	
	INV_RUIDO = 1.0/RUIDO;
	//fprintf(stderr,"%s escolhida!\n G=%d\nN=%lld\n",REDE_ATUAL_NAME,G,N); fflush(stderr);
	return;
}
/********************************************************************
***                          Main                                 ***
********************************************************************/
int main(int argc, char *argv[])
{	
	//gera arquivo
	char filename[200];
	char REDE_ATUAL_NAME[50];
	
	FILE *fp;
		
  	int t=0;
  	
	double payoff[5], gama, delta,r;//,Px,Py;
    //unsigned long int seed = time(NULL); 
    //srand((unsigned)seed);
 
	if (argc!=7)
	{
		printf("O programa precisa de 6 argumentos:\n1) r\n2) gama\n3) delta\n4) tipo de rede\n5) L\n6) RUIDO");
		exit(1);
	}
	r=atof(argv[1]);
	gama=atof(argv[2]);
    delta=atof(argv[3]);
    sprintf(REDE_ATUAL_NAME,"%s",argv[4]);
    L=atoi(argv[5]);
    RUIDO=atof(argv[6]); 
    
    L2 = L*L; 
	L3 = L2*L;
	L4 = L3*L; 
    
    
#ifdef PRISONERS_DILEMMA
	//TT = r; RR = 1.0; PP = 0.0; SS=0.0;
	TT = 2.0-r; RR = 1.0; PP = 0.0; SS=-1.0+r; // 1 parametro apenas
#endif   
	set_gsl_rng();
	    
	initialize_network(REDE_ATUAL_NAME,filename,r,gama,delta,rseed);
	    
	//N_viz = G-1;
	int state[N],**viz,topologia[N];
	
	//viz = create_2d_int_pointer_h(N,N_viz+1);	
	viz = create_2d_int_pointer_h(N,G);	
	
	fp=fopen(filename,"w");
	
//------------------------------------------------------------------------------------
	fprintf(stderr,"REDE_ATUAL=%d\n",REDE_ATUAL);
	switch (REDE_ATUAL)
	{
		case QUADRADA: rede_quadrada(viz,L);
			break;
		case CUBICA: rede_cubica(viz,L);
			break;
		case QUADRIDIMENSIONAL: rede_quadridimensional(viz,L); 
			break;
		case HEXAGONAL:	rede_hexagonal(viz,L);
			break;
		case KAGOME: rede_kagome(viz,L);
			break;
		case TRIANGULAR: rede_triangular(viz,L);
			break;
		case MOORE: rede_moore(viz,L);
			break;
		default:
			fprintf(stderr,"ERRO inicializacao rede!\n");
			fflush(stderr);
	} 
	//fprintf(stderr,"Antes calculo_ci\n"); fflush(stderr);
	calculo_ci(state,topologia);
	//fprintf(stderr,"Antes calculo_densidades\n"); fflush(stderr);	
	calculo_densidades(state,t,fp);

	#ifdef snapshot_gnuplot	
	snap_gnuplot(state, topologia,t);
	#endif 
	#ifdef snaphot_gif	
	snap_gif(state, topologia,t);
	#endif 
	#ifdef snapshot_hexa	
	snap_hexa(state, topologia,t);
	#endif 

	//MCS		
	for(t=1; t < tmax; t++)
	{			
		calculo_mcs(payoff,state,viz,r,gama,delta,topologia);
		//calculo_mobilidade(state,sitio,viz);	
		//if(t==25 || t==100 || t==1000){snapshot(state,topologia,t);}
	
		#ifdef snapshot_gnuplot	
		snap_gnuplot(state, topologia,t);
		#endif 
		#ifdef snaphot_gif	
		o_gif(state, topologia,t);
		#endif 
		#ifdef snapshot_hexa	
		snap_hexa(state, topologia,t);
		#endif 
//------------------------------------------------------------------------------------

		if (t >= measure_time)
		{
			//fprintf(stderr,"t = %d\n",t); fflush(stderr);
			calculo_densidades(state,t,fp);
			measure_time *= 1.1;
			if (floor(measure_time)-t < EPSILON) 
				measure_time=ceil(measure_time);
		}    
  		if((NC/(N)==1) || (NP/(N)==1) || (NPC/(N)==1) || (ND/(N)==1) || ((NC+NP)/(N)==1))
		{
			do
			{
				if ( t >= measure_time)
				{
					fprintf(fp,"%d %lf %lf %lf %lf %lf\n", t, (double)NC/(N), (double)ND/(N), (double)NP/(N),(double)NPC/(N),(double)NDC/(N));
					measure_time *= 1.1;
					if (floor(measure_time)-t < EPSILON) 
					measure_time=ceil(measure_time);
				}
				t=t+1;
			}
			while(t<tmax);
		 break;
		}
	
	}//MCS

fclose(fp);

return 0;
//free_2d_int_pointer(viz,N,N_viz+1);
free_2d_int_pointer(viz,N,G);
} //main
