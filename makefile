CC = gcc
CFLAGS = -Wall -g
SRCS = GRAPH_SEARCH.c HashTable.c SpecificToProblem.c Standart_Search.c map_loader.c
TARGET = program.exe

$(TARGET): $(SRCS)
	@$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)
	@cls
	@$(TARGET)

run:
	@cls
	@$(TARGET)

clean:
	@powershell "if (Test-Path $(TARGET)) {Remove-Item -Path $(TARGET) -Recurse -Force}"

test:
	@$(CC) $(CFLAGS) -o $(TARGET) test.c
	@cls
	@$(TARGET)
