 #include <assert.h>                                                                             
 #include "bit_writer.h"                                                                         
                                                                                                 
 BitWriter open_bit_writer(const char* path) {                                                   
     return (BitWriter) {.file = fopen(path, "w"), .current_byte = 0, .num_bits_left = 8};       
 }                                                                                               
                                                                                                 
 void write_bits(BitWriter* a_writer, uint8_t bits, uint8_t num_bits_to_write) {                 
     //Assertion checks                                                                          
     assert(num_bits_to_write >= 0 && num_bits_to_write <= 8);                                   
     assert(a_writer -> num_bits_left >= 1 && a_writer -> num_bits_left <= 8);                   
                                                                                                 
     //if it can fit                                                                             
     if(a_writer -> num_bits_left >= num_bits_to_write){                                         
         //put it in                                                                             
         a_writer -> current_byte = a_writer -> current_byte | ((bits << ((8 - num_bits_to_write) - (8 -     a_writer -> num_bits_left))) & (0xff >> (8 - a_writer -> num_bits_left)));
         //update num bits left                                                                  
         a_writer -> num_bits_left = a_writer -> num_bits_left - num_bits_to_write;              
     }                                                                                           
     else {                                                                                      
         //putting what can fit BROKE IT FIX                                                     
         a_writer -> current_byte = a_writer -> current_byte | (((bits << (8 - num_bits_to_write)) & (0x    ff << (8 - a_writer -> num_bits_left))) >> (8 - a_writer -> num_bits_left));
         //writing to file and clearing                                                          
         fputc(a_writer -> current_byte, a_writer -> file);                                      
         //reset a_write to blank                                                                
         a_writer -> current_byte = 0;                                                           
         //set the rest of the byte into current byte                                            
         a_writer -> current_byte = a_writer -> current_byte | ((bits << (8 - num_bits_to_write + a_writ    er -> num_bits_left)));
         //set num bits left to correct value                                                    
         a_writer -> num_bits_left = (8  - num_bits_to_write + a_writer -> num_bits_left);       
     }                                                                                           
     if(a_writer -> num_bits_left == 0) {                                                        
         fputc(a_writer -> current_byte, a_writer -> file);                                      
         a_writer -> current_byte = 0;                                                           
         a_writer -> num_bits_left = 8;                                                          
     }                                                                                           
                                                                                                 
     //Assertion check                                                                           
     assert(a_writer -> num_bits_left >= 1 && a_writer -> num_bits_left <= 8);                   
 }                                                                                               
                                                                                                 
 void flush_bit_writer(BitWriter* a_writer) {                                                    
     if(a_writer -> num_bits_left != 8){                                                         
         a_writer -> current_byte = a_writer -> current_byte & 0xff;                             
         fputc(a_writer -> current_byte, a_writer -> file);                                      
     }                                                                                           
     a_writer -> current_byte = 0;                                                               
     a_writer -> num_bits_left = 8;                                                              
 }                                                                                               
                                                                                                 
 void close_bit_writer(BitWriter* a_writer){                                                                                              
     flush_bit_writer(a_writer);                                                                 
     fclose(a_writer -> file);                                                                   
     a_writer -> file = NULL;                                                                    
                                                                                                 
 }                                                                                               
                                                                                                 
 #define __BIT_WRITER_C_V1__                                                                     
 /* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab colorcolumn=96: */  