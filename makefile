CC := gcc
CFLAGS := -g

src_files := main.o \
doubleLinkedList\doubleLinkedList.o

all:$(src_files)
	$(CC) $(CFLAGS) -o main $? 

$(src_files): %.o : %.c

clean:
	del $(src_files)