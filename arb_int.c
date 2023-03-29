#include "arb_int.h"
#include <stdio.h>
#include <string.h>

// void print(arb_int_t b) {
//     Node * temp = b.integer->head;
//     while (temp) {
//         printf("%c", temp->c);
//         temp = temp->next;
//     }
//     printf("\n");
//     // temp = b.integer->tail;
//     // while (temp) {
//     //     printf("%c", temp->c);
//     //     temp = temp->prev;
//     // }
//     // printf("\n");
// }

void arb_free (arb_int_t * i) {
    free(i->integer);
    i->integer = NULL;
    i = NULL;
}

void insert_into_LL_anywhere(LinkedList* L, Node * prev_node, 
    Node* node) {
        if (L->head == NULL || L->tail == NULL) {
            L->head = node;
            L->tail = node;
            return;
        }

        if (prev_node == NULL) {
            node->next = L->head;
            L->head->prev = node;
            L->head = node;
            return;
        }

        if (L->tail == prev_node) {
            L->tail->next = node;
            node->prev = L->tail;
            L->tail = node;
            return;
        }
        
        node->next = prev_node->next;
        prev_node->next->prev = node;
        node->prev = prev_node;
        prev_node->next = node;
        return;
}

int arb_duplicate (arb_int_t * new, const arb_int_t original) {
    new->integer = (LinkedList*)malloc(sizeof(LinkedList));
    if (new->integer == NULL)
        return ARB_INT_ERROR;
    new->integer->head = NULL;
    new->integer->tail = NULL;
    Node* temp_og = original.integer->head;

    for (int i = 0; i < original.integer->length; i++) {
        Node* node = (Node*)malloc(sizeof(Node));
        if (node == NULL)
            return ARB_INT_ERROR;
        node->c = temp_og->c;
        node->next = NULL;
        insert_into_LL_anywhere(new->integer, new->integer->tail, node);
        temp_og = temp_og->next;
    }
    new->integer->length = original.integer->length;
    new->integer->is_negative = original.integer->is_negative;
    return 0;
}

int arb_from_string (arb_int_t * i, const char * s) {
    bool isNeagtive = false;
    int length = strlen(s);
    if (s[0] == '0') {
        if (length > 1)
            return ARB_INT_ERROR;
    }

    if (s[0] == '+') {
        length--;
        s = (s+1);
    }

    else if (s[0] == '-') {
        length--;
        if (s[1] != '0')
            isNeagtive = true;
        s = (s+1);
    }

    i->integer = (LinkedList*)malloc(sizeof(LinkedList));
    if (i->integer == NULL)
        return ARB_INT_ERROR;
    i->integer->is_negative = isNeagtive;
    i->integer->length = length;
    i->integer->head = NULL;
    i->integer->tail = NULL;
    for (int j = 0; j < length; j++) {
        if ((s[j] > '9' || s[j] < '0')) {
            return ARB_INT_ERROR;
        }
        Node* node = (Node*)malloc(sizeof(Node));
        if (node == NULL)
            return ARB_INT_ERROR;
        node->c = s[j];
        node->next = NULL;
        node->prev = NULL;
        insert_into_LL_anywhere(i->integer, i->integer->tail, node);
    }
    return 0;
}

int arb_from_int (arb_int_t * i, signed long long int source) {
    int length = 0;
    bool is_negative = false;

    if (source < 0) {
        is_negative = true;
        source *= -1;
    }

    i->integer = (LinkedList*)malloc(sizeof(LinkedList));
    if (i->integer == NULL)
        return ARB_INT_ERROR;
    i->integer->is_negative = is_negative;
    i->integer->head = NULL;
    i->integer->tail = NULL;

    if (source == 0) {
        Node * node = (Node*)malloc(sizeof(Node));
        if (node == NULL)
            return ARB_INT_ERROR;
        node->c = '0';
        node->next = NULL;
        node->prev = NULL;
        insert_into_LL_anywhere(i->integer, NULL, node);
        i->integer->length = 1;
        return 0;
    }

    while (source != 0) {
        Node * node = (Node*)malloc(sizeof(Node));
        if (node == NULL)
            return ARB_INT_ERROR;
        int mod = source % 10;
        node->c = mod + '0';
        node->next = NULL;
        node->prev = NULL;
        source /= 10;
        insert_into_LL_anywhere(i->integer, NULL, node);
        length++;
    }
    i->integer->length = length;
    return 0;
}

