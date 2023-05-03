CC				= gcc -Wall -O3
SRC_DIR			= src
BUILD_DIR		= build
COMMON_LIB		= common
SEM_LIB			= semaphore
SHARED_MEM_LIB	= shared_mem
QUEUE_LIB		= queue
LIBS			= $(SRC_DIR)/$(SEM_LIB).c $(SRC_DIR)/$(SHARED_MEM_LIB).c $(SRC_DIR)/$(QUEUE_LIB).c

build: clean buildir
	make simulation STANDARD=SYSTEMV

buildir:
	mkdir $(BUILD_DIR)

simulation: hairdresser client
	$(CC) $(SRC_DIR)/simulation.c $(LIBS) -D$(STANDARD) -lrt -lpthread -o $(BUILD_DIR)/simulation_$(STANDARD)

hairdresser:
	$(CC) $(SRC_DIR)/hairdresser.c $(LIBS) -D$(STANDARD) -lrt -lpthread -o $(BUILD_DIR)/hairdresser_$(STANDARD)

client:
	$(CC) $(SRC_DIR)/client.c $(LIBS) -D$(STANDARD) -lrt -lpthread -o $(BUILD_DIR)/client_$(STANDARD)

clean:
	rm -rf $(BUILD_DIR)