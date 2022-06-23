rm xx*
logAnalyse.py -f %1 -u -l -e | grep -i state | uniq -c  > sp.out
csplit sp.out  "/SLEEP/+1"  \{*\}
mv xx00 xy00.bak
sh cmprefStateTest1