int arb_to_string (const arb_int_t i, char * buf, size_t max) {
    if (i.integer->length > max) {
        return ARB_INT_ERROR;
    }

    Node * temp = i.integer->head;
    int index = 0;
    if (i.integer->is_negative) {
        buf[index++] = '-';
        if (i.integer->length == max) {
            return ARB_INT_ERROR;
        }
    }

    for (int j = 0; j < i.integer->length; j++) {
        buf[index++] = temp->c;
        temp = temp->next;
    }
    buf[index] = '\0';
    return 0;
}

long long int plus_or_minus(long long int a, long long int b, bool is_negative) {
    return is_negative ? (a - b) : (a + b);
}

bool comp(long long int a, long long int b, bool is_negative) {
    return is_negative ? (a > b) : (a < b);
}

int arb_to_int (const arb_int_t i, long long int * out) {
    long long int val = 0;
    Node * temp = i.integer->head;
    if (i.integer->is_negative) {
        temp = temp->next;
    }

    while(temp) {
        long long int new_val;
        new_val = plus_or_minus(val*10, (temp->c - '0'), i.integer->is_negative);
        if (comp(new_val, val, i.integer->is_negative))
            return ARB_INT_ERROR;
        val = new_val;
        temp = temp->next;
    }
    *out = val;
    return 0;
}

int arb_assign (arb_int_t x, const arb_int_t y) {
    LinkedList* LL = (LinkedList*)malloc(sizeof(LinkedList));
    if (LL == NULL)
        return ARB_INT_ERROR;
    LL->head = NULL;
    LL->tail = NULL;
    Node* temp_y = y.integer->head;
    for (int i = 0; i < y.integer->length; i++) {
        Node* node = (Node*)malloc(sizeof(Node));
        if (node == NULL)
            return ARB_INT_ERROR;
        node->c = temp_y->c;
        node->next = NULL;
        node->prev = NULL;
        insert_into_LL_anywhere(LL, LL->tail, node);
        temp_y = temp_y->next;
    }
    free(x.integer);
    x.integer = (LinkedList*)malloc(sizeof(LinkedList));
    x.integer->is_negative = y.integer->is_negative;
    x.integer->length = y.integer->length;
    if (x.integer == NULL)
        return ARB_INT_ERROR;
    x.integer->head = LL->head;
    x.integer->tail = LL->tail;
    return 0;
}

int add_linked_lists(arb_int_t a, const arb_int_t b) {
    LinkedList * l1 = a.integer;
    LinkedList * l2 = b.integer;
    bool longer = a.integer->length > b.integer->length;
    Node * t1 = l1->tail;
    Node * t2 = l2->tail;

    if (longer) {
        int carry = 0;
        while (t2) {
            int sum = (t1->c - '0') + (t2->c - '0') + carry;
            carry = sum >= 10 ? 1 : 0;
            sum %= 10;
            t1->c = '0' + sum;
            t1 = t1->prev;
            t2 = t2->prev;
        }

        while (t1) {
            int sum = (t1->c - '0') + carry;
            carry = sum == 10 ? 1 : 0;
            sum %= 10;
            t1->c = '0' + sum;
            t1 = t1->prev;
        }

        if (carry) {
            Node* node = (Node*)malloc(sizeof(Node));
            if (node == NULL)
                return ARB_INT_ERROR;
            node->c = '1';
            node->prev = NULL;
            node->next = NULL;
            insert_into_LL_anywhere(l1, NULL, node);
        }
        return 0;
    }

    else {
        int carry = 0;
        while (t1) {
            int sum = (t1->c - '0') + (t2->c - '0') + carry;
            carry = sum >= 10 ? 1 : 0;
            sum %= 10;
            t1->c = '0' + sum;
            t1 = t1->prev;
            t2 = t2->prev;
        }

        while (t2) {
            int sum = (t2->c - '0') + carry;
            carry = sum == 10 ? 1 : 0;
            sum %= 10;
            Node* node = (Node*)malloc(sizeof(Node));
            if (node == NULL)
                return ARB_INT_ERROR;
            node->c = '0' + sum;
            node->prev = NULL;
            node->next = NULL;
            insert_into_LL_anywhere(l1, NULL, node);
            t2 = t2->prev;
        }

        if (carry) {
            Node* node = (Node*)malloc(sizeof(Node));
            if (node == NULL)
                return ARB_INT_ERROR;
            node->c = '1';
            node->prev = NULL;
            node->next = NULL;
            insert_into_LL_anywhere(l1, NULL, node);
        }
        return 0;
    }
}

