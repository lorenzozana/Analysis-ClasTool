#Analysis
 
Part_ident_clas2 is based on TClasTool and have some "utilities" for shortening the analysys later.

Acceptance: It is defined the clas that is based on the one created in Part_ident_clas2 . This one has the particle id.

The way is used is in Run.
see rootlogon for loaded library
see in order:
create_run_part_data.sh
submit_part_job.sh (xjobs is a program similar to xargs... but I preferred it. Permits to use multicore easily)
run_script_5.20.sh 
run_part_41332_11.C
FilterAll.C
rootlogon.C

I divided my analysys like this because Lamiaa was trowing away some single BOS (root) file , and was easier then for me clean the output with a filter in the end (and see the effect of the cleaning, in case). 
