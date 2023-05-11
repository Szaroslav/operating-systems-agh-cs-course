#ifndef __COMMON_H__
#define __COMMON_H__

#define REINDEER_NUMBER     9
#define ELF_NUMBER          10
#define MAX_PROBLEM_NUMBER  3
#define SEC_TO_USEC         1000000

typedef struct IntervalUSec {
    int start;
    int end;
} IntervalUSec;

const IntervalUSec SANTA_SOLUTION_DURATION = { 1 * SEC_TO_USEC, 2 * SEC_TO_USEC };
const IntervalUSec SANTA_DELIVERY_DURATION = { 2 * SEC_TO_USEC, 4 * SEC_TO_USEC };
const IntervalUSec ELF_WORK_DURATION = { 2 * SEC_TO_USEC,  5 * SEC_TO_USEC };
const IntervalUSec REINDEER_HOLIDAYS_DURATION = { 5 * SEC_TO_USEC, 10 * SEC_TO_USEC };

#endif // __COMMON_H__
