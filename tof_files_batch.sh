# Prepare JDL file
JDL_FILE="ToF.jdl" #Name of produced .jdl file
EXECUTABLE="/home/t2k/aspeers/ToF_Systematics/exec_tof_files_batch.sh"
#DATA_DIRECTORY="/data/aspeers/4pi_Selection/mcp/P6AA/P6AA_FHC_flattrees"
DATA_DIRECTORY="/data/aspeers/ToF_Systematics/flattrees/P7_V13_run4_air_rdp"
OUTFILE_DIR="/data/aspeers/ToF_Systematics/P7_V13_FHC_run4air_Data_default_settings"

# Write JDL file header
#notification=Never #Lots of jobs => lots of emails. Keep it like this for less spam
#getenv = True #Uses currrent environmental variables. Probably important if I've got lots of things set up.
#concurrency_limits = aspeers:10 #How much computeryness to dedicate to each task, out of a total limit of 1000. 10=>100 jobs at once.
#requirements = OPSYSMAJORVER == 7 #Sets proper verison of something. I think version 6 is depreciated anyway
cat > ${JDL_FILE} <<EOF

notify_user = a.speers@lancaster.ac.uk
notification = Never
getenv = True
executable = ${EXECUTABLE}
output = /home/t2k/aspeers/condor_err/std-\$(CLUSTER).\$(Process).out
error = /home/t2k/aspeers/condor_err/std-\$(CLUSTER).\$(Process).err
log = /home/t2k/aspeers/condor_err/std-\$(CLUSTER).\$(Process).log
concurrency_limits = aspeers:10
requirements = OPSYSMAJORVER == 7

EOF

for INFILE in ${DATA_DIRECTORY}/*.root; do #For loop to create jobs for each file in the directory using wildcard

    OUTFILE="$(basename $INFILE _flattree.root)" #Chops _flattree.root off the end of the name of the infile
    OUTFILE="${OUTFILE_DIR}/${OUTFILE}_4pi.root" #Adds _splines.root to the end of the outfile and gives it directions to the outdirectory
    ARGUMENTS=" ${INFILE} ${OUTFILE}" #Sets up arguments for the executable
	
    cat >> ${JDL_FILE} <<EOF
Arguments = ${ARGUMENTS}
Queue

EOF
done;

condor_submit ${JDL_FILE}
