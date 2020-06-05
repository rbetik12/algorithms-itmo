#!/usr/bin/python3


def main():
    numbers = []
    with open("input.txt", "r") as f:
        ss = f.read()
        ss = ss.strip().split("\n")[1].strip().split()
        for y, x in enumerate(ss):
            numbers.append((float(x), y + 1))

    numbers = sorted(numbers, key=lambda x: x[0])

    # print(numbers[0][1], numbers[int((len(numbers) - 1) / 2)][1], numbers[len(numbers) - 1][1])
    with open("output.txt", "w") as f:
        f.write("{} {} {}".format(numbers[0][1], numbers[int((len(numbers) - 1) / 2)][1], numbers[len(numbers) - 1][1]))


if __name__ == '__main__':
    main()
