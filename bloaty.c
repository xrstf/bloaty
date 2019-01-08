#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void currentTime(char* buf, size_t len) {
  time_t t = time(NULL);
  struct tm *tm = gmtime(&t);

  strftime(buf, len, "%F %T", tm);
}

void logLine(const char* format, ...) {
  va_list args;
  va_start(args, format);

  char timeBuf[24];
  currentTime(timeBuf, sizeof(timeBuf));

  fprintf(stderr, "[%s UTC] ", timeBuf);
  vfprintf(stderr, format, args);
  fprintf(stderr, "\n");

  va_end(args);
}

bool eatMemory(size_t total) {
  short *buffer = malloc(total);
  if (buffer == NULL) {
    return false;
  }

  memset(buffer, 0, total);
  return true;
}

size_t parseChunkSize(const char* arg) {
  char *endptr;
  size_t amount = strtol(arg, &endptr, 10);

  if (endptr == arg) {
    logLine("Parse error, amount must start with a number: %s", arg);
    exit(EXIT_FAILURE);
  }

  // parse suffix
  if (strcmp(endptr, "K") == 0) {
    amount *= 1000;
  } else if (strcmp(endptr, "M") == 0) {
    amount *= 1000 * 1000;
  } else if (strcmp(endptr, "Ki") == 0) {
    amount *= 1024;
  } else if (strcmp(endptr, "Mi") == 0) {
    amount *= 1024 * 1024;
  } else if (strlen(endptr) > 0) {
    logLine("Parse error, unrecognized suffix: %s", endptr);
    exit(EXIT_FAILURE);
  }

  return amount;
}

#define DIM(x) (sizeof(x)/sizeof(*(x)))
static const char *sizes[] = {"B", "KiB", "MiB", "GiB"};

char* formatSize(size_t size) {
  char   *result = (char *) malloc(sizeof(char) * 20);
  int    unit    = 0;
  int    units   = DIM(sizes);
  double s       = size;

  while (s >= 1024 && unit < (units-1)) {
    unit++;
    s /= 1024;
  }

  sprintf(result, "%.2f %s", s, sizes[unit]);
  return result;
}

int main(int argc, char *argv[]) {
  size_t chunkSize;

  if (argc >= 2) {
    chunkSize = parseChunkSize(argv[1]);
  } else {
    chunkSize = parseChunkSize("1Mi");
  }

  if (chunkSize == 0) {
    logLine("Cannot eat zero bytes per iteration.");
    exit(EXIT_FAILURE);
  }

  logLine("Going to eat %s per second...", formatSize(chunkSize));

  size_t consumed = 0;

  while (true) {
    if (!eatMemory(chunkSize)) {
      logLine("Failed to allocate memory!");
      exit(EXIT_FAILURE);
    }

    consumed += chunkSize;

    logLine("Consumed %s so far.", formatSize(consumed));
    sleep(1);
  }
}
