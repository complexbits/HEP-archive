executable      = /home/hegarty/root/bin/root.exe
universe        = vanilla
log		= con_root-100204-1636.log
getenv          = True

arguments = -b -q varsigma_1.C
output = varsigma_1.log
error = varsigma_1.err
queue 


arguments = -b -q varsigma_2.C
output = varsigma_2.log
error = varsigma_2.err
queue 


arguments = -b -q varsigma_3.C
output = varsigma_3.log
error = varsigma_3.err
queue 


arguments = -b -q varsigma_4.C
output = varsigma_4.log
error = varsigma_4.err
queue 

