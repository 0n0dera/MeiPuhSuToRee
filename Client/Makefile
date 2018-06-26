CC=g++
INCLUDE= -Iinclude/ -I../lib/glm
LINKER_INCLUDE=
LIBS= -lGL -lGLEW -lGLU
CFLAGS=-v -std=c++11 -c -Wall $(INCLUDE)
LDFLAGS=-v -std=c++11 -Wall $(LINKER_INCLUDE) $(LIBS)
SRCS= src/collision_detector.cpp \
      src/entity.cpp \
      src/fixed_camera.cpp \
      src/main.cpp \
      src/player.cpp \
      src/window_manager.cpp \
      src/world.cpp 
OBJS=$(SRCS:.cpp=.o)
EXEC=maplestory

all: $(SRCS) $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean

clean:
	rm src/*.o
