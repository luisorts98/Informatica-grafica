.PHONY: x clean tar

EJECUTABLE= practica_objetos_B2

MODULOS:= practica_objetos_B2.o\
         objetos_B2.o\
         file_ply_stl.o\
      
LIBS:= -L/usr/X11R6/lib/ -lGL -lGLU -lglut -lm -lX11 -lpthread

#-framework OpenGL -framework GLUT -lm -lc -lstdc++ -lpthread 
CPPFLAGS:= -Wall -w -fmax-errors=2 -g

CC= g++

x: $(EJECUTABLE)
	./$(EJECUTABLE) beethoven

$(EJECUTABLE): $(MODULOS)	
	$(CC) -o $(EJECUTABLE) $(LDFLAGS) $(MODULOS) $(LIBS) 

clean:
	rm -rf *.o $(EJECUTABLE)

