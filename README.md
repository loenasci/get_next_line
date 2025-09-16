# get_next_line

`get_next_line` is a C function that reads a line from a file or file descriptor, allowing you to read a file line by line through successive calls. This project is part of the 42 School curriculum.

## Features

- Reads any file line by line
- Efficiently manages memory
- Works with any buffer size

## How it works

The `get_next_line` function takes a file descriptor and returns a read line. Successive calls to the function will allow reading the file line by line.

```c
char *get_next_line(int fd);
```

## Implementation
The implementation uses the following concepts:

- Static variables: To maintain state between calls
- Dynamic memory allocation: To handle lines of varying sizes
- Buffer reading: To optimize I/O operations
- String manipulation: To process the read data

## Requirements
- The function must read until it finds a newline or the end of the file
- It must return `NULL` in case of error or when there are no more lines to read
- It must be efficient in terms of memory usage and performance

## Testing
To test the function, you can create a test file (main.c for example) that opens a file and calls `get_next_line` in a loop until all lines are read.

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int fd = open("file.txt", O_RDONLY);
	char *line;
		
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
```
