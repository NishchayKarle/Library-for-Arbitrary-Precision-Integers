The struct arb_int_t would represent the arbitary precision integer.
int LinkedList::length - would indicate how long the integer is in string representation. This includes "-" character 
    for negative numbers. For positive numbers(including 0), no length is alloted for "+" sign.
bool LinkedList:: is_negative - would indicate if the stored integer is negative or not.
LinkedList* arb_int_t:: integer - is a linked list that would store the provided integer with 
    each node being a char from the string representation of the integer provided.

Functions in arb_int.c
1. "arb_free" - free the memory alloted to storing the integer.

2. "arb_duplicate" - will duplicate the provided arb_int_t and create a new arb_int_t.
                   - memory required will be alloted to the duplicate arb_int_t, and the length and is_negative
                        attributes are set the same as the arb_int_t being duplicated.

3. "arb_from_string" - error out if the string provied has trailing zero's (lines 61-64)
                     - if the string has a "+" sign, move the starting point of the string to index 1 (lines 66-69)
                     - (lines 71-76) set is_negative to true if the integer is negative and check for "-0" case.
                     - (lines 58-96) allocate memory required for the integer and store the integer in the struct
                        arb_int_t.

4. "arb_from_int" - (lines 103-107) set is_negative to true if the provided integer is negative
                  - (lines 109-136) allocate memory required for the integer and store the integer in the struct
                        arb_int_t. 

5. "arb_to_string" - (lines 139-147) build the string representation of the arb_int_t by traversing through the LinkedList
                        arb_int_t:: integer.

6. "arb_to_int" - build the 'long long int' from arb_int_t by traversing through the LinkedList
                        arb_int_t:: integer and creating the 'long long int' as we do the traversal.

7. "arb_assign" - (lines 177-191) create a linked list copy of the arb_int_t whose value we are 
                    assigning to the other arb_int_t.
                - (lines 192-200) free the linked list of the other arb_int_t and assign the new linked list as its 
                    arb_int_t::integer.

8. "arb_add" - (lines 353 - 357) if both arn_int_t's are positive or both are negative then we add the numbers
                    using "add_linked_lists" and the sign stays the same as original.
               (lines 359 - 373) if the first number is negative and second number is positive, we ignore the sign of
                    of the first number and subtract the first number from the second using arb_subtract, which will also
                    take care of the sign of the result.
               (lines 375-385) if the first arb_int_t is positive and second is negative, we ignore the sign of the second,
                    and subtract the second number from the first using arb_subtract, which will also take care of the sign 
                    of the result.

9. "arb_subtract" - (lines 388 - 391) if the two arb_int_t's are opposite signs, we add the numbers using "add_linked_lists"
                        which adds two linked lists, and doesn't look at the sign. The sign of the first number will be the 
                        same as the sign of the result.
                    now both numbers are of the same sign
                    (lines 394 - 396) if both number of the same length and the first number is greater, we use "sub_linked_lists"
                        to subtract second number from the first.
                    (lines 398 - 405) if both numbers are the same, the answer is 0
                    (lines 407 - 423) we duplicate both numbers, subtract the first one from the second and change the sign of 
                        the result.

10. "arb_multiply" - (lines 426 - 482) we use the classical multiplication method to multiply the numbers represented by the
                        linked lists.

11. "arb_divide" - INCOMPLETE
                   if the second number is greater, we return 0.
                   if both numbers are equal, we return 

12. "arb_compare" - (lines 523 - 524) if the first arb_int_t is positive and the second is negative, the first is bigger 
                        so we return 1.
                    (lines 526 - 527) if the first arb_int_t is negative and the second is positive, the second is bigger
                        so we return -1
                    (lines 529 - 538) both numbers are negative,
                        (lines 530 - 531) if both numbers are of equal length, we use "comp_eq_length_linked_lists" to arb_compare
                            two linked lists of equal length and multiply the result by -1 since both were negative integers
                        (lines 533 - 534) if the first number is longer in length, we return -1
                        (lines 536 - 537) else we return 1
                    (lines 540 - 550) both numbers are positive,
                        (lines 541 - 542) if both numbers are of equal length, we use "comp_eq_length_linked_lists" to arb_compare
                            two linked lists of equal length. 
                        (lines 544 - 545) if the first number is longer in length, we return 1.
                        (lines 547 - 548) else we return -1.

13. "arb_digit_count" - (lines 552) if the number is positive, we return the stored length. 
                            if the number is negative, we add 1 to the stored length and return it.