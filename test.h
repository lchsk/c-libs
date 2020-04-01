#ifndef TEST_H
#define TEST_H

#define TEST_EQ(val1, val2) assert(val1 == val2)
#define TEST_NULL(val) assert(val == NULL)
#define TEST_EQ_STR(str1, str2) assert(strcmp(str1, str2) == 0)

#endif
