EXECUTABLE:= DeltaPlayground
CXX := g++
SRCDIR := .
BUILDDIR := ../build/DeltaPlayground
BINDIR := ../bin
TARGET := $(BINDIR)/$(EXECUTABLE)

SRC := cpp
HEADER := hpp
SOURCES := $(shell find $(SRCDIR) -type f -name '*.$(SRC)')
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRC)=.o))
CXXFLAGS := -Wfatal-errors -Wall -O2 -std=c++17  -I..
LDFLAGS := -pthread -L$(BINDIR) -Wl,-rpath=. -ldelta `pkg-config sfml-graphics sfml-window sfml-system --libs`


run: $(TARGET)
	@echo Lauching $(EXECUTABLE)
	@cd $(BINDIR) && ./$(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p "$(BINDIR)"
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRC) $(SRCDIR)/*.$(HEADER)
	@mkdir -p "$(@D)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) -r $(BUILDDIR)/* $(TARGET)

.PHONY: clean run
