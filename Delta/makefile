EXECUTABLE:= libdelta.a
CXX := g++
SRCDIR := .
BUILDDIR := ../build/Delta
BINDIR := ../bin
TARGET := $(BINDIR)/$(EXECUTABLE)

SRC := cpp
HEADER := hpp
SOURCES := $(shell find $(SRCDIR) -type f -name '*.$(SRC)')
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRC)=.o))
CXXFLAGS := -Wfatal-errors -Wall -g -std=c++17
LIB := 


$(TARGET): $(OBJECTS)
	@mkdir -p "$(BINDIR)"
	$(AR) -rcs "$@" $(OBJECTS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRC) $(SRCDIR)/*.$(HEADER)
	@mkdir -p "$(@D)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) -r $(BUILDDIR)/* $(TARGET)

.PHONY: clean
