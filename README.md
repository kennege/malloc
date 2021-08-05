# malloc
A simple malloc/free memory management demo in C

The demo included in main() produces:

line 104:
address: 0x5635b6985000, size: 4, free: 0

[inserted 3 bytes into freed memory]

line 112:
address: 0x5635b6985000, size: 4, free: 0

line 120:
address: 0x5635b6985000, size: 4, free: 1
address: 0x5635b69a7000, size: 5, free: 0

[inserted 5 bytes into freed memory]

line 128:
address: 0x5635b6985000, size: 4, free: 1
address: 0x5635b69a7000, size: 5, free: 0

line 133:
address: 0x5635b6985000, size: 4, free: 1
address: 0x5635b69a7000, size: 5, free: 0

line 136:
address: 0x5635b6985000, size: 4, free: 1
address: 0x5635b69a7000, size: 5, free: 1
