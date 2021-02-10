ifdef HIGH_QUALITY
CXXFLAGS=-Wall -Wextra -std=c++2a -O2 -DHIGH_QUALITY
else
CXXFLAGS=-Wall -Wextra -std=c++2a -O2
endif

all: utilities/*.hpp *.hpp hittable/*.hpp material/*.hpp texture/*.hpp transform/*.hpp medium/*.hpp \
	                 *.cpp hittable/*.cpp material/*.cpp texture/*.cpp transform/*.cpp medium/*.cpp
	clang++ ${CXXFLAGS} -o main                                                                    \
		-Iutilities -I.       -Ihittable       -Imaterial       -Itexture       -Itransform       -Imedium        \
		              ./*.cpp   hittable/*.cpp   material/*.cpp   texture/*.cpp   transform/*.cpp   medium/*.cpp  \
