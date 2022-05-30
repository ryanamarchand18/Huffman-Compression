 #include <stdio.h>
 #include <stdlib.h>
 #include <stdbool.h>
 #include <assert.h>
 #include "miniunit.h"
 #include "clog.h"
 #include "huffman.h"
 #include "bit_writer.h"
 
 #define _mu_check_int_value(in, expected) mu_check((in) == expected)
  
 int _test_null(){
     mu_start();
     //----------
     TreeNode* null_tree = make_huffman_tree(NULL);
     mu_check(null_tree == NULL);
     //----------
     mu_end();
 }
 
 
 int _test_simple(){
     mu_start();
     //----------
     Frequencies new_freq = {0};
     const char* error = NULL;
     const char* path = "test_simple.txt";
     FILE* contents = fopen(path, "r");
     uint8_t contentBytes[24];
     int bytes_read_contents = fread(contentBytes, sizeof(*contentBytes), 24, contents);
     fclose(contents);
     mu_check(bytes_read_contents == 24);
 
     bool is_success = calc_frequencies(new_freq, path, &error);
     mu_check(is_success);
     //pq
     Node* new_node = make_huffman_pq(new_freq);
     //tree
     TreeNode* new_tree = make_huffman_tree(new_node);
     //write to table
     BitWriter new_bit = open_bit_writer("new_file.bits");
     write_compressed(new_tree, &new_bit, contentBytes);
 
     //call write coding table for coverage
     BitWriter tableBits = open_bit_writer("tableBits.bits");
     write_coding_table(new_tree, &tableBits);
     close_bit_writer(&tableBits);
 
     //close / destroy
     destroy_huffman_tree(&new_tree);
     close_bit_writer(&new_bit);
 
 
     //look at file
     FILE* results = fopen("new_file.bits", "r");
     uint8_t resultBytes[15];
     int bytes_read = fread(resultBytes, sizeof(*resultBytes), 15, results);
     fclose(results);
 
     //check
     mu_check(resultBytes[8] == 111);
     mu_check(bytes_read == 10);
     //----------
     mu_end();
 
 }
 
 
 int main(int argc, char* argv[]) {
     mu_run(_test_simple);
     mu_run(_test_null);
 
 
     return EXIT_SUCCESS;
 }
 /* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */