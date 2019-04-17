SRCDIR=src/
BUILDDIR=build/
OBJDIR=$(BUILDDIR)obj/

program:$(OBJDIR)main.o $(OBJDIR)image.o $(OBJDIR)statistics.o $(OBJDIR)conv.o
	gcc -o program $(OBJDIR)main.o $(OBJDIR)image.o -lm $(OBJDIR)statistics.o $(OBJDIR)conv.o

$(OBJDIR)main.o: $(SRCDIR)main.c $(SRCDIR)statistics.h $(SRCDIR)image.h $(SRCDIR)conv.h
	gcc -c $(SRCDIR)main.c -o $(OBJDIR)main.o

$(OBJDIR)image.o: $(SRCDIR)image.h $(SRCDIR)image.c
	gcc -c $(SRCDIR)image.c -o $(OBJDIR)image.o

$(OBJDIR)statistics.o: $(SRCDIR)statistics.h $(SRCDIR)statistics.c
	gcc -c $(SRCDIR)statistics.c -o $(OBJDIR)statistics.o

$(OBJDIR)conv.o: $(SRCDIR)conv.h $(SRCDIR)conv.c
	gcc -c $(SRCDIR)conv.c -o $(OBJDIR)conv.o