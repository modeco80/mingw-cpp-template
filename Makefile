DEBUG=0
MINGW = i686-w64-mingw32-

ifeq ($(MINGW), i686-w64-mingw32-)
ARCH = x86
else
ARCH = x64
endif

RC = $(MINGW)windres -O coff
CXX = $(MINGW)g++

# By default, I (modeco80) choose to (most of the time) when I'm using MinGW not use the STL.
# I do this since (under MinGW, at least) it tends to bloat executables a *ton*.
#
# If you want to use the STL (or you love having huge binaries), either:
# in final linking steps add -lstdc++ -static-libstdc++
# or switch LD to $(MINGW)g++ (and add -static-libstdc++, as while
# g++ will implicitly link libstdc++, it won't implicitly statically link it).
LD = $(MINGW)gcc

ifeq ($(DEBUG), 0)
BD=Release
CXXFLAGS = -fno-exceptions -fno-ident -fno-stack-protector -funroll-loops -fomit-frame-pointer -fno-unwind-tables -fno-asynchronous-unwind-tables -msse -Wall -Wno-write-strings -Werror
else
BD=Debug
CXXFLAGS = -fno-exceptions -fno-ident -fno-stack-protector -funroll-loops -fomit-frame-pointer -fno-unwind-tables -fno-asynchronous-unwind-tables -msse -Wall -Wno-write-strings -g -DDEBUG
endif

BDIR = bin/$(ARCH)/$(BD)
ODIR = obj/$(ARCH)/$(BD)

# automatic sources detection (besides rc, as it's a good practice to just include from a main rc file)
CXXSRCS = $(wildcard src/*.cc)
RCSRCS = src/mwapp.rc
OBJS = $(CXXSRCS:src/%.cc=$(ODIR)/%.o) $(RCSRCS:src/%.rc=$(ODIR)/%.res)

# name of the output executable
PROJECT = mwapp

# c++ compiler flags specified by user
USER_CXX = -Iinclude

.PHONY: all clean

all: $(BDIR)/$(PROJECT).exe

clean:
	-rm -rf $(ODIR)/
	-rm -rf $(BDIR)/

$(ODIR)/:
	mkdir -p $@

$(BDIR)/:
	mkdir -p $@

$(ODIR)/%.res: src/%.rc
	$(RC) $< -o $@

$(ODIR)/%.o: src/%.cc
	$(CXX) -c $(CXXFLAGS) $(USER_CXX) -MT $@ -MD -MP -MF $(ODIR)/$*.d $< -o $@

$(BDIR)/$(PROJECT).exe: $(BDIR)/ $(ODIR)/ $(OBJS)
ifeq ($(DEBUG), 0)
	$(LD) $(CXXFLAGS) -mwindows -s $(OBJS) -o $@
else
	$(LD) $(CXXFLAGS) -mwindows $(OBJS) -o $@
endif
-include $(wildcard $(ODIR)/*.d)
