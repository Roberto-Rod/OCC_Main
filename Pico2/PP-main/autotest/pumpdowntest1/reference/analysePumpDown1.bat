rm xx*
logAnalyse.py -f %1 -u -l -e -p | grep -i state | uniq -c  > sp.out
csplit sp.out  "/SLEEP/+1"  \{*\}
sh cmprefPumpDown1
