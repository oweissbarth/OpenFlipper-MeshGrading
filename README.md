# OpenFlipper-MeshGrading
Mesh pre-processing for Mesh2HRTF (mesh grading). Originally from https://sourceforge.net/p/mesh2hrtf/code/HEAD/tree/

## Building
It should be possible to build this plugin without building OpenFlipper. However the easisest way is to build them together.
```
git clone --recursive https://graphics.rwth-aachen.de:9000/OpenFlipper-Free/OpenFlipper-Free.git
cd OpenFlipper-Free
git clone https://github.com/oweissbarth/OpenFlipper-MeshGrading.git Plugin-MeshGrading
mkdir dir
cd build
cmake ..
make
```
Afterwards the binary can be found build/Build/bin/.
