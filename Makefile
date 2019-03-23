SRCDIR=src/
BUILDDIR=build/
OBJDIR=$(BUILDDIR)obj/

program:$(OBJDIR)main.o $(OBJDIR)image.o $(OBJDIR)statistics.o
	gcc -o program $(OBJDIR)main.o $(OBJDIR)image.o -lm $(OBJDIR)statistics.o

$(OBJDIR)main.o: $(SRCDIR)main.c $(SRCDIR)statistics.h $(SRCDIR)image.h 
	gcc -c $(SRCDIR)main.c -o $(OBJDIR)main.o

$(OBJDIR)image.o: $(SRCDIR)image.h $(SRCDIR)image.c
	gcc -c $(SRCDIR)image.c -o $(OBJDIR)image.o

$(OBJDIR)statistics.o: $(SRCDIR)statistics.h $(SRCDIR)statistics.c
	gcc -c $(SRCDIR)statistics.c -o $(OBJDIR)statistics.o