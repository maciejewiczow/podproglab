CC = gcc
CFLAGS = 
LIB = -lm

TARGET = calc

%.o: %.c
	$(CC) -c $^

$(TARGET): $(TARGET).o
	$(CC) -o $@ $^ $(CFLAGS) $(LIB)

clean:
	rm *.o $(TARGET)

run:
	./$(TARGET)