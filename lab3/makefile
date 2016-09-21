# set this variable to the director in which you saved the common files
commondir = ../common/

all : lab3mac

lab3mac : lab3.c $(commondir)GL_utilities.c $(commondir)VectorUtils3.c $(commondir)loadobj.c $(commondir)LoadTGA.c $(commondir)zpr.c $(commondir)Mac/MicroGlut.m
	gcc -Wall -o lab3 -I$(commondir) -I$(commondir)Mac -DGL_GLEXT_PROTOTYPES lab3.c $(commondir)GL_utilities.c $(commondir)loadobj.c $(commondir)VectorUtils3.c $(commondir)LoadTGA.c $(commondir)zpr.c $(commondir)Mac/MicroGlut.m -framework OpenGL -framework Cocoa


lab3 : lab3.c $(commondir)GL_utilities.c $(commondir)VectorUtils3.c $(commondir)loadobj.c $(commondir)LoadTGA.c $(commondir)zpr.c $(commondir)Linux/MicroGlut.c
	gcc -Wall -o lab3 -I$(commondir) -I../common/Linux -DGL_GLEXT_PROTOTYPES lab3.c $(commondir)GL_utilities.c $(commondir)loadobj.c $(commondir)VectorUtils3.c $(commondir)LoadTGA.c $(commondir)zpr.c $(commondir)Linux/MicroGlut.c -lXt -lX11 -lGL -lm

run :
	./lab3

clean :
	rm lab3
