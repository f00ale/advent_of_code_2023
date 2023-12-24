#!/usr/bin/env python3

from aoclib import *

import re
import z3

def get_intersection(line1, line2):
    x1,x2 = line1[0].x,line1[1].x
    y1,y2 = line1[0].y,line1[1].y
    x3,x4 = line2[0].x,line2[1].x
    y3,y4 = line2[0].y,line2[1].y

    pn = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4)
    if pn == 0:
        return None,None
    px = (x1*y2 - y1*x2)*(x3-x4) - (x1-x2)*(x3*y4 - y3*x4)
    py = (x1*y2 - y1*x2)*(y3-y4) - (y1-y2)*(x3*y4 - y3*x4)
    return px/pn, py/pn

class vec3:
    def __init__(self, x,y,z):
        self.x = x
        self.y = y
        self.z = z
    def __add__(self, other):
        return vec3(self.x+other.x, self.y+other.y, self.z+other.z)

def main():
    ans1, ans2 = 0, 0
    lines = readdata()
    fdata = []
    for line in lines:
        line = line.strip()
        fdata.append(list(map(int,re.findall(r'-?\d+', line))))

    data = []
    for x,y,z,dx,dy,dz in fdata:
        data.append((vec3(x,y,z),vec3(dx,dy,dz)))


    for i1 in range(len(data)):
        a,va = data[i1]
        for i2 in range(i1+1, len(data)):
            b,vb = data[i2]

            px,py = get_intersection((a,a+va), (b,b+vb))
            if not px:
                continue

            t1 = (px - a.x)/va.x
            t2 = (px - b.x)/vb.x

            if(t1 >= 0 and t2 >= 0):

                if(200000000000000 <= px <= 400000000000000 and 200000000000000 <= py <= 400000000000000):
                    ans1 = ans1 + 1

    solver = z3.Solver()

    z3x = z3.Int('x')
    z3y = z3.Int('y')
    z3z = z3.Int('z')
    z3vx = z3.Int('vx')
    z3vy = z3.Int('vy')
    z3vz = z3.Int('vz')

    idx = 0
    for p,v in data:
        t = z3.Int(f't{idx}')
        idx+=1
        solver.add(t >= 0)
        solver.add(z3x + z3vx * t == p.x + v.x * t)
        solver.add(z3y + z3vy * t == p.y + v.y * t)
        solver.add(z3z + z3vz * t == p.z + v.z * t)

    res = solver.check()
    assert res == z3.sat

    model = solver.model()
    x = model.eval(z3x).as_long()
    y = model.eval(z3y).as_long()
    z = model.eval(z3z).as_long()

    ans2 = x + y + z

    return ans1, ans2

if __name__ == '__main__':
    checkans(*main())
