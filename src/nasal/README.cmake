Compile instructions with CMake
===============================

- Create a directory in the root directory or outside it. It is recommended
  that you name it 'build/'

- Switch to that directory.

- Ensure that you have the dependencies you want since Nasal by itself
  doesn't require any other libraries.

- Run 'cmake ..' to create Makefiles. If you want GTK2 support for Nasal, use
  'cmake .. -DENABLE_GTK=TRUE'.

- Once it is done, run 'make' to compile.

- Optionally, run 'make install' to install Nasal globally in your system.

Running the examples/demos
===============================

Most of the examples require use of the "driver.nas" module in the lib sub directory.
This needs to be loaded prior to any other source files. This can be accomplished
by running:
	 ./nasal-bin ../lib/driver.nas foo.nas

Or simply by using the shell "nasal" shell script in the /src directory.
Note: When building outside the source tree, you'll probably want to set up a symlink to
point at nasal-bin in your build tree.

