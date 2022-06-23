echo off
echo ---------------------------------------------
echo Extract external pressure 

logAnalyse.py -f %1 -u -l | grep -i Extern | sort | uniq -c | grep -iv Time.*Diff

echo ---------------------------------------------
echo Extract IPD times 
logAnalyse.py -f %1 -u -l | grep -i IPD | sort | uniq -c | grep -iv Time.*Diff


echo ---------------------------------------------
echo Extract differential pressure when in therapy state 
logAnalyse.py -f %1 -u | grep -i therapy | gawk -F, '{ print $2 }' | sort | uniq -c

echo ---------------------------------------------
echo Extract Temperature 
logAnalyse.py -f %1 -u -l   | grep -i temper | sort   | uniq -c   | grep -iv Time.*Diff

echo ---------------------------------------------
echo Extract Duty Ratio 
logAnalyse.py -f %1 -u -l   | grep -i duty | sort   | uniq -c   | grep -iv Time.*Diff

echo ---------------------------------------------
echo Extract Unloaded Voltage 
logAnalyse.py -f %1 -u -l   | grep -i un.*voltage | sort   | uniq -c   | grep -iv Time.*Diff

echo ---------------------------------------------
echo Extract Loaded Voltage 
logAnalyse.py -f %1 -u -l   | grep -i voltage | grep -iv un  | sort   | uniq -c   | grep -iv Time.*Diff

