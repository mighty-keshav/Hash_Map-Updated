/*
 * Jenkins.cpp
 *
 *  Created on: Nov 6, 2018
 *      Author: murthk5
 */


#include <iostream>
#define JHASH_GOLDEN_RATIO  0x9e3779b9
#define __jhash_mix(a, b, c)\
{ \
          a -= b; a -= c; a ^= (c>>13); \
          b -= c; b -= a; b ^= (a<<8); \
          c -= a; c -= b; c ^= (b>>13); \
          a -= b; a -= c; a ^= (c>>12);  \
          b -= c; b -= a; b ^= (a<<16); \
          c -= a; c -= b; c ^= (b>>5); \
          a -= b; a -= c; a ^= (c>>3);  \
          b -= c; b -= a; b ^= (a<<10); \
          c -= a; c -= b; c ^= (b>>15); \
}


static inline uint32_t JenkinsHash(const uint32_t * k, uint32_t length, uint32_t initval)
			{
				uint32_t a, b, c, len;


				a = b = JHASH_GOLDEN_RATIO;
				c = initval;
				len = length;


				while (len >= 3)
				{
					a += k[0];
					b += k[1];
					c += k[2];
					__jhash_mix(a, b, c);
					k += 3;
					len -= 3;
				}


				c += length * 4;


				switch (len)
				{
					case 2:
						b += k[1];
						break;
					case 1:
						a += k[0];
						break;
				}


      __jhash_mix(a, b, c);


      return c;
	}
