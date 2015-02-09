#!/bin/sh

#
# Script to download LCDD schemas from standard URL.
#

# The first argument of the script is an optional target directory which must already exist.
dir=$PW D
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
echo "lcdd.xsd
lcdd_display.xsd
lcdd_fields.xsd
lcdd_header.xsd
lcdd_iddict.xsd
lcdd_limits.xsd
lcdd_regions.xsd
lcdd_sensitive_detectors.xsd" > lcddSchemaFiles.txt
wget -i lcddSchemaFiles.txt -B 'http://www.lcsim.org/schemas/lcdd/1.0/'
rm lcddSchemaFiles.txt
)
