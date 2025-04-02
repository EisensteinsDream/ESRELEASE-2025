# COMPILER #

CC=gcc -O3 -fsanitize=address,undefined
CCD=gcc -g3

# FLAGS #

FLAGS=-Wall -Wextra -Wno-sign-compare -Werror -Wno-strict-prototypes -pedantic -std=c18 -march=native -I$(INC) -I$(HINC) -Wno-unused-parameter
OBJFLAGS=-c
LOBJFLAGS=-fPIC
LIBFLAGS=-shared
LLIBS=-pthread -lrt -lm

# DIRECTORIES #

INC=./include/
HINC=./include/plex
SRC=./src

OBJD=./obj
BIND=./bin
LIBD=./lib

ROBJD=$(OBJD)/release
DOBJD=$(OBJD)/debug

RBIND=$(BIND)/release
DBIND=$(BIND)/debug

RLIBD=$(LIBD)/release
DLIBD=$(LIBD)/debug

EROUTD=./error
THOUTD=./headerlesstex

# OBJECTS TO INCLUDE #

ROBJ=$(ROBJD)/game.o

DOBJ=$(DOBJD)/game.o

# PHONIES #

.PHONY: all release debug clean rclean dclean rebuild rrebuild drebuild errclean htclean

all: release debug
clean: 
	rm $(ROBJD)/*; rm $(RBIND)/*; rm $(RLIBD)/*; rm $(DOBJD)/*; rm $(DBIND)/*; rm $(DLIBD)/*; rm $(EROUTD)/*; rm $(THOUTD)/*;

rebuild:
	make rclean; make dclean; sh updateplex.sh; make release; make debug;

release: $(ROBJ) $(RLIBD)/lib(PROJ).so $(RBIND)/main
debug: $(DOBJ) $(DLIBD)/lib(PROJ).so $(DBIND)/main

rclean:
	rm $(ROBJD)/*; rm $(RBIND)/*; rm $(RLIBD)/*; rm $(EROUTD)/*; rm $(THOUTD)/*;

dclean:
	rm $(DOBJD)/*; rm $(DBIND)/*; rm $(DLIBD)/*; rm $(EROUTD)/*; rm $(THOUTD)/*;

rrebuild:
	make rclean; sh updateplex.sh; make release;

drebuild:
	make dclean; sh updateplex.sh; make debug;

errclean:
	 rm $(EROUTD)/*;

thclean:
	 rm $(THOUTD)/*;

# HEADER RULES #

HRPLEX=$(HINC)/plex.h

HRLANGUAGE=$(INC)/meta/proj_language.h $(INC)/meta/language/proj_language_en.h
HRFILENAME=$(INC)/meta/proj_filepaths.h $(HRLANGUAGE)

HRGAME=$(INC)/game.h $(SRC)/game.c $(HRPLEX) $(HRFILENAME)

# OBJ COMPILES #

## RELEASE ##

$(ROBJD)/game.o : $(HRGAME)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/game.c -o $(ROBJD)/game.o

## DEBUG ##

$(DOBJD)/game.o : $(HRGAME)
	$(CCD) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/game.c -o $(DOBJD)/game.o

# LIBRARY COMPILES #

$(RLIBD)/lib(PROJ).so : $(ROBJ)
	$(CC) $(LIBFLAGS) $(ROBJ) -o $(RLIBD)/lib(PROJ).so -L$(RLIBD) -lPLEX $(LLIBS)

$(DLIBD)/lib(PROJ).so : $(DOBJ)
	$(CCD) $(LIBFLAGS) $(DOBJ) -o $(DLIBD)/lib(PROJ).so -L$(DLIBD) -lPLEX $(LLIBS)

# BINARY COMPILES #

$(RBIND)/main : $(SRC)/main.c
	$(CC) $(FLAGS) $(SRC)/main.c -o $(RBIND)/main -L$(RLIBD) -lPLEX -l(PROJ) $(LLIBS)

$(DBIND)/main : $(SRC)/main.c
	$(CCD) $(FLAGS) $(SRC)/main.c -o $(DBIND)/main -L$(DLIBD) -lPLEX -l(PROJ) $(LLIBS)
