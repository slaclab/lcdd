#!/bin/sh

if [ -z "${LCDD_BASE}" ]; then
  echo "ERROR: Set LCDD_BASE."
else

  if [ -e ${LCDD_BASE}/VERSION ]; then
    appname=`cat ${LCDD_BASE}/VERSION | awk '{print $1}'`
    ver=`cat ${LCDD_BASE}/VERSION | awk '{print $2}'`

    echo "appname=$appname"
    echo "ver=$ver"

    ver_okay=`echo $ver | egrep "^v[0-9]*r[0-9]*p[0-9_]*$"`

    if [ -n "${ver_okay}" ]; then
      cmd="cvs rtag $ver_okay lcdd"
      echo "exec: $cmd"
      echo "Press ENTER to rtag..."
      read
      $cmd
    else
       echo "$ver does not match v#r#p# format."
    fi

  else
    echo "ERROR: Could not find VERSION."
  fi

fi
