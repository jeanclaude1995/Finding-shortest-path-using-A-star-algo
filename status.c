/* status.c */

#include "status.h"

/** default error message for unknown errors */
static char* unknownError = "Unknown error";

/** defined error messages */
static char* msg[] = {
  "",
  "File open failed",
  "Access refused",
  "File close failed",
  "Memory allocation failed",
  "Wrong date",
  "Full structure",
  "Empty structure",
  "Value not found",
  "Value already exists",
  "index out of bounds",
  "unable to perform operation",
  
  "unknown error"
};

/** get message associated with the given status value (O(1)).
 * @param s the status value
 * @return the associated message
 */
char* message(status s) {
  return (s<0 || s >= ERRUNKNOWN) ? msg[ERRUNKNOWN] : msg[s];
}
