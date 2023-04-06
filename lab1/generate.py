a, b, c, d = map(int, input().split())
x1 = a + c
y1 = max(b, d)
s1 = x1 * y1

a2, b2 = b, a
x2 = a2 + c
y2 = max(b2, d)
s2 = x2 * y2

c3, d3 = d, c
x3 = a + c3
y3 = max(b, d3)
s3 = x3 * y3

a4, b4 = b, a
c4, d4, = d, c
x4 = a4 + c4
y4 = max(b4, d4)
s4 = x4 * y4

if s1 <= min(s2, s3, s4):
    print(x1, y1)
elif s2 <= min(s1, s3, s4):
    print(x2, y2)
elif s3 <= min(s1, s2, s4):
    print(x3, y3)
else:
    print(x4, y4)