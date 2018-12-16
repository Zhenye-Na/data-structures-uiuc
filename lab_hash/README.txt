$ ./test


===============================================================================
===============================================================================
===============================================================================
"A lot of the things that I say are true, but I don't actually mean them." ~ Alexey Stepanov
===============================================================================
===============================================================================
===============================================================================


===============================================================================
All tests passed (15 assertions in 11 test cases)



$ ./charcount lab_hash_data/sherlock_holmes.txt 10000 schash
Finding chars in lab_hash_data/sherlock_holmes.txt with frequency >= 10000 using SCHashTable...
54459   e
40038   t
35944   a
34570   o
30921   i
29449   h
29436   n
27805   s
25298   r
18981   d
17548   l
13495   u
12060   m
11432   w
10847   c


$ ./wordcount lab_hash_data/metamorphoses.txt 1000 lphash
Finding words in lab_hash_data/metamorphoses.txt with frequency >= 1000 using LPHashTable...
10473	the
5753	of
4739	and
3078	to
2246	a
1989	in
1706	was
1572	his
1548	that
1500	her
1456	with
1306	is
1241	he
1185	by


$ ./anagramtest lab_hash_data/words.txt retinas schash
Checking file lab_hash_data/words.txt for anagrams of retinas using SCHashTable...
anestri is an anagram of retinas
asterin is an anagram of retinas
eranist is an anagram of retinas
nastier is an anagram of retinas
ratines is an anagram of retinas
resiant is an anagram of retinas
restain is an anagram of retinas
retains is an anagram of retinas
retinas is an anagram of retinas
retsina is an anagram of retinas
sainter is an anagram of retinas
stainer is an anagram of retinas
starnie is an anagram of retinas
stearin is an anagram of retinas


$ ./lfparse lab_hash_data/log2.txt
Parsing logfile: lab_hash_data/log2.txt...
Number of unique URLs: 10
Printing unique URLs:
	/product/5/
	/product/0/
	/product/7/
	/product/1/
	/product/6/
	/product/8/
	/product/2/
	/product/3/
	/product/4/
	/product/9/
Running sample visited queries...
	chase visited /product/0/ on Tue Mar 27 20:15:05 2018
	chase visited /product/1/ on Tue Mar 27 21:12:07 2018
	chase visited /product/2/ on Tue Mar 27 18:46:05 2018
	chase visited /product/3/ on Sat Mar 24 19:57:35 2018
	chase visited /product/4/ on Mon Mar 26 21:05:44 2018
	chase visited /product/5/ on Tue Mar 27 20:12:16 2018
	chase visited /product/7/ on Mon Mar 26 20:06:51 2018
	chase visited /product/8/ on Sun Mar 25 19:27:13 2018
	chase visited /product/9/ on Mon Mar 26 19:29:58 2018
