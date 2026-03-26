ms = int(input("Enter total memory: "))
temp = ms
mp = []
n = 0
ch = 'y'

i = 0
while ch == 'y' and temp > 0:
    mem = int(input(f"\nMemory required for process {i+1}: "))
    
    if mem <= temp:
        print(f"Allocated for Process {i+1}")
        temp -= mem
        mp.append(mem)
        i += 1
        n += 1
    else:
        print("Memory Full!")
        break
    
    if temp > 0:
        ch = input("Continue? (y/n): ")
    else:
        print("\nMemory Completely Full!")
        break

print(f"\nTotal Memory: {ms}")
print("\nProcess\tMemory Allocated")
for i in range(n):
    print(f"{i+1}\t{mp[i]}")

print(f"\nTotal Allocated: {ms - temp}")
print(f"External Fragmentation: {temp}")