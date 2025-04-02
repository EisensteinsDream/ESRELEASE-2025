CC=gcc -O3 -fsanitize=address,undefined -DPLEX_RECDIRECTORY=\"$(RECFOLDER)\" -DPLEX_HEADERLESSDIRECTORY=\"$(HEADERLESSDIRECTORY)\" -DPLEX_ERRORCHECKDIRECTORY="\"$(ERRORDIRECTORY)\""
CCD=gcc -g3 -DPLEX_DEBUGMOUSEMODE=1 -DPLEX_RECDIRECTORY=\"$(RECFOLDER)\" -DPLEX_HEADERLESSDIRECTORY=\"$(HEADERLESSDIRECTORY)\" -DPLEX_ERRORCHECKDIRECTORY="\"$(ERRORDIRECTORY)\""

# FLAGS #

FLAGS=-Wall -Wextra -Wno-sign-compare -Werror -Wno-strict-prototypes -Wno-unused-but-set-parameter -pedantic -std=c18 -march=native -I$(INC) -Wno-unused-parameter
OBJFLAGS=-c
LOBJFLAGS=-fPIC
LIBFLAGS=-shared
LIBS=-lsndfile -lSDL2 -lSDL2_image
LLIBS=-pthread -lm -lrt -lportaudio

# DIRECTORIES #

INC=./include
SRC=./src

OBJD=./obj
LIBD=./lib

ROBJD=$(OBJD)/release
DOBJD=$(OBJD)/debug

RLIBD=$(LIBD)/release
DLIBD=$(LIBD)/debug

# OBJECTS TO INCLUDE #

ROBJ=$(ROBJD)/terminate.o $(ROBJD)/memprofile.o $(ROBJD)/protoexpandarray.o $(ROBJD)/mem.o $(ROBJD)/expandarray.o $(ROBJD)/fakestrings.o $(ROBJD)/math.o $(ROBJD)/error.o $(ROBJD)/timer.o $(ROBJD)/globaltime.o $(ROBJD)/defaults.o $(ROBJD)/graphics_low.o $(ROBJD)/texture_low.o $(ROBJD)/window.o $(ROBJD)/input.o $(ROBJD)/texture.o $(ROBJD)/graphics.o $(ROBJD)/animationplate.o $(ROBJD)/animation.o $(ROBJD)/sprite.o $(ROBJD)/screeneffects.o $(ROBJD)/sound.o $(ROBJD)/generator.o $(ROBJD)/prominencemachine.o $(ROBJD)/fileparse.o $(ROBJD)/directory.o $(ROBJD)/stringbank.o $(ROBJD)/scroller.o $(ROBJD)/datetime.o $(ROBJD)/spritetheater.o $(ROBJD)/plex.o

DOBJ=$(DOBJD)/terminate.o $(DOBJD)/memprofile.o $(DOBJD)/protoexpandarray.o $(DOBJD)/mem.o $(DOBJD)/expandarray.o  $(DOBJD)/fakestrings.o $(DOBJD)/math.o $(DOBJD)/error.o $(DOBJD)/timer.o $(DOBJD)/globaltime.o $(DOBJD)/defaults.o $(DOBJD)/graphics_low.o $(DOBJD)/texture_low.o $(DOBJD)/window.o $(DOBJD)/input.o $(DOBJD)/texture.o $(DOBJD)/graphics.o $(DOBJD)/animationplate.o $(DOBJD)/animation.o $(DOBJD)/sprite.o $(DOBJD)/screeneffects.o $(DOBJD)/sound.o $(DOBJD)/generator.o $(DOBJD)/prominencemachine.o $(DOBJD)/fileparse.o $(DOBJD)/directory.o $(DOBJD)/stringbank.o $(DOBJD)/scroller.o $(DOBJD)/datetime.o $(DOBJD)/spritetheater.o $(DOBJD)/plex.o

# PHONIES #

.PHONY: all release debug clean rclean dclean rebuild rrebuild drebuild

