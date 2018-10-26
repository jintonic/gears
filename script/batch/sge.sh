#!/bin/sh
# submit batch jobs to cluster using qsub

# http://stackoverflow.com/questions/10496758/unexpected-end-of-file-and-error-importing-function-definition-error-running
unset module

# location of gears
GEARSYS=$HOME/github/gears
exe=$GEARSYS/gears.exe

echo "parse arguments..."
njob=100 # number of jobs
nevt=1000 # number of events in each run
if [ $# -lt 1 ]; then echo "mac needed"; exit; fi
if [ ${1: -4} != ".mac" ]; then echo "mac needed"; exit; fi
if [ $# -gt 1 ]; then 
  if [[ "$2" =~ ^[0-9]+$ ]]; then njob=$2; fi
  if [ $# -gt 2 ]; then 
    if [[ "$3" =~ ^[0-9]+$ ]]; then nevt=$3; fi
  fi
fi

echo "create directory to hold data"
d=`date +%s`
mkdir -p $d

echo "submit $njob jobs, each with $nevt events..."
job=0
while [ $job -lt $njob ]; do
  sed -r "/^\/random/ s/[0-9]+/$RANDOM/" $1 >> $d/$job.mac
  sed -i "/^\/random/ s/[0-9][0-9]*[ ]*$/$RANDOM/" $d/$job.mac
  sed -i "/^\/output/ s| .*$| $d/${job}.root|" $d/$job.mac
  sed -i "/^\/geometry/ s| geom| $GEARSYS/geom|" $d/$job.mac
  sed -i "/^\/control/ s| macro| $GEARSYS/macro|" $d/$job.mac
  sed -i "/beamOn/ s/[0-9][0-9]*/$nevt/" $d/$job.mac
  qsub -N j${d: -2}.$job -V -cwd -o $d/$job.log -e $d/$job.log -b y $exe $d/$job.mac
  job=$((job+1))
done

while true; do
  qstat
  njobs=`qstat | egrep " j${d: -2}.[0-9]+" | wc -l`
  if [ $njobs -eq 0 ]; then break; fi
  sleep 3
done
