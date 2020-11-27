@echo off
echo Please close the keil project before proceeding...
pause
del TN2115s1.h
d:\Keil_v5\UV4\SVDConv.exe TN2115s1.svd --generate=sfr --generate=header --fields=enum --fields=macro --fields=struct
pause