all: release debug
clean: 
	rm $(ROBJD)/*; rm $(RLIBD)/*; rm $(DOBJD)/*; rm $(DLIBD)/*;

rebuild:
	make rclean; make dclean; make release; make debug;

release: $(ROBJ) $(RLIBD)/libPLEX.so
debug: $(DOBJ) $(DLIBD)/libPLEX.so

rclean:
	rm $(ROBJD)/*; rm $(RLIBD)/*;

dclean:
	rm $(DOBJD)/*; rm $(DLIBD)/*;

rrebuild:
	make rclean; make release;

drebuild:
	make dclean; make debug;

# HEADER RULES #

HROSADAPT=$(INC)/meta/osadapt.h
HRHARDLIMITS=$(INC)/meta/hardlimits.h
HRSTANDARDNUMBERS=$(INC)/meta/standardnumbers.h
HRLANGUAGE=$(INC)/meta/language.h $(INC)/meta/language/language_en.h
HRERRORMESS=$(INC)/meta/errormess/errormess_en.h $(INC)/meta/errormess.h $(HRLANGUAGE)

HRCINCLUDE=$(INC)/meta/cinclude.h $(HROSADAPT) $(HRHARDLIMITS) $(HRERRORMESS) $(HRFILELOC) $(HRSTANDARDNUMBERS)

HRTERMINATE=$(INC)/terminate.h $(SRC)/terminate.c $(HRCINCLUDE)

HRMEMPROFILE=$(INC)/mem/memprofile.h $(SRC)/mem/memprofile.c $(HRCINCLUDE)
HRPROTOEXPANDARRAY=$(INC)/mem/protoexpandarray.h $(SRC)/mem/protoexpandarray.c $(HRCINCLUDE)
HRMEM=$(INC)/mem/mem.h $(SRC)/mem/mem.c $(HRPROTOEXPANDARRAY) $(HRMEMPROFILE)
HREXPANDARRAY=$(INC)/mem/expandarray.h $(SRC)/mem/expandarray.c $(HRMEM)

HRFAKESTRINGS=$(INC)/utility/fakestrings.h $(SRC)/utility/fakestrings.c $(HRCINCLUDE)
HRMATH=$(INC)/utility/math.h $(SRC)/utility/math.c $(HRCINCLUDE)

HRTIMER=$(INC)/utility/timer.h $(SRC)/utility/timer.c $(HRFAKESTRINGS)

HRGLOBALTIMER=$(INC)/utility/globaltime.h $(SRC)/utility/globaltime.c $(HRTIMER)

HRDEFAULTS=$(INC)/meta/defaultnames.h $(INC)/meta/defaultnames/defaultnames_en.h $(INC)/utility/defaults.h $(SRC)/utility/defaults.c $(HRCINCLUDE) $(HRPROTOEXPANDARRAY) $(HRMEMPROFILE)

HRERROR=$(INC)/utility/error.h $(SRC)/utility/error.c $(HRTERMINATE)

HRTEXTURE_LOW=$(INC)/windowing/texture_low.h $(SRC)/windowing/texture_low.c $(SRC)/windowing/texture_low/texture_low_SDL.c.h $(HRDEFAULTS)

HRGRAPHICS_LOW=$(INC)/windowing/graphics_low.h $(SRC)/windowing/graphics_low.c $(SRC)/windowing/graphics_low/graphics_low_SDL.c.h $(HRTEXTURE_LOW)

HRWINDOW=$(INC)/windowing/window.h $(SRC)/windowing/window.c $(HRGRAPHICS_LOW)
HRINPUT=$(INC)/windowing/input.h $(SRC)/windowing/input.c $(HRWINDOW) $(HRMATH) $(HRTIMER) $(HRTERMINATE)
HRTEXTURE=$(INC)/windowing/texture.h $(SRC)/windowing/texture.c $(HRWINDOW)
HRGRAPHICS=$(INC)/windowing/graphics.h $(SRC)/windowing/graphics.c $(HRTEXTURE) $(HRINPUT) $(HRMEMPROFILE)
HRANIMATIONPLATE=$(INC)/windowing/animationplate.h $(SRC)/windowing/animationplate.c $(HRGRAPHICS)
HRANIMATION=$(INC)/windowing/animation.h $(SRC)/windowing/animation.c $(HRANIMATIONPLATE)
HRSPRITE=$(INC)/windowing/sprite.h $(SRC)/windowing/sprite.c $(HRANIMATION)

HRSCREENEFFECTS=$(INC)/windowing/screeneffects.h $(SRC)/windowing/screeneffects.c $(HRGRAPHICS)

HRSOUND=$(INC)/sound/sound.h $(SRC)/sound/sound.c $(HRCINCLUDE)

HRGENERATOR=$(INC)/utility/generator.h $(SRC)/utility/generator.c $(HRMATH) $(HRMEMPROFILE)

HRPROMINENCEMACHINE=$(INC)/utility/prominencemachine.h $(SRC)/utility/prominencemachine.c $(HRMATH) $(HRMEMPROFILE)

HRFILEPARSE=$(INC)/utility/fileparse.h $(SRC)/utility/fileparse.c $(HRFAKESTRINGS) $(HRMEMPROFILE)

HRDIRECTORY=$(INC)/utility/directory.h $(SRC)/utility/directory.c $(SRC)/utility/directory_unix.c.h $(HRFAKESTRINGS)

HRSTRINGBANK=$(INC)/utility/stringbank.h $(SRC)/utility/stringbank.c $(HRFILEPARSE)

HRSCROLLER=$(INC)/utility/scroller.h $(SRC)/utility/scroller.c $(HRCINCLUDE)

HRDATETIME=$(INC)/utility/datetime.h $(SRC)/utility/datetime.c $(HRCINCLUDE)

HRSPRITETHEATER=$(INC)/utility/spritetheater.h $(SRC)/utility/spritetheater.c $(HRGRAPHICS) $(HRTIMER) $(HRMEMPROFILE)

HRPLEX=$(INC)/plex.h $(SRC)/plex.c $(HRANIMATION) $(HRERROR) $(HRGENERATOR) $(HRFILEPARSE) $(HRSTRINGBANK) $(HRSCROLLER)

# OBJ COMPILES #

## RELEASE ##

$(ROBJD)/terminate.o : $(HRTERMINATE)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/terminate.c -o $(ROBJD)/terminate.o

$(ROBJD)/memprofile.o : $(HRMEMPROFILE)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/mem/memprofile.c -o $(ROBJD)/memprofile.o

$(ROBJD)/protoexpandarray.o : $(HRPROTOEXPANDARRAY)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/mem/protoexpandarray.c -o $(ROBJD)/protoexpandarray.o

$(ROBJD)/mem.o : $(HRMEM)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/mem/mem.c -o $(ROBJD)/mem.o

$(ROBJD)/expandarray.o : $(HREXPANDARRAY)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/mem/expandarray.c -o $(ROBJD)/expandarray.o

$(ROBJD)/fakestrings.o : $(HRFAKESTRINGS)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/utility/fakestrings.c -o $(ROBJD)/fakestrings.o

$(ROBJD)/math.o : $(HRMATH)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/utility/math.c -o $(ROBJD)/math.o

$(ROBJD)/error.o : $(HRERROR)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/utility/error.c -o $(ROBJD)/error.o

$(ROBJD)/timer.o : $(HRTIMER)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/utility/timer.c -o $(ROBJD)/timer.o

$(ROBJD)/globaltime.o : $(HRGLOBALTIMER)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/utility/globaltime.c -o $(ROBJD)/globaltime.o

$(ROBJD)/defaults.o : $(HRDEFAULTS)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/utility/defaults.c -o $(ROBJD)/defaults.o

$(ROBJD)/graphics_low.o : $(HRWINDOW)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/windowing/graphics_low.c -o $(ROBJD)/graphics_low.o

$(ROBJD)/texture_low.o : $(HRWINDOW)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/windowing/texture_low.c -o $(ROBJD)/texture_low.o

$(ROBJD)/window.o : $(HRWINDOW)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/windowing/window.c -o $(ROBJD)/window.o

$(ROBJD)/input.o : $(HRINPUT)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/windowing/input.c -o $(ROBJD)/input.o

$(ROBJD)/texture.o : $(HRTEXTURE)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/windowing/texture.c -o $(ROBJD)/texture.o

$(ROBJD)/graphics.o : $(HRGRAPHICS)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/windowing/graphics.c -o $(ROBJD)/graphics.o

$(ROBJD)/animationplate.o : $(HRANIMATIONPLATE)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/windowing/animationplate.c -o $(ROBJD)/animationplate.o

$(ROBJD)/animation.o : $(HRANIMATION)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/windowing/animation.c -o $(ROBJD)/animation.o

$(ROBJD)/sprite.o : $(HRSPRITE)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/windowing/sprite.c -o $(ROBJD)/sprite.o

$(ROBJD)/screeneffects.o : $(HRSCREENEFFECTS)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/windowing/screeneffects.c -o $(ROBJD)/screeneffects.o

$(ROBJD)/sound.o : $(HRSOUND)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/sound/sound.c -o $(ROBJD)/sound.o

$(ROBJD)/generator.o : $(HRGENERATOR)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/utility/generator.c -o $(ROBJD)/generator.o

$(ROBJD)/prominencemachine.o : $(HRPROMINENCEMACHINE)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/utility/prominencemachine.c -o $(ROBJD)/prominencemachine.o

$(ROBJD)/fileparse.o : $(HRFILEPARSE)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/utility/fileparse.c -o $(ROBJD)/fileparse.o

$(ROBJD)/directory.o : $(HRDIRECTORY)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/utility/directory.c -o $(ROBJD)/directory.o

$(ROBJD)/stringbank.o : $(HRSTRINGBANK)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/utility/stringbank.c -o $(ROBJD)/stringbank.o

$(ROBJD)/scroller.o : $(HRSCROLLER)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/utility/scroller.c -o $(ROBJD)/scroller.o

$(ROBJD)/datetime.o : $(HRDATETIME)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/utility/datetime.c -o $(ROBJD)/datetime.o

$(ROBJD)/spritetheater.o : $(HRSPRITETHEATER)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/utility/spritetheater.c -o $(ROBJD)/spritetheater.o

$(ROBJD)/plex.o : $(HRPLEX)
	$(CC) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/plex.c -o $(ROBJD)/plex.o

## DEBUG ##

$(DOBJD)/terminate.o : $(HRTERMINATE)
	$(CCD) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/terminate.c -o $(DOBJD)/terminate.o

$(DOBJD)/memprofile.o : $(HRMEMPROFILE)
	$(CCD) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/mem/memprofile.c -o $(DOBJD)/memprofile.o

$(DOBJD)/protoexpandarray.o : $(HRPROTOEXPANDARRAY)
	$(CCD) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/mem/protoexpandarray.c -o $(DOBJD)/protoexpandarray.o

$(DOBJD)/mem.o : $(HRMEM)
	$(CCD) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/mem/mem.c -o $(DOBJD)/mem.o

$(DOBJD)/expandarray.o : $(HREXPANDARRAY)
	$(CCD) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/mem/expandarray.c -o $(DOBJD)/expandarray.o

$(DOBJD)/fakestrings.o : $(HRFAKESTRINGS)
	$(CCD) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/utility/fakestrings.c -o $(DOBJD)/fakestrings.o

$(DOBJD)/math.o : $(HRMATH)
	$(CCD) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/utility/math.c -o $(DOBJD)/math.o

$(DOBJD)/error.o : $(HRERROR)
	$(CCD) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/utility/error.c -o $(DOBJD)/error.o

$(DOBJD)/timer.o : $(HRTIMER)
	$(CCD) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/utility/timer.c -o $(DOBJD)/timer.o

$(DOBJD)/globaltime.o : $(HRGLOBALTIMER)
	$(CCD) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/utility/globaltime.c -o $(DOBJD)/globaltime.o

$(DOBJD)/defaults.o : $(HRDEFAULTS)
	$(CCD) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/utility/defaults.c -o $(DOBJD)/defaults.o

$(DOBJD)/graphics_low.o : $(HRWINDOW)
	$(CCD) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/windowing/graphics_low.c -o $(DOBJD)/graphics_low.o

$(DOBJD)/texture_low.o : $(HRWINDOW)
	$(CCD) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/windowing/texture_low.c -o $(DOBJD)/texture_low.o

$(DOBJD)/window.o : $(HRWINDOW)
	$(CCD) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/windowing/window.c -o $(DOBJD)/window.o

$(DOBJD)/fileparse.o : $(HRFILEPARSE)
	$(CCD) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/utility/fileparse.c -o $(DOBJD)/fileparse.o

$(DOBJD)/directory.o : $(HRDIRECTORY)
	$(CCD) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/utility/directory.c -o $(DOBJD)/directory.o

$(DOBJD)/stringbank.o : $(HRSTRINGBANK)
	$(CCD) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/utility/stringbank.c -o $(DOBJD)/stringbank.o

$(DOBJD)/scroller.o : $(HRSCROLLER)
	$(CCD) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/utility/scroller.c -o $(DOBJD)/scroller.o

$(DOBJD)/datetime.o : $(HRDATETIME)
	$(CCD) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/utility/datetime.c -o $(DOBJD)/datetime.o

$(DOBJD)/input.o : $(HRINPUT)
	$(CCD) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/windowing/input.c -o $(DOBJD)/input.o

$(DOBJD)/texture.o : $(HRTEXTURE)
	$(CCD) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/windowing/texture.c -o $(DOBJD)/texture.o

$(DOBJD)/graphics.o : $(HRGRAPHICS)
	$(CCD) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/windowing/graphics.c -o $(DOBJD)/graphics.o

$(DOBJD)/animationplate.o : $(HRANIMATIONPLATE)
	$(CCD) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/windowing/animationplate.c -o $(DOBJD)/animationplate.o

$(DOBJD)/animation.o : $(HRANIMATION)
	$(CCD) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/windowing/animation.c -o $(DOBJD)/animation.o

$(DOBJD)/sprite.o : $(HRSPRITE)
	$(CCD) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/windowing/sprite.c -o $(DOBJD)/sprite.o

$(DOBJD)/screeneffects.o : $(HRSCREENEFFECTS)
	$(CCD) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/windowing/screeneffects.c -o $(DOBJD)/screeneffects.o

$(DOBJD)/sound.o : $(HRSOUND)
	$(CCD) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/sound/sound.c -o $(DOBJD)/sound.o

$(DOBJD)/generator.o : $(HRGENERATOR)
	$(CCD) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/utility/generator.c -o $(DOBJD)/generator.o

$(DOBJD)/prominencemachine.o : $(HRPROMINENCEMACHINE)
	$(CCD) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/utility/prominencemachine.c -o $(DOBJD)/prominencemachine.o

$(DOBJD)/spritetheater.o : $(HRSPRITETHEATER)
	$(CCD) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/utility/spritetheater.c -o $(DOBJD)/spritetheater.o

$(DOBJD)/plex.o : $(HRPLEX)
	$(CCD) $(FLAGS) $(OBJFLAGS) $(LOBJFLAGS) $(SRC)/plex.c -o $(DOBJD)/plex.o

# LIBRARY COMPILES #

$(RLIBD)/libPLEX.so : $(ROBJ) $(HRPLEX)
	$(CC) $(LIBFLAGS) $(ROBJ) -o $(RLIBD)/libPLEX.so $(LIBS) $(LLIBS)

$(DLIBD)/libPLEX.so : $(DOBJ) $(HRPLEX)
	$(CCD) $(LIBFLAGS) $(DOBJ) -o $(DLIBD)/libPLEX.so $(LIBS) $(LLIBS)
