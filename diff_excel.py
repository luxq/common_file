#!/usr/bin/python

#-*- coding:gbk -*-
import sys,os
import xlrd
import codecs

def row_to_str(row):
    strRow = u""
    for c in row:
        v = c.value
        #print c.value
        if isinstance(v,str) or isinstance(v,unicode):
            strRow += ("\t" + v)
        else:
            strRow += ("\t" + str(v))

    return strRow


def diff_row(row1,row2):
    n1 = len(row1)
    n2 = len(row2)
    nc = max(n1,n2)
    report = []

    for c in range(nc):
        c1 = None
        c2 = None
        if c < n1:
            c1 = row1[c]
        if c < n2:
            c2 = row2[c]

        s = u""
        if c1 == None and c2 != None:
            v = c2.value
            if isinstance(v,unicode):
                s = v
            else:
                s = str(v)
            report.append("\t\t-CELL["+str(c+1)+"]" + s + "\n")

        if c1 != None and c2 == None:
            v = c1.value
            if isinstance(v,unicode):
                s = v
            else:
                s = str(v)
            report.append("\t\t+CELL["+str(c+1)+"]" + s + "\n")
            
        if c1 != None and c2 != None:
            if c1.value != c2.value:
                s1 = u""
                s2 = u""
                v1 = c1.value
                v2 = c2.value
                if isinstance(v1,unicode):
                    s1 = v1
                else:
                    s1 = str(v1)
                if isinstance(v2,unicode):
                    s2 = v2
                else:
                    s2 = str(v2)
                report.append("\t\t#DIFF CELL["+str(c+1)+"]"+ "\n")
                report.append("\t\t#CELL-1:"+s1+ "\n")
                report.append("\t\t#CELL-2:"+s2+ "\n")
        
    return report


def diff_sheet(sh1,sh2):
    n1 = sh1.nrows
    n2 = sh2.nrows
    nr = max(n1,n2)
    report = []
    
    for r in range(nr):
        row1 = None
        row2 = None
        if r < n1:
            row1 = sh1.row(r)
        if r < n2:
            row2 = sh2.row(r)
            
        diff = 0; # 0:equal, 1: not equal, 2: row1 is more, 3: row1 is less
        if row1 == None and row2 != None:
            diff = 3
            report.append("\t-ROW[" + str(r+1) +"]:" + row_to_str(row2)+ "\n")
        if row1 != None and row2 == None:
            diff = 2
            report.append("\t+ROW[" + str(r+1) +"]" + row_to_str(row1)+ "\n")
        if row1 == None and row2 == None:
            diff = 0
        if row1 != None and row2 != None:
            report_row = diff_row(row1, row2)
            if len(report_row) == 0:
                diff = 0
            else:
                report.append("\t#DIFF ROW["+str(r+1)+"]"+ "\n")
                report.append("\t#ROW-1:" + row_to_str(row1)+ "\n")
                report.append("\t#ROW-2:" + row_to_str(row2)+ "\n")
                report.append(report_row)
                diff = 1
    return report
            
            


if __name__ == '__main__':
    if len(sys.argv) < 3:
        exit()
    
    excel_1 = sys.argv[1]
    excel_2 = sys.argv[2]
    
    wb_1 = xlrd.open_workbook(excel_1)
    wb_2 = xlrd.open_workbook(excel_2)
    
    sheets_1 = wb_1.sheet_names()
    sheets_2 = wb_2.sheet_names()
    output_name = "diff_" + excel_1 + "_" + excel_2 + ".txt"

    report = []
    for sheet in sheets_1:
        if sheet in sheets_2:
            print "diff sheet "+sheet + "....."
            report_sheet = diff_sheet(wb_1.sheet_by_name(sheet), wb_2.sheet_by_name(sheet))
            if len(report_sheet) > 0:
                report.append("####[Sheet "+sheet+"]"+ "\n")
                report.append(report_sheet)
        else:
            report.append("+[sheet]" + sheet+ "\n")
    for sheet in sheets_2:
        if sheet not in sheets_1:
            report.append("-[sheet]" + sheet+ "\n")

    if os.path.isfile(output_name):
        os.remove(output_name)

    for s in report:
        if isinstance(s,list):
            for ss in s:
                if isinstance(ss, list):
                    for sss in ss:
                        with codecs.open(output_name,"a", 'utf-8') as f:
                            f.write(sss)
                else:
                    with codecs.open(output_name,"a", 'utf-8') as f:
                        f.write(ss)
        else:
            with codecs.open(output_name,"a", 'utf-8') as f:
                f.write(s)

    print "diff finished.........."


