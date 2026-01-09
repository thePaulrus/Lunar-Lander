default file directory for debugging is the same file with the vxpobg

you want to make a folder in that folder to hold the read and write data. then you have to tell the compiler how to get to the needed files from the default folder


FILE* pFile;
fopen_s( &pFile, "Data/filename.ext", "rb"); 
//rb means binary read mode
//Data/ means go into the folder called Data to find the file

if(pFile){		
	char buffer[512] = {}; //this is just a block of memory to store the contents of the file
	//fread(something to store the contents of the file, how large is each peice of information in bytes, how many peices of info to read, the FILE* we used in fopen)
	size_t numCharsRead = fread(buffer, 1, 512, pFile)
	fclose(pFile);
}




//returns an error or a warning because it "isn't safe"
//this works on every platform though
FILE* pFile fopen("filename.ext", "rb"); 
