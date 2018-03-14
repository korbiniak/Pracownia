for i in {1..100}
do
	echo $i
	python gen.py $i 10 2 > test.in
	# cat test.in
	./ob < test.in > test.out
	./optdis < test.in > wa.out
	diff -w test.out wa.out 
done 