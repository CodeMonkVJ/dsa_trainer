# Dynamic Array

Use the existing `DynamicArray` API to maintain a growable array of integers.

Requirements:

- Append values while growing capacity safely.
- Pop from the back and report whether an element existed.
- Support indexed access and clearing all elements.
- Keep append amortized `O(1)` and avoid leaks.
- Start with a capacity of at least 4 and grow before writing past capacity.
- `daAt` must return `-111111` for an index outside the current size.
- `daFree` must release the allocation and reset `data`, `size`, and `capacity`.
