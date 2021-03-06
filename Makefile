OBJS = obj/winmain.o obj/resource.o obj/callbacks.o obj/vectors.o obj/winmain.exe 
all: 
	windres -I.\include -I.\res -i res/resource.rc -o obj/resource.o
	gcc -I".\include" -O0 -g -D _WIN32_IE=0x0900 -c src/vectors.c -o obj/vectors.o "C:\\MinGW\\lib\\libgdi32.a"
	gcc -I".\include" -O0 -g -D _WIN32_IE=0x0900 -c src/callbacks.c -o obj/callbacks.o "C:\\MinGW\\lib\\libgdi32.a"
	gcc -I".\include" -O0 -g -D _WIN32_IE=0x0900 -c src/winmain.c -o obj/winmain.o
	gcc obj/resource.o obj/callbacks.o obj/winmain.o obj/vectors.o -o obj/winmain.exe -g -D _WIN32_IE=0x0900 "C:\\MinGW\\lib\\libgdi32.a" -lcomctl32 -lcomdlg32 -Wl,--subsystem,windows

clean: ${OBJS}
	rm  $^