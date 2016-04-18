
for i in $(echo "select distinct runno from GoldenRuns where LTarg like 'D2' and STarg like 'Fe-thick' and BeamE like '5014.830078' and quality>6" |  mysql -h clasdb.jlab.org -u clasuser eg2_offline | grep 4)
  do
  limit=`echo " select distinct runno,runfiles from GoldenRuns where LTarg like 'D2' and STarg like 'Fe-thick' and BeamE like '5014.830078' and quality>6 " |  mysql -h clasdb.jlab.org -u clasuser eg2_offline | grep $i | awk '{printf($2)}' `
  a="0"
  while [ "$a" -lt $limit ]
    do
    if [ "$a" -lt "10" ]
	then
	b=`echo "0"$a`
    else
	b=`echo $a`
    fi
    echo "{" > run_part_${i}_${b}.C
    echo "gROOT->LoadMacro(\"FilterAll.C\");"  >> run_part_${i}_${b}.C
    echo "Filter(\"/net/home/lzana/Eg2/Data/New_Cooking/clas_${i}_${b}.pass2.root\",\"/net/data/pumpkin1/lzana/Fe/5GeV/elec_${i}_${b}.root\");" >> run_part_${i}_${b}.C
    echo "}"  >> run_part_${i}_${b}.C
    let "a+=1"
  done
done


  



