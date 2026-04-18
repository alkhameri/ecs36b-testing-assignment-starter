# Google Test And Debugging Writeup

## Things I Thought To Test
Honestly, I didn't think much of what to test since I knew the test cases were given to us, but this is some of what I would think to if I knew they weren't.
1. That the min index function correctly returned the min.
2. That the swap function swapped correctly.
3. That the sort function worked in all scopes of sort, no matter how the array was formatted.
...

## Bugs

### Bug 1

### Location

Lines 62 - 72

```c++

void swap(int* a, int* b) {
  /**
 * Swap the values held in a and b.
 * @param a: The address of the first element to swap.
 * @param b: The address of the second element to swap.
 */

  int *temp = a;
  a = b;
  b = temp;
}
```

### How the bug was located

Nothing was swapping

### Description

This bug only swap s the pointer variables, and not the values, which made them unchanged when swap was called.

### Fix 

Dereferencing the pointers and swapping the values is the correct approach.

```c++
int temp = *a;
  *a = *b;
  *b = temp;
```

### Bug 2

### Location

Line 54

```c++
if (ar[i] > ar[min_index]);
```

### How the bug was located

The maximum was being returned.

### Description

The maximum was being found instead of the minimum.

### Fix

Swap the operator from greater than to less than.

```c++
if (ar[i] < ar[min_index]);
```

### Bug 3

### Location

Line 34

```c++
// 
ar_out = (int*)malloc(*len_out);
```

### How the bug was located

The values weren't being stored in the array as they should've been

### Description

ar_out is an int*, and assigning new memory to it inside parse_args didnt change the pointer given in main.

### Fix

Instead of allocating memory in parse_args, mem allocation was moved to main.

```c++
len = argc - 1;
int* given_numbers = new int[len];
```