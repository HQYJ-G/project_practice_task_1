CC = g++ -o 
CFLAGE = -g -Wall
BIN =  client

all:$(BIN)
	@echo "bian yi cheng gong"
#server:server.cpp net.cpp staff.h net.h
#	$(CC) $@ $^ $(CFLAGE)
client:client.cpp net.cpp  net.h ../protocol.cpp ../protocol.h
	$(CC) $@ $^ $(CFLAGE)
clean:
	rm $(BIN)
