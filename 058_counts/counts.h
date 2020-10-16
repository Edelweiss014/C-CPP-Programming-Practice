#ifndef __COUNTS_H__
#define __COUNTS_H__
struct _one_count_t {
  char * name;
  size_t num;
};
typedef struct _one_count_t one_count_t;

struct _counts_t {
  size_t numElements;
  size_t unknownCount;
  one_count_t ** countList;
};
typedef struct _counts_t counts_t;

counts_t * createCounts(void);
void addCount(counts_t * c, const char * name);
void printCounts(counts_t * c, FILE * outFile);

void freeCounts(counts_t * c);

#endif
