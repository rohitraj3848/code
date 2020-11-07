from tkinter import *
from random import shuffle

a,b = 0,0
n = [l for l in range(16)]
shuffle(n)
mat = [[0 for l in range(4)] for l in range(4)]
k = 0
for i in range(4):
	for j in range(4):
		if n[k] == 0:
			a = i
			b = j
		mat[i][j] = n[k]
		k = k + 1


def isValidup(y_0):
	if y_0==0:
		return False
	else:
		return True


def isValidleft(x_0):
	if x_0 == 0:
		return False
	else:
		return True


def isValidright(x_0):
	if x_0 == 3:
		return False
	else:
		return True


def isValiddown(y_0):
	if y_0==3:
		return False
	else:
		return True


def down(x_0, y_0, matrix):
	print("up")
	if isValidup(y_0):
		temp = matrix[x_0][y_0]
		matrix[x_0][y_0] = matrix[x_0][y_0-1]
		matrix[x_0][y_0-1] = temp
		global b
		b=y_0-1
		getnewboard(matrix)


def up(x_0, y_0, matrix):
	print("down")
	if isValiddown(y_0):
		temp=matrix[x_0][y_0]
		matrix[x_0][y_0]=matrix[x_0][y_0+1]
		matrix[x_0][y_0+1]=temp
		global b
		b = y_0 + 1
		getnewboard(matrix)


def right(x_0, y_0, matrix):
	print("left")
	if isValidleft(x_0):
		temp=matrix[x_0][y_0]
		matrix[x_0][y_0]=matrix[x_0-1][y_0]
		matrix[x_0-1][y_0]=temp
		global a
		a = x_0-1
		getnewboard(matrix)


def left(x_0, y_0, matrix):
	print("right")
	if isValidright(x_0):
		temp = matrix[x_0][y_0]
		matrix[x_0][y_0] = matrix[x_0+1][y_0]
		matrix[x_0+1][y_0] = temp
		global a
		a = x_0 + 1
		getnewboard(matrix)


def getnewboard(matrix):
	for i in (0,100,200,300):
		for j in (0,100,200,300):
			w.create_rectangle(i, j, i+100, j+100, fill="red")
	for i in (0, 100, 200, 300):
		for j in (0, 100, 200, 300):
			if matrix[i//100][j//100] != 0:
				w.create_text((2*i+100)/2, (2*j+100)/2, text=matrix[i//100][j//100])


root = Tk()
w = Canvas(root, width=400, height=400)
w.pack()
getnewboard(mat)
button1 = Button(root, command=lambda: up(a, b, mat), text="UP")
button2 = Button(root, command=lambda: down(a, b, mat), text="DOWN")
button3 = Button(root, command=lambda: left(a, b, mat), text="LEFT")
button4 = Button(root, command=lambda: right(a, b, mat), text="RIGHT")
button1.pack(side=TOP)
button2.pack(side=BOTTOM)
button3.pack(side=LEFT)
button4.pack(side=RIGHT)
root.mainloop()
