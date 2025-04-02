# COMPILER #

CC=gcc -O3 -fsanitize=address,undefined -DPLEX_RECDIRECTORY=\"../resources/\" -DPLEX_HEADERLESSDIRECTORY=\"../headerlesstex/\" -DPLEX_ERRORCHECKDIRECTORY=\"./MMS_SideTales/error\"

# FLAGS #

FLAGS=-Wall -Wextra -Wno-sign-compare -Werror -Wno-strict-prototypes -Wno-nonnull -Wno-enum-compare -pedantic -std=c18 -march=native -I$(INC) -I$(HINC) -I$(HINC2) -Wno-unused-parameter
OBJFLAGS=-c
LOBJFLAGS=-fPIC
LIBFLAGS=-shared
LLIBS=-pthread -lrt -lm

# DIRECTORIES #

INC=./include/
HINC=./include/plex
HINC2=./include/mm_common
SRC=./src

OBJD=./obj
BIND=./bin
LIBD=./lib
EROD=./error

ROBJD=$(OBJD)/release
RBIND=$(BIND)/release
RLIBD=$(LIBD)/release

EROUTD=./error
THOUTD=./headerlesstex

# OBJECTS TO INCLUDE #

ROBJ=$(ROBJD)/game.o $(ROBJD)/unlock.o $(ROBJD)/minigame0ThePrize.o $(ROBJD)/minigame0Table.o $(ROBJD)/minigame0Player.o $(ROBJD)/minigame0Enemy.o $(ROBJD)/minigame0.o $(ROBJD)/minigame1Collision.o $(ROBJD)/minigame1PamAndCar.o $(ROBJD)/minigame1Environment.o $(ROBJD)/minigame1Obstructions.o $(ROBJD)/minigame1ObstructionManager.o $(ROBJD)/minigame1.o $(ROBJD)/minigame2GameoverSnapshot.o $(ROBJD)/minigame2Tutorial.o $(ROBJD)/minigame2GUI.o $(ROBJD)/minigame2CalmArea.o $(ROBJD)/minigame2Player.o $(ROBJD)/minigame2Enemy.o $(ROBJD)/minigame2Cover.o $(ROBJD)/minigame2Treasure.o $(ROBJD)/minigame2Room.o $(ROBJD)/minigame2PenultimateCut.o $(ROBJD)/minigame2FinalBoss.o $(ROBJD)/minigame2.o $(ROBJD)/mms0.o $(ROBJD)/mms0Outro.o $(ROBJD)/mms0OutroB.o $(ROBJD)/mms0Intro.o $(ROBJD)/mms0IntroB.o $(ROBJD)/mms1.o $(ROBJD)/mms2.o $(ROBJD)/mms3.o $(ROBJD)/mms3Section1.o $(ROBJD)/mms3Section2.o $(ROBJD)/mms3Section3.o $(ROBJD)/mms3Section4.o $(ROBJD)/mms3Section5.o

# PHONIES #

.PHONY: all release clean rebuild

