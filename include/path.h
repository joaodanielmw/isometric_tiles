#ifndef PATH_H_
#define PATH_H_

#include <stdbool.h>

bool path_open(char **path, const char *file);
void path_close(char *path);

#endif