int sub_linked_lists(arb_int_t a, const arb_int_t b) {
    LinkedList * l1 = a.integer;
    LinkedList * l2 = b.integer;
    Node * t1 = l1->tail;
    Node * t2 = l2->tail;

    int borrow = 0;
    while (t2) {
        int sub = (t1->c - '0') - (t2->c - '0') - borrow;
        borrow = sub < 0 ? 1 : 0;
        if (sub < 0)
            sub += 10;
        t1->c = '0' + sub;
        t1 = t1->prev;
        t2 = t2->prev;
    }

    if (borrow) {
        int sub = (t1->c - '0') - borrow;
        t1->c = '0' + sub;
    }

    Node * temp = l1->head;
    int count = 0;
    while (temp->c == '0') {
        Node * prev = temp;
        temp = temp->next;
        free(prev);
        prev = NULL;
        count++;
    }
    l1->head = temp;
    a.integer->length -= count;
    return 0;
}

int arb_add (arb_int_t x, const arb_int_t y) {
    if ((!x.integer->is_negative && !y.integer->is_negative) 
            || (x.integer->is_negative && y.integer->is_negative)) {
        return add_linked_lists(x, y);
    }

    else if (x.integer->is_negative && !y.integer->is_negative) {
            arb_int_t *x1, *y1;
            x1 = (arb_int_t*)malloc(sizeof(arb_int_t));
            y1 = (arb_int_t*)malloc(sizeof(arb_int_t));
            if (arb_duplicate(x1, x) == ARB_INT_ERROR)
                return ARB_INT_ERROR;
            x1->integer->is_negative = false;

            if (arb_duplicate(y1, y) == ARB_INT_ERROR)
                return ARB_INT_ERROR;
            arb_subtract(*y1, *x1);
            if (arb_assign(x, *y1) == ARB_INT_ERROR)
                return ARB_INT_ERROR;
            arb_free(x1);
            arb_free(y1);
            return 0;
    }

    else {
        arb_int_t * y1;
        y1 = (arb_int_t*)malloc(sizeof(arb_int_t));
        if (arb_duplicate(y1, y) == ARB_INT_ERROR)
            return ARB_INT_ERROR;
        y1->integer->is_negative = false; 
        arb_subtract(x, *y1);
        arb_free(y1);
        return 0;
    }

}

int arb_subtract (arb_int_t x, const arb_int_t y) {
    if ((!x.integer->is_negative && y.integer->is_negative) 
            || (x.integer->is_negative && !y.integer->is_negative)) {
        return add_linked_lists(x, y);
    }
    
    else {
        if (x.integer->length > y.integer->length || 
                (x.integer->length == y.integer->length && arb_compare(x, y) == 1))
            return sub_linked_lists(x, y);

        else if ((x.integer->length == y.integer->length) && (arb_compare(x, y) == 0)) {
            arb_int_t *x1;
            x1 = (arb_int_t*)malloc(sizeof(arb_int_t));
            arb_from_int(x1, 0);
            if (arb_assign(x, *x1) == ARB_INT_ERROR)
                return ARB_INT_ERROR;
            arb_free(x1);
            return 0;
        } 

        arb_int_t *x1, *y1;
        x1 = (arb_int_t*)malloc(sizeof(arb_int_t));
        y1 = (arb_int_t*)malloc(sizeof(arb_int_t));
        if (arb_duplicate(x1, x) == ARB_INT_ERROR)
            return ARB_INT_ERROR;

        if (arb_duplicate(y1, y) == ARB_INT_ERROR)
            return ARB_INT_ERROR;

        sub_linked_lists(*y1, *x1);
        if (arb_assign(x, *y1) == ARB_INT_ERROR)
            return ARB_INT_ERROR;

        x.integer->is_negative = !x.integer->is_negative;

        arb_free(x1);
        arb_free(y1);
    }
    return 0;
}

