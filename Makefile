TARGET = client_naas.out

# XXX: Don't forget backslash at the end of any line except the last one
HDRS = \
	   project/include

SRCS = \
	   project/src/*.c

.PHONY: all clean

all: $(SRCS)
	$(CC) -Wall -Wextra $(addprefix -I,$(HDRS)) -o $(TARGET) $(CFLAGS) $(SRCS)

clean:
	rm -f $(TARGET)
