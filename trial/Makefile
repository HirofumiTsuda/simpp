CC			= g++
CFLAGS		= -lboost_context
TARGET		= main
SRCS    	= main.cpp event.cpp core.cpp
OBJS    	= $(SRCS:.cpp=.o)


# target
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)
# object flle
$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)

all:            $(TARGET)

clean:;         rm -f *.o *~ $(TARGET)
