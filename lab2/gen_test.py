import random


def gen_name():
    s = 'qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM'
    n = random.randint(1, 5)
    res = ''
    for _ in range(n):
        res += s[random.randint(0, len(s) - 1)]
    return res


for k in range(1, 10):
    n = k * 10 ** 5
    file = open(f'test{k}.txt', 'w')

    var = []

    for m in range(n):
        print(f'{m} / {n}')
        name = gen_name()
        # var.append(name)
        value = random.randint(0, 18446744073709551615)

        mode = random.randint(0, 3)

        if mode <= 1:                              # +
            file.write(f'+ {name} {value}\n')
            if name not in var:
                var.append(name)
        elif mode == 2:                             # -
            r = random.randint(0, 3)
            if r == 0 or len(var) == 0:
                file.write(f'- {name}\n')
            else:
                name = var[random.randint(0, len(var) - 1)]
                file.write(f'- {name}\n')
                var.remove(name)
        elif mode == 3:                             # ! name
            r = random.randint(0, 3)
            if r == 0 or len(var) == 0:
                file.write(f'{name}\n')
            else:
                file.write(f'{var[random.randint(0, len(var) - 1)]}\n')
