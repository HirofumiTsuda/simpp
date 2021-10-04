CC			= g++
CFLAGS		= -lboost_context -g -O2
TARGET		= test
SRCS    	= test.cpp event.cpp core.cpp timeout.cpp queue_event.cpp \
                  process.cpp condition.cpp allof.cpp anyof.cpp
OBJS    	= $(SRCS:.cpp=.o)


# target
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)
# object flle
$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)

all:            $(TARGET)

clean:;         rm -f *.o *~ $(TARGET)

