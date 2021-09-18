CC=gcc
OFLAGS=-O3
CFLAGS=-g -Wall
GSLFLAGS=-lgsl -lgslcblas
MFLAGS=-lm 

debug: dil3_mhv_prisoners_dilemma_parametro_r.c
	${CC} -DDEBUG ${CFLAGS} ${OFLAGS} dil3_mhv_prisoners_dilemma_parametro_r.c ${GSLFLAGS} -o debug_pris_dil ${MFLAGS}

pris_dil: dil3_mhv_prisoners_dilemma.c
	${CC} ${CFLAGS} ${OFLAGS} dil3_mhv_prisoners_dilemma_parametro_r.c ${GSLFLAGS} -o pris_dil ${MFLAGS}
	
pris_reescalado: dil3_mhv_prisoners_dilemma.c
	${CC} -DNORMALIZED_PAYOFFS ${CFLAGS} ${OFLAGS} dil3_mhv_prisoners_dilemma_parametro_r.c ${GSLFLAGS} -o pris_reescalado ${MFLAGS}
	
