# COMPILER #

CC=gcc -O3 -fsanitize=address,undefined -DPLEX_RECDIRECTORY=\"../resources/\" -DPLEX_HEADERLESSDIRECTORY=\"../headerlesstex/\" -DPLEX_ERRORCHECKDIRECTORY=\"./error\"

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
LIBD=./lib

ROBJD=$(OBJD)/release

RLIBD=$(LIBD)/release

# OBJECTS TO INCLUDE #

ROBJ=$(ROBJD)/mmcommon.o $(ROBJD)/mmsoundeffects.o $(ROBJD)/mmthememain.o $(ROBJD)/mmthemeextrap.o $(ROBJD)/mmthemenewsroom.o $(ROBJD)/mmthemecomedy.o $(ROBJD)/mmthemepanic.o $(ROBJD)/mmthemedarkcity.o $(ROBJD)/mmthemepamaleana.o $(ROBJD)/mmthemesuspense.o $(ROBJD)/mmthemedaytoday.o $(ROBJD)/mmthemedream.o $(ROBJD)/mmthemedesertwinds.o $(ROBJD)/mmthemedeserttown.o $(ROBJD)/mmthemeaggression.o $(ROBJD)/mmthemeworkday.o $(ROBJD)/mmthemefear.o $(ROBJD)/mmthemepunk.o $(ROBJD)/mmthememetal.o $(ROBJD)/mmthemestrife.o $(ROBJD)/mmthemes.o

# PHONIES #

.PHONY: all release clean rebuild

