EXECUTABLE:= deltatest
CXX := g++
SRCDIR := .
BUILDDIR := ../build/DeltaTest
BINDIR := ../bin
TARGET := $(BINDIR)/$(EXECUTABLE)

SRC := cpp
HEADER := hpp
SOURCES := $(shell find $(SRCDIR) -type f -name '*.$(SRC)')
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRC)=.o))
CXXFLAGS := -Wfatal-errors -Wall -g -std=c++17  -I..
LIB := -pthread -L$(BINDIR) -ldelta `pkg-config sfml-graphics sfml-window sfml-system --libs`


run: $(TARGET) 
	@echo Lauching $(EXECUTABLE)
	@./$(TARGET)

$(TARGET): $(OBJECTS) $(BINDIR)/libdelta.a
	@mkdir -p "$(BINDIR)"
	$(CXX) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRC) $(SRCDIR)/*.$(HEADER)
	@mkdir -p "$(@D)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) -r $(BUILDDIR)/* $(TARGET)

.PHONY: clean
