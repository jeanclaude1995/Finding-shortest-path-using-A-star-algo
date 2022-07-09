/* status.h */

#ifndef __STATUS_H
#define __STATUS_H

typedef enum {
	OK,
	ERROPEN,
	ERRACCESS,
	ERRCLOSE,
	ERRALLOC,
	ERRDATE,
	ERRFULL,
	ERREMPTY,
	ERRABSENT,
	ERREXIST,
	ERRINDEX,
	ERRUNABLE,
	
	ERRUNKNOWN,
	} status;

/** get message associated with the given status value (O(1)).
 * @param s the status value
 * @return the associated message
 */
extern char* message(status s);


#endif
