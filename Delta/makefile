EXECUTABLE:= libdelta.a
CXX := g++
SRCDIR := .
BUILDDIR := ../build/Delta
BINDIR := ../bin
TARGET := $(BINDIR)/$(EXECUTABLE)
PREFIX := /usr

SRC := cpp
HEADER := hpp
SOURCES := $(shell find $(SRCDIR) -type f -name '*.$(SRC)')
HEADERS := $(shell find $(SRCDIR) -type f -path '*.$(HEADER)')
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRC)=.o))
CXXFLAGS := -Wfatal-errors -Wall -g -std=c++17
LIB := 


$(TARGET): $(OBJECTS)
	@mkdir -p "$(BINDIR)"
	$(AR) -rcs "$@" $(OBJECTS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRC) $(SRCDIR)/*.$(HEADER)
	@mkdir -p "$(@D)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

install: $(TARGET)
	@mkdir -p "$(DESTDIR)$(PREFIX)/lib"
	@mkdir -p "$(DESTDIR)$(PREFIX)/include/Delta"
	install $(TARGET) $(DESTDIR)$(PREFIX)/lib/$(EXECUTABLE)
	find $(SRCDIR) -type f -name '*.hpp' -exec install -D {} $(DESTDIR)$(PREFIX)/include/Delta/{} \;

uninstall:
	$(RM) -r  $(DESTDIR)$(PREFIX)/include/Delta
	$(RM) -r  $(DESTDIR)$(PREFIX)/lib/$(EXECUTABLE)

clean:
	$(RM) -r $(BUILDDIR)/* $(TARGET)

.PHONY: clean install uninstall
