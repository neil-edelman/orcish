# Makefile 1.2 (GNU Make 3.81; MacOSX gcc 4.2.1; MacOSX MinGW 4.3.0)

PROJ  := TestOrcish
VA    := 0
VB    := 1

# dirs
SDIR  := src
TDIR  := test
BDIR  := bin
BACK  := backup

# files in bdir
INST  := $(PROJ)-$(VA)_$(VB)

# extra stuff we should back up
EXTRA :=

# John Graham-Cumming:
# rwildcard is a recursive wildcard
rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

# select all automatically
SRCS  := $(call rwildcard, $(SDIR), *.c)
TEST  := $(call rwildcard, $(TDIR), *.c)
H     := $(call rwildcard, $(SDIR), *.h)
OBJS  := $(patsubst $(SDIR)/%.c, $(BDIR)/%.o, $(SRCS))
TOBJS := $(patsubst $(TDIR)/%.c, $(BDIR)/%.o, $(TEST))

CC   := gcc # /usr/local/i386-mingw32-4.3.0/bin/i386-mingw32-gcc javac nxjc
CF   := -Wall -Wextra -O3 -ffast-math -funroll-loops -pedantic -ansi # or -std=c99 -mwindows or -g:none -O -verbose -d $(BDIR) $(SDIR)/*.java -Xlint:unchecked -Xlint:deprecation
OF   := # -framework OpenGL -framework GLUT or -lglut -lGLEW

# props Jakob Borg and Eldar Abusalimov
# $(ARGS) is all the extra arguments
# $(BRGS) is_all_the_extra_arguments
EMPTY :=
SPACE := $(EMPTY) $(EMPTY)
ifeq (backup, $(firstword $(MAKECMDGOALS)))
  ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  BRGS := $(subst $(SPACE),_,$(ARGS))
  ifneq (,$(BRGS))
    BRGS := -$(BRGS)
  endif
  $(eval $(ARGS):;@:)
endif

######
# compiles the programme by default

default: $(BDIR)/$(PROJ)
	# . . . success; executable is in $(BDIR)/$(PROJ)

# linking
$(BDIR)/$(PROJ): $(OBJS) $(TOBJS)
	$(CC) $(CF) $(OF) $(OBJS) $(TOBJS) -o $@

# compiling
$(OBJS): $(BDIR)/%.o: $(SDIR)/%.c $(H)
	@mkdir -p $(BDIR)
	$(CC) $(CF) -c $(SDIR)/$*.c -o $@

$(TOBJS): $(BDIR)/%.o: $(TDIR)/%.c
	@mkdir -p $(BDIR)
	$(CC) $(CF) -c $(TDIR)/$*.c -o $@

######
# phoney targets

.PHONY: setup clean backup icon

clean:
	-rm -f $(OBJS)

backup:
	@mkdir -p $(BACK)
	zip $(BACK)/$(INST)-`date +%Y-%m-%dT%H%M%S`$(BRGS).zip readme.txt gpl.txt copying.txt Makefile $(SRCS) $(H) $(SDIR)/$(ICON) $(EXTRA)
	#git commit -am "$(ARGS)"

icon: default
	# . . . setting icon on a Mac.
	cp $(MDIR)/$(ICON) $(BDIR)/$(ICON)
	-sips --addIcon $(BDIR)/$(ICON)
	-DeRez -only icns $(BDIR)/$(ICON) > $(BDIR)/$(RSRC)
	-Rez -append $(BDIR)/$(RSRC) -o $(BDIR)/$(PROJ)
	-SetFile -a C $(BDIR)/$(PROJ)

setup: default icon
	@mkdir -p $(BDIR)/$(INST)
	cp $(BDIR)/$(PROJ) readme.txt gpl.txt copying.txt $(BDIR)/$(INST)
	rm -f $(BDIR)/$(INST)-MacOSX.dmg
	# or rm -f $(BDIR)/$(INST)-Win32.zip
	hdiutil create $(BDIR)/$(INST)-MacOSX.dmg -volname "$(PROJ) $(VA).$(VB)" -srcfolder $(BDIR)/$(INST)
	# or zip $(BDIR)/$(INST)-Win32.zip -r $(BDIR)/$(INST)
	rm -R $(BDIR)/$(INST)
