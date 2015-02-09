#!/bin/sh

#
# Script to download GDML schemas from standard URL.
#

# The first argument of the script is an optional target directory which must already exist.
dir=$PWD
if [ -n "$1" ]; then
  dir=$1
  if [[ ! -d "$dir" ]]; then
    echo "ERROR: Directory $dir does not exist."
    exit 1
  fi 
fi

# Use wget to download the schemas to the local dir.
(
cd $dir
echo "gdml.xsd
gdml_core.xsd
gdml_define.xsd
gdml_extensions.xsd
gdml_materials.xsd 
gdml_parameterised.xsd
gdml_replicas.xsd 	
gdml_solids.xsd" > gdmlSchemaFiles.txt
wget -i gdmlSchemaFiles.txt -B 'http://service-spi.web.cern.ch/service-spi/app/releases/GDML/schema/'
rm gdmlSchemaFiles.txt
)
