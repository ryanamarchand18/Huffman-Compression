 #include <stdio.h>
 #include <stdlib.h>
 #include <stdbool.h>
 #include <string.h>
 #include <assert.h>
 #include "huffman.h"
 
 int _compare_fn(const void* o1, const void* o2){
     const TreeNode* o1_int = o1;
     const TreeNode* o2_int = o2;
     int n1 = o1_int -> frequency;
     int n2 = o2_int -> frequency;
 
     return (n1 - n2);
 }
 
 Node* make_huffman_pq(Frequencies freqs){
     Node* head = NULL;
     for(int i = 0; i < 256; i++) {
         if(freqs[i] != 0){
             TreeNode* new_tree = malloc(sizeof(*new_tree));
             *new_tree = (TreeNode) {.left = NULL, .right = NULL, .character = i, .frequency = freqs[i]};
             pq_enqueue(&head, new_tree, _compare_fn);
         }
     }
     return head;
 }
 
 TreeNode* make_huffman_tree(Node* head) {
     if(head == NULL){
         return NULL;
     }
     while(head -> next != NULL){
         //store the data from the front two nodes
         Node* temp_one = pq_dequeue(&head);
         Node* temp_two = pq_dequeue(&head);
 
         //add the two frequencies
         size_t freq = (((TreeNode*)(temp_one -> a_value)) -> frequency) + (((TreeNode*)(temp_two -> a_value)) -> frequency);
         //allocate new memory for new tree
         TreeNode* new_tree = malloc(sizeof(*new_tree));
 
         //set the trees Left and right to poped nodes values
         *new_tree = (TreeNode) {.left = temp_one -> a_value, .right = temp_two -> a_value, .character = '\0', .frequency = freq};
 
         //set the a_value of temp node one to new tree
         temp_one -> a_value = new_tree;
 
         //send node back into queue
         pq_enqueue(&head, new_tree, _compare_fn);
 
         //frees unused node
         free(temp_two);
 
         free(temp_one);
     }
     //free the last node and  turn it into a tree node for the retunr
 
     TreeNode* final_head = head -> a_value;
 
     free(head);
     return final_head;
 }
 
 
 void _destroy_huffman_tree(TreeNode* a_root){
     if(a_root != NULL){
         _destroy_huffman_tree(a_root -> left);
         _destroy_huffman_tree(a_root -> right);
         free(a_root);
     }
 
 }
 
 void destroy_huffman_tree(TreeNode** a_root) {
     _destroy_huffman_tree(*a_root);
     *a_root = NULL;
 }
 
 void write_coding_table(TreeNode* root, BitWriter* a_writer){
     if(root != NULL){
         write_coding_table(root -> left, a_writer);
         write_coding_table(root -> right, a_writer);
 
         if(root -> left == NULL && root -> right == NULL){
             //write the 1 if its a leaf
             write_bits(a_writer, 0xff, 1);
             //write the  bit value if its a leaf
             write_bits(a_writer, root -> character, 8);
         }
         else{
             write_bits(a_writer, 0x00, 1);
         }
     }
 }
 
 
 void _create_table(TreeNode* root, BitCode* char_array, uint8_t byte_holder, int num_bits_holder){
     if(root != NULL){
         if(root -> left != NULL){
             _create_table(root -> left, char_array, byte_holder << 1, num_bits_holder + 1);
         }
         if(root -> right != NULL){
             _create_table(root -> right, char_array, (byte_holder << 1) | 0x01, num_bits_holder + 1);
         }
         else{
             char_array[root -> character] = (BitCode){.bits = byte_holder, .num_bits = num_bits_holder};
         }
 
     }
 
 }
 
 
 void write_compressed(TreeNode* root, BitWriter* a_writer, uint8_t* uncompressed_bytes){
     //assign letters to their compressed value and number of bits in that value
     //create an array of struct to store info
     BitCode char_array[256];
     for(int i = 0; i < 256; i++) {
         char_array[i] = (BitCode){ .bits = 0x00, .num_bits = 0};
     }
     //creates the table
     _create_table(root, char_array, 0x00, 0);
     //loop for str length
     int counter = 0;
     for(int i = 0; uncompressed_bytes[i] != '\0' ; i++) {
         counter  =  i;
     }
 
     for(int i = 0; i < counter + 1; i++) {
             write_bits(a_writer, char_array[uncompressed_bytes[i]].bits, char_array[uncompressed_bytes[i]].num_bits);
     }
 
     //take input in and find compressed  value and write it
 
 }
 /* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */