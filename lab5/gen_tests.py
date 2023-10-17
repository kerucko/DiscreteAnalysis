import random

def randomString(n):
    s = 'abc'
    return ''.join(random.choice(s) for _ in range(n))


test = 1
patterns = 3

while patterns < 15:
    text = randomString(random.randint(20000 * patterns, 30000 * patterns))
    file = open(f'test{test}.txt', 'w')
    file.write(f'{text}\n')
    file.write(f'{patterns}\n')
    for _ in range(patterns):
        file.write(f'{randomString(random.randint(500, 1000))}\n')
    file.close()
    test += 1
    patterns += 1