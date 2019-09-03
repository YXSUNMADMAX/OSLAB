touch output.txt
cd /bin
ls -l | tee /Users/madmaxkgb/Developer/OSLAB/OSLAB1/output.txt
cd /Users/madmaxkgb/Developer/OSLAB/OSLAB1/
sed -i "" '1d' output.txt
awk '{print $9,$3,$1}' output.txt | tee output.txt
sed -i "" 's/^/b&/g' output.txt

