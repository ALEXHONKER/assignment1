import string
import sys
import math
global count
dic={}

nodes={}
edges=[]
class street:
	def __init__(self):
		self.name=""
		self.setxy=[]
		self.segline=[]
		self.intersec=[]
		self.no={}
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
	str1= street()
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
				newstr=dic[strs]
				newstr.no={}
				dic[strs]=newstr
				x2=coor[i+1][0]+0.0
				y2=coor[i+1][1]+0.0
				print "x"
				print x2
				print x1
				print "y"
				print y2
				print y1
				print "dic:"
				print dic.keys()
				if (x2-x1)==0:
					str_name2 = dic.keys()
					str_name2.remove(strs)
					for strs2 in str_name2:
						coor2=dic[strs2].setxy
						for j in range(len(coor2)):
							x3=coor2[j][0]
							y3=coor2[j][1]
							if j != (len(coor2)-1):
								x4=coor2[j+1][0]+0.0
								y4=coor2[j+1][1]+0.0
								if(x4-x3)!=0:
									k2=(y4-y3)/(x4-x3)
									b2=y4-k2*x4
									maxy=y1
									miny=y2
									if y2>y1:
										maxy=y2
										miny=y1
									xx=x2
									yy=k2*xx+b2
									if  yy>=miny and yy<=maxy:
										new_street=dic[strs]
										new_street.addintersec([xx,yy])	

										nidx1y1=str(x1)+'_'+str(y1)
										if not nodes.has_key(nidx1y1):
											pairx1y1=[[x1,y1],count]
											count=count+1
											nodes[nidx1y1]=pairx1y1
											new_street.no[nidx1y1]=pairx1y1
										else:
											if not new_street.no.has_key(nidx1y1):
												pairx1y1=nodes[nidx1y1]
												new_street.no[nidx1y1]=pairx1y1


										nidx2y2=str(x2)+'_'+str(y2)
										if not nodes.has_key(nidx2y2):
											pairx2y2=[[x2,y2],count]
											count=count+1
											nodes[nidx2y2]=pairx2y2
											new_street.no[nidx2y2]=pairx2y2
										else:
											if not new_street.no.has_key(nidx2y2):
												pairx2y2=nodes[nidx2y2]
												new_street.no[nidx2y2]=pairx2y2

										nid=str(xx)+'_'+str(yy)										
										if not nodes.has_key(nid):
											pair=[[xx,yy],count]
											count=count+1
											nodes[nid]=pair
											new_street.no[nid]=pair
										else:
											if not new_street.no.has_key(nid):
												pair2=nodes[nid]
												new_street.no[nid]=pair2


										dic[strs]=new_street    # add the intersection node

					my=y1
					ny=y2
					nidx1y1=str(x1)+'_'+str(y1)
					nidx2y2=str(x2)+'_'+str(y2)
					idmin=nidx2y2
					idmax=nidx1y1
					if y2>y1:
						my=y2
						ny=y1
						idmin=nidx1y1
						idmax=nidx2y2
					list_node=dic[strs].no.keys()
					if not list_node==[]:
						list_node.remove(nidx1y1)
						list_node.remove(nidx2y2)
						if not list_node==[]:
							list_node.append(idmax)	
							mindis=9999999.0
							minpair=[]
							minid2=idmin
							while list_node!=[]:
								for ns in list_node:
									pair3=dic[strs].no[ns]
									dis=pair3[0][1]-ny
									if dis<mindis:
										mindis=dis
										minpair=pair3
										minid2=ns
								edges.append([dic[strs].no[idmin][1],minpair[1]])
								idmin=minid2
								ny=minpair[0][1]
								list_node.remove(minid2)



					

				else:
					k1=(y2-y1)/(x2-x1)
					b1=y2-k1*x2
					str_name2 = dic.keys()
					str_name2.remove(strs)
					for strs2 in str_name2:
						coor2=dic[strs2].setxy
						for j in range(len(coor2)):
							x3=coor2[j][0]+0.0
							y3=coor2[j][1]+0.0
							if j != (len(coor2)-1):
								x4=coor2[j+1][0]+0.0
								y4=coor2[j+1][1]+0.0
								if (x4-x3)==0:
									maxy=y3
									miny=y4
									if y4>y3:
										maxy=y4
										miny=y3
									xx=x3
									yy=k1*xx+b1
									if  yy>=miny and yy<=maxy:
										new_street=dic[strs]
										new_street.addintersec([xx,yy])	

										nidx1y1=str(x1)+'_'+str(y1)
										if not nodes.has_key(nidx1y1):
											pairx1y1=[[x1,y1],count]
											count=count+1
											nodes[nidx1y1]=pairx1y1
											new_street.no[nidx1y1]=pairx1y1
										else:
											if not new_street.no.has_key(nidx1y1):
												pairx1y1=nodes[nidx1y1]
												new_street.no[nidx1y1]=pairx1y1


										nidx2y2=str(x2)+'_'+str(y2)
										if not nodes.has_key(nidx2y2):
											pairx2y2=[[x2,y2],count]
											count=count+1
											nodes[nidx2y2]=pairx2y2
											new_street.no[nidx2y2]=pairx2y2
										else:
											if not new_street.no.has_key(nidx2y2):
												pairx2y2=nodes[nidx2y2]
												new_street.no[nidx2y2]=pairx2y2

										nid=str(xx)+'_'+str(yy)										
										if not nodes.has_key(nid):
											pair=[[xx,yy],count]
											count=count+1
											nodes[nid]=pair
											new_street.no[nid]=pair
										else:
											if not new_street.no.has_key(nid):
												pair2=nodes[nid]
												new_street.no[nid]=pair2


										dic[strs]=new_street    # add the intersection node

								else:
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

											nidx1y1=str(x1)+'_'+str(y1)
											if not nodes.has_key(nidx1y1):
												pairx1y1=[[x1,y1],count]
												count=count+1
												nodes[nidx1y1]=pairx1y1
												new_street.no[nidx1y1]=pairx1y1
											else:
												if not new_street.no.has_key(nidx1y1):
													pairx1y1=nodes[nidx1y1]
													new_street.no[nidx1y1]=pairx1y1


											nidx2y2=str(x2)+'_'+str(y2)
											if not nodes.has_key(nidx2y2):
												pairx2y2=[[x2,y2],count]
												count=count+1
												nodes[nidx2y2]=pairx2y2
												new_street.no[nidx2y2]=pairx2y2
											else:
												if not new_street.no.has_key(nidx2y2):
													pairx2y2=nodes[nidx2y2]
													new_street.no[nidx2y2]=pairx2y2

											nid=str(xx)+'_'+str(yy)										
											if not nodes.has_key(nid):
												pair=[[xx,yy],count]
												count=count+1
												nodes[nid]=pair
												new_street.no[nid]=pair
											else:
												if not new_street.no.has_key(nid):
													pair2=nodes[nid]
													new_street.no[nid]=pair2


											dic[strs]=new_street    # add the intersection node
					mx1=x1
					my1=y1
					nidx1y1=str(x1)+'_'+str(y1)
					nidx2y2=str(x2)+'_'+str(y2)
					idmin=nidx1y1
					idmax=nidx2y2
					list_node=dic[strs].no.keys()
					if not list_node==[]:
						list_node.remove(nidx1y1)
						list_node.remove(nidx2y2)
						if not list_node==[]:
							list_node.append(idmax)	
							mindis=9999999.0
							minpair=[]
							minid2=idmin
							while list_node!=[]:
								for ns in list_node:
									pair3=dic[strs].no[ns]
									dis=math.sqrt((pair3[0][1]-my1)**2+(pair3[0][0]-mx1)**2)
									if dis<mindis:
										mindis=dis
										minpair=pair3
										minid2=ns
								edges.append([dic[strs].no[idmin][1],minpair[1]])
								idmin=minid2
								ny=minpair[0][1]
								list_node.remove(minid2)

			

count=0
while True:
	stdin=sys.stdin.readlines()
	if not stdin:
		break
	#a= "a \"ws\" (2,-1) (2,2) (5,5) (5,6) (3,8)"
	for i in range(len(stdin)):
		a=stdin[i]
		a=a.strip()
		first=a[0]
		if first=='a' and (a[1]==" " or a[1]=="\""):
			add(a)
		elif first=='c' and (a[1]==" " or a[1]=="\""):
			delete(a)
		elif first=='r' and (a[1]==" " or a[1]=="\""):
			remove(a)
		elif first=='g':
			graph()
			str_name=dic.keys()
		str_name=dic.keys()
		print str_name
		for strs in str_name:
			print strs+"    23333"
			print dic[strs].setxy
			print len(dic)
	for strs in str_name:
		print strs+"    23333"
		print dic[strs].intersec

	

















