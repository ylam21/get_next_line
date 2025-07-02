#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"
#include <unistd.h>

char *ft_strchr(const char *s, char c);
size_t ft_strlen(char const *s);
char *ft_strjoin(char const *s1, char const *s2);
char *ft_strndup(char const *s, size_t n);

char *read_and_stash(int fd, char *stash) {
  char buffer[BUFFER_SIZE + 1];
  char *tmp;
  ssize_t bytes_read = 1;
  while (0 < bytes_read && ft_strchr(stash, '\n') == NULL)
  {
      bytes_read = read(fd, buffer, BUFFER_SIZE);
      if (bytes_read == 0) {
          free(stash);
          return NULL;
      }
      buffer[bytes_read] = '\0';
      tmp = ft_strjoin(stash, buffer);
      free(stash);
      stash = tmp;
  }
  return stash;
}

char *extract_line(char *stash)
{
    if (!stash)
        return NULL;
    size_t len = 0;
    while (stash[len] != '\n' && stash[len] != '\0')
        len++;
    char *line = ft_strndup(stash, len + 1); // "len + 1" to caputure '\n' character
    if (!line) {
        return NULL;
    }
    return line;
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

  if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0) {
    return NULL;
  }
  stash = read_and_stash(fd, stash);
  if (!stash) {
    free(stash);
    return NULL;
  }

  line = extract_line(stash);
  stash = clean_stash(stash);

  return line;
}