all: release
clean: 
	rm $(ROBJD)/*; rm $(RBIND)/*; rm $(RLIBD)/*; rm $(EROUTD)/*; rm $(THOUTD)/*;

rebuild:
	make clean; make release;

release: $(ROBJ) $(RLIBD)/libMMS.so $(RBIND)/main

errclean:
	 rm $(EROUTD)/*;

thclean:
	 rm $(THOUTD)/*;

# HEADER RULES #

HRPLEX=$(HINC)/plex.h
HRMMCOMMON=$(HINC2)/mmcommon.h

HRLANGUAGE=$(INC)/meta/mms_language.h $(INC)/meta/language/mms_language_en.h $(INC)/meta/language/mms_errormess_en.h

HRFILEPATH=$(INC)/meta/mms_filepaths.h

HRUNLOCK=$(INC)/chapters/unlock.h $(SRC)/chapters/unlock.c

HRMINIGAME0=$(INC)/minigame/minigame0/meta.h $(INC)/minigame/minigame0/struct.h $(INC)/minigame/minigame0/function.h $(INC)/minigame/minigame0/minigame0.h $(SRC)/minigame/minigame0/theprize.c $(SRC)/minigame/minigame0/table.c $(SRC)/minigame/minigame0/player.c $(SRC)/minigame/minigame0/enemy.c $(SRC)/minigame/minigame0/minigame0.c $(HRUNLOCK) $(HRPLEX) $(HRMMCOMMON) $(HRLANGUAGE) $(HRFILEPATH)

HRMINIGAME1=$(INC)/minigame/minigame1/meta.h $(INC)/minigame/minigame1/struct.h $(INC)/minigame/minigame1/function.h $(INC)/minigame/minigame1/minigame1.h $(SRC)/minigame/minigame1/collision.c $(SRC)/minigame/minigame1/pamandcar.c $(SRC)/minigame/minigame1/environment.c $(SRC)/minigame/minigame1/minigame1.c $(SRC)/minigame/minigame1/obstructions.c $(SRC)/minigame/minigame1/obstructionmanager.c $(HRMMS0) $(HRUNLOCK) $(HRPLEX) $(HRMMCOMMON) $(HRLANGUAGE) $(HRFILEPATH)

HRMINIGAME2=$(INC)/minigame/minigame2/meta.h $(INC)/minigame/minigame2/struct.h $(INC)/minigame/minigame2/function.h $(INC)/minigame/minigame2/structbodies.h $(INC)/minigame/minigame2/minigame2.h $(SRC)/minigame/minigame2/gameoversnapshot.c $(SRC)/minigame/minigame2/tutorial.c $(SRC)/minigame/minigame2/gui.c $(SRC)/minigame/minigame2/calmarea.c $(SRC)/minigame/minigame2/player.c $(SRC)/minigame/minigame2/enemy.c $(SRC)/minigame/minigame2/cover.c $(SRC)/minigame/minigame2/treasure.c $(SRC)/minigame/minigame2/room.c $(SRC)/minigame/minigame2/penultimatecut.c $(SRC)/minigame/minigame2/finalboss.c $(SRC)/minigame/minigame2/minigame2.c $(HRUNLOCK) $(HRPLEX) $(HRMMCOMMON) $(HRLANGUAGE) $(HRFILEPATH)

HRMMS0=$(INC)/chapters/mms0.h $(SRC)/chapters/mms0/mms0.c $(SRC)/chapters/mms0/mms0Intro.c $(SRC)/chapters/mms0/mms0IntroB.c $(SRC)/chapters/mms0/mms0Outro.c $(SRC)/chapters/mms0/mms0OutroB.c $(HRMINIGAME0)
HRMMS1=$(INC)/chapters/mms1.h $(SRC)/chapters/mms1.c $(HRMINIGAME1)
HRMMS2=$(INC)/chapters/mms2.h $(SRC)/chapters/mms2.c $(HRMINIGAME2)
HRMMS3=$(INC)/chapters/mms3.h $(SRC)/chapters/mms3/mms3.c $(SRC)/chapters/mms3/section1.c $(SRC)/chapters/mms3/section2.c $(SRC)/chapters/mms3/section3.c $(SRC)/chapters/mms3/section4.c $(SRC)/chapters/mms3/section5.c $(HRUNLOCK) $(HRPLEX) $(HRMMCOMMON) $(HRLANGUAGE) $(HRFILEPATH)

HRGAME=$(INC)/game.h $(SRC)/game.c $(HRPLEX) $(HRMMCOMMON) $(HRLANGUAGE) $(HRFILEPATH) $(HRMMS0) $(HRMMS1) $(HRMMS2) $(HRMMS3)

# OBJ COMPILES #

$(ROBJD)/game.o : $(HRGAME)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/game.c -o $(ROBJD)/game.o

$(ROBJD)/unlock.o : $(HRUNLOCK)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/chapters/unlock.c -o $(ROBJD)/unlock.o

$(ROBJD)/minigame0ThePrize.o : $(HRMINIGAME0)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/minigame/minigame0/theprize.c -o $(ROBJD)/minigame0ThePrize.o

$(ROBJD)/minigame0Table.o : $(HRMINIGAME0)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/minigame/minigame0/table.c -o $(ROBJD)/minigame0Table.o

$(ROBJD)/minigame0Player.o : $(HRMINIGAME0)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/minigame/minigame0/player.c -o $(ROBJD)/minigame0Player.o

$(ROBJD)/minigame0Enemy.o : $(HRMINIGAME0)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/minigame/minigame0/enemy.c -o $(ROBJD)/minigame0Enemy.o

$(ROBJD)/minigame0.o : $(HRMINIGAME0)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/minigame/minigame0/minigame0.c -o $(ROBJD)/minigame0.o

$(ROBJD)/mms0.o : $(HRMMS0)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/chapters/mms0/mms0.c -o $(ROBJD)/mms0.o

$(ROBJD)/mms0Intro.o : $(HRMMS0)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/chapters/mms0/mms0Intro.c -o $(ROBJD)/mms0Intro.o

$(ROBJD)/mms0IntroB.o : $(HRMMS0)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/chapters/mms0/mms0IntroB.c -o $(ROBJD)/mms0IntroB.o

$(ROBJD)/mms0Outro.o : $(HRMMS0)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/chapters/mms0/mms0Outro.c -o $(ROBJD)/mms0Outro.o

$(ROBJD)/mms0OutroB.o : $(HRMMS0)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/chapters/mms0/mms0OutroB.c -o $(ROBJD)/mms0OutroB.o

$(ROBJD)/minigame1Obstructions.o : $(HRMINIGAME1)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/minigame/minigame1/obstructions.c -o $(ROBJD)/minigame1Obstructions.o

$(ROBJD)/minigame1ObstructionManager.o : $(HRMINIGAME1)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/minigame/minigame1/obstructionmanager.c -o $(ROBJD)/minigame1ObstructionManager.o

$(ROBJD)/minigame1Collision.o : $(HRMINIGAME1)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/minigame/minigame1/collision.c -o $(ROBJD)/minigame1Collision.o

$(ROBJD)/minigame1PamAndCar.o : $(HRMINIGAME1)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/minigame/minigame1/pamandcar.c -o $(ROBJD)/minigame1PamAndCar.o

$(ROBJD)/minigame1Environment.o : $(HRMINIGAME1)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/minigame/minigame1/environment.c -o $(ROBJD)/minigame1Environment.o

$(ROBJD)/minigame1.o : $(HRMINIGAME1)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/minigame/minigame1/minigame1.c -o $(ROBJD)/minigame1.o

$(ROBJD)/mms1.o : $(HRMMS1)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/chapters/mms1.c -o $(ROBJD)/mms1.o

$(ROBJD)/minigame2Tutorial.o : $(HRMINIGAME2)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/minigame/minigame2/tutorial.c -o $(ROBJD)/minigame2Tutorial.o

$(ROBJD)/minigame2GameoverSnapshot.o : $(HRMINIGAME2)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/minigame/minigame2/gameoversnapshot.c -o $(ROBJD)/minigame2GameoverSnapshot.o

$(ROBJD)/minigame2GUI.o : $(HRMINIGAME2)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/minigame/minigame2/gui.c -o $(ROBJD)/minigame2GUI.o

$(ROBJD)/minigame2CalmArea.o : $(HRMINIGAME2)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/minigame/minigame2/calmarea.c -o $(ROBJD)/minigame2CalmArea.o

$(ROBJD)/minigame2Player.o : $(HRMINIGAME2)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/minigame/minigame2/player.c -o $(ROBJD)/minigame2Player.o

$(ROBJD)/minigame2Enemy.o : $(HRMINIGAME2)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/minigame/minigame2/enemy.c -o $(ROBJD)/minigame2Enemy.o

$(ROBJD)/minigame2Cover.o : $(HRMINIGAME2)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/minigame/minigame2/cover.c -o $(ROBJD)/minigame2Cover.o

$(ROBJD)/minigame2Treasure.o : $(HRMINIGAME2)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/minigame/minigame2/treasure.c -o $(ROBJD)/minigame2Treasure.o

$(ROBJD)/minigame2Room.o : $(HRMINIGAME2)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/minigame/minigame2/room.c -o $(ROBJD)/minigame2Room.o

$(ROBJD)/minigame2PenultimateCut.o : $(HRMINIGAME2)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/minigame/minigame2/penultimatecut.c -o $(ROBJD)/minigame2PenultimateCut.o

$(ROBJD)/minigame2FinalBoss.o : $(HRMINIGAME2)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/minigame/minigame2/finalboss.c -o $(ROBJD)/minigame2FinalBoss.o

$(ROBJD)/minigame2.o : $(HRMINIGAME2)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/minigame/minigame2/minigame2.c -o $(ROBJD)/minigame2.o

$(ROBJD)/mms2.o : $(HRMMS2)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/chapters/mms2.c -o $(ROBJD)/mms2.o

$(ROBJD)/mms3.o : $(HRMMS3)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/chapters/mms3/mms3.c -o $(ROBJD)/mms3.o

$(ROBJD)/mms3Section1.o : $(HRMMS3)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/chapters/mms3/section1.c -o $(ROBJD)/mms3Section1.o

$(ROBJD)/mms3Section2.o : $(HRMMS3)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/chapters/mms3/section2.c -o $(ROBJD)/mms3Section2.o

$(ROBJD)/mms3Section3.o : $(HRMMS3)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/chapters/mms3/section3.c -o $(ROBJD)/mms3Section3.o

$(ROBJD)/mms3Section4.o : $(HRMMS3)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/chapters/mms3/section4.c -o $(ROBJD)/mms3Section4.o

$(ROBJD)/mms3Section5.o : $(HRMMS3)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/chapters/mms3/section5.c -o $(ROBJD)/mms3Section5.o

# LIBRARY COMPILES #

$(RLIBD)/libMMS.so : $(ROBJ)
	$(CC) $(LIBFLAGS) $(ROBJ) -o $(RLIBD)/libMMS.so -L$(RLIBD) -lPLEX -lMM_COMMON $(LLIBS)

# BINARY COMPILES #

$(RBIND)/main : $(SRC)/main.c $(HRGAME)
	$(CC) $(FLAGS) -Wno-unused-parameter $(SRC)/main.c -o $(RBIND)/main -L$(RLIBD) -lPLEX -lMM_COMMON -lMMS $(LLIBS)
