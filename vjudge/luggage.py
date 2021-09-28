def main(): 
    t = int(input()) 

    for i in range (t):
        luggage = input().split()
        boot1 = 0
        boot2 = 0

        for i in range(len(luggage)):
            luggage[i] = int(luggage[i])
        
        luggage.sort(reverse = True)

        for i in luggage:
            if (boot1 < boot2):
                boot1 += i
            else:
                boot2 += i  

        if boot1 == boot2:
            print("YES")
        else:
            print("NO")

if __name__ == '__main__':
    main()