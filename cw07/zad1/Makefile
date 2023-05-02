CC = gcc -Wall -O3
SRC_DIR = src
BUILD_DIR = build
COMMON_LIB = common
SEM_LIB = semaphore
SHARED_MEM_LIB = shared_mem
LIBS = $(SRC_DIR)/$(SEM_LIB).c $(SRC_DIR)/$(SHARED_MEM_LIB).c

build: clean buildir
	$(CC) $(SRC_DIR)/simulation.c $(LIBS) -lrt -lpthread -o $(BUILD_DIR)/simulation

buildir:
	mkdir $(BUILD_DIR)

common:
	$(CC) -c $(SRC_DIR)/$(COMMON_LIB).c -o $(BUILD_DIR)/$(COMMON_LIB).o
	ar rcs $(BUILD_DIR)/lib$(COMMON_LIB).a $(BUILD_DIR)/$(COMMON_LIB).o

semaphore:
	$(CC) -c $(SRC_DIR)/$(SEM_LIB).c -o $(BUILD_DIR)/$(SEM_LIB).o
	ar rcs $(BUILD_DIR)/lib$(SEM_LIB).a $(BUILD_DIR)/$(SEM_LIB).o

shared_mem:
	$(CC) -c $(SRC_DIR)/$(SHARED_MEM_LIB).c -o $(BUILD_DIR)/$(SHARED_MEM_LIB).o
	ar rcs $(BUILD_DIR)/lib$(SHARED_MEM_LIB).a $(BUILD_DIR)/$(SHARED_MEM_LIB).o

clean:
	rm -rf $(BUILD_DIR)