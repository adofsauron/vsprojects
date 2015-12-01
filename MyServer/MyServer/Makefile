DeBug	=	./debug
OBJ_R	=	./obj_r
TARGET	=	$(DeBug)/myserver
XML		=	./Server.xml

SOURCES =	$(wildcard *.cpp)
OBJS	:=	$(patsubst %.cpp, $(OBJ_R)/%.o,$(SOURCES))

MACRO	=	DEBUGALL
CFLAGS	+=	-g -w -lpthread -D$(MACRO)
CC		=	g++

$(TARGET): $(OBJS)
	$(CC) $^	$(CFLAGS) -o $@	

$(OBJ_R)/%.o: %.cpp
	$(CC) -c $^ $(CFLAGS)  -o $@

.PHONY : rebuild \
		 clean	 \
		 test	 \
		 tclean

rebuild:
	rm		$(OBJ_R) $(DeBug)	-rf
	mkdir	$(OBJ_R) $(DeBug)
	cp		$(XML)	 $(DeBug)	-f
	make	$(TARGET)

clean:
	rm  $(OBJS)		-rf
	rm  $(TARGET)	-f
	
test:
	gcc ./Epoll.c $(CFLAGS)	 -o $(DeBug)/Epoll.bin
	gcc ./Client.c $(CFLAGS) -o $(DeBug)/Client.bin

tclean:
	rm	$(DeBug)/Epoll.bin	-f
	rm	$(DeBug)/Client.bin	-f