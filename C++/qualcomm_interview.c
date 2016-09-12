extern static ?

static int z; // data segment
void foo() {
  int bar = 0; // stack
  bar += 10;
  static int x = 0;
  int y;
  for (int i = 0; i < 10; i++)
    ++x;
  printf("%d %d", bar, x); // 10 10 // 10 20
  foo();
}

void function()
{
    ++x;
    printf("%d", x); // x = 11
}

Memory Address Space:
heap
text
data
stack


"123" => 123
int atoi(char *str) {
  // String to Integer
  int result = 0;
  for (int i = 0; str[i] != '\0'; ++i) // "173'\0'"
  {
      result = result * 10 + str[i]; // 1, 17, 173
  }
  return result;
}

Design a data strutructure,
void add_word(string x); // LL - O(1) Trie - O(logn)
bool exists(string x); // LL - O(n) Trie - O(logn)

add_word("hello"); add_word("xxx") exists("hello")  => true
add_word("xxor")

root(NULL)
h x
e x o
l x r
l
o

x is 32-bit number: x = 0 => 32, x =1 => 31, x = 15 (00000000..1111)=> 28
int count_leading_zeros(uint32_t x) {
    int foo = 0;
    for (foo = 0; x != 0; x >>= 1)
        foo += 1;
    return (32 - foo);
}
root(NULL)
1-10 11-20 21-30 ...
1-3 4-6
hello xxx xxor (log3n)



printing k largest elements in an array. Elements in array can be in any order.

For example, if given array is [1, 23, 12, 9, 30, 2, 50] and you are asked for the largest 3 elements i.e., k = 3 then your program should print 50, 30 and 23.

find_k_largest(arr, 3);
vector<int> find_k_largest(vector<int> data, int k) {

}


void quick_sort( int *arr, int start, int end)
{
    if(start < end)
    {
        int partition_index = partition(arr, start, end);
        quick_sort(arr, start, partition_index - 1);
        quick_sort(arr, partition_index+1, end);
    }
}

1- 00000000...1
23 - 00xcxc
12 - 0000..
9 -
