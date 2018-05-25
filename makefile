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
CFLAGS := -Wall
LIB :=

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
