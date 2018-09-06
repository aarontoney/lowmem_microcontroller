# lowmem_microcontroller

<P>This library implements some useful data structures like lists, queues, and stacks for use on low memory microcontrollers. The data structures are implemented in such a way that they are all built from common bases like array_list or array_linked list. The common base minimizes the flash memory requirement, especially when using multiple different data structures built from a common base. The data sructures whose names begin with the all_ prefix also use a free list for simple dynamic memory management.</P>

<P>The common parts of the data structures are basically all directly derived from the underlying base data structures, with some function wrapping to make the interfaces and namespaces what humans expect. This lets you use operations like push and pop when using a stack, or enqueue and dequeue when using a queue, even when both are using an array_list or array_linked list as their base. Modern optimizing compilers will optimize off most of the overlay. So using the code common base works out to be about a 40% reduction on required flash space. The specific savings goes up with the number of different types of data types being used.</P>

<B>Who is this library for?</B>
<P>This library implements some useful common data structures and algorithms intended for use on low power embedded processors. As a quick rule of thumb – if you are measuring your RAM in megabytes and not kilobytes, or if you are not worried about needing to make your program fit into on chip flash memory, than this library is probably not for you. That said, there is not reason you cant run these libraries on a more powerful machine, just on those you can useually scale up to a number of libraries containing this same functionality. </P>

<B>Why an implementation with handles over pointers?</B>
<P>This library makes the tradeoff of using 8 bit array indexes, as opposed to pointers. This saves 1-3 bytes of data for each value stored. That adds up fast in an embedded context. Practically it means being able to store more than twice the elements for the same amount of memory. While this approach does have the drawback of only being able to store 256 elements in any derived data structure, if you need to do more than that on tiny embedded devices you probably need to re-think your embedded approach. </P>

