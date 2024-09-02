# TASK_MANAGER

Create a Property File:
Ensure you have a property file (e.g., config.properties) with the database path defined. For example:
properties
Copy code
db_path=tasks.db

## Clean Build Folder

This step ensures that any previous build artifacts are removed before starting a new build. Running `make clean` will delete the existing build files and directories, which helps prevent conflicts and ensures a clean slate for the new build.

```bash
make clean
```

## Build

After cleaning the build folder, you need to compile and assemble the project. Running `make` will process the source files, compile them, and link them to produce the final executable. This step generates the necessary binaries and places them in the specified build directory.

```bash
make
```

## Run

Once the build process is complete, you can run the task manager application. The executable is located in the `build` directory. Running `./build/task_manager` will start the application and allow you to interact with it.

```bash
./build/task_manager
```

---

*Created by SUDHI S*
