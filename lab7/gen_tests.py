import random

i = 10
test = 1
while test < 4:
    n = i
    m = i
    matrix = []
    for _ in range(n):
        row = []
        for _ in range(m):
            row.append(random.randint(1, 100))  # Здесь можно указать нужный диапазон случайных чисел
        matrix.append(row)

    file = open(f'test{test}.txt', 'w')
    file.write(f'{n} {m}\n')
    for row in matrix:
        for num in row:
            file.write(str(num) + ' ')
        file.write('\n')
    file.close()

    i *= 10
    test += 1