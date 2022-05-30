 #include <stdio.h>
 #include <stdlib.h>
 #include <errno.h>
 #include <string.h>
 #include "frequencies.h"
 
 bool calc_frequencies(Frequencies freqs, const char* path, const char** a_error) {
     FILE* fp = fopen(path,"r");
     if(fp != NULL) {
         for(uchar ch = fgetc(fp); ! feof(fp); ch = fgetc(fp)) {
             freqs[ch] += 1;
         }
         fclose(fp);
         //in future dont return true return !fclose(fp) (will return 1 if  it closes)
         return true;
     }
     else{
         *a_error = strerror(errno);
         return false;
     }
 }
 /* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */Copy-paste code here to remove the line numbers.