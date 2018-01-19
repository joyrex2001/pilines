TARGET=$(shell basename $$(pwd))
SOURCES=$(shell echo *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
CXXFLAGS=-Wall -march=native -gdwarf-3 -std=c++1y -O3 -g $(shell pkg-config --cflags sdl2 libavdevice libavformat libavutil libavcodec)
LDFLAGS=$(shell pkg-config --libs sdl2 libavdevice libavformat libavutil libavcodec)

$(TARGET): $(OBJECTS)
	g++ $(OBJECTS) $(LDFLAGS) -o $(TARGET)
%.o: %.cpp
	g++ $(CXXFLAGS) -c $< -MT $@ -MMD -MP -MF $*.mk~
-include *.mk~

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f *~
	rm -f *.o
	rm -f $(TARGET)

install_deps:
	apt-get install -y libavdevice-dev libavformat-dev
	curl https://www.libsdl.org/release/SDL2-2.0.7.tar.gz > SDL2-2.0.7.tar.gz
	cd SDL2-2.0.7; ./configure --host=arm-raspberry-linux-gnueabihf --disable-video-opengl --disable-video-x11 --disable-pulseaudio --disable-esd --disable-video-mir --disable-video-wayland; make -j 4 ; make install

.PHONY: run clean install_deps
