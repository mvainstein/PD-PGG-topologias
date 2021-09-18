CC=gcc
OFLAGS=-O3
CFLAGS=-g -Wall
GSLFLAGS=-lgsl -lgslcblas
MFLAGS=-lm 

debug: PD_PGG_parametro_r.c
	${CC} -DDEBUG ${CFLAGS} ${OFLAGS} PD_PGG_parametro_r.c ${GSLFLAGS} -o debug_pris_dil ${MFLAGS}

pris_dil: PD_PGG_parametro_r.c
	${CC} ${CFLAGS} ${OFLAGS} PD_PGG_parametro_r.c ${GSLFLAGS} -o pris_dil ${MFLAGS}
	
pris_reescalado: PD_PGG_parametro_r.c
	${CC} -DNORMALIZED_PAYOFFS ${CFLAGS} ${OFLAGS} PD_PGG_parametro_r.c ${GSLFLAGS} -o pris_reescalado ${MFLAGS}
	
