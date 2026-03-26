ms = int(input("Enter total memory: "))
bs = int(input("Enter block size: "))

nob = ms // bs
ef = ms - nob * bs

n = int(input("Enter number of processes: "))

mp = []
for i in range(n):
    mem = int(input(f"Memory required for process {i+1}: "))
    mp.append(mem)

print(f"\nBlocks available: {nob}")
print("\nProcess\tMemory\tAllocated\tInternal Frag")

tif = 0
p = 0
i = 0

while i < n and p < nob:
    print(f"{i+1}\t{mp[i]}\t", end="")
    
    if mp[i] > bs:
        print("NO\t\t---")
    else:
        print(f"YES\t\t{bs - mp[i]}")
        tif += bs - mp[i]
        p += 1
    i += 1

if i < n:
    print("\nMemory Full!")

print(f"\nTotal Internal Fragmentation: {tif}")
print(f"Total External Fragmentation: {ef}")