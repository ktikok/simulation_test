ource init_lcg.sh does not work by script. you should do it manually

#run the bellow command
# nohup ./0_MyScript.sh > 0_nohup.out & tail -f 0_nohup.out


#for i in "e-" "pi+"
for i in "pi+"
# particle names(e-, pi+)
do
    run_beamOn="30"





    for j in 50
    #for j in 10 20 30 50 70 90 110
    # energy with the unit of GeV. I did alread for 20GeV
    do
        #x1=$((${j} - 10))
        
        x1=0
        # start point of graph
        #x2=$((${j} + 10))
        x2=$((${j} + 10))
        # values depend on particle.
        # it meanse starting and ending x value on graph.


        #if [ "$i" = "e-" ]
        #then
        #
        #fi 
        
        #------------------------------------------------------------#
        # events number = beamon*queue. so change "/run/beamOn 10" when you simulate difrerent events number.
        # usually queue = 100, so, you may change beamOn 10 or 30.
        #------------------------------------------------------------#
                
        gun_particle=$i
        #gun_particle="pi+"
        gun_energy="$j GeV"
        root_name="${j}GeV_${i:0:-1}"
        echo "starting submit for $gun_energy $gun_particle and the output will be $root_name.root"    
        echo ""
        
        # ctrl+shift+L >> select same words    


        
        echo "#This macro can not be executed standalone" > 0_SimulationMacFile.mac
        echo "/run/numberOfThreads 4" >> 0_SimulationMacFile.mac
        echo "/run/initialize" >> 0_SimulationMacFile.mac
        echo "/run/verbose 1" >> 0_SimulationMacFile.mac
        echo "/DRsim/generator/theta -0.0372899" >> 0_SimulationMacFile.mac
        echo "/DRsim/generator/phi 0.0174533" >> 0_SimulationMacFile.mac
        echo "/DRsim/generator/y0 -3.142" >> 0_SimulationMacFile.mac
        echo "/DRsim/generator/z0 -4.7135" >> 0_SimulationMacFile.mac
        echo "/DRsim/generator/randx 10." >> 0_SimulationMacFile.mac
        echo "/DRsim/generator/randy 10." >> 0_SimulationMacFile.mac
        echo "/gun/particle $i" >> 0_SimulationMacFile.mac
        echo "/gun/energy $j GeV" >> 0_SimulationMacFile.mac
        echo "/run/beamOn $run_beamOn" >> 0_SimulationMacFile.mac
        #cat 0_SimulationMacFile.mac

        echo "#! /bin/sh" > 0_SimulationShFile.sh
        echo "source /cvmfs/sft.cern.ch/lcg/views/LCG_97a_FCC_1/x86_64-centos7-gcc8-opt/setup.sh" >> 0_SimulationShFile.sh
        echo "export PYTHIA8_ROOT_DIR=/cvmfs/sft.cern.ch/lcg/views/LCG_97a_FCC_1/x86_64-centos7-gcc8-opt/" >> 0_SimulationShFile.sh
        echo "source /cvmfs/sft.cern.ch/lcg/releases/LCG_97a_FCC_1/hepmc3/3.2.2/x86_64-centos7-gcc8-opt/hepmc3-env.sh" >> 0_SimulationShFile.sh
        echo "source /cvmfs/sft.cern.ch/lcg/releases/LCG_97a_FCC_1/DD4hep/01-12-01/x86_64-centos7-gcc8-opt/bin/thisdd4hep.sh" >> 0_SimulationShFile.sh
        echo "export LD_LIBRARY_PATH=\$LD_LIBRARY_PATH:\$PWD/lib" >> 0_SimulationShFile.sh
        echo "./bin/DRsim 0_SimulationMacFile.mac \$1 ${i:0:-1}_${j}GeV_v0022_2000mm" >> 0_SimulationShFile.sh

        #cat 0_SimulationShFile.sh
        mkdir log
        condor_submit 0_SimulationSubFile.sub
        #break
        flag=`condor_q -all | grep "tikim ID"`
        #flag1=$(condor_q -all | grep "tikim ID")
        #same command

        echo $flag
        while [ "${flag:1:2}" == "ik" ]
        do 
            sleep 1m
            flag=`condor_q -all | grep "tikim ID"`        

        done
        #echo $((${j} - 10))
        #break
        echo "Simulation is done"
        echo "preparing analysis"
        hadd "$root_name.root" ./*.root
        #./bin/analysis "$root_name" $((${j} - 10)) $((${j} + 10))
        ./bin/analysis "$root_name" $((${x1})) $((${x2}))
        mkdir ${root_name}
        mv log "./${root_name}/"
        cp 0_Simulation* "./${root_name}/"
        mkdir root
        mv "$root_name.root" "./${root_name}/"
        mv *.root ./root/
        mv root "./${root_name}/"
        mv *.png "./${root_name}/"
        echo "analysis and arranging directory is done for $i ${j}GeV"
    done
    
done

