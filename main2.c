#include <stdio.h>
#include <string.h>
//#include "str.h"
#define DST "/Users/adityakotwal/Intern-dump/dump2"
#define MAX_BLKS 1024
#define SIZE_BLK 4096 // Each block is 4K

unsigned long
   bufferToFile(char *buf,  // IN: Buffer containing hex-formatted MD5 values
		  int len,    // IN: Length of the buffer containing MD5 values
		  char *UID,  // IN: Unique ID of component
		  unsigned int callNo)	// IN: Call number with same UID
{
   char hash[16 * 2 + 1];  // Each bytes represeneted by 2 hex chars
			   // and terminted by a null character
   int buf_pos;
   FILE* op;
   unsigned long offset;
   offset = MAX_BLKS * SIZE_BLK * (unsigned long)(callNo - 1);
   op = fopen(DST,"ab");
   buf_pos = 0;
   while(buf_pos < len){
      strncpy(hash, buf + buf_pos, 32);
      hash[16 * 2] = '\0';
      fprintf(op, "%s,%s,%lu\n", UID, hash, offset);
      offset += SIZE_BLK;
      buf_pos += 32;
   }

   fclose(op);
   return offset;
}

void testCase(){
   char buf[100];
   char uid[100];
   strcpy(buf,"12345678911234561234567890123456");
   strcat(buf,"21345678911234561234567890123456");
   strcpy(uid,"abc");
   bufferToFile(buf,strlen(buf),uid,1);
}

int main(){
   testCase();
   return 0;
}
