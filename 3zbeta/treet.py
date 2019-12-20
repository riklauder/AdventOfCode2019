import time

def get_corners(movements):
  x = 0
  y = 0
  corners = []
  for mov in movements:
    direction = mov[0]
    amt = int(mov[1:])
    
    if(direction == "U"):
      y += amt
    elif(direction == "D"):
      y -= amt
    elif(direction == "R"):
      x += amt
    elif(direction == "L"):
      x -= amt

    pos = (x, y)
    corners.append(pos)

  return corners

def get_lines(corners):
  lines = []
  for i in range(len(corners) - 1):
    p1 = corners[i]
    p2 = corners[i+1]
    seg = [(p1[0], p1[1]), (p2[0], p2[1])]
    lines.append(seg)
  
  return lines

def get_lines_of_dir(lines, horiz=False, vert=False):
  if((not horiz) and (not vert)):
    return []
  elif(horiz and vert):
    return lines

  output_lines = []
  for line in lines:
    if vert and line[0][0] == line[1][0]:
      output_lines.append(line)
    elif horiz and line[0][1] == line[1][1]:
      output_lines.append(line)
  
  return output_lines

def get_intersections(hlines, vlines):
  pts = []
  for w1 in vlines:
    for w2 in hlines:
      ymin = min(w1[0][1], w1[1][1])
      ymax = max(w1[0][1], w1[1][1])

      xmin = min(w2[0][0], w2[1][0])
      xmax = max(w2[0][0], w2[1][0])

      if(w2[0][1] >= ymin and w2[0][1] <= ymax and w1[0][0] >= xmin and w1[0][0] <= xmax):
        pts.append((w1[0][0], w2[0][1]))

  return pts

def get_steps_to_pt(x, y, lines):
  steps = 0
  for line in lines:
    if line[0][0] == line[1][0]: # Line is vertical
      ymin = min(line[0][1], line[1][1])
      ymax = max(line[0][1], line[1][1])
      if(line[0][0] == x and y >= ymin and y <= ymax):
        # Reached the point!
        steps += abs(line[0][1] - y)
        return steps
      steps += abs(line[0][1] - line[1][1])
    elif line[0][1] == line[1][1]: # Line is horizontal
      xmin = min(line[0][0], line[1][0])
      xmax = max(line[0][0], line[1][0])
      if(line[0][1] == y and x >= xmin and x <= xmax):
        # Reached the point!
        steps += abs(line[0][0] - x)
        return steps
      steps += abs(line[0][0] - line[1][0])
  
  return None

lines = open('input.txt').read().split('\n')

start = time.time()
lines = [ line.split(',') for line in lines ]

w1c = get_corners(lines[0])
w2c = get_corners(lines[1])

w1l = get_lines(w1c)
w2l = get_lines(w2c)

w1v = get_lines_of_dir(w1l, vert=True)
w1h = get_lines_of_dir(w1l, horiz=True)
w2v = get_lines_of_dir(w2l, vert=True)
w2h = get_lines_of_dir(w2l, horiz=True)

isections = get_intersections(w1h, w2v)
isections += get_intersections(w2h, w1v)

steps = []
for (x, y) in isections:
  w1s = get_steps_to_pt(x, y, w1l)
  w2s = get_steps_to_pt(x, y, w2l)
  tot = w1s + w2s
  steps.append(tot)



steps = []
for (x, y) in isections:
  w1s = get_steps_to_pt(x, y, w1l)
  w2s = get_steps_to_pt(x, y, w2l)
  tot = w1s + w2s
  steps.append(tot)

distances = [ abs(x) + abs(y) for (x, y) in isections ]

print("Part 1 solution: ")

print(f"Closest by Manhattan distance: {min(distances)}")


print("Part 2 solution: ")
print(f"Least steps: {min(steps)}")

print("--- %s seconds ---" % (time.time() - start))