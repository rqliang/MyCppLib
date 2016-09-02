import os
import pandas as pd
import argparse

def myValues(f):
    myf = open(f,'r')
    lns = myf.readlines()
    myf.close()
    (st,ed)=(0,0)
    res=[]
    res.append("2_"+ os.path.basename(f)[:-4])
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

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='get scores from PDB file from Rosetta')
    parser.add_argument('-d', action='store', help='dir to be walked', required=True)
    parser.add_argument('-o', action='store', help='output file name', required=True)
    args = parser.parse_args()
    abspath = os.path.abspath(args.d)
    outf = os.path.abspath(args.o)
    
    fl=[f for f in os.listdir(abspath) if f.endswith('.pdb')]
    myp=[]
    for f in fl:
        myp.append(os.path.join(abspath,f))
        
    lab = getNames(myp[0])
    test=[]
    for f in myp:
        test.append(myValues(f))
    df = pd.DataFrame(test, columns = lab)
    df.to_csv(outf, index=False, sep='\t' )
