/**
 * @file fac.h
 * Contains factorial-calculating functions both utilizing and not
 * utilizing memoization.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#ifndef FAC_H
#define FAC_H

/**
 * Calculates the factorial of the given number.
 * @param n Number to calculate factorial for.
 * @return n!.
 */
unsigned long fac(unsigned long n);

/**
 * Calculates the factorial of the given number.
 * This version utilizes memoization.
 * @param n Number to calculate factorial for.
 * @return n!.
 */
unsigned long memoized_fac(unsigned long n);

#endif /* FAC_H */
