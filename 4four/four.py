def check(n):
    return list(n) == sorted(n) and 2 in map(n.count, n)

print(sum(check(str(n)) for n in range(168630, 718098)))

from collections import Counter

def meets_part_1(num):
    digits = str(num)
    return list(digits) == sorted(digits) and any(x >= 2 for x in Counter(digits).values())

def meets_part_2(num):
    digits = str(num)
    return list(digits) == sorted(digits) and any(x == 2 for x in Counter(digits).values())

print(sum(1 for num in range(168630, 718098) if meets_part_1(num)))
print(sum(1 for num in range(168630, 718098) if meets_part_2(num)))

part1 = len({i for i in range(168630, 718098) 
            if sorted(str(i)) == list(str(i))
            and len(set(str(i))) is not (len(list(str(i))))})

part2 = len({i for i in range(168630, 718098)
              if sorted(str(i)) == list(str(i))
              and 2 in {str(i).count(x) for x in str(i)}})

print ( part1 ) 
print ( part2 )
