CC = g++ -o 
CFLAGE = -g -Wall
BIN = server client

all:$(BIN)
	@echo "bian yi cheng gong"
server:server.cpp net.cpp
	$(CC) $@ $^ $(CFLAGE)
client:client.cpp net.cpp
	$(CC) $@ $^ $(CFLAGE)
clean:
	rm $(BIN)
