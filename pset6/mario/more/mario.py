# Get input
while True:
    try:
        height = int(input("Height: "))

    except:
        height = -1

    if height > 0 and height < 9:
        break;

# Pyramid loop
for i in range(1,height+1):

    #Empty spaces to the left/right
    empty = height - i

    #Print pyramid
    print(' '*empty + '#'*i + '  ' + '#'*i)

