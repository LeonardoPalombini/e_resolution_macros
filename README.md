This directory contains two sets of macros for evaluating electron reco performances, using a "manual" cone algorithm.
Tracks come from the Si_Tracks_refitted collection of Pandora, hits from SimHits (also DigiHits can be used)

calib.cpp: macro to obtain E correction functions for different angular bins
resol.cpp: macro to obtain E,p resolutions and tracking/matching efficiency, vs E and Theta

include (folder): common includes >> data structure and branches
resinclude (folder): includes for resol.cpp
calinclude (folde): includes for calib.cpp