int arb_multiply (arb_int_t x, const arb_int_t y) {
    LinkedList * l1 = x.integer;
    LinkedList * l2 = y.integer;
    int mul[l1->length + l2->length + 1];
    for (int i = 0; i < l1->length + l2->length + 1; i++) {
        mul[i] = 0;
    }

    Node * t1 = l1->tail;
    Node * t2 = l2->tail;
    int i = 0, j, carry;
    while (t2) {
        carry = 0;
        t1 = l1->tail;
        j = i;
        while (t1) {
            int m = (t2->c - '0') * (t1->c - '0') + carry;
            carry = m/10;
            m %= 10;
            mul[j] += m;
            carry = carry + mul[j]/10;
            mul[j] = mul[j]% 10;
            t1 = t1->prev;
            j++;
        }
        if (carry)
            mul[j] += carry;
        i++;
        t2 = t2->prev;
    }
    if (carry)
        mul[i] += carry;
    
    int last = l1->length + l2->length + 1;
    for (int x = l1->length + l2->length + 1; x >=0; x--) {
        if (mul[x] == 0)
            continue;
        else {
            last = x;
            break;
        }
    }

    char res[last+2];
    for (int x = last; x >=0; x--) {
        res[last - x] = mul[x] + '0';
    }
    res[last+1] = '\0';
    arb_int_t * x1;
    x1 = (arb_int_t*)malloc(sizeof(arb_int_t));
    if (arb_from_string(x1, res) == ARB_INT_ERROR)
        return ARB_INT_ERROR;
    if (arb_assign(x, *x1) == ARB_INT_ERROR)
        return ARB_INT_ERROR;

    arb_free(x1);
    return 0;
}

int arb_divide (arb_int_t x, const arb_int_t y) {
    int val = arb_compare(x, y);
    arb_int_t * x1;
    x1 = (arb_int_t*)malloc(sizeof(arb_int_t));
    if (val == -1) {
        arb_from_int(x1, 0);
        arb_assign(x, *x1);
        free(x1);
    }
    else if (val == 0) {
        arb_from_int(x1, 1);
        arb_assign(x, *x1);
        free(x1);
    }
    
    return 0;
}

int comp_eq_length_linked_lists(Node * N1, Node * N2) {
    while (N1) {
        if (N1->c > N2->c)
            return 1;
        
        else if (N2->c > N1->c) 
            return -1;
        
        N1 = N1->next;
        N2 = N2->next;
    }
    return 0;
}

int arb_compare (const arb_int_t x, const arb_int_t y) {
    if (!x.integer->is_negative && y.integer->is_negative)
        return 1;
    
    else if (x.integer->is_negative && !y.integer->is_negative)
        return -1;
    
    else if (x.integer->is_negative && y.integer->is_negative) {
        if (x.integer->length == y.integer->length)
            return -1 * comp_eq_length_linked_lists(x.integer->head, y.integer->head);
        
        else if (x.integer->length > y.integer->length)
            return -1;
        
        else
            return 1;
    }

    else {
        if (x.integer->length == y.integer->length) 
            return comp_eq_length_linked_lists(x.integer->head, y.integer->head);
        
        else if (x.integer->length > y.integer->length)
            return 1;
        
        else
            return -1;
    }
}

int arb_digit_count (const arb_int_t x) {
    return (x.integer->is_negative ? x.integer->length + 1 : x.integer->length);
}

// int main () {
//     arb_int_t a, b;
//     arb_from_string(&a, "-123123123123123123123123123123");
//     arb_from_string(&b, "123123123123123123123123123123");
//     printf("a neg %d\n", a.integer->is_negative);
//     printf("b neg %d\n", b.integer->is_negative);
//     arb_multiply(a, b);
//     printf("neg %d ", a.integer->is_negative);
//     print(a);
//     printf("15159303447591735880024168312426282137993849705561417273129\n");
//     // arb_subtract(a, b);
//     // printf("neg %d ", a.integer->is_negative);
//     // print(a);

//     // arb_from_int(&a, -2);
//     // arb_subtract(a, b);
//     // printf("neg %d ", a.integer->is_negative);
//     // print(a);

//     // arb_from_int(&a, 2);
//     // arb_from_int(&b, -1);
//     // arb_subtract(a, b);
//     // printf("neg %d ", a.integer->is_negative);
//     // print(a);
//     return EXIT_SUCCESS;
// }