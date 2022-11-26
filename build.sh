base_dir=$(pwd)
build_dir=$base_dir/build

mkdir -p $build_dir

pushd $build_dir
cmake ..
make
if [ "$?" == "0" ]; then
	./car-racing
fi

popd

