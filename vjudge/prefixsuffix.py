def main():
    s=input()
    l=len(s)
    count = [0] * (l+1)
    arr = [0]
    lengths = []

    for i in range(1,l):
        j=arr[i-1]

        while j > 0 and s[j]!= s[i]:
            j = arr[j-1]

        if (s[j] == s[i]):
            j += 1

        arr.append(j)

    m = l

    while m != 0:
        lengths += [m]
        m = arr[m-1]
    k = len(lengths)   

    for i in range(l):
        count[arr[i]] += 1

    for i in range(l-1, 1, -1):
        count[arr[i-1]] += count[i]
    print(k)
    for i in range(k-1, -1, -1):
        print(str(lengths[i])+" "+str(count[lengths[i]]+1))


if __name__ == '__main__':
    main()