def part1():
    with open("input.txt") as f:
        lines = f.readlines()

    sum = 0

    for line in lines:
        a, b = None, None

        for c in line:
            if c.isdigit() and not a:
                a = int(c)
                break

        for c in reversed(line):
            if c.isdigit() and not b:
                b = int(c)
                break

        n = a*10+b
        sum += n

    print(sum)

# part1()

def part2():
    with open("sample.txt") as f:
        lines = f.readlines()

    words = {
        "eight": 8,
        "two": 2,
        "one": 1,
        "three": 3,
        "four": 4,
        "five": 5,
        "six": 6,
        "seven": 7,
        "nine": 9,
    }

    wordsr = { word[::-1]:n for word,n in words.items() }

    sum = 0

    for line in lines:
        a, b = None, None

        for word in words:
            line = line.replace(word, str(words[word]))

        for i,c in enumerate(line):
            if c.isdigit() and not a:
                a = int(c)
                break

        for i,c in enumerate(reversed(line)):
            if c.isdigit() and not b:
                b = int(c)
                break

        print(line, a, b)

        n = a*10+b
        sum += n

    print(sum)
part2()
