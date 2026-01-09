
# One time setup

- Download CMake from https://cmake.org
	- You probably want the 64bit installer for Windows
- Check if you have access to my repo: https://github.com/JimmysClass/24W_GG3
	- If not, message me
- Fork the repo
- In your fork:
	- Under Settings -> Collaborators
		- Remove team access

# Cloning your repo

- Use whatever git client you prefer
	- If you use command line
		- add `--recursive` to your clone command
			- `git clone <url> --recursive`
	- If you use TortoiseGit
		- Check the "recursive" box in the clone window
		- If you clone without recursive
		- Find "Git -> Submodule Update" and run that

# Building the game

- Run `GenerateProjectFiles.bat`
- Go into your build folder for the solution file

# Improve the Code

- If cmake is not part of your default path, add it as the first line in the batch file
	- `set path=%path%;C:\Program Files\CMake\bin`

- In Game/cmakelists.txt, the links to the shader files are incorrect
	- The DataRaw folder isn't in the Game folder,
		- so all references to it need a `../` in front

- In Mesh::Create
	- There are 2 calls to `bgfx::makeRef`
		- These make references to memory addresses so the bgfx library can build the VBOs on another thread later on
		- If you passed in temporary pointers, for example from a vector on the stack, these will be deleted before bgfx can build the VBO
		- So, change these 2 calls to `bgfx::copy`

- Add a new mesh to the game that isn't a static list of verts
	- I recommend a circle
	- Watch out for the winding order of the indices
		- Triangles will only appear if the vertices wind around clock-wise

# Useful VS Plugins

- GLSL Language Integration (for VS2022)
	- Not perfect for BGFX shaders, but still worth having
- Open Command Line
	- Allows you to right click a batch file in your solution and execute it
	- Great for GenerateProjectFiles.bat and CompileShaders.bat
- Open File in Solution
	- Allows you to bind a key to quickly open a file based on substring searches
