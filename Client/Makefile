CC=g++
INCLUDE= -Iinclude/ -I../lib/glm -I../lib/glfw-3.2.1/include
LINKER_INCLUDE=-L ../lib
LIBS= -lGLEW -lGLU -lGL -lglfw3 -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread -ldl
CFLAGS= -std=c++11 -c -Wall $(INCLUDE)
LDFLAGS=-std=c++11 -Wall $(LINKER_INCLUDE) $(LIBS)
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
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean

clean:
	rm src/*.o
