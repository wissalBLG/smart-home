# Workspace map — 22 file(s)

A map, not a substitute for reading. Paths are workspace-relative. Use read_file (with
start_line/end_line) or search_files on these paths instead of re-listing directories.

(root)
  .gitignore
  platformio.ini
.vscode/
  extensions.json
board-1-outdoor/
  .gitignore
  platformio.ini
board-1-outdoor/.vscode/
  c_cpp_properties.json
  extensions.json
  launch.json
board-1-outdoor/src/
  main.cpp — entry point
board-1-outdoor/src/domain/
  OutdoorState.h — header
board-1-outdoor/src/hal/
  ExteriorHAL.cpp
  ExteriorHAL.h — header
  GreenhouseHAL.cpp
  GreenhouseHAL.h — header
board-2-indoor/
  platformio.ini
board-2-indoor/src/
  main.cpp — entry point
board-2-indoor/src/domain/
  IndoorState.h — header
board-2-indoor/src/hal/
  InteriorHAL.cpp
  InteriorHAL.h — header
include/
  README
lib/
  README
test/
  README
