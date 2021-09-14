#Codeforcese 268A
#Victor Franco

def main():
    n = int(input()) #receives number of matches to be played
    colors = [] #creates array that will contain the colors
    count = 0

    for i in range(n):
        colors.append(list(map(int, input().split()))) #adds the colors used in each match

    for i in colors:
        for j in colors:
            if (i[0] == j[1]): #checks the home team color against all away teams colors
                count +=1   #count 1 for each time a home team will play with away kits

    print(count)


if __name__ == "__main__":
    main()      