#  +------------------------------------------------------------+
#  |                      RetroSpace v1.0                       |
#  |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
#  |           Bakalarska prace, FIT VUT v Brne, 2011           |
#  +------------------------------------------------------------+
#    @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
#    @date   18.5.2011
#    @file   Makefile
#    @brief  Prelozi, spusti nebo vycisti projekt.
#
#    @attention
#            Pro preklad na serveru merlin.fit.vutbr.cz pouzit misto SDL_LIB cestu
#            SDL_LIB_MERLIN, jelikoz 'sdl-config --libs' vraci cestu ke knihovne
#            /usr/lib64, s kterou program nelze slinkovat.
#

# OPENGL_INC= -I/usr/X11R6/include
OPENGL_LIB=-L/usr/X11R6/lib -lGL -lGLU
SDL_INC=`sdl-config --cflags`
SDL_LIB=`sdl-config --libs`
SDL_LIB_MERLIN=-L/usr/lib -lpthread -lSDL 

OBJS=$(shell ls *.cpp | sed 's/.cpp/.o/')

CC=g++
FLAGS=-O2
INCLUDE=$(SDL_INC)
LIBS=$(SDL_LIB) $(OPENGL_LIB) -lm
EXEC=RetroSpace

$(EXEC): $(OBJS)
	$(CC) $(FLAGS) -o $(EXEC) $(OBJS) $(LIBS)

%.o: %.cpp
	$(CC) -c $(FLAGS) -o $@ $< $(INCLUDE)
    
.PHONY: run pack doc clean

run:
	./$(EXEC)
    
pack:
	zip $(EXEC).zip *.h *.cpp *.bmp Makefile Doxyfile

doc:
	doxygen Doxyfile

clean:
	rm -f $(EXEC) $(OBJS)  
