## Testing

For exercises that have unit tests, the project must be built with the approprate test cpp file. This can be done by using `cmake_tests` instead of `cmake`. For example, from the build directory:
```
cd build
cmake_tests ..
make
../bin/test
```

Find the tests here ->

`/home/workspace/CppND-Route-Planning-Project/test/utest_rp_a_star_search.cpp`

## Run

Within the virtualized desktop and inside the VSCode terminal

```bash
cd build
cmake ..
make
../bin/CppND-Route-Planning-Project -f ../map.osm
```

Not all exercises have tests. The table is given below with the complete list of exercises with tests for reference:

| Exercise Name               | 
|-----------------------------|
| The RouteModel Class        |
| The Node Class              |
| Create RouteModel Nodes     |
| Write the Distance Function |
| Create Road to Node Hashmap |
| Write FindNeighbors         |
| Find the Closest Node       |
| Write the A* Search Stub    |
| Finish A* Search            |
