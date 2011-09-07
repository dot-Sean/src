#ifndef KFC_GZ_H /* { */
#define KFC_GZ_H

/* 
 * Get the real-name of a gzipped file. Return value is statically
 * allocated area and valid till the next function call. If the 
 * file is not a gzipped file or error occured, (void *) 0 returns.
 */

const char * zname(const char * filename);

#endif /* } */
