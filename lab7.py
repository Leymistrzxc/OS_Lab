def main():

    print("Enter the no. of processes and resources: ", end="")
    n, m = map(int, input().split())
    
    finish = ['n'] * n
    
    print("Enter the claim matrix:")
    max_need = []
    for i in range(n):
        row = list(map(int, input().split()))
        max_need.append(row)
    
    print("Enter the allocation matrix:")
    alloc = []
    for i in range(n):
        row = list(map(int, input().split()))
        alloc.append(row)
    
    print("Resource vector: ", end="")
    total = list(map(int, input().split()))
    m = len(total)
    
    avail = [0] * m
    for i in range(n):
        for j in range(m):
            avail[j] += alloc[i][j]
    
    work = [total[j] - avail[j] for j in range(m)]
    
    need = []
    for i in range(n):
        row = []
        for j in range(m):
            row.append(max_need[i][j] - alloc[i][j])
        need.append(row)
    
    count = 0
    while count < n:
        for i in range(n):
            if finish[i] == 'n':
                c = 0
                for j in range(m):
                    if need[i][j] <= work[j]:
                        c += 1
                if c == m:
                    print(f"\nAll the resources can be allocated to Process {i+1}")
                    print("Available resources are:", end="")
                    for k in range(m):
                        work[k] += alloc[i][k]
                        print(f" {work[k]:4d}", end="")
                    print()
                    finish[i] = 'y'
                    print(f"Process {i+1} executed?: {finish[i]}")
                    count += 1
    
    print("\nSystem is in safe mode")
    print("The given state is a safe state")

if __name__ == "__main__":
    main()