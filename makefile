EXECUTABLE:= delta
CC := g++
SRCDIR := src
BUILDDIR := build
BINDIR := bin
TARGET := $(BINDIR)/$(EXECUTABLE)

SRC := cpp
HEADER := hpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRC))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRC)=.o))
CFLAGS := -Wfatal-errors -Wall -g -std=c++17
LIB := -pthread `pkg-config sfml-graphics sfml-window sfml-system --libs`


run: $(TARGET)
	@./$(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p "$(BINDIR)"
	$(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRC) $(SRCDIR)/*.$(HEADER)
	@mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(BUILDDIR)/* $(TARGET)

.PHONY: clean
