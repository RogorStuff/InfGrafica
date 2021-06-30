#*****************************************************************
# File:   Makefile
# Author: Andrés Gavín Murillo, 716358
# Author: Abel Naya Forcano, 544125
# Date:   Enero 2020
# Coms:   Informática Gráfica - Path Tracer
#         Ejecutar "make" para compilar (o "make -f Makefile")
#         Ejecutar "make clean" para limpiar (borrar lo que genere)
#*****************************************************************

#---------------------------------------------------------
# macros
RM = /bin/rm -f  # para limpiar
CC = g++         # compilador
#---------------------------------------------------------
# compilación y enlazado ("linkado")
CPPFLAGS=-std=c++11 -fmax-errors=1 # opciones compilación
#---------------------------------------------------------
# vars
EJEC = PathTracer

EM = emission
IM = image
MAIN = main
MT = material
OBS = obstacle
PX = pixel
PL = plane
RAY = ray
RFL = reflentance
SN = sensor
SPH = sphere
VC = vector

all: ${EJEC}

${EJEC}:${MAIN}.o ${EM}.o ${IM}.o ${MT}.o ${OBS}.o ${PX}.o ${PL}.o ${RAY}.o ${RFL}.o ${SN}.o ${SPH}.o ${VC}.o
	${CC} ${MAIN}.o ${EM}.o ${IM}.o ${MT}.o ${OBS}.o ${PX}.o ${PL}.o ${RAY}.o ${RFL}.o ${SN}.o ${SPH}.o ${VC}.o -o ${EJEC} ${CPPFLAGS}

${MAIN}.o: ${MAIN}.cpp ${EM}.hpp ${EM}.cpp ${IM}.hpp ${IM}.cpp ${MT}.hpp ${MT}.cpp ${OBS}.hpp ${OBS}.cpp ${PX}.hpp ${PX}.cpp ${PL}.hpp ${PL}.cpp ${RAY}.hpp ${RAY}.cpp ${RFL}.hpp ${RFL}.cpp ${SN}.hpp ${SN}.cpp ${SPH}.hpp ${SPH}.cpp ${VC}.hpp
	${CC} -c ${MAIN}.cpp ${CPPFLAGS}

${EM}.o: ${EM}.hpp ${EM}.cpp
	${CC} -c ${EM}.cpp ${CPPFLAGS}

${IM}.o: ${IM}.hpp ${IM}.cpp
	${CC} -c ${IM}.cpp ${CPPFLAGS}

${MT}.o: ${MT}.hpp ${MT}.cpp
	${CC} -c ${MT}.cpp ${CPPFLAGS}

${OBS}.o: ${OBS}.hpp ${OBS}.cpp
	${CC} -c ${OBS}.cpp ${CPPFLAGS}

${PX}.o: ${PX}.hpp ${PX}.cpp
	${CC} -c ${PX}.cpp ${CPPFLAGS}

${PL}.o: ${PL}.hpp ${PL}.cpp
	${PL} -c ${PL}.cpp ${CPPFLAGS}

${RAY}.o: ${RAY}.hpp ${RAY}.cpp
	${CC} -c ${RAY}.cpp ${CPPFLAGS}

${RFL}.o: ${RFL}.hpp ${RFL}.cpp
	${CC} -c ${RFL}.cpp ${CPPFLAGS}	

${SN}.o: ${SN}.hpp ${SN}.cpp
	${CC} -c ${SN}.cpp ${CPPFLAGS}	

${SPH}.o: ${SPH}.hpp ${SPH}.cpp
	${CC} -c ${SPH}.cpp ${CPPFLAGS}	

${VC}.o: ${VC}.hpp
	${CC} -c ${VC}.hpp ${CPPFLAGS}						

# Cuidado con lo que se pone aquí, que se borra sin preguntar
#clean:
#	$(RM) ${MAIN}.o ${BRDF}.o ${COL}.o ${GEO}.o ${HC}.o ${IM}.o ${MA}.o ${OB}.o ${PR}.o ${RA}.o ${RE}.o ${SC}.o ${TE}.o ${TR}.o