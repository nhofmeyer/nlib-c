# nlib-c: container library suitable for embedded systems

## Design goals
- All containers have static allocation
- Containers are generic and can handle arbitraty data types size
- Dependent on minimal c libraries (right now only uses memcpy)

## Container Types
### Stack
- Provides push and pop (LIFO) semantics
- Provides peek to preview element without removing

### Ring Buffer (Circular queue)

- Provides push and pop (FIFO) semantics
- No random access to elements
- Select whether or not to over-write oldest element on attempted write to a full ring buffer.
- Ideal for producer/consumer type applications

### List (not implemented yet)
- Static linked list
- Provides random add/delete but in static space
- Uses internal allocation to assign new spots
- No random access, may only walk the list.
