# Battleship: Cartesian Product Version
> The clean version of battleships code, combining
> [the original work](https://github.com/TalitaJames/battleship)
> and [Karl's work](https://github.com/KarlRombauts/battleship-ts)[^1].

Uses [`JsonCPP`](https://github.com/open-source-parsers/jsoncpp)
for parsing `json` data.

## Running instructions
`start.py` will facilitate the building, testing, running and logging.

|Name|Description|data type|
|----|-----------|---------|
|`-t`, `--threads`|Number of threads to make| `int`|
|`-s`, `--size`|Size of the board grid| `int` (1,10]|
|`-f`, `--fleet`|Which ships to include on the board| `string` (csv of ints)|
|`-m`, `--memory`|How many boards maximum should the game remember?| `int`|
|`-c`, `--clean`|flag to clean and restart the build process| `boolean`|
|`--utest`|flag to run the unit tests then exit| `boolean`|

Default values for these are found in [`defaultSettings.json`](defaultSettings.json) and the c++ code stores them in [`lib/constants.h`](lib/constants.h).

Both these files are assumed-unchanged in git, with
`git update-index --assume-unchanged defaultSettings.json lib/constants.h`.
If there are updates to commit, restore git checking with
`--no-assume-unchanged`.


## To Do list
- [ ] MonteCarlo Tree search
- [ ] implement hitmask checking in `cartesianProduct` calculations
    - [ ] also is it checking in `iterateBoardsToGenerateProbabilityGrid`?
- [x] change `runThreads` to have a better name (iterateBoardsToGenerateProbabilityGrid?)
    - [x] make the function a parseable option to play methods(so that a different function could be used instead)

[^1]: Karl's thoughts are involved, though his direct suggestions
and approach (as in the repo linked) are not.