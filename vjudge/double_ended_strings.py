def main():
    t = int(input())

    for i in range (t):
        a = input()
        b = input()
        helper=0
        numOp=0
        
        for i in range(len(a)):
            for j in range(i, len(a)+1):
                if (a[i:j] in b) and (j-i > helper):
                    helper = j-i

        numOp = (len(a)+len(b)-2*helper)
        print(numOp)


if __name__ == "__main__":
    main()