#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"
#include <unistd.h>

char *ft_strchr(const char *s, char c);
size_t ft_strlen(char const *s);
char *ft_strjoin(char const *s1, char const *s2);
char *ft_strndup(char const *s, size_t n);
int contains_non_newline(char *s);

char *read_and_stash(int fd, char *stash) {
  char *buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
  if (!buffer)
      return NULL;
  char *tmp;
  ssize_t bytes_read = 1;
  while (0 < bytes_read && ft_strchr(stash, '\n') == NULL)
  {
      bytes_read = read(fd, buffer, BUFFER_SIZE);
      if (bytes_read < 0) {
          free(buffer);
          return NULL;
      }
      if (bytes_read == 0) {
          free(buffer);
          return stash;
      }
      buffer[bytes_read] = '\0';
      tmp = ft_strjoin(stash, buffer);
      free(stash);
      if (tmp == NULL) {
        free(buffer);
        return NULL;
      }
      stash = tmp;
  }
  free(buffer);
  return stash;
}


char *extract_line(char *stash)
{
    if (!stash || stash[0] == '\0') {
        return NULL;
    }
    size_t len = 0;
    while (stash[len] && stash[len] != '\n')
        len++;
    if (stash[len] == '\n')
        len++;

    return ft_strndup(stash, len);
}

char *clean_stash(char *stash)
{
    if (!stash)
        return NULL;
    char *newl = ft_strchr(stash, '\n');
    if (!newl) {
        free(stash);
        return NULL;
    }
    newl++;
    char *clean = ft_strndup(newl, ft_strlen(newl));
    free(stash);
    return clean;
}

char *get_next_line(int fd) {
  static char *stash = NULL;
  char *line;
  char tmp;
  if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &tmp, 0) < 0) {
    return NULL;
  }
  stash = read_and_stash(fd, stash);
  if (stash == NULL)
    return NULL;
  line = extract_line(stash);
  if (!line) {
      if (stash && stash[0] != '\0')
          line = ft_strndup(stash, ft_strlen(stash));
      free(stash);
      stash = NULL;
      return line;
  }
  stash = clean_stash(stash);
  return line;
}
