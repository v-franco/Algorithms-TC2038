#Codeforces 160A - Twins
#Victor Franco


def main():
    n = int(input()) #Receives number of coins
    seq = list(map(int, input().split()[:n])) #Receives a sequence of coins' values separated with spaces
    seq.sort(reverse = True) #sorts the values in descending order
    count = 0

    for i in range (len(seq)): 
        if (sum(seq[:i]) > sum(seq[i:])): #compares if the sum of the values left of i are  greater than the sum of the values right of i
            print(count)    #prints output and program ends
            return 0
        else:
            count += 1  #continues coin count

if __name__ == "__main__":
    main()
