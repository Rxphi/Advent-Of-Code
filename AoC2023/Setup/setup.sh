cd ../
rm -r Day*
for day in {1..25}
do
	mkdir Day$day
	cp Setup/mainTemplate.c Day$day/main.c
	touch Day$day/input.txt
	touch Day$day/test.txt
done