all: release
clean: 
	rm $(ROBJD)/*; rm $(RLIBD)/*;

rebuild:
	make clean; make release;

release: $(ROBJ) $(RLIBD)/libMM_COMMON.so

# HEADER RULES #

HRPLEX=$(HINC)/plex.h

HRLANGUAGE=$(INC)/meta/mmcommon_language.h $(INC)/meta/language/mmcommon_language_en.h
HRFILENAME=$(INC)/meta/mmcommon_filepaths.h $(HRLANGUAGE)

HRMMCOMMON=$(INC)/mmcommon.h $(SRC)/mmcommon.c $(HRPLEX)

HRMMSOUNDEFFECTS=$(SRC)/themes/mmsoundeffects.c $(HRMMCOMMON)

HRMMTHEMEMAIN=$(SRC)/themes/mmthememain.c $(HRMMCOMMON)
HRMMTHEMEEXTRAP=$(SRC)/themes/mmthemeextrap.c $(HRMMCOMMON)
HRMMTHEMENEWSROOM=$(SRC)/themes/mmthemenewsroom.c $(HRMMCOMMON)
HRMMTHEMECOMEDY=$(SRC)/themes/mmthemecomedy.c $(HRMMCOMMON)
HRMMTHEMEPANIC=$(SRC)/themes/mmthemepanic.c $(HRMMCOMMON)
HRMMTHEMEDARKCITY=$(SRC)/themes/mmthemedarkcity.c $(HRMMCOMMON)
HRMMTHEMEPAMALEANA=$(SRC)/themes/mmthemepamaleana.c $(HRMMCOMMON)
HRMMTHEMESUSPENSE=$(SRC)/themes/mmthemesuspense.c $(HRMMCOMMON)
HRMMTHEMEDAYTODAY=$(SRC)/themes/mmthemedaytoday.c $(HRMMCOMMON)
HRMMTHEMEDREAM=$(SRC)/themes/mmthemedream.c $(HRMMCOMMON)
HRMMTHEMEDESERTWINDS=$(SRC)/themes/mmthemedesertwinds.c $(HRMMCOMMON)
HRMMTHEMEDESERTTOWN=$(SRC)/themes/mmthemedeserttown.c $(HRMMCOMMON)
HRMMTHEMEAGGRESSION=$(SRC)/themes/mmthemeaggression.c $(HRMMCOMMON)
HRMMTHEMEWORKDAY=$(SRC)/themes/mmthemeworkday.c $(HRMMCOMMON)
HRMMTHEMEFEAR=$(SRC)/themes/mmthemefear.c $(HRMMCOMMON)
HRMMTHEMEPUNK=$(SRC)/themes/mmthemepunk.c $(HRMMCOMMON)
HRMMTHEMEMETAL=$(SRC)/themes/mmthememetal.c $(HRMMCOMMON)
HRMMTHEMESTRIFE=$(SRC)/themes/mmthemestrife.c $(HRMMCOMMON)

HRMMTHEMES=$(INC)/mmthemes.h $(SRC)/mmthemes.c $(HRPLEX) $(HRFILENAME) $(HRMMSOUNDEFFECTS) $(HRMMTHEMEMAIN) $(HRMMTHEMEEXTRAP) $(HRMMTHEMENEWSROOM) $(HRMMTHEMECOMEDY) $(HRMMTHEMEPANIC) $(HRMMTHEMEDARKCITY) $(HRMMTHEMEPAMALEANA) $(HRMMTHEMESUSPENSE) $(HRMMTHEMEDAYTODAY) $(HRMMTHEMEDREAM) $(HRMMTHEMEDESRTWINDS) $(HRMMTHEMEDESERTTOWN) $(HRMMTHEMEAGGRESSION) $(HRMMTHEMEWORKDAY) $(HRMMTHEMEFEAR) $(HRMMTHEMEPUNK) $(HRMMTHEMEMETAL) $(HRMMTHEMESTRIFE)

# OBJ COMPILES #

## RELEASE ##

$(ROBJD)/mmcommon.o : $(HRMMCOMMON)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/mmcommon.c -o $(ROBJD)/mmcommon.o

$(ROBJD)/mmsoundeffects.o : $(HRMMSOUNDEFFECTS)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/themes/mmsoundeffects.c -o $(ROBJD)/mmsoundeffects.o

$(ROBJD)/mmthememain.o : $(HRMMTHEMEMAIN)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/themes/mmthememain.c -o $(ROBJD)/mmthememain.o

$(ROBJD)/mmthemeextrap.o : $(HRMMTHEMEEXTRAP)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/themes/mmthemeextrap.c -o $(ROBJD)/mmthemeextrap.o

$(ROBJD)/mmthemenewsroom.o : $(HRMMTHEMENEWSROOM)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/themes/mmthemenewsroom.c -o $(ROBJD)/mmthemenewsroom.o

$(ROBJD)/mmthemecomedy.o : $(HRMMTHEMECOMEDY)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/themes/mmthemecomedy.c -o $(ROBJD)/mmthemecomedy.o

$(ROBJD)/mmthemepanic.o : $(HRMMTHEMEPANIC)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/themes/mmthemepanic.c -o $(ROBJD)/mmthemepanic.o

$(ROBJD)/mmthemedarkcity.o : $(HRMMTHEMEDARKCITY)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/themes/mmthemedarkcity.c -o $(ROBJD)/mmthemedarkcity.o

$(ROBJD)/mmthemepamaleana.o : $(HRMMTHEMEPAMALEANA)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/themes/mmthemepamaleana.c -o $(ROBJD)/mmthemepamaleana.o

$(ROBJD)/mmthemesuspense.o : $(HRMMTHEMESUSPENSE)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/themes/mmthemesuspense.c -o $(ROBJD)/mmthemesuspense.o

$(ROBJD)/mmthemedaytoday.o : $(HRMMTHEMEDAYTODAY)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/themes/mmthemedaytoday.c -o $(ROBJD)/mmthemedaytoday.o

$(ROBJD)/mmthemedream.o : $(HRMMTHEMEDREAM)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/themes/mmthemedream.c -o $(ROBJD)/mmthemedream.o

$(ROBJD)/mmthemedesertwinds.o : $(HRMMTHEMEDESERTWINDS)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/themes/mmthemedesertwinds.c -o $(ROBJD)/mmthemedesertwinds.o

$(ROBJD)/mmthemedeserttown.o : $(HRMMTHEMEDESERTTOWN)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/themes/mmthemedeserttown.c -o $(ROBJD)/mmthemedeserttown.o

$(ROBJD)/mmthemeaggression.o : $(HRMMTHEMEAGGRESSION)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/themes/mmthemeaggression.c -o $(ROBJD)/mmthemeaggression.o

$(ROBJD)/mmthemeworkday.o : $(HRMMTHEMEWORKDAY)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/themes/mmthemeworkday.c -o $(ROBJD)/mmthemeworkday.o

$(ROBJD)/mmthemefear.o : $(HRMMTHEMEFEAR)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/themes/mmthemefear.c -o $(ROBJD)/mmthemefear.o

$(ROBJD)/mmthemepunk.o : $(HRMMTHEMEPUNK)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/themes/mmthemepunk.c -o $(ROBJD)/mmthemepunk.o

$(ROBJD)/mmthememetal.o : $(HRMMTHEMEMETAL)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/themes/mmthememetal.c -o $(ROBJD)/mmthememetal.o

$(ROBJD)/mmthemestrife.o : $(HRMMTHEMESTRIFE)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/themes/mmthemestrife.c -o $(ROBJD)/mmthemestrife.o

$(ROBJD)/mmthemes.o : $(HRMMTHEMES)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/mmthemes.c -o $(ROBJD)/mmthemes.o

# LIBRARY COMPILES #

$(RLIBD)/libMM_COMMON.so : $(ROBJ)
	$(CC) $(LIBFLAGS) $(ROBJ) -o $(RLIBD)/libMM_COMMON.so -L$(RLIBD) -lPLEX $(LLIBS)
