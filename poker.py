import sys
import random

#kolory: pik [P], trefl [T], kier [K], karo [Q]

blotki = [	(2, 'P'), (2, 'T'), (2, 'K'), (2, 'Q'), 
			(3, 'P'), (3, 'T'), (3, 'K'), (3, 'Q'), 
			(4, 'P'), (4, 'T'), (4, 'K'), (4, 'Q'), 
			(5, 'P'), (5, 'T'), (5, 'K'), (5, 'Q'), 
			(6, 'P'), (6, 'T'), (6, 'K'), (6, 'Q'), 
			(7, 'P'), (7, 'T'), (7, 'K'), (7, 'Q'), 
			(8, 'P'), (8, 'T'), (8, 'K'), (8, 'Q'), 
			(9, 'P'), (9, 'T'), (9, 'K'), (9, 'Q'), 
			(10, 'P'), (10, 'T'), (10, 'K'), (10, 'Q') ]
figury = [	(11, 'P'), (11, 'T'), (11, 'K'), (11, 'Q'), 
			(12, 'P'), (12, 'T'), (12, 'K'), (12, 'Q'), 
			(13, 'P'), (13, 'T'), (13, 'K'), (13, 'Q'), 
			(14, 'P'), (14, 'T'), (14, 'K'), (14, 'Q') 	]

def losujReke(osoba, karty):
	while len(osoba) < 5:
		karta = random.choice(karty)
		dodac = True
		for i in xrange(0, len(osoba)):
			if osoba[i] == karta:
				dodac = False
				break
		if dodac == True:
			osoba.append(karta)
	osoba.sort()

def jakiUklad(reka):
	#poker
	if (reka[0][1] == reka[1][1] and
		reka[1][1] == reka[2][1] and 
		reka[2][1] == reka[3][1] and
		reka[3][1] == reka[4][1] and
		reka[0][0] + 1 == reka[1][0] and 
		reka[1][0] + 1 == reka[2][0] and
		reka[2][0] + 1 == reka[3][0] and
		reka[3][0] + 1 == reka[4][0]):
		return 9
	#kareta
	if ((reka[0][0] == reka[1][0] and reka[1][0] == reka[2][0] and reka[2][0] == reka[3][0]) or
		(reka[1][0] == reka[2][0] and reka[2][0] == reka[3][0] and reka[3][0] == reka[4][0])):
		return 8
	#full
	if ((reka[0][0] == reka[1][0] and reka[1][0] == reka[2][0] and reka[3][0] == reka[4][0]) or
		(reka[0][0] == reka[1][0] and reka[2][0] == reka[3][0] and reka[3][0] == reka[4][0])):
		return 7
	#kolor
	if (reka[0][1] == reka[1][1] and
		reka[1][1] == reka[2][1] and 
		reka[2][1] == reka[3][1] and
		reka[3][1] == reka[4][1]):
		return 6
	#strit
	if (reka[0][0] + 1 == reka[1][0] and 
		reka[1][0] + 1 == reka[2][0] and
		reka[2][0] + 1 == reka[3][0] and
		reka[3][0] + 1 == reka[4][0]):
		return 5
	#trojka
	if ((reka[0][0] == reka[1][0] and reka[1][0] == reka[2][0]) or
		(reka[1][0] == reka[2][0] and reka[2][0] == reka[3][0]) or
		(reka[2][0] == reka[3][0] and reka[3][0] == reka[4][0])):
		return 4
	#dwie pary
	if ((reka[0][0] == reka[1][0] and reka[2][0] == reka[3][0]) or
		(reka[0][0] == reka[1][0] and reka[3][0] == reka[4][0]) or
		(reka[1][0] == reka[2][0] and reka[3][0] == reka[4][0])):
		return 3
	if (reka[0][0] == reka[1][0] or reka[1][0] == reka[2][0] or
		reka[2][0] == reka[3][0] or reka[3][0] == reka[4][0]):
		return 2
	return 1


def whoWins():
	rekaBlotkarza = []
	rekaFiguranta = []
	losujReke(rekaBlotkarza, blotki)
	losujReke(rekaFiguranta, figury)
	# print rekaFiguranta
	# print jakiUklad(rekaFiguranta)
	# print rekaBlotkarza
	# print jakiUklad(rekaBlotkarza)
	if jakiUklad(rekaFiguranta) >= jakiUklad(rekaBlotkarza):
		# print 'Figurant wygrywa'
		return 'F'	
	else:
		# print 'Blotkarz wygrywa'
		return 'B'

random.seed(sys.argv[1])
n = int(sys.argv[2])

figWins = 0
ratio = 0

for i in xrange(1, n + 1):
	if whoWins() == 'F':
		figWins += 1
	ratio = figWins / float(i)
	# print ratio
print ratio
