#------------------------------------------------------------------------------
# File:   Makefile
# Author: Javier Perez y Máximo Valenciano
# Date:   mayo 2022
# Coms:   Makefile para el trabajo práctico de Programación II 2022
#------------------------------------------------------------------------------

#---------------------------------------------------------
# Definición de macros
CC = g++
CPPFLAGS = -I. -std=c++11      #opciones de compilación
LDFLAGS =                      #opciones de linkado
RM = rm -f                     #comando para borrar ficheros

all: mainB
#-----------------------------------------------------------
# Compilacion
betris.o: betris.cpp betris.hpp
	${CC} -c betris.cpp ${CPPFLAGS}
# Linkado
mainB: betris.o mainB.o
	${CC} betris.o mainB.o -o mainB ${LDFLAGS}
mainB.o: mainB.cpp betris.hpp
	${CC} -c mainB.cpp ${CPPFLAGS}
#-----------------------------------------------------------	
# LIMPIEZA de todo lo generado. Ojo: se borrarán sin preguntar
clean:
	${RM} mainB.o betris.o mainB
