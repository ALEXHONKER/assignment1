import string
import sys

dic={}

class street (object):
	name=""
	setxy=[]
	segline=[]
	intersec=[]
	def setsxy(self,temp):
		self.setxy.append(temp)
	def setname(self,na):
		self.name=na
	def addintersec(self,xy):
		self.intersec.append(xy)


def add(strs):
	c1=strs.find("\"",0)
	c2=strs.find("\"",c1+1)
	if c1==-1 or c2==-1:
		print "Error: Wrong format of street name"
		return
	street_name=strs[c1+1:c2]
	strs=strs[c2+1:]
	strs=strs.strip()
	lis=strs.split()
	str1=street()
	print street_name+"   ddfdfd"
	str1.setname(street_name)

	for i in lis:
		lens=len(i)
		if i[0]!="(" or i[lens-1]!=")":
			print "Error:Wrong format of GPS coordiante: "+i 
			return
		w=i[1:lens-1]
		cor=w.split(",")

		if len(cor)!=2 :
			print "Error:Wrong format of GPS coordinate: "+i
			return
		if cor[0].isdigit():
			x1=string.atoi(cor[0])
		elif cor[0][0]=="-" and cor[0][1:].isdigit() :
			x1=-1*string.atoi(cor[0][1:])
		else :
			print "Error:Wrong format of GPS coordinate: "+i
			return 
		if cor[1].isdigit():
			y1=string.atoi(cor[1])
		elif cor[1][0]=="-" and cor[1][1:].isdigit() :
			y1=-1*string.atoi(cor[1][1:])
		else :
			print "Error:Wrong format of GPS coordinate: "+i
			return
		
		par=[x1,y1]
		#par.append(x1)
		#par.append(y1)
		str1.setsxy(par)
		
	dic[street_name]=str1

def delete(strs):
	c1=strs.find("\"",0)
	c2=strs.find("\"",c1+1)
	if c1==-1 or c2==-1:
		print "Error: Wrong format of street name"
		return
	street_name=strs[c1+1:c2]
	if not dic.has_key(street_name):
		print "Error: 'c' or 'r' specified for a street that does not exits."
		return
	else:
		del dic[street_name]
		add(strs)

def remove(strs):
	c1=strs.find("\"",0)
	c2=strs.find("\"",c1+1)
	if c1==-1 or c2==-1:
		print "Error: Wrong format of street name"
		return
	street_name=strs[c1+1:c2]
	if not dic.has_key(street_name):
		print "Error: 'c' or 'r' specified for a street that does not exits."
		return
	else:
		del dic[street_name]

def graph():
	str_name=dic.keys()
	for strs in str_name:
		coor=dic[strs].setxy
		for i in range(len(coor)):
			x1=coor[i][0]+0.0
			y1=coor[i][1]+0.0
			if i != (len(coor)-1):
				x2=coor[i+1][0]+0.0
				y2=coor[i+1][1]+0.0
				k1=(y2-y1)/(x2-x1)
				b1=y2-k1*x2
				str_name2 = dic.keys()
				str_name2=str_name2.remove(str)
				for strs2 in str_name2:
					coor2=dic[strs2].setxy
					for j in range(len(coor2)):
						x3=coor2[j][0]+0.0
						y3=coor2[j][1]+0.0
						if j != (len(coor2)-1):
							x4=coor2[j+1][0]+0.0
							y4=coor2[j+1][1]+0.0
							k2=(y4-y3)/(x4-x3)
							b2=y4-k2*x4
						if k1!=k2:
							maxx=x1
							minx=x2
							if x2>x1:
								maxx=x2
								minx=x1
							maxy=y1
							miny=y2
							if y2>y1:
								maxy=y2
								miny=y1
							xx=(b2-b1)/(k1-k2)
							yy=k1*xx+b1
							if xx>=minx and xx<=maxx and yy>=miny and yy<=maxy:
								new_street=dic[strs]
								new_street.addintersec([xx,yy])
								dic[strs]=new_street    # add the intersection node



while True:
	a=sys.stdin.readlines()
	if not a:
		break
	#a= "a \"ws\" (2,-1) (2,2) (5,5) (5,6) (3,8)"
	a=a.strip()
	first=a[0]
	if first=='a' and (a[1]==" " or a[1]=="\""):
		print "suc"
		add(a)
	elif first=='c' and (a[1]==" " or a[1]=="\""):
		delete(a)
	elif first=='r' and (a[1]==" " or a[1]=="\""):
		remove(a)
	elif first=='g':
		graph()
	print dic.has_key('ws')
	print dic['ws'].setxy

















