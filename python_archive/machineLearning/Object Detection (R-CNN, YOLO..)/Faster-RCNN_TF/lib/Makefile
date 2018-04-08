# EXTRA_CXXFLAGS = -Wno-sign-compare -I$(TENSORFLOW)/bazel-tensorflow/external/protobuf/src \
#                  -I$(TENSORFLOW)/bazel-genfiles -I$(TENSORFLOW) \
#                  -I../../tools/tensorflow/bazel-tensorflow/external/nsync/public \
#                  -I$(TENSORFLOW)/tensorflow/contrib/makefile/downloads/eigen \
#                  -I$(TENSORFLOW)/tensorflow/contrib/makefile/downloads/protobuf/src \
#                  -I$(TENSORFLOW)/tensorflow/contrib/makefile/downloads/nsync/public


all:
	python setup.py build_ext --inplace
	rm -rf build
	bash make.sh

