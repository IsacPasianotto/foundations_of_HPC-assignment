CC=mpicc
INCDIR=include
OBJDIR=obj
SRCDIR=src
SNAPDIR=snaps

CFLAGS=-I$(INCDIR) -Wall -c -fopenmp
OBJFLAGS=-Wall -fopenmp -O3 -march=native

OBJECTS=$(OBJDIR)/main.o $(OBJDIR)/initialize.o $(OBJDIR)/read_write.o $(OBJDIR)/run.o\
        $(OBJDIR)/should_live.o $(OBJDIR)/ordered_evolution.o $(OBJDIR)/static_evolution.o

main.x: $(OBJECTS)
	$(CC) $(OBJFLAGS) -o $@ $^
$(OBJDIR)/main.o: main.c
	$(CC) $(CFLAGS) -o $@ $^	
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -o $@ $^
clean:
	rm -f $(OBJDIR)/*.o *.x
image:
	rm -f *.pbm
	rm -f $(SNAPDIR)/*

