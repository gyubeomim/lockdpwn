#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
     pygame ==> Memory Puzzle 같은그림 맞추기 게임 코드
'''
import pygame, sys, random
from pygame.locals import *

# 환경설정
FPS = 30
WINDOWWIDTH = 1200
WINDOWHEIGHT = 900
REVEALSPEED = 16
BOXSIZE = 80
GAPSIZE = 20
BOARDWIDTH = 10
BOARDHEIGHT = 7

assert (BOARDWIDTH * BOARDHEIGHT) % 2 == 0, 'Board needs to have an evenbynber of boxes for pairs of matches'

XMARGIN = int((WINDOWWIDTH - (BOARDWIDTH * (BOXSIZE + GAPSIZE)))/2)
YMARGIN = int((WINDOWHEIGHT - (BOARDHEIGHT * (BOXSIZE + GAPSIZE)))/2)

# 색깔 설정
#				 R		G		 B
GRAY = (100, 100 ,100)
NAVYBLUE = (60, 60, 100)
WHITE = (255, 255, 255)
RED = (255, 0 ,0)
GREEN = (0,255,0)
BLUE = (0,0,255)
YELLOW = (255,255,0)
ORANGE = (255,128,0)
PURPLE = (255,0,255)
CYAN = (0,255,255)

BGCOLOR = NAVYBLUE
LIGHTBGCOLOR = GRAY
BOXCOLOR = WHITE
HIGHLIGHTCOLOR = BLUE

DONUT = 'donut'
SQUARE = 'square'
DIAMOND = 'diamond'
LINES = 'lines'
OVAL = 'oval'

ALLCOLORS = (RED,GREEN,BLUE,YELLOW,ORANGE,PURPLE,CYAN)
ALLSHAPES = (DONUT,SQUARE,DIAMOND,LINES,OVAL)

assert len(ALLCOLORS) * len(ALLSHAPES) * 2 >= BOARDWIDTH * BOARDHEIGHT,"Board is too big for the number of shapes/color defined"

def main():
    global FPSCLOCK, DISPLAYSURF
    pygame.init()

    FPSCLOCK = pygame.time.Clock()
    DISPLAYSURF = pygame.display.set_mode((WINDOWWIDTH,WINDOWHEIGHT))
    mousex = 0
    mousey = 0

    pygame.display.set_caption('Memory Game')
    mainBoard = getRandomizedBoard()
    revealedBoxes = generateRevealedBoxesData(False)
    firstSelection = None
    DISPLAYSURF.fill(BGCOLOR)
    startGameAnimation(mainBoard)

    while True:
        mouseClicked = False
        DISPLAYSURF.fill(BGCOLOR)
        drawBoard(mainBoard, revealedBoxes)

        for event in pygame.event.get():
                        if event.type == QUIT or (event.type == KEYUP and event.key == K_ESCAPE):
                                        pygame.quit()
                                        sys.exit()

                        elif event.type == MOUSEMOTION:
                                        mousex,mousey = event.pos

                        elif event.type == MOUSEBUTTONUP:
                                        mousex,mousey = event.pos
                                        mouseClicked = True

        boxx, boxy = getBoxAtPixel(mousex, mousey)
        if boxx != None and boxy != None:
                        if not revealedBoxes[boxx][boxy]:
                                        drawHighlightBox(boxx,boxy)

                        if not revealedBoxes[boxx][boxy] and mouseClicked:
                                        revealBoxesAnimation(mainBoard, [(boxx,boxy)])
                                        revealedBoxes[boxx][boxy] = True

                                        # 첫번째 클릭인 경우
                                        if firstSelection == None:
                                                        firstSelection = (boxx,boxy)
                                        # 두번째 클릭인 경우
                                        else:
                                                        icon1shape, icon1color = getShapeAndColor(mainBoard, firstSelection[0], firstSelection[1])
                                                        icon2shape, icon2color = getShapeAndColor(mainBoard, boxx,boxy)

                                                        if icon1shape != icon2shape or icon1color != icon2color:
                                                                        pygame.time.wait(1000)
                                                                        coverBoxesAnimation(mainBoard, [(firstSelection[0], firstSelection[1], (boxx,boxy))])
                                                                        revealedBoxes[firstSelection[0]][firstSelection[1]] = False
                                                                        revealedBoxes[boxx][boxy] = False
                                                        # 게임을 클리어 한 경우
                                                        elif hasWon(revealedBoxes):
                                                                        gameWonAnimation(mainBoard)
                                                                        pygame.time.wait(2000)
                                                                        mainBoard = getRandomizedBoard()
                                                                        revealedBoxes = generateRevealedBoxesData(False)
                                                                        drawBoard(mainBoard, revealedBoxes)
                                                                        pygame.display.update()
                                                                        pygame.time.wait(1000)
                                                                        startGameAnimation(mainBoard)
                                                        firstSelection = None

                        pygame.display.update()
                        FPSCLOCK.tick(FPS)


def generateRevealedBoxesData(val):
		revealedBoxes	 = []
		for i in range(BOARDWIDTH):
				revealedBoxes.append([val] * BOARDHEIGHT)
		return revealedBoxes

# 랜덤으로 판만드는 코드
def getRandomizedBoard():
		icons = []
		for color in ALLCOLORS:
				for shape in ALLSHAPES:
						icons.append((shape, color))

		random.shuffle(icons)
		numIconsUsed = int(BOARDWIDTH * BOARDHEIGHT /2)
		icons = icons[:numIconsUsed] * 2
		random.shuffle(icons)

		board =[]
		for x in range(BOARDWIDTH):
				column = []
				for y in range(BOARDHEIGHT):
						column.append(icons[0])
						del icons[0]
				board.append(column)
		return board

# 2차원 리스트를 만든다. 아이콘을 a x b 리스트로 만드는 코드
def splitIntoGroupOf(groupSize, theList):
		result = []

		for i in range(0, len(theList), groupSize):
				result.append(theList[i:i + groupSize])
		return result

# 게임판 좌표계 코드를 반환하는 코드
def leftTopCoordsOfBox(boxx,boxy):
		left = boxx * (BOXSIZE + GAPSIZE) + XMARGIN
		top = boxy * (BOXSIZE + GAPSIZE) + YMARGIN
		return (left,top)

# 클릭한 박스의 위치를 반환하는 코드
def getBoxAtPixel(x,y):
		for boxx in range(BOARDWIDTH):
				for boxy in range(BOARDHEIGHT):
						left, top = leftTopCoordsOfBox(boxx,boxy)
						boxRect = pygame.Rect(left,top,BOXSIZE,BOXSIZE)
						if boxRect.collidepoint(x,y):
								return (boxx,boxy)
		return (None,None)

# 아이콘 그려주는 코드
def drawIcon(shape, color, boxx,boxy):
		quarter = int(BOXSIZE * 0.25)
		half = int(BOXSIZE * 0.5)

		left,top = leftTopCoordsOfBox(boxx,boxy)

		if shape == DONUT:
				pygame.draw.circle(DISPLAYSURF, color, (left + half, top + half), half -5)
				pygame.draw.circle(DISPLAYSURF, BGCOLOR, (left + half, top + half), quarter -5)

		elif shape == SQUARE:
				pygame.draw.rect(DISPLAYSURF, color, (left + quarter, top + quarter, BOXSIZE-half, BOXSIZE-half))

		elif shape == DIAMOND:
				pygame.draw.polygon(DISPLAYSURF, color, ((left + half, top),(left + BOXSIZE -1 , top+ half),(left + half, top+BOXSIZE -1),(left,top + half)))

		elif shape == LINES:
				for i in range(0,BOXSIZE, 4):
						pygame.draw.line(DISPLAYSURF, color,(left,top+i), (left+i, top))
						pygame.draw.line(DISPLAYSURF, color, (left+i,top+BOXSIZE-1),(left + BOXSIZE-1,top+i))

		elif shape == OVAL:
				pygame.draw.ellipse(DISPLAYSURF,color,(left, top + quarter, BOXSIZE,half))


def getShapeAndColor(board,boxx,boxy):
		return board[boxx][boxy][0], board[boxx][boxy][1]


def drawBoxCovers(board, boxes, coverage):
		for box in boxes:
				left, top = leftTopCoordsOfBox(box[0],box[1])
				pygame.draw.rect(DISPLAYSURF,BGCOLOR, (left,top,BOXSIZE,BOXSIZE))
				shape, color = getShapeAndColor(board,box[0],box[1])
				drawIcon(shape, color, box[0], box[1])

				if coverage > 0:
						pygame.draw.rect(DISPLAYSURF,BOXCOLOR, (left,top,coverage,BOXSIZE))

		pygame.display.update()
		FPSCLOCK.tick(FPS)

# 그림을 보여주는 애니메이션 코드
def revealBoxesAnimation(board, boxesToReveal):
		for coverage in range(BOXSIZE,(-REVEALSPEED) - 1, -REVEALSPEED):
				drawBoxCovers(board, boxesToReveal, coverage)

# 그림을 가리는 애니메이션 코드
def coverBoxesAnimation(board, boxesToCover):
		for coverage in range(0,BOXSIZE + REVEALSPEED, REVEALSPEED):
				drawBoxCovers(board,boxesToCover, coverage)


def drawBoard(board, revealed):
		for boxx in range(BOARDWIDTH):
				for boxy in range(BOARDHEIGHT):
						left, top = leftTopCoordsOfBox(boxx,boxy)
						if not revealed[boxx][boxy]:
								pygame.draw.rect(DISPLAYSURF, BOXCOLOR, (left, top, BOXSIZE,BOXSIZE))
						else:
								shape, color = getShapeAndColor(board,boxx,boxy)
								drawIcon(shape, color, boxx,boxy)

# 마우스 올리면 하이라이팅해주는 코드
def drawHighlightBox(boxx,boxy):
		left, top = leftTopCoordsOfBox(boxx, boxy)
		pygame.draw.rect(DISPLAYSURF,HIGHLIGHTCOLOR, (left -5, top -5, BOXSIZE+10, BOXSIZE+10),4)

# 게임 시작 애니메이션 코드
def startGameAnimation(board):
		coveredBoxes = generateRevealedBoxesData(False)
		boxes = []
		for x in range(BOARDWIDTH):
				for y in range(BOARDHEIGHT):
						boxes.append((x,y))

		random.shuffle(boxes)
		boxGroups = splitIntoGroupOf(8,boxes)

		drawBoard(board, coveredBoxes)
		for boxGroup in boxGroups:
				revealBoxesAnimation(board,boxGroup)
				coverBoxesAnimation(board,boxGroup)

# 게임을 클리어하면 생기는 애니메이션 코드
def gameWonAnimation(board):
		coveredBoxes = generateRevealedBoxesData(True)
		color1 = LIGHTBGCOLOR
		color2 = BGCOLOR

		for i in range(13):
				color1, color2 = color2, color1
				DISPLAYSURF.fill(color1)
				drawBoard(board,coveredBoxes)
				pygame.display.update()
				pygame.time.wait(300)

# 게임을 클리어했는지 검사하는 코드
def hasWon(revealedBoxes):
		for i in revealedBoxes:
				if False in i:
						return False
		return True


if __name__ == '__main__':
		main()
