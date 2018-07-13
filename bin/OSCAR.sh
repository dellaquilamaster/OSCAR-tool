#For questions, talk to Daniele Dell'Aquila (dellaquila.daniele@gmail.com)

##################################################################
export ROOTCLINGORCINT='rootcint'
##################################################################

#determining OSCAR path from config/OSCAR.conf
while IFS= read -r line;do
    fields=($(printf "%s" "$line"|cut --output-delimiter=' ' -f1-))
    if [ ${fields[1]} ] && [ ${fields[1]} = "OSCAR_DIR" ] ; then
      OSCARPath=$(echo ${fields[2]} | sed 's/[\"]//g')
    fi
done < config/OSCAR.conf

#Set environmental variables for OSCAR
export OSCARSRC=${OSCARPath}
export OSCARLIB=${OSCARPath}/lib
export OSCARBIN=${OSCARPath}/bin

export LD_LIBRARY_PATH=$ROOTSYS/lib/root:$LD_LIBRARY_PATH:$OSCARLIB:./

export PATH=$OSCARBIN:$PATH

#Making scripts executable
chmod +x ${OSCARBIN}/OSCAR*