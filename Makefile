STD :=c++17
SRCDIR := src
CPPFLAGS= -std=$(STD) -O3 -DDEBUG
CC=g++-5
TARGET := bin/filtering
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%, $(SRCDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

all: ${TARGET}

clean:
	rm $(OBJECTS)
	rm $(TARGET)

%.o: %.cpp
	$(CC) -c $< $(CPPFLAGS)
	cd ..
	mv *.o ./src
	cd src

$(TARGET): $(OBJECTS)
	rm bin -rf
	mkdir bin
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(CPPFLAGS)"; $(CC) $^ -o $(TARGET) $(CPPFLAGS)
