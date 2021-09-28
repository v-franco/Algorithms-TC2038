def main():
    t = int(input())

    for i in range (t):
        numLetters = 0
        poem = list(input())

        for i in range (1, len(poem)):
            if (poem[i] == poem[i-1] and i-1 >= 0) or (poem[i] == poem[i-2] and i-2 >= 0):
                poem[i] = "#"
                numLetters += 1
                
        print (numLetters)

if __name__ == "__main__":
    main()