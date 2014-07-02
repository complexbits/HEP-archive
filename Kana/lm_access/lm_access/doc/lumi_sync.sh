echo ' ' >> /grid/fzk.de/home/nunne/luminosity/lumi_sync.log
echo Luminosity Syncronization started: `date` >> /grid/fzk.de/home/nunne/luminosity/lumi_sync.log
rsync -rLptgoD --delete -e '/grid/fzk.de/d0/software/ups/missing_binaries/ssh -l nunne' begel-clued0.fnal.gov:~begel/stage2a /grid/fzk.de/home/nunne/scratch/luminosity >> /grid/fzk.de/home/nunne/luminosity/lumi_sync.log
echo rsync finished: `date` >> /grid/fzk.de/home/nunne/luminosity/lumi_sync.log
