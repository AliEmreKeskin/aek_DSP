SRCDIR=src/
BUILDDIR=build/
OBJDIR=$(BUILDDIR)obj/

program:$(OBJDIR)main.o $(OBJDIR)image.o $(OBJDIR)statistics.o $(OBJDIR)conv.o $(OBJDIR)FIR_filter.o $(OBJDIR)DFT.o
	gcc -o program $(OBJDIR)main.o $(OBJDIR)image.o -lm $(OBJDIR)statistics.o $(OBJDIR)conv.o $(OBJDIR)FIR_filter.o $(OBJDIR)DFT.o

$(OBJDIR)main.o: $(SRCDIR)main.c $(SRCDIR)statistics.h $(SRCDIR)image.h $(SRCDIR)conv.h $(SRCDIR)FIR_filter.h $(SRCDIR)DFT.h
	gcc -c $(SRCDIR)main.c -o $(OBJDIR)main.o

$(OBJDIR)image.o: $(SRCDIR)image.h $(SRCDIR)image.c
	gcc -c $(SRCDIR)image.c -o $(OBJDIR)image.o

$(OBJDIR)statistics.o: $(SRCDIR)statistics.h $(SRCDIR)statistics.c
	gcc -c $(SRCDIR)statistics.c -o $(OBJDIR)statistics.o

$(OBJDIR)conv.o: $(SRCDIR)conv.h $(SRCDIR)conv.c
	gcc -c $(SRCDIR)conv.c -o $(OBJDIR)conv.o

$(OBJDIR)FIR_filter.o: $(SRCDIR)FIR_filter.h $(SRCDIR)FIR_filter.c
	gcc -c $(SRCDIR)FIR_filter.c -o $(OBJDIR)FIR_filter.o

$(OBJDIR)DFT.o: $(SRCDIR)DFT.h $(SRCDIR)DFT.c
	gcc -c $(SRCDIR)DFT.c -o $(OBJDIR)DFT.o