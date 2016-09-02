import os
import pandas as pd


def myValues(f):
    myf = open(f,'r')
    lns = myf.readlines()
    myf.close()
    (st,ed)=(0,0)
    res=[]
    res.append(f[:-4])
    for i in range(len(lns)):
        if lns[i].find('ClassicGrid_grid_X') == 0:
            st = i
        if lns[i].find('total_score_X') == 0:
            ed = i
    for i in range(st,ed+1):
        ln = lns[i]
        wds = ln.split()
        res.append(float(wds[1]))
    return res

def getNames(f):
    myf = open(f,'r')
    lns = myf.readlines()
    myf.close()
    (st,ed)=(0,0)
    res=[]
    res.append('desciption')
    for i in range(len(lns)):
        if lns[i].find('ClassicGrid_grid_X') == 0:
            st = i
        if lns[i].find('total_score_X') == 0:
            ed = i
    for i in range(st,ed+1):
        ln = lns[i]
        wds = ln.split()
        res.append(str(wds[0]))
    return res

if __name__ = '__main__':
    fl=[f for f in os.listdir('.') if f.endswith('.pdb')]
    lab = getNames(fl[0])
    test=[]
    for f in fl:
        test.append(myValues(f))
    df = pd.DataFrame(test, columns = lab)
    df.to_csv('design_results.sc',index=False)
