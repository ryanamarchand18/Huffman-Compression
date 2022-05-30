 #include <stdio.h>
 #include <stdlib.h>
 #include <stdbool.h>
 #include <assert.h>
 #include "priority_queue.h"
 
 Node* pq_enqueue(Node** a_head, void* a_value, int (*cmp_fn)(const void*, const void*)) {
     Node* new_node = malloc(sizeof(*new_node));
     *new_node = (Node) {.a_value = a_value, .next = NULL};
 
     Node* temp = *a_head;
 
     if(*a_head == NULL) {
         *a_head = new_node;
     }
     else if(cmp_fn(a_value, (*a_head) -> a_value) < 0){
         new_node -> next = *a_head;
         (*a_head) = new_node;
     }
     else {
         while(temp -> next != NULL && cmp_fn(a_value, temp -> next -> a_value) >= 0){
             temp = temp -> next;
         }
         new_node -> next = temp -> next;
         temp -> next = new_node;
     }
     return new_node;
 }
 
 Node* pq_dequeue(Node** a_head) {
     Node* pop_node = *a_head;
     if(*a_head != NULL){
         (*a_head) = (*a_head) -> next;
     }
 
     return pop_node;
 }
 
 
 Node* stack_push(Node** a_head, void* a_value) {
     Node* new_node = malloc(sizeof(*new_node));
     *new_node = (Node) {.a_value = a_value, .next = *a_head};
     *a_head = new_node;
     return new_node;
 }
 
 
 Node* stack_pop(Node** a_head) {
     Node* pop_node = *a_head;
     if(*a_head != NULL){
         (*a_head) = (*a_head) -> next;
     }
     return pop_node;
 }


 void destroy_list(Node** a_head, void (*destroy_value_fn)(void*)) {
     while(*a_head != NULL){
         Node* pop_node = pq_dequeue(a_head);
         destroy_value_fn(pop_node -> a_value);
         free(pop_node);
     }
 }
 
 
 #define HUFFMAN_C_V1