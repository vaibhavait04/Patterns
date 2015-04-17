## Myths of performance tuning 

Performance tuning is a serious business and requires much more than gut feeling and intuition. And yet, in many projects that I review I find code that’s based on unfounded assumptions and myths about performance. Some of the common myths are dispelled here.

## Using Tiny Loop Counters

Suppose you have a loop that executes 100 times. Some programmers believe that by using char as the loop counter’s type they are gaining any performance boost:

for (char cout=0; count <MAX; count++)
{
 //do something
}

This is a wrong idea. The code seemingly saves thee bytes(!) from the stack memory but in reality, there’s no saving here at all. A 32-bit compiler will have to convert the char to int. If you examine the CPU registers when the loop is running you will discover that the counter is actually represented as a 32-bit value, on a 32 bit register. To conclude, this "performance tweak" doesn’t improve anything, neither in terms of speed nor in terms of space. As a rule, always use int for loop counters. Generally speaking, int is the fastest datatype on your machine. If you’re a loop optimization connoisseur, you can use one of the C99 fastest minimum-width signed integer types e.g., int_fast8_t int_fast16_t etc.

## Passing Everything by Reference

For most cases, passing object by reference is more efficient than passing an object by value. There are however two exceptions to this rule: passing pointers (as well as arrays), and passing native types. Is there any difference between passing a pointer and passing a reference to a pointer? Consider:

void func(char *& s); 
void func(char * t); 

s isn’t more efficient than t in any way. References are implemented as pointers under the hood so if you disassemble the code of these two functions you will find out that what’s passed as the argument is a pointer in both cases. Passing a reference to a pointer is required in one case -- when the callee may assign a new value to the pointer itself, not just the object to which the pointer is bound. For example, if func() is to allocate a new array and assign that array’s address to its argument you should use the first overloaded version:

void func(char *& s)
{
 s= new char[2];
}

However, if the callee merely accesses the object bound to the pointer, use the second form:

void func(char * t)
{
 t[0]= ’\t’;
}

## Inlining Every Member Function

With respect to inline, the rule is simple: forget about it. Why? Because we’re almost in 2008, not 1988. Chances are that your compiler knows better than you which functions should be inlined, if any. Furthermore, inlining is the implementation’s business. I’ve dedicated a lot of time to explaining how and when inline might backfire. There’s one more problem with inline -- the programmer who wrote the function can’t predict where that function will be called from, and how often. Theoretically, some calls of a certain function will be inlined, whereas other calls will not. Therefore, let the implementation decide whether a function should be inlined, and when.

Using register variables is also included in this category of performance myths. However, since most compilers completely ignore the register storage specifier, it’s less harmful than inline.

## Reverting to Built-in Arrays instead of Using Containers

There’s no arguing that built-in arrays are more efficient than std::vector both in terms of speed and space. However, this is a simplistic and unfair comparison. Programmers don’t use arrays in isolation. They also wrap the code that accesses array elements with range-checking code, exception handling and also keep track of the array’s size using another variable. All this excess baggage incurs unavoidable performance overhead. A fair comparison should take all that into account. You will find that most of the time, you can also improve your vectors’ performance by preallocating storage or using move semantics. If vector is still too expensive for your taste, consider std::tr1::array<T> instead of a built-in array.

## Using const to Optimize Code

const was never meant to improve performance. Rather, it instructs the compiler to protect an object from inadvertent modification by the programmer. As a bonus, const happens to be a performance booster in many cases because it enables the implementation to cache the object in a register or the ROM. That said, const should not be used just for the sake of performance. Remember also that const objects can also be volatile-qualified. In that case, const’s performance benefits are usually lost. There is little or no difference between a plain volatile object and a const volatile object with respect to performance (and performance only!), so don’t use const just because you believe it will make your program run slightly faster. 

Source: http://www.informit.com/guides/content.aspx?g=cplusplus&seqNum=372

