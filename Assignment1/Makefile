# C compiler
CC=mpicc


INCDIR=include
SRCDIR=src

CFLAGS=-I$(INCDIR) -Wall -c -fopenmp

# Object files
OBJDIR=obj
OBJECTS=$(OBJDIR)/main.o $(OBJDIR)/initialize.o $(OBJDIR)/read_write.o
OBJFLAGS= -Wall -fopenmp

main.x: $(OBJECTS)
	$(CC) $(OBJFLAGS) -o $@ $^
$(OBJDIR)/main.o: main.c
	$(CC) $(CFLAGS) -o $@ $^	
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -o $@ $^
clean:
	rm -f $(OBJDIR)/*.o *.x
	rm -f *.pbm