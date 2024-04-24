CC = gcc
CFLAGS = -Wall -g
SRCS = GRAPH_SEARCH.c HashTable.c SpecificToProblem.c Standart_Search.c
TARGET = program.exe

$(TARGET): $(SRCS)
	@$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)
	@cls
	@$(TARGET)

clean:
	@powershell "if (Test-Path $(TARGET)) {Remove-Item -Path $(TARGET) -Recurse -Force}"
