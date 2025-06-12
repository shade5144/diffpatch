### Description

Generate a `diff` of 2 files and apply it as a patch to one of the files to get the other. Note that in-place patching and taking diffs of directories is not supported.

### Implementation Notes

- Uses Meyer's algorithm for finding the diff.

- While most of the C code in the repository reflects the ruby counter-part shown in the referenced blog, I had to take a different approach for backtracking.

- The author stores the array at each stage of the algorithm in the blog, but I realized that for each `d` there are `d + 1` changes. That is, for `d = 0`, there is 1 change, `d = 1` , there are 2 changes forming the natural numbers series `1,2,3,4...d`.

- This means that if we store just the changes at each stage we can use `d * (d + 1) / 2` to get the starting index of changes made at step `d`. Since there are `d + 1` changes at each stage and the iteration ranges from `-d` to `+d` in steps of 2, we can easily modify the source array, and thus backtrack.

- The format of the patch file is simple:
    - `IN` Marks insertion at line `N`.
    - `>TEXT` Text to be inserted that follows an `I` command.
    - `D,start,end` Delete from `start` to `end`(inclusive).

### Dependencies
- gcc
- shell

### Installation

Just do `./build.sh` and the files will be installed into the `build` directory.

### Usage

- diff

```shell
./build/mydiff <source> <file to compare to> <name of patch file>
```

- patch

```shell
./build/mypatch <source> <patch file> <output file>
```

### References
- Reference implementation of the algorithm in Ruby: https://blog.jcoglan.com/2017/02/12/the-myers-diff-algorithm-part-1/