# set this variable to the director in which you saved the common files
commondir = ../common/

mac: $(commondir)LoadTGA.c SpriteLight.c lab4.c $(commondir)VectorUtils3.c $(commondir)GL_utilities.c $(commondir)Mac/MicroGlut.m
	gcc -Wall -o lab4 -I$(commondir) $(commondir)LoadTGA.c $(commondir)VectorUtils3.c $(commondir)GL_utilities.c $(commondir)Mac/MicroGlut.m SpriteLight.c lab4.c -I../common/Mac -DGL_GLEXT_PROTOTYPES -framework OpenGL -framework Cocoa

linux: $(commondir)LoadTGA.c SpriteLight.c lab4.c $(commondir)VectorUtils3.c $(commondir)GL_utilities.c $(commondir)Linux/MicroGlut.c
	gcc -Wall -o lab4 -I$(commondir) $(commondir)LoadTGA.c $(commondir)VectorUtils3.c $(commondir)GL_utilities.c $(commondir)Linux/MicroGlut.c SpriteLight.c lab4.c -I../common/Linux -DGL_GLEXT_PROTOTYPES -lXt -lX11 -lGL -lm

clean:
	rm -f lab4

run:
	./lab4
