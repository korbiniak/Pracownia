slownik = set([])
file = open('slownik.txt', 'r')
s = file.read().splitlines()
for line in s:
	slownik.add(line)
# print(slownik)

def spacjuj(tekst):
	slowa = []
	dp = []
	prev = []
	dl = len(tekst)
	for i in range(0, dl):
		for j in range(1, min(50, dl - i + 1)):
			if tekst[i:i+j] in slownik:
				slowa.append([i+j - 1, i])
	slowa = sorted(slowa)
	for i in range(0, dl + 1):
		dp.append(-1)
		prev.append(-1)
	dp[0] = 0
	# if "najwymowniejsza" in slownik:
		# print("no jest")
	# print(slowa)
	for slowo in slowa:
		dlugosc = slowo[0] - slowo[1] + 1
		if not dp[slowo[1]] == -1:
			if (dlugosc**2 + dp[slowo[1]] > dp[slowo[0] + 1]):
				dp[slowo[0] + 1] = dlugosc**2 + dp[slowo[1]]
				prev[slowo[0] + 1] = slowo[1]
	index = prev[dl]
	spacje = [1000000000]
	while index != 0:
		spacje.append(index)
		index = prev[index]
	spacje = list(reversed(spacje))
	# print(spacje)
	ans = ""
	index = 0
	for i in range(0, dl):
		if(i == spacje[index]):
			ans += " "
			index += 1
		ans += tekst[i]
	print(ans)

file = open('tadek.txt', 'r')
tadek = file.read().splitlines()
# print(tadek)

for lane in tadek:
	spacjuj(lane)
