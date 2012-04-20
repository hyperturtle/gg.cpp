CPP = g++
RM = rm
MKDIR = mkdir
CPPFLAGS = -I/mingw/SFML-1.6/include -I/mingw/include/ -std=gnu++0x
LDFLAGS = -static-libstdc++ -static-libgcc -lsfml-audio-s -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lmingw32 -lopengl32 -lglu32 -L/mingw/SFML-1.6/lib -L/mingw/lib -O0 -Wall -fmessage-length=0
OBJDIR = temp/

all: build/main.exe

build/main.exe: main.cpp gg.hpp $(OBJDIR)/gg.o Makefile
	$(CPP) -o build/main.exe main.cpp $(OBJDIR)/gg.o $(LDFLAGS) $(CPPFLAGS)

$(OBJDIR)/gg.o: gg.cpp gg.hpp Makefile
	test -d $(OBJDIR) || $(MKDIR) $(OBJDIR)
	$(CPP) -o $(OBJDIR)/gg.o gg.cpp -c $(LDFLAGS) $(CPPFLAGS)

clean:
	test -d $(OBJDIR) || $(RM) -rf $(OBJDIR)
	$(RM) build/main.exe