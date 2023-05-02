CC				= gcc -Wall -O3
SRC_DIR			= src
BUILD_DIR		= build
COMMON_LIB		= common
SEM_LIB			= semaphore
SHARED_MEM_LIB	= shared_mem
QUEUE_LIB		= queue
LIBS			= $(SRC_DIR)/$(SEM_LIB).c $(SRC_DIR)/$(SHARED_MEM_LIB).c $(SRC_DIR)/$(QUEUE_LIB).c

build: clean buildir simulation hairdresser client

buildir:
	mkdir $(BUILD_DIR)

simulation:
	$(CC) $(SRC_DIR)/simulation.c $(LIBS) -lrt -lpthread -o $(BUILD_DIR)/simulation

hairdresser:
	$(CC) $(SRC_DIR)/hairdresser.c $(LIBS) -lrt -lpthread -o $(BUILD_DIR)/hairdresser

client:
	$(CC) $(SRC_DIR)/client.c $(LIBS) -lrt -lpthread -o $(BUILD_DIR)/client

clean:
	rm -rf $(BUILD_DIR)