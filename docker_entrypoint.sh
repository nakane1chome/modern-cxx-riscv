#!/bin/bash
# USAGE: ./docker_entrypoint.sh <path to git volume> <path to project source with CMakelist.txt>

time=$(date)
echo "::set-output name=start_time::$time"


if [ -d $1 ] ; then
    echo "Changing to working directory: $1"
    cd $1
else
    echo "Not changing directory: $1"
fi

# Remove $1 from args.
shift 

# Default path
if [ "$#" == "0" ]; then
	echo "$USAGE"
	exit 1
fi

BUILD_BASE=build
CMAKE_DIR=cmake

rc=0

while (( "$#" )) ; do

    PROJECT_SRC=$1
    BUILD_DIR=${BUILD_BASE}/$(basename ${PROJECT_SRC/\/src})
    
    rm -rf  ${BUILD_DIR}
    mkdir -p ${BUILD_DIR}

    cmake \
	-DCMAKE_MAKE_PROGRAM=make \
	-DCMAKE_TOOLCHAIN_FILE=../../${CMAKE_DIR}/riscv.cmake \
	-G "Unix Makefiles" \
	-B ${BUILD_DIR} \
	-S ${PROJECT_SRC} \

    cmake --build ${BUILD_DIR}
    
    if [ "$?" != "0" ] ; then
	echo "CMAKE: ${PROJECT_SRC}; Build failed: $?"
	rc = $[$rc + 1]
    else
	echo "CMAKE: ${PROJECT_SRC}; Build success"
    fi

    shift

done
    
time=$(date)
echo "::set-output name=end_time::$time"

exit $rc
