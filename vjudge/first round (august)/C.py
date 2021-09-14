#Codeforces 96A
#Victor Franco

def main():
    cont = 1    #starts counter for continuous players
    s = input() #receives string with players

    for i in range (1, len(s)): 

        if(s[i] == s[i-1]): #compares current char in string with next char
            cont += 1 #if the char is continuous, count 1

            if(cont == 7):
                print("YES") #if the count reaches 7, the play is dangerous, prints output, and exits program
                return 0
        else:
            cont = 1 #if there is another char in between, the count resets to 1
            
    print("NO") #if the count never reaches 7, the play isn't dangerous, prints output, and exits program


if __name__ == "__main__":
    main()
