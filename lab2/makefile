# set this variable to the director in which you saved the common files
commondir = ../common/

all : lab2-1mac lab2-2mac

lab2-1mac : skinning.c $(commondir)GL_utilities.c $(commondir)VectorUtils3.c $(commondir)loadobj.c $(commondir)Mac/MicroGlut.m
	gcc -Wall -o skinning -I$(commondir) -I$(commondir)Mac -DGL_GLEXT_PROTOTYPES skinning.c $(commondir)GL_utilities.c $(commondir)loadobj.c $(commondir)VectorUtils3.c $(commondir)Mac/MicroGlut.m -framework OpenGL -framework Cocoa

lab2-1 : skinning.c $(commondir)GL_utilities.c $(commondir)VectorUtils3.c $(commondir)loadobj.c $(commondir)Linux/MicroGlut.c
	gcc -Wall -o skinning -I$(commondir) -I$(commondir)/Linux -DGL_GLEXT_PROTOTYPES skinning.c $(commondir)GL_utilities.c $(commondir)loadobj.c $(commondir)VectorUtils3.c $(commondir)Linux/MicroGlut.c -lXt -lX11 -lGL -lm

lab2-2mac : skinning2.c $(commondir)GL_utilities.c $(commondir)VectorUtils3.c $(commondir)loadobj.c $(commondir)Mac/MicroGlut.m
	gcc -Wall -o skinning2 -I$(commondir) -I$(commondir)Mac -DGL_GLEXT_PROTOTYPES skinning2.c $(commondir)GL_utilities.c $(commondir)loadobj.c $(commondir)VectorUtils3.c $(commondir)Mac/MicroGlut.m -framework OpenGL -framework Cocoa

lab2-2 : skinning2.c $(commondir)GL_utilities.c $(commondir)VectorUtils3.c $(commondir)loadobj.c $(commondir)Linux/MicroGlut.c
	gcc -Wall -o skinning2 -I$(commondir) -I$(commondir)/Linux -DGL_GLEXT_PROTOTYPES skinning2.c $(commondir)GL_utilities.c $(commondir)loadobj.c $(commondir)VectorUtils3.c $(commondir)Linux/MicroGlut.c -lXt -lX11 -lGL -lm

clean :
	rm skinning skinning2

run1 :
	./skinning

run2 :
	./skinning2
