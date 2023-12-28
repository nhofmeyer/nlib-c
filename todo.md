1. Add test cases for ring buffer
2. Add randomized test cases (fuzzing)
    - Randomize data size from 1 to n bytes (largish number)
    - Randomize order of operations (pop, push, etc)
    - Record order of operations in case of failure to trace
2. Remove memcpy dependency from containers
3. Implement list type data structure