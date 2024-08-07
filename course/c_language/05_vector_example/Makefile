# 定义编译器和编译选项  
CC = gcc  
CFLAGS = -Wall -Wextra -std=c99
  
# 定义源文件  
SRCS = main.c vector.c vec_algorithm.c
  
# 定义目标文件名  
TARGET = vector  
  
# 默认目标：构建程序  
all: $(TARGET)  
  
# 构建程序  
$(TARGET): $(SRCS)  
	$(CC) $(CFLAGS) -o $@ $^ -lm -g
  
# 清除构建产物  
clean:  
	rm -f $(TARGET)  
  
# 伪目标，用于显示帮助信息  
.PHONY: help  
help:  
	@echo "Makefile usage:"  
	@echo "  make          Build the program."  
	@echo "  make clean    Remove generated files."  
	@echo "  make help     Show this help message."