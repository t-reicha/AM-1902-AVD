#ifndef _BUFFER_H_
#define _BUFFER_H_

#define BUFFER_SIZE 5    

int buffer[BUFFER_SIZE];
int HEAD = 0;


int roundToFive(int num) {
  housekeeping();
  int remainder = num % 5;
  if (remainder <= 2) {
    // Round down to the nearest 5
    return num - remainder;
  } else {
    // Round up to the nearest 5
    return num + 5 - remainder;
  }
}


void addValue(int value) {
  housekeeping();
  buffer[HEAD++] = value;
  if (HEAD >= BUFFER_SIZE) {
    HEAD = 0;
  }
}

int getMode() {
  housekeeping();
  int mode = 0;
  int maxCount = 0;
  for (int i = 0; i < BUFFER_SIZE; i++) {
    int currentValue = buffer[i];
    int currentCount = 0;
    for (int j = 0; j < BUFFER_SIZE; j++) {
      if (buffer[j] == currentValue) {
        currentCount++;
      }
    }
    if (currentCount > maxCount) {
      maxCount = currentCount;
      mode = currentValue;
    }
  }
  return mode;
}


#endif
