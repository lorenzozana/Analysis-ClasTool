export ROOTSYS=/net/data/pumpkin1/lzana/root
export PATH=$ROOTSYS/bin:$PATH
export LD_LIBRARY_PATH=$ROOTSYS/lib
export MYNE_OS=Linux64RHEL5
export CLASTOOL=/net/home/lzana/packages/ClasTool
export LD_LIBRARY_PATH=$CLASTOOL/slib/$MYNE_OS/:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/net/home/lzana/PRODUCTION/lib/$MYNE_OS/:$LD_LIBRARY_PATH
echo "CLASTOOL=" $CLASTOOL
echo "ROOTSYS=" $ROOTSYS
echo "LD_LIBRARY_PATH=" $LD_LIBRARY_PATH
nice -n 19 root -b -q $1