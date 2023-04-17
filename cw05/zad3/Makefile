CC = gcc -Wall
SRC_DIR = src
BUILD_DIR = build

build: clean
	mkdir $(BUILD_DIR)
	$(CC) $(SRC_DIR)/evaluator.c -o $(BUILD_DIR)/evaluator
	$(CC) $(SRC_DIR)/main.c -o $(BUILD_DIR)/main -lm

test: build
	rm -f results.txt
	while read -r line; do $(BUILD_DIR)/main $$line >> results.txt; echo "" >> results.txt; done < tests.txt; cat results.txt

clean:
	rm -rf $(BUILD_DIR